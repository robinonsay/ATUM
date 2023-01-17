import dearpygui.dearpygui as dpg
from pathlib import Path


ROBOTO = Path(__file__).parent.parent / Path('assets/Roboto')
font_light = None
font_medium = None
font_bold = None

def init_fonts():
    global font_light, font_medium, font_bold
    with dpg.font_registry():
        font_light = dpg.add_font(str(ROBOTO / 'Roboto-Light.ttf'), 18)
        font_medium = dpg.add_font(str(ROBOTO / 'Roboto-Medium.ttf'), 18)
        font_bold = dpg.add_font(str(ROBOTO / 'Roboto-Bold.ttf'), 18)

