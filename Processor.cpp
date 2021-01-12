#include "Processor.h"
#include "Commands/Movements.h"
#include "Commands/IO.h"
#include "Commands/IMath.h"
#include "Commands/RMath.h"
#include "Commands/Jumps.h"

Processor::Processor() {
    commands[stop] = nullptr;
    commands[move] = new class Move();

    commands[iAdd] = new class IMath([](int a, int b) { return (a + b); });
    commands[iSub] = new class IMath([](int a, int b) { return (a - b); });
    commands[iMul] = new class IMath([](int a, int b) { return (a * b); });
    commands[iDiv] = new class IMath([](int a, int b) { return (a / b); });
    commands[iMod] = new class IMath([](int a, int b) { return (a % b); });
    commands[iInc] = new class IMath([](int a, int b) { return (a + 1); });
    commands[iDec] = new class IMath([](int a, int b) { return (a - 1); });
    commands[iAnd] = new class IMath([](int a, int b) { return (a & b); });
    commands[iOr]  = new class IMath([](int a, int b) { return (a | b); });
    commands[iNot] = new class IMath([](int a, int b) { return (~a); });

    commands[rAdd] = new class RMath([](float a, float b) { return (a + b); });
    commands[rSub] = new class RMath([](float a, float b) { return (a - b); });
    commands[rMul] = new class RMath([](float a, float b) { return (a * b); });
    commands[rDiv] = new class RMath([](float a, float b) { return (a / b); });

    commands[input] = new class Input();
    commands[output] = new class Output();

    // - Тут просто "return true", так как безусловный переход :)
    commands[jmp] = new class Jumps([](Processor& p) { return true; });
    commands[jzf] = new class Jumps([](Processor& p) { return (p.psw.ZF == 1); });
    commands[jnzf] = new class Jumps([](Processor& p) { return (p.psw.ZF == 0); });
    commands[jsf] = new class Jumps([](Processor& p) { return (p.psw.SF == 1); });
    commands[jnsf] = new class Jumps([](Processor& p) { return (p.psw.ZF == 0); });

    commands[call] = new class Call();
    commands[ret] = new class Ret();
}

Processor::~Processor() {
    for (auto &i : commands) {
        delete i;
        i = nullptr;
    }
}

void Processor::load_curr_cmd() noexcept {
    cmd = memory[psw.IP].cmd;
}

void Processor::reset() noexcept {
    psw.reset_flags();
    psw.IP = 0;
}

void Processor::run() noexcept {
    load_curr_cmd();    // - Загрузка первой команды
    while (cmd.code != stop) {
        commands[cmd.code]->operator()(*this);
        psw.IP++;
        load_curr_cmd();
    }
}