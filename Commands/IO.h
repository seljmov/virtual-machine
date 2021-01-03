#ifndef IO_H
#define IO_H

#include "Command.h"

// - Ввод числа
class Input : public Command
{
public:
    void operator()(Processor& processor) final;
};

// - Вывод числа
class Output : public Command
{
public:
    void operator()(Processor& processor) final;
};

#endif // IO_H