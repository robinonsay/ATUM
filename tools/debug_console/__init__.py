import struct
import serial
import binascii
types_map = [('f', 4),
         ('d', 8),
         ('h', 2),
         ('H', 2),
         ('l', 4),
         ('L', 4),
         ('q', 8),
         ('Q', 8),
         ('s', -1)]

class Msg:
    def __init__(self, ser:serial.Serial) -> None:
        hdr = ser.read(10)
        self.empty = False
        if hdr and len(hdr) == 10:
            self.id, self.size, self.type = struct.unpack('<LLH', hdr)
            msg_size = 256 + 2
            data = ser.read(msg_size)
            if data and len(data) == msg_size:
                self.crc16 = struct.unpack('<H', data[-2:])[0]
                self.valid = binascii.crc_hqx(hdr + data[:-2], 0) == self.crc16
                self.raw_data = data
                self.data = data[:self.size]
            else:
                self.empty = True
        else:
            self.empty = True
        

class Log:
    def __init__(self, bytes: bytes) -> None:
        self.string = bytes.decode('UTF-8').replace('\0', '')

class Telemetry:

    def __init__(self, bytes: bytes) -> None:
        data_start = 2
        self.type = struct.unpack('<H', bytes[:data_start])[0]
        data_end = data_start + types_map[self.type][1]
        self.data = struct.unpack(f'<{types_map[self.type][0]}',
                                  bytes[data_start:data_end])[0]
