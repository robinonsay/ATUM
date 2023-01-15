import serial
import struct
import curses
from curses import wrapper
import time


def main(stdscr):
    curses.noecho()
    curses.cbreak()
    stdscr.keypad(True)
    with serial.Serial('/dev/ttyACM0', 57600, parity=serial.PARITY_EVEN) as ser:
        stdscr.clear()
        stdscr.addstr(0, 0, "MET:",
                    curses.A_BOLD)
        first = True
        while True:
            last = time.time_ns()
            byte_range  = ser.readline()[:-1]
            now = time.time_ns()
            if len(byte_range) == 4:
                met = struct.unpack('<L', byte_range)[0]
                stdscr.addstr(0, 5, f"{met}")
                stdscr.addstr(1, 5, f"{(now-last) / 1E9}")
            stdscr.refresh()


wrapper(main)
