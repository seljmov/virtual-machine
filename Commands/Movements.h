#ifndef MOVEMENTS_H
#define MOVEMENTS_H

#include "Command.h"

class Move : public Command
{
protected:
    void operator()(Processor &processor) noexcept override;

private:
    // - Обработка команды типа Регистр-Регистр (dd = 00/0)
    void handle_reg_to_reg(Processor& processor) noexcept;
    // - Обработка команды типа Регистр-Память (dd = 01/1)
    void handle_reg_to_mem(Processor& processor) noexcept;
    // - Обработка команды типа Память-Регистр (dd = 10/2)
    void handle_mem_to_reg(Processor& processor) noexcept;
    // - Обработка команды типа Память-Память (dd = 11/3)
    void handle_mem_to_mem(Processor& processor) noexcept;
};

#endif // MOVEMENTS_H