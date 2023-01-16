import serial
import struct
import binascii
from serial import Serial

class Msg:
    
    DATA_TYPES_MAP = [('f', 4),
                      ('d', 8),
                      ('h', 2),
                      ('H', 2),
                      ('l', 4),
                      ('L', 4),
                      ('q', 8),
                      ('Q', 8),
                      ('s', -1)]

    def __init__(self, mid:int, msize:int, mtype:int, mdata:bytes=b'') -> None:
        self.mid = mid
        self.msize = msize
        self.mtype = mtype
        self.mdata = mdata
    
    @property
    def bytes(self):
        b = struct.pack('<LLH', self.mid, self.msize, self.mtype)
        b += self.mdata
        b += struct.pack('>H', binascii.crc_hqx(b, 0))
        return b
    
    def to_telem(self):
        if self.mtype == 0:
            return Telem(self.mid, self.msize, self.mdata)
        return None


class Telem(Msg):
    
    def __init__(self, mid: int, msize: int, mdata: bytes) -> None:
        super().__init__(mid, msize, 0, mdata)
        self.telem_type = struct.unpack('<H', mdata[:2])[0]
        data_end = 2 + self.DATA_TYPES_MAP[self.telem_type][1]
        self.telem_data = struct.unpack(f'<{self.DATA_TYPES_MAP[self.telem_type][0]}',
                                  mdata[2:data_end])[0]


class Cmd(Msg):

    def __init__(self, mid: int, cmd_id: int, cmd_type: int, cmd_data) -> None:
        data = struct.pack('<BH', cmd_id, cmd_type)
        if cmd_type == 8:
            data += cmd_data
        elif cmd_data != 9:
            data += struct.pack(f'<{self.DATA_TYPES_MAP[cmd_type][0]}', cmd_data)
        else:
            pass
        super().__init__(mid, len(data), 2, data)



class AtumIO(Serial):

    HDR_SIZE = 10
    MSG_SIZE = 130

    def __init__(self, port:str, baudrate:int,
                 bytesize: int = serial.EIGHTBITS,
                 parity: str = serial.PARITY_EVEN,
                 stopbits: float = serial.STOPBITS_ONE,
                 timeout: float | None = None,
                 xonxoff: bool = False,
                 rtscts: bool = False,
                 write_timeout: float | None = None,
                 dsrdtr: bool = False,
                 inter_byte_timeout: float | None = None,
                 exclusive: float | None = None) -> None:
        super().__init__(port, baudrate, bytesize, parity, stopbits, timeout, xonxoff, rtscts, write_timeout, dsrdtr, inter_byte_timeout, exclusive)
    
    def read_msg(self) -> Msg:
        hdr = super().read(self.HDR_SIZE)
        msg = None
        if hdr and len(hdr) == self.HDR_SIZE:
            mid, msize, mtype = struct.unpack('<LLH', hdr)
            data = super().read(self.MSG_SIZE)
            if data and len(data) == self.MSG_SIZE:
                crc16 = struct.unpack('>H', data[-2:])[0]
                if binascii.crc_hqx(hdr + data, 0) == 0:
                    msg = Msg(mid, msize, mtype, data)
        return msg
    
    def write_msg(self, msg: Msg):
        super().write(msg.bytes)
