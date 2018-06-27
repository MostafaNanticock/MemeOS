#include <string.h>
#include <stdint.h>
#include <terminal.h>

uint32_t strlen(char* str){
    uint32_t len = 0;
	while (str[len])
		len++;
	return len;
}

bool strcmp(char* str_a, char* str_b) {
	if (strlen(str_a) != strlen(str_b)) {
		return false;
	}
	for (uint32_t i = 0; i < strlen(str_a); i++) {
		if (str_a[i] != str_b[i]) {
			return false;
		}
	}
	return true;
}

void* memmove(void* dstptr, void* srcptr, uint64_t size) {
	unsigned char* dst = (unsigned char*) dstptr;
	unsigned char* src = (unsigned char*) srcptr;
	if (dst < src) {
		for (uint64_t i = 0; i < size; i++)
			dst[i] = src[i];
	} else {
		for (uint64_t i = size; i != 0; i--)
			dst[i-1] = src[i-1];
	}
	return dstptr;
}

char HEX_ALPHABET[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

char* dumpHexByte(uint8_t n) {
    char* rtn = "00";
    rtn[1] = HEX_ALPHABET[n & 0x0F];
    rtn[0] = HEX_ALPHABET[(n & 0xF0) >> 4];
    return rtn;
}

string itoa(uint32_t n, uint8_t base) {
	string ret = "";
	while (n > 0) {
		uint32_t digit = n % base;
		string str = "";
		str += HEX_ALPHABET[digit];
		ret = str + ret;
		n -= digit;
		n /= base;
	}
	return ret;
}

uint32_t strcnt(char* str, char c) {
	uint32_t count = 0;
	for (uint32_t i = 0; i < strlen(str); i++) {
		if (str[i] == c) {
			count++;
		}
	}
	return count;
}

int strfio(char* str, char c) {
	uint32_t index = 0;
	for (uint32_t i = 0; i < strlen(str); i++) {
		if (str[i] == c) {
			return i;
		}
	}
	return -1;
}

char* substr(char* str, uint32_t index) {
	return str + index;
}

// <=============================== STRING CLASS ===============================>

string::string(char* str) {
	this->_length = strlen(str);
	this->_str = (char*)malloc(this->_length + 1);
	memmove(this->_str, str, this->_length);
	this->_str[this->_length] = 0x00;
}

string::string() {
	this->_length = 0;
	this->_str = (char*)malloc(1);
	this->_str[0] = 0x00;
}

string::~string() {
	this->_length = 0;
	free(this->_str);
}

string string::operator+(string str) {
	string ret;
	ret = this->toCharArray();
	ret += str;
	return ret;
}

string string::operator+(char c) {
	string ret;
	ret = this->toCharArray();
	ret += c;
	return ret;
}

void string::operator+=(string str) {
	this->_str = (char*)realloc(this->_str, this->_length + str.length() + 1);
	memmove(this->_str + this->_length, str.toCharArray(), str.length());
	this->_str[this->_length + str.length()] = 0x00;
	this->_length += str.length();
}

void string::operator+=(char c) {
	this->_str = (char*)realloc(this->_str, this->_length + 2);
	this->_str[this->_length] = c;
	this->_str[this->_length + 1] = 0x00;
	this->_length++;
}

char string::operator[](uint32_t i) {
	if (i < this->_length) {
		return this->_str[i];
	}
	return 0x00;
}

bool string::operator==(string str) {
	return strcmp(this->_str, str.toCharArray());
}

bool string::operator!=(string str) {
	return !strcmp(this->_str, str.toCharArray());
}

bool string::operator==(char* str) {
	return strcmp(this->_str, str);
}

bool string::operator!=(char* str) {
	return !strcmp(this->_str, str);
}

uint32_t string::length() {
	return this->_length;
}

char* string::toCharArray() {
	return this->_str;
}

void string::reserve(uint32_t len) {
	if (len > this->_length) {
		this->_str = (char*)realloc(this->_str, len + 1);
	}
}

string string::substring(uint32_t index) {
	string ret;
	if (index < this->_length) {
		ret = (this->toCharArray() + index);
	}
	return ret;
}

string string::substring(uint32_t index, uint32_t length) {
	string out;
	out.reserve(length);
    for (uint32_t i = index; i < index + length; i++) {
        out += this->_str[i];
    }
    return out;
}

bool string::startsWith(string str) {
	if (str.length() > this->_length) {
		return false;
	}
	for (uint32_t i = 0; i < str.length(); i++) {
		if (this->_str[i] != str[i]);
	}
	return true;
}

// <=============================== STRING CLASS ===============================>