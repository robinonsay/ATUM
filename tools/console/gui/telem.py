import dearpygui.dearpygui as dpg
from console import gui
from console.io import Msg, Telem
from console.gui import font
from typing import List
from multiprocessing import Queue
import queue


class TelemWindow:

    def __init__(self, msg_queue: Queue) -> None:       
        self.width = dpg.get_viewport_width() // 2
        self.height = dpg.get_viewport_height()
        self.msg_queue = msg_queue
        with dpg.window(label='Telemetry',
                        width=self.width,
                        height=self.height) as telem_window:
            self.window = telem_window
            dpg.add_text('ATUM_LED: ', tag=f'LED_TEST{0}')
            log_label = dpg.add_text("LOG:", pos=(5, self.height // 2 - 20))
            dpg.bind_item_font(log_label, font.font_bold)
            self.log_window = gui.Log(telem_window, pos=(5, self.height // 2))
    

    def update(self):
        try:
            msg = self.msg_queue.get_nowait()
        except queue.Empty:
            msg = None
        if msg:
            telem = msg.to_telem()
            if telem:
                # print(f'{telem.mid}: {telem.telem_data}')
                dpg.configure_item(f'LED_TEST{telem.mid}', default_value=f'ATUM_LED: {telem.telem_data}')
            elif msg.mtype == 1:
                log = msg.mdata[:-2].decode('UTF-8').replace('\0', '')
                self.log_window.print(log)
