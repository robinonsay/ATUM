import serial
import struct
import curses
import argparse
from curses import wrapper
import time

dev = '/dev/ttyACM0'

def main(stdscr, device, baud_rate):
    curses.noecho()
    curses.cbreak()
    stdscr.keypad(True)
    with serial.Serial(device, baud_rate, parity=serial.PARITY_EVEN) as ser:
        stdscr.clear()
        stdscr.addstr((curses.LINES - 1) // 2 -1, 0, "Raw Output:",
                    curses.A_BOLD)
        while True:
            byte_range  = ser.readline()
            stdscr.addstr((curses.LINES - 1) // 2, 0, f"{byte_range.decode('UTF-8')}")
            stdscr.refresh()



if __name__ == '__main__':
    parser = argparse.ArgumentParser(description="Debug Console For Atum Flight Computer")
    parser.add_argument('-d', '--device',
                        default='/dev/ttyACM0',
                        help='The Flight Computer Serial Port')
    parser.add_argument('-b', '--baud_rate',
                        default=57600,
                        help='The Flight Computer Serial Port Baud Rate')
    args = parser.parse_args()
    wrapper(main, args.device, args.baud_rate)

