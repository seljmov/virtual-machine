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

    // - Проверка адреса, присутствующая в обоих методах,
    // - может кинуть исключение, поэтому нет noexcept
    // - Добавление в память
    void push(const data_t& data, const address_t& addr);
    // - Возвращение из памяти
    data_t get_data(const address_t& addr) const;

private:
    // - ВМ маленькая, тут и 255 команд хватит :)
    constexpr static const uint8_t SIZE = std::numeric_limits<uint8_t>::max();
    data_t* memory{nullptr};

    // - Метод кидает исключение, поэтому void
    // - Проверка адреса
    void verify_address(const address_t& address) const;
};

#endif // MEMORY_H