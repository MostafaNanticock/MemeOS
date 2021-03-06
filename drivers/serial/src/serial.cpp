#include <drivers/serial/serial.h>
#include <libs/kernel/io.h>
#include <libs/std/string.h>

Serial::Serial(uint16_t baud, uint16_t addr) {
    this->baudrate = baud;
    this->address = addr;
    uint8_t lcr = inb(addr + 0x03);
    lcr |= 0x80;
    outb(addr + 0x03, lcr);
    uint16_t divisor = 115200 / baud;
    outb(addr, divisor & 0x00FF);
    outb(addr + 0x01, (divisor >> 8) & 0x00FF);
    lcr = inb(addr + 0x03);
    lcr &= 0x7F;
    outb(addr + 0x03, lcr);
    outStream = stream<char, Serial>(_streamHandler, this);
}

void Serial::print(char* str) {
    for (uint32_t i = 0; i < strlen(str); i++) {
        outb(this->address, str[i]);
    }
}

void Serial::println(char* str) {
    for (uint32_t i = 0; i < strlen(str); i++) {
        outb(this->address, str[i]);
    }
    outb(this->address, '\n');
}

void Serial::write(char c) {
    outb(this->address, c);
}

void Serial::_streamHandler(char* str, int size, Serial* serial) {
    for (int i = 0; i < size; i++) {
        serial->write(str[i]);
    }
}