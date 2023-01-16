import serial
import curses
import argparse
from curses import wrapper
from debug_console import Telemetry, Log, Msg, Cmd

dev = '/dev/ttyACM0'

MAIN_SCH_ID = 0x96653400
CMD_READY = (MAIN_SCH_ID, 0xFF, b'', 9)

def main(stdscr, device, baud_rate):
    curses.noecho()
    curses.cbreak()
    curses.curs_set(0)
    stdscr.keypad(True)
    log_pad = curses.newpad(curses.LINES // 2, curses.COLS // 2)
    log_pad.scrollok(True)
    bytes_pad = curses.newpad(curses.LINES // 2, curses.COLS // 2)
    bytes_pad.idlok(True)
    with serial.Serial(device, baud_rate, parity=serial.PARITY_EVEN, timeout=0.5) as ser:
        stdscr.clear()
        stdscr.addstr(curses.LINES // 2 - 1, 0, "LOG:", curses.A_BOLD)
        while True:
            msg = Msg(ser)
            if msg.empty:
                pass
            elif msg.type == 0 and msg.valid:
                telem = Telemetry(msg.data)
                if (msg.id & 0xFFFF0000) == 0:
                    stdscr.addstr(0, 0, "ATUM LED:")
                    stdscr.addstr(1, 0, f"COUNT: {telem.data}")
            elif msg.type == 1 and msg.valid:
                log = Log(msg.data)
                pos = log_pad.getyx()
                log_pad.addstr(pos[0], pos[1]+1, f"{msg.id}: {log.string}")
            bytes_pad.border()
            log_pad.border()
            bytes_pad.refresh(0, 0, curses.LINES // 2, curses.COLS // 2, curses.LINES - 1, curses.COLS - 1)
            log_pad.refresh(0, 0, curses.LINES // 2, 0, curses.LINES - 1, curses.COLS // 2 - 1)
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

