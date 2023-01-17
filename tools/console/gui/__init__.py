import dearpygui.dearpygui as dpg


class Log:

    def __init__(self, parent: int | str, pos: tuple, log_max=256) -> None:
        self.parent = parent
        with dpg.child_window(pos=pos, parent=parent) as log_window:
            self.log_window = log_window
        self.log_max = log_max
        self.log = list()

    def print(self, msg: str):
        scroll_height = dpg.get_item_height(self.log_window)
        _, font_height = dpg.get_text_size('HELLO')
        font_height += 10
        self.log.append(dpg.add_text(msg, parent=self.log_window))
        if len(self.log) > self.log_max:
            dpg.delete_item(self.log.pop(0))
        if len(self.log) > scroll_height / font_height:
            dpg.set_y_scroll(self.log_window, dpg.get_y_scroll(self.log_window) + font_height)
