#ifndef JUMPS_H
#define JUMPS_H

#include <functional>
#include "Command.h"

class Jumps : public Command
{
public:
    Jumps(std::function<bool(Processor&)> l) : execute(l) {}
    void go_to(Processor& processor) noexcept;
    inline void operator()(Processor& processor) noexcept override {
        if (execute(processor)) {
            go_to(processor);
        }
    }

private:
    std::function<bool(Processor&)> execute;
};

// - Вывод подпрограммы
class Call : public Command
{
public:
    inline void operator()(Processor& processor) noexcept final {
        // - Адрес возрата (текущий IP) кладем в 1 регистр,
        // - а во втором регистре лежит адрес для прыжка
        // - Тут сделан выбор в пользу s = 0, dd = 10
        const uint8_t r1_i = processor.cmd.r1;
        const uint8_t r2_i = processor.cmd.r2;
        const address_t _ret_ip = processor.psw.IP;
        set_uint16(processor, _ret_ip, r1_i);
        const address_t _new_ip = get_uint16(processor, r2_i);
        processor.psw.IP = _new_ip;
    }
};

// - Возврат из подпрограммы
class Ret : public Command
{
public:
    inline void operator()(Processor& processor) noexcept final {
        // - Узнаем адрес возврата и делаем безусловный прыжок
        const uint8_t r1_i = processor.cmd.r1;
        const address_t _ret_ip = get_uint16(processor, r1_i);
        processor.psw.IP = _ret_ip;
    }
};

#endif //JUMPS_H