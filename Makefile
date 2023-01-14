CC:= avr-gcc
DEV ?= /dev/ttyACM0
SRC_DIR:= $(abspath ./fsw/src)
OUT_DIR:= $(abspath ./)/out
TARGET:= $(OUT_DIR)/atum
HEX:= $(patsubst %,%.hex,$(TARGET))
DEFS:=
INCS:= -I$(abspath ./maat)
SRCS:= $(SRC_DIR)/atum.c
LIBS:=

MCU:= atmega328p

.PHONY: all hex clean install

all: hex $(TARGET)

hex: $(TARGET)
	avr-objcopy -O ihex $(TARGET) $(HEX)

$(TARGET): $(OUT_DIR)
	$(CC) -mmcu=$(MCU) $(DEFS) $(INCS) -o $@ $(SRCS) $(LIBS)

$(OUT_DIR):
	mkdir $@

clean:
	rm -r $(OUT_DIR)

install: hex
	avrdude -c arduino -p m328p -P $(DEV) -U flash:w:$(HEX)
