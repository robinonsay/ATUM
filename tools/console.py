import serial
import struct

if __name__ == '__main__':
     with serial.Serial('/dev/ttyACM0', 9600, parity=serial.PARITY_EVEN) as ser:
        while True:
            byte_range  = ser.readline()[:-1]
            if len(byte_range) == 8:
                met = struct.unpack('<Q', byte_range)[0]
                print(met/1E6)
