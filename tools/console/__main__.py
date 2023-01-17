import argparse
import dearpygui.dearpygui as dpg
from console import tasks
from console.gui import font, telem
from multiprocessing import Process, Queue

WIDTH = 1024
HEIGHT = WIDTH * 9 // 16

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description="Console For Atum Flight Computer")
    parser.add_argument('-d', '--device',
                        default='/dev/tty.usbmodem14201',
                        help='The Flight Computer Serial Port')
    parser.add_argument('-b', '--baud_rate',
                        default=9600,
                        help='The Flight Computer Serial Port Baud Rate')
    args = parser.parse_args()
    msg_queue = Queue()
    msg_process = Process(target=tasks.get_msgs, args=(msg_queue, args.device, args.baud_rate))
    dpg.create_context()
    dpg.create_viewport(title="Atum Ground Console",x_pos=0, y_pos=0, width=WIDTH, height=HEIGHT)
    font.init_fonts()
    dpg.bind_font(font.font_light)
    telem_window = telem.TelemWindow(msg_queue=msg_queue)
    with dpg.window(label='Command',
                    pos=(dpg.get_viewport_width() // 2, 0),
                    width=dpg.get_viewport_width() // 2,
                    height= dpg.get_viewport_height()) as cmd_window:
        dpg.add_text("Hello Cmd")
    dpg.setup_dearpygui()
    dpg.show_viewport()
    dpg.show_font_manager()
    msg_process.start()
    while dpg.is_dearpygui_running():
        telem_window.update()
        dpg.render_dearpygui_frame()
    msg_process.kill()
    dpg.destroy_context()

