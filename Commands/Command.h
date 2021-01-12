#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include <limits>
#include <cmath>
#include "../Processor.h"
#include "../Exceptions.h"

class Command
{
public:
    virtual void operator()(Processor& processor) = 0;
    virtual ~Command() = default;

    // - Работа с регистрами
    // - Получить из указанного регистра int16
    static int16_t get_int16(const Processor& p, const uint8_t& _reg);
    // - Получить из указанного регистра uint16
    static uint16_t get_uint16(const Processor& p, const uint8_t& _reg);
    // - Получить из указанного регистра int32
    static int32_t get_int32(const Processor& p, const uint8_t& _reg);
    // - Получить из указанного регистра real32
    static float get_real32(const Processor& p, const uint8_t& _reg);

    // - Положить в указанный регистр int16
    void set_int16(Processor& p, const int16_t& int16, const uint8_t& _reg);
    // - Положить в указанный регистр uint16
    void set_uint16(Processor& p, const uint16_t& uint16, const uint8_t& _reg);
    // - Положить в указанный регистр int32
    void set_int32(Processor& p, const int32_t& int32, const uint8_t& _reg);
    // - Положить в указанный регистр real32
    void set_real32(Processor& p, const float& real32, const uint8_t& _reg);

    // - Метод проверки кидает исключения
    // - Проверка номера 32-битного регистра
    static void verify_register(const uint8_t& _reg);
};

#endif // COMMAND_H