#ifndef MEMORY_H
#define MEMORY_H

#include <limits>
#include "Types.h"
#include "Exceptions.h"

class Memory 
{
public:
    Memory();
    virtual ~Memory();

    Memory(const Memory&) = delete;
    Memory(const Memory&&) = delete;
    Memory& operator=(const Memory&) = delete;
    Memory& operator=(const Memory&&) = delete;

    inline data_t& operator[](const address_t& addr) noexcept
    { return memory[addr]; }

private:
    // - Тут получается 10922, ибо 65535 / 6
    constexpr static const address_t SIZE =
            std::numeric_limits<uint16_t>::max() / sizeof(data_t);
    data_t* memory{nullptr};
};

#endif // MEMORY_H