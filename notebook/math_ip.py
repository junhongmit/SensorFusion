
import time
from pynq import MMIO
from pynq.iop import request_iop
from pynq.iop import iop_const
from pynq.iop import PMODA

MATH_IP_PROGRAM = "math_ip.bin"

class Math_IP(object):
    def __init__(self):
        self.iop = request_iop(1, MATH_IP_PROGRAM)
        self.mmio = self.iop.mmio
        self.iop.start()
		
    def add(self, op1, op2):
        self.mmio.write(iop_const.MAILBOX_OFFSET + 0, op1) # 0 ---> MAILBOX_DATA(0)
        self.mmio.write(iop_const.MAILBOX_OFFSET + 4, op2) # 4 ---> MAILBOX_DATA(1)
        self.mmio.write(iop_const.MAILBOX_OFFSET + iop_const.MAILBOX_PY2IOP_CMD_OFFSET, 3)
        while not(self.mmio.read(iop_const.MAILBOX_OFFSET + iop_const.MAILBOX_PY2IOP_CMD_OFFSET) == 0):
            pass
        return self.mmio.read(iop_const.MAILBOX_OFFSET + 0x8) # 8 ---> MAILBOX_DATA(2)
		
    def clear(self):
        self.mmio.write(iop_const.MAILBOX_OFFSET + iop_const.MAILBOX_PY2IOP_CMD_OFFSET, 5)
        self.mmio.write(iop_const.MAILBOX_OFFSET + 0, 0)
        self.mmio.write(iop_const.MAILBOX_OFFSET + 4, 0)
        while not(self.mmio.read(iop_const.MAILBOX_OFFSET + iop_const.MAILBOX_PY2IOP_CMD_OFFSET) == 0):
            pass
