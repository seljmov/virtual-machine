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
        const uint8_t r1_i = processor.get_cmd_r1();
        const uint8_t r2_i = processor.get_cmd_r2();
        const address_t _ret_ip = processor.psw.get_IP();
        processor.set_uint16(_ret_ip, r1_i);
        const address_t _new_ip = processor.get_uint16(r2_i);
        processor.psw.set_IP(_new_ip);
    }
};

class Ret : public Jmp
{
public:
    inline void operator()(Processor& processor) noexcept final {
        const uint8_t r1_i = processor.get_cmd_r1();
        const address_t _ret_ip = processor.get_uint16(r1_i);
        processor.psw.set_IP(_ret_ip);
    }
};

#endif // CONVERSIONS_H