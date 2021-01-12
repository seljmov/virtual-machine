#include "Memory.h"

Memory::Memory() {
    memory = new data_t[SIZE];
}

Memory::~Memory() {
    delete[] memory;
}