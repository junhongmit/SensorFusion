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

class Arduino_IKS01A1(object):

    def __init__(self, if_id):
        if not if_id in [ARDUINO]:
            raise ValueError("No such IOP for Arduino device.")

        self.iop = request_iop(if_id, ARDUINO_IKS01A1_PROGRAM)
        self.mmio = self.iop.mmio
        self.log_interval_ms = 1000
        self.iop.start()
    def read_LSM6DS0_gyroRawData_XYZ(self, XYZ):
        """Read the analog raw value from the analog peripheral.

        Parameters
        ----------
        None

        Returns
        -------
        list
            The raw values from the analog device.

        """
        if XYZ == 'X':
            self.mmio.write(iop_const.MAILBOX_OFFSET + \
                        iop_const.MAILBOX_PY2IOP_CMD_OFFSET, 3)
            while not (self.mmio.read(iop_const.MAILBOX_OFFSET + \
                                          iop_const.MAILBOX_PY2IOP_CMD_OFFSET) == 0):
                pass
            value = self.mmio.read(iop_const.MAILBOX_OFFSET)
            return self._reg2float(value)
        elif XYZ == 'Y':
            self.mmio.write(iop_const.MAILBOX_OFFSET + \
                        iop_const.MAILBOX_PY2IOP_CMD_OFFSET, 5)
            while not (self.mmio.read(iop_const.MAILBOX_OFFSET + \
                                          iop_const.MAILBOX_PY2IOP_CMD_OFFSET) == 0):
                pass
            value = self.mmio.read(iop_const.MAILBOX_OFFSET)
            return self._reg2float(value)
        else:
            self.mmio.write(iop_const.MAILBOX_OFFSET + \
                        iop_const.MAILBOX_PY2IOP_CMD_OFFSET, 7)
            while not (self.mmio.read(iop_const.MAILBOX_OFFSET + \
                                          iop_const.MAILBOX_PY2IOP_CMD_OFFSET) == 0):
                pass
            value = self.mmio.read(iop_const.MAILBOX_OFFSET)
            return self._reg2float(value)
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

