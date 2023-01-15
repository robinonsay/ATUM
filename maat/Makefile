CC:= avr-gcc
AR:= avr-ar
COMPILE_OPTIONS?= -Wall -Werror -pedantic
SRC_DIR:= $(abspath .)
OUT_DIR?= $(abspath $(SRC_DIR)/..)
LIB_DIR:= $(OUT_DIR)/lib
INC_OUT:= $(OUT_DIR)/include
TARGET:= $(LIB_DIR)/libMaat.a
DEFS:=
INCS:=
SRCS:= $(wildcard $(SRC_DIR)/*.c)
OBJS:= $(addprefix $(LIB_DIR)/,$(notdir $(patsubst %.c,%.o,$(SRCS))))
LIBS:=

MCU ?= atmega328p

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(AR) cr $@ $?
	cp *.h $(INC_OUT)

$(OBJS): $(LIB_DIR)/%.o: $(SRC_DIR)/%.c $(OUT_DIR) $(LIB_DIR) $(INC_OUT)
	$(CC) -c -mmcu=$(MCU) $(COMPILE_OPTIONS) $(DEFS) $(INCS) -o $@ $< $(LIBS)

$(OUT_DIR) $(INC_OUT) $(LIB_DIR):
	mkdir -p $@

clean:
	rm -rf $(OUT_DIR)
