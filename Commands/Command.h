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
};

#endif // COMMAND_H