#pragma once
#include <stdint.h>
#include <libs/kernel/liballoc.h>
#include <libs/std/string.h>

template <class T>
class iostream {
public:
    inline iostream() {
        
    }
    virtual int read(T* buf, int size) {
        return read(buf, size);
    }
    virtual int write(T* buf, int size) {
        return write(buf, size);
    }
    virtual void flush() {
        flush();
    }
};

template <class T, class D>
class stream : public iostream<T> {
public:
    stream();
    stream(void (*handler)(T*, int, D*), D* args, int buffer_size = 1);
    int read(T* buf, int size);
    int write(T* buf, int size);
    void flush();

private:
    T _item_unb;
    T* _items;
    uint32_t itemCount = 0;
    uint32_t bufferSize = 0;
    void (*_handler)(T*, int, D*);
    D* _args = nullptr;
};

template<class T, class D>
stream<T,D>::stream() {
    bufferSize = 0;
}

template<class T, class D>
stream<T,D>::stream(void (*handler)(T*, int, D*), D* args, int buffer_size) {
    bufferSize = buffer_size;
    _handler = handler;
    _args = args;
    if (buffer_size <= 1) {
        _items = &_item_unb;
    }
    else {
        _items = (T*)malloc(buffer_size);
    }
}

template<class T, class D>
int stream<T,D>::read(T* buf, int size) {
    if (size == 0 || bufferSize == 0) {
        return -1;
    }
    if (size > itemCount) {
        size = itemCount;
    }
    memmove(buf, _items, size);
    return size;
}

template<class T, class D>
int stream<T,D>::write(T* buf, int size) {
    if (size <= 0 || bufferSize == 0) {
        return -1;
    }
    for (int i = 0; i < size; i++) {
        _items[itemCount] = buf[i];
        itemCount++;
        if (itemCount == bufferSize) {
            flush();
        }
    }
    return size;
}

template<class T, class D>
void stream<T,D>::flush() {
    if (bufferSize == 0) {
        return;
    }
    
    _handler(_items, itemCount, _args);
    itemCount = 0;
}