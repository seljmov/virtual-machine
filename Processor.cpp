#include "Processor.h"
#include "Commands/Movements.h"
#include "Commands/IntegerArithmetic.h"
#include "Commands/RealArithmetic.h"
#include "Commands/Conversions.h"
#include "Commands/IO.h"

Processor::Processor() {
    command[stop] = nullptr;
    command[move] = new class Move();

    command[iAdd] = new class iAdd();
    command[iSub] = new class iSub();
    command[iMul] = new class iMul();
    command[iDiv] = new class iDiv();
    command[iMod] = new class iMod();
    command[iInc] = new class iInc();
    command[iDec] = new class iDec();
    command[iAnd] = new class iAnd();
    command[iOr] = new class iOR();
    command[iNot] = new class iNot();

    command[rAdd] = new class rAdd();
    command[rSub] = new class rSub();
    command[rMul] = new class rMul();
    command[rDiv] = new class rDiv();

    command[input] = new class Input();
    command[output] = new class Output();

    command[jmp] = new class Jmp();
    command[jzf] = new class Jzf();
    command[jnzf] = new class Jnzf();
    command[jsf] = new class Jsf();
    command[jnsf] = new class Jnsf();

    command[call] = new class Call();
    command[ret] = new class Ret();
}

Processor::~Processor() {
    for (Command* &i : command) {
        delete i;
        i = nullptr;
    }
}

data_t Processor::get_from_mem(const address_t &addr) const noexcept {
    return memory.get_data(addr);
}

void Processor::push_to_mem(const data_t &data, const address_t &addr) noexcept {
    memory.push(data, addr);
}

void Processor::load_curr_cmd() noexcept {
    cmd = memory.get_data(psw.get_IP()).cmd;
}

void Processor::reset() noexcept {
    psw.reset_flags();
    psw.set_IP(0);
}

void Processor::run() noexcept {
    load_curr_cmd();    // - Загрузка первой команды
    while (cmd.code != stop) {
        command[cmd.code]->operator()(*this);
        psw.inc_IP();
        load_curr_cmd();
    }
}