MCU = atmega4809
F_CPU = 20000000UL
UPLOAD_NAME = baremetal-avr

# Arduino toolchain paths
ARDUINO_DIR = $(HOME)/Library/Arduino15/packages/arduino
GCC_VER = 7.3.0-atmel3.6.1-arduino7
TOOLCHAIN = $(ARDUINO_DIR)/tools/avr-gcc/$(GCC_VER)/bin

CC = $(TOOLCHAIN)/avr-gcc
OBJCOPY = $(TOOLCHAIN)/avr-objcopy

# Arduino CLI & board config
ARDUINO_CLI = arduino-cli
FQBN = arduino:megaavr:nona4809
PORT = $(shell ls /dev/cu.usbmodem* 2>/dev/null | head -n 1)

# Project structure
SRC_DIR = src
BUILD_DIR = build
SRC = $(wildcard $(SRC_DIR)/*.c)
INCLUDES = -I$(SRC_DIR)

CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall -std=c11 $(INCLUDES)
LDFLAGS = -mmcu=$(MCU)

TARGET_ELF = $(BUILD_DIR)/$(UPLOAD_NAME).elf
TARGET_HEX = $(BUILD_DIR)/$(UPLOAD_NAME).ino.hex

# Default target
all: $(TARGET_HEX)

# Build rules
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TARGET_ELF): $(SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

$(TARGET_HEX): $(TARGET_ELF)
	$(OBJCOPY) -O ihex -R .eeprom $< $@

upload: all
	$(ARDUINO_CLI) upload \
		--fqbn $(FQBN) \
		--input-dir $(BUILD_DIR) \
		--port $(PORT)

clean:
	rm -rf $(BUILD_DIR)
