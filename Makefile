# Target MCU and clock
MCU        := atmega4809
F_CPU      := 20000000UL
UPLOAD_NAME := baremetal-avr

# Arduino toolchain paths
ARDUINO_DIR := $(HOME)/Library/Arduino15/packages/arduino
GCC_VER     := 7.3.0-atmel3.6.1-arduino7
TOOLCHAIN   := $(ARDUINO_DIR)/tools/avr-gcc/$(GCC_VER)/bin

CC        := $(TOOLCHAIN)/avr-gcc
OBJCOPY   := $(TOOLCHAIN)/avr-objcopy
SIZE      := $(TOOLCHAIN)/avr-size

# Arduino CLI & board config
ARDUINO_CLI := arduino-cli
FQBN        := arduino:megaavr:nona4809
PORT        := $(shell ls /dev/cu.usbmodem* 2>/dev/null | head -n 1)

# Project structure
SRC_DIR   := src
BUILD_DIR := build
SRC       := $(wildcard $(SRC_DIR)/*.c)
OBJS      := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC))
INCLUDES  := -I$(SRC_DIR)

# Compiler flags
CFLAGS := -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall -Werror -MMD -MP -std=c11 $(INCLUDES)
LDFLAGS := -mmcu=$(MCU)

TARGET_ELF := $(BUILD_DIR)/$(UPLOAD_NAME).elf
TARGET_HEX := $(BUILD_DIR)/$(UPLOAD_NAME).hex

.PHONY: all size upload clean

all: $(TARGET_HEX)

# Print code size
size: $(TARGET_ELF)
	@$(SIZE) --format=avr --mcu=$(MCU) $<

# Ensure build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Compile each C file
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Link objects into ELF
$(TARGET_ELF): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

# Convert ELF to Intel HEX
$(TARGET_HEX): $(TARGET_ELF)
	$(OBJCOPY) -O ihex -R .eeprom $< $@

upload: $(TARGET_HEX)
	@test -n "$(PORT)" || (echo "No USB serial port found!" && exit 1)
	$(ARDUINO_CLI) upload \
		--fqbn $(FQBN) \
		--port $(PORT) \
		--input-file $(TARGET_HEX)

# Clean out build artifacts
clean:
	rm -rf $(BUILD_DIR)

-include $(OBJS:.o=.d)
