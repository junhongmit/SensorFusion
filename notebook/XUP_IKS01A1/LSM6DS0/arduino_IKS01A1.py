__author__ = "Lite Xia"
__copyright__ = "Copyright 2016, Xilinx"
__email__ = "mengxian@xilinx.com"

import time
import struct
from pynq import MMIO
from pynq.iop import request_iop
from pynq.iop import iop_const
from pynq.iop import ARDUINO

ARDUINO_IKS01A1_PROGRAM = "arduino_IKS01A1.bin"
ARDUINO_IKS01A1_LOG_START = iop_const.MAILBOX_OFFSET + 16
ARDUINO_IKS01A1_LOG_END =  ARDUINO_IKS01A1_LOG_START + (1000 * 4)
class Arduino_IKS01A1(object):

    def __init__(self, if_id):
        if not if_id in [ARDUINO]:
            raise ValueError("No such IOP for Arduino device.")

        self.iop = request_iop(if_id, ARDUINO_IKS01A1_PROGRAM)
        self.mmio = self.iop.mmio
        self.log_interval_ms = 1000
        self.iop.start()
    def read_LSM6DS0_gyroRawData_XYZ(self):
        """Read the analog raw value from the analog peripheral.

        Parameters
        ----------
        None

        Returns
        -------
        list
            The raw values from the analog device.

        """
        gyroRawData = [0, 0, 0]
        self.mmio.write(iop_const.MAILBOX_OFFSET + iop_const.MAILBOX_PY2IOP_CMD_OFFSET, 3)
        while not (self.mmio.read(iop_const.MAILBOX_OFFSET + iop_const.MAILBOX_PY2IOP_CMD_OFFSET) == 0):
            pass
        gyroRawData[0] = self._reg2float(self.mmio.read(iop_const.MAILBOX_OFFSET + 0))
        gyroRawData[1] = self._reg2float(self.mmio.read(iop_const.MAILBOX_OFFSET + 4))
        gyroRawData[2] = self._reg2float(self.mmio.read(iop_const.MAILBOX_OFFSET + 8))
        return gyroRawData

    def read_LSM6DS0_accelRawData_XYZ(self):
        """Read the analog raw value from the analog peripheral.

        Parameters
        ----------
        None

        Returns
        -------
        list
            The raw values from the analog device.

        """
        aceelRawData = [0, 0, 0]
        self.mmio.write(iop_const.MAILBOX_OFFSET + iop_const.MAILBOX_PY2IOP_CMD_OFFSET, 5)
        while not (self.mmio.read(iop_const.MAILBOX_OFFSET + iop_const.MAILBOX_PY2IOP_CMD_OFFSET) == 0):
            pass
        aceelRawData[0] = self._reg2float(self.mmio.read(iop_const.MAILBOX_OFFSET + 12))
        aceelRawData[1] = self._reg2float(self.mmio.read(iop_const.MAILBOX_OFFSET + 16))
        aceelRawData[2] = self._reg2float(self.mmio.read(iop_const.MAILBOX_OFFSET + 20))
        return aceelRawData
    def set_log_interval_ms(self, log_interval_ms):
        """Set the sampling interval for the Pmod TMP2.

        Parameters
        ----------
        log_interval_ms : int
            Time in milliseconds between sampled reads of the TMP2 sensor

        Returns
        -------
        None

        """
        if (log_interval_ms < 0):
            raise ValueError("Log length should not be less than 0.")
        self.log_interval_ms = log_interval_ms
        self.mmio.write(iop_const.MAILBOX_OFFSET + 4, self.log_interval_ms)

    def start_log_gyro(self):
        """Start recording multiple values in a log.

        This method will first call set_log_interval_ms() before writting to
        the MMIO.

        Parameters
        ----------
        None

        Returns
        -------
        None

        """
        self.set_log_interval_ms(self.log_interval_ms)
        self.mmio.write(iop_const.MAILBOX_OFFSET + \
                        iop_const.MAILBOX_PY2IOP_CMD_OFFSET, 7)
    def start_log_accel(self):
        """Start recording multiple values in a log.

        This method will first call set_log_interval_ms() before writting to
        the MMIO.

        Parameters
        ----------
        None

        Returns
        -------
        None

        """
        self.set_log_interval_ms(self.log_interval_ms)
        self.mmio.write(iop_const.MAILBOX_OFFSET + \
                        iop_const.MAILBOX_PY2IOP_CMD_OFFSET, 9)

    def stop_log(self):
        """Stop recording multiple values in a log.

        Simply write to the MMIO to stop the log.

        Parameters
        ----------
        None

        Returns
        -------
        None

        """
        self.mmio.write(iop_const.MAILBOX_OFFSET + \
                        iop_const.MAILBOX_PY2IOP_CMD_OFFSET, 1)

    def get_log(self):
        """Return list of logged samples.

        Parameters
        ----------
        None

        Returns
        -------
        List of valid samples from the temperature sensor in Celsius.

        """
        # First stop logging
        self.stop_log()

        # Prep iterators and results list
        head_ptr = self.mmio.read(iop_const.MAILBOX_OFFSET + 0x8)
        tail_ptr = self.mmio.read(iop_const.MAILBOX_OFFSET + 0xC)
        temps = list()

        # Sweep circular buffer for samples
        if head_ptr == tail_ptr:
            return None
        elif head_ptr < tail_ptr:
            for i in range(head_ptr, tail_ptr, 4):
                temps.append(self._reg2float(self.mmio.read(i)))
        else:
            for i in range(head_ptr, ARDUINO_IKS01A1_LOG_END, 4):
                temps.append(self._reg2float(self.mmio.read(i)))
            for i in range(ARDUINO_IKS01A1_LOG_START , tail_ptr, 4):
                temps.append(self._reg2float(self.mmio.read(i)))
        return temps

    def _reg2float(self, reg):
        """Translate the register value to a floating-point number.

        Note
        ----
        The float precision is specified to be 1 digit after the decimal
        point.

        Bit [31]    (1 bit)        ->    Sign (S)
        Bit [30:23] (8 bits)       ->    Exponent (E)
        Bit [22:0]  (23 bits)      ->    Mantissa (M)

        Parameters
        ----------
        reg : int
            A 4-byte integer.

        Returns
        -------
        float
            The floating-point number translated from the input.

        """
        if reg == 0:
            return 0.0
        sign = (reg & 0x80000000) >> 31 & 0x01
        exp = ((reg & 0x7f800000) >> 23) - 127
        if (exp == 0):
            man = (reg & 0x007fffff) / pow(2, 23)
        else:
            man = 1 + (reg & 0x007fffff) / pow(2, 23)
        result = pow(2, exp) * (man) * ((sign * -2) + 1)
        return float("{0:.1f}".format(result))

