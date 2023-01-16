import argparse

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description="Console For Atum Flight Computer")
    parser.add_argument('-d', '--device',
                        default='/dev/tty.usbmodem14201',
                        help='The Flight Computer Serial Port')
    parser.add_argument('-b', '--baud_rate',
                        default=9600,
                        help='The Flight Computer Serial Port Baud Rate')
    args = parser.parse_args()
    
