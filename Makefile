MCU = atmega4809
F_CPU = 20000000UL

ARDUINO_DIR = $(HOME)/Library/Arduino15/packages/arduino
GCC_VER = 7.3.0-atmel3.6.1-arduino7
TOOLCHAIN = $(ARDUINO_DIR)/tools/avr-gcc/$(GCC_VER)/bin

CC = $(TOOLCHAIN)/avr-gcc
OBJCOPY = $(TOOLCHAIN)/avr-objcopy
ARDUINO_CLI = arduino-cli
FQBN = arduino:megaavr:nona4809

SRC_DIR = src
BUILD_DIR = build
SRC = $(wildcard $(SRC_DIR)/*.c)
INCLUDES = -I$(SRC_DIR)

CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall -std=c11 $(INCLUDES)
LDFLAGS = -mmcu=$(MCU)

TARGET = $(BUILD_DIR)/edl-final

all: $(TARGET).hex

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TARGET).elf: $(SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

clean:
	rm -rf $(BUILD_DIR)
