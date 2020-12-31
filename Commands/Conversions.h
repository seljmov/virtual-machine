#ifndef CONVERSIONS_H
#define CONVERSIONS_H

#include "Command.h"

class Jmp : public Command
{
public:
    void go_to(Processor& processor) noexcept;
    inline void operator()(Processor& processor) noexcept override {
        go_to(processor);
    }
};

class Jzf : public Jmp
{
public:
    inline void operator()(Processor& processor) noexcept final {
        if (processor.psw.get_ZF() == 1) {
            go_to(processor);
        }
    }
};

class Jnzf : public Jmp
{
public:
    inline void operator()(Processor& processor) noexcept final {
        if (processor.psw.get_ZF() == 0) {
            go_to(processor);
        }
    }
};

class Jsf : public Jmp
{
public:
    inline void operator()(Processor& processor) noexcept final {
        if (processor.psw.get_SF() == 1) {
            go_to(processor);
        }
    }
};

class Jnsf : public Jmp
{
public:
    inline void operator()(Processor& processor) noexcept final {
        if (processor.psw.get_SF() == 0) {
            go_to(processor);
        }
    }
};

class Call : public Jmp
{
public:
    inline void operator()(Processor& processor) noexcept final {
        word_t word;
        word.word16->uint16 = processor.psw.get_IP();
        const uint8_t r1_i = processor.get_cmd_r1();
        const uint8_t r2_i = processor.get_cmd_r2();
        processor.regs[r1_i/2-1].word16[r1_i%2].uint16 = r1_i;
        processor.psw.set_IP(processor.regs[r2_i/2-1].word16[r2_i%2].uint16);
    }
};

class Ret : public Jmp
{
public:
    inline void operator()(Processor& processor) noexcept final {
        const uint8_t r1_i = processor.get_cmd_r1();
        processor.psw.set_IP(processor.regs[r1_i/2-1].word16[r1_i%2].uint16);
    }
};

#endif // CONVERSIONS_H