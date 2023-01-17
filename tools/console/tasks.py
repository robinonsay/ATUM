from multiprocessing import Queue
from console.io import AtumIO, Msg, Telem, Cmd


def get_msgs(msg_queue: Queue, device, baud_rate):
    with AtumIO(device, baud_rate, timeout=1) as atum:
        while True:
            msg = atum.read_msg()
            if msg:
                msg_queue.put(msg)
