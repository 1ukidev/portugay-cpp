CC := g++
CFLAGS := -O2 -march=native -pipe -std=gnu++17 -Wall

TARGET := portugay
INSTALL_DIR := /usr/local/bin

.PHONY: all clean install uninstall

all: $(TARGET)

$(TARGET): portugay.cpp
	$(CC) $(CFLAGS) $^ -o $@

install: $(TARGET)
	cp $(TARGET) $(INSTALL_DIR)

uninstall:
	rm $(INSTALL_DIR)/$(TARGET)

clean:
	rm $(TARGET)
