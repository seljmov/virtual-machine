#include "Processor.h"
#include "Commands/Movements.h"
#include "Commands/RealArithmetic.h"
#include "Commands/Conversions.h"
#include "Commands/IO.h"
#include "Commands/IMath.h"

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

    commands[rAdd] = new class rAdd();
    commands[rSub] = new class rSub();
    commands[rMul] = new class rMul();
    commands[rDiv] = new class rDiv();

    commands[input] = new class Input();
    commands[output] = new class Output();

    commands[jmp] = new class Jmp();
    commands[jzf] = new class Jzf();
    commands[jnzf] = new class Jnzf();
    commands[jsf] = new class Jsf();
    commands[jnsf] = new class Jnsf();

    commands[call] = new class Call();
    commands[ret] = new class Ret();
}

Processor::~Processor() {
    for (auto &i : commands) {
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
        commands[cmd.code]->operator()(*this);
        psw.inc_IP();
        load_curr_cmd();
    }
}

int16_t Processor::get_int16(const uint8_t &_reg) const {
    // - Так как у нас 4 массива по 2 регистра, что равно 8 регистрам,
    // - то доступ тоже производится особенным образом.
    // - [0][0] и [0][1] - 0,1 регистры
    // - [1][0] и [1][1] - 2,3 регистры
    // - [2][0] и [2][1] - 4,5 регистры
    // - [3][0] и [3][1] - 6,7 регистры
    // - Определение внешнего массива:
    // - Чтобы определить какой из 4-х массив используется:
    // - Если _reg четный, то _reg / 2, иначе _reg / 2 - 1;
    // - Определение внутреннего массива:
    // - Для доступа ко второму массиву:
    // - Если _reg четный, то 0, иначе 1;
    uint8_t ex = 0; // - Индекс внешнего массива
    uint8_t in = 0; // - Индекс внутреннего массива
    // - Определяем внешний массив
    if (_reg % 2 == 0) ex = _reg / 2;
    else ex = _reg / 2 - 1;
    // - Определяем внутренний массив
    if (_reg % 2 == 0) in = 0;
    else in = 1;
    // - Возвращаем результат
    return regs[ex].word16[in].int16;
}

uint16_t Processor::get_uint16(const uint8_t &_reg) const {
    uint8_t ex = 0; // - Индекс внешнего массива
    uint8_t in = 0; // - Индекс внутреннего массива
    // - Определяем внешний массив
    if (_reg % 2 == 0) ex = _reg / 2;
    else ex = _reg / 2 - 1;
    // - Определяем внутренний массив
    if (_reg % 2 == 0) in = 0;
    else in = 1;
    // - Возвращаем результат
    return regs[ex].word16[in].uint16;
}

int32_t Processor::get_int32(const uint8_t &_reg) const {
    verify_register(_reg);
    // - Тут все проще - достаточно только определить внешний массив
    // - Так как все номера четные, то _reg / 2;
    uint8_t ex = _reg / 2;
    return regs[ex].word32.int32;
}

float Processor::get_real32(const uint8_t &_reg) const {
    verify_register(_reg);
    // - Тут все проще - достаточно только определить внешний массив
    // - Так как все номера четные, то _reg / 2 ;
    uint8_t ex = _reg / 2;
    return regs[ex].word32.real32;
}

void Processor::set_int16(const int16_t& int16, const uint8_t &_reg) {
    uint8_t ex = 0; // - Индекс внешнего массива
    uint8_t in = 0; // - Индекс внутреннего массива
    // - Определяем внешний массив
    if (_reg % 2 == 0) ex = _reg / 2;
    else ex = _reg / 2 - 1;
    // - Определяем внутренний массив
    if (_reg % 2 == 0) in = 0;
    else in = 1;
    regs[ex].word16[in].int16 = int16;
}

void Processor::set_uint16(const uint16_t& uint16, const uint8_t &_reg) {
    uint8_t ex = 0; // - Индекс внешнего массива
    uint8_t in = 0; // - Индекс внутреннего массива
    // - Определяем внешний массив
    if (_reg % 2 == 0) ex = _reg / 2;
    else ex = _reg / 2 - 1;
    // - Определяем внутренний массив
    if (_reg % 2 == 0) in = 0;
    else in = 1;
    regs[ex].word16[in].uint16 = uint16;
}

void Processor::set_int32(const int32_t& int32, const uint8_t &_reg) {
    verify_register(_reg);
    // - Тут все проще - достаточно только определить внешний массив
    // - Так как все номера четные, то _reg / 2;
    uint8_t ex = _reg / 2;
    regs[ex].word32.int32 = int32;
}

void Processor::set_real32(const float& real32, const uint8_t &_reg) {
    verify_register(_reg);
    // - Тут все проще - достаточно только определить внешний массив
    // - Так как все номера четные, то _reg / 2;
    uint8_t ex = _reg / 2;
    regs[ex].word32.real32 = real32;
}

void Processor::verify_register(const uint8_t &_reg) {
    // - Если номер не в диапазоне [1,8] или нечетный,
    // - То кидаем исключение
    if ((_reg < 1 || _reg > 8) || _reg % 2 == 1) {
        throw invalid_register("Неправильный номер 32-битного регистра!");
    }
}