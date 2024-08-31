#pragma once
#include <cstdint>
#include "disk.hpp"

class Flash
{
private:
    bool is_erased(const unsigned char *data, unsigned int len);

public:
    uint32_t address;
    Flash();
    void printAll();
    void print(uint32_t endAddress);
    void write(void *buf);
    void dumpToSD(Disk &disk);
    void eraseAll();
    void printHumanReadable();
};