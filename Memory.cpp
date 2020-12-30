#include "Memory.h"

Memory::Memory() {
    memory = new data_t[SIZE];
}

Memory::~Memory() {
    delete[] memory;
}

void Memory::push(const data_t &data, const address_t &addr) {
    verify_address(addr);
    memory[addr] = data;
}

data_t Memory::get_data(const address_t &addr) const {
    verify_address(addr);
    return memory[addr];
}

void Memory::verify_address(const address_t &address) const {
    if (address < 0 || address >= SIZE) {
        throw out_of_memory("Выход за пределы памяти!");
    }
}