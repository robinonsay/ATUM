import serial
import curses
import argparse
from curses import wrapper
from console.io import AtumIO, Msg, Telem

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
    with AtumIO(device, baud_rate, parity=serial.PARITY_EVEN, timeout=0.5) as atum:
        stdscr.clear()
        stdscr.addstr(curses.LINES // 2 - 1, 0, "LOG:", curses.A_BOLD)
        while True:
            msg = atum.read_msg()
            if msg:
                telem = msg.to_telem()
                if telem:
                    if (telem.mid & 0xFFFF0000) == 0:
                        stdscr.addstr(0, 0, "ATUM LED:")
                        stdscr.addstr(1, 0, f"COUNT: {telem.telem_data}")
                else:
                    pos = log_pad.getyx()
                    log = msg.mdata[:-2].decode('UTF-8').replace('\0', '')
                    log_pad.addstr(pos[0], pos[1]+1, f"{msg.mid}: {log}")
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
                        default=9600,
                        help='The Flight Computer Serial Port Baud Rate')
    args = parser.parse_args()
    wrapper(main, args.device, args.baud_rate)

