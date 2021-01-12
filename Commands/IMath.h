#ifndef IMATH_H
#define IMATH_H

#include <functional>
#include "Command.h"

class IMath : public Command
{
public:
    IMath(std::function<int(int,int)> l) : lambda(l) {}
    void operator()(Processor& processor) override;

private:
    std::function<int(int,int)> lambda;

    // - Устновка флагов
    static void set_flags(Processor& processor) noexcept;
    // - Обработка команды типа Регистр-Регистр (dd = 00/0)
    void handle_reg_to_reg(Processor& processor) noexcept;
    // - Обработка команды типа Регистр-Память (dd = 01/1)
    void handle_reg_to_mem(Processor& processor) noexcept;
    // - Обработка команды типа Память-Регистр (dd = 10/2)
    void handle_mem_to_reg(Processor& processor) noexcept;
    // - Обработка команды типа Память-Память (dd = 11/3)
    void handle_mem_to_mem(Processor& processor) noexcept;
};

#endif // IMATH_H