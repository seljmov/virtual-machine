#ifndef IO_H
#define IO_H

#include "Command.h"

class Input : public Command
{
public:
    void operator()(Processor& processor) final;
};

class Output : public Command
{
public:
    void operator()(Processor& processor) final;
};

#endif // IO_H