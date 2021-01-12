#include "Command.h"

int16_t Command::get_int16(const Processor &p, const uint8_t &_reg) {
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
    uint8_t ex; // - Индекс внешнего массива
    uint8_t in; // - Индекс внутреннего массива
    // - Определяем внешний массив
    if (_reg % 2 == 0) ex = _reg / 2;
    else ex = _reg / 2 - 1;
    // - Определяем внутренний массив
    if (_reg % 2 == 0) in = 0;
    else in = 1;
    // - Возвращаем результат
    return p.regs[ex].word16[in].int16;
}

uint16_t Command::get_uint16(const Processor &p, const uint8_t &_reg) {
    uint8_t ex; // - Индекс внешнего массива
    uint8_t in; // - Индекс внутреннего массива
    // - Определяем внешний массив
    if (_reg % 2 == 0) ex = _reg / 2;
    else ex = _reg / 2 - 1;
    // - Определяем внутренний массив
    if (_reg % 2 == 0) in = 0;
    else in = 1;
    // - Возвращаем результат
    return p.regs[ex].word16[in].uint16;
}

int32_t Command::get_int32(const Processor &p, const uint8_t &_reg) {
    verify_register(_reg);
    // - Тут все проще - достаточно только определить внешний массив
    // - Так как все номера четные, то _reg / 2;
    uint8_t ex = _reg / 2;
    return p.regs[ex].word32.int32;
}

float Command::get_real32(const Processor &p, const uint8_t &_reg) {
    verify_register(_reg);
    // - Тут все проще - достаточно только определить внешний массив
    // - Так как все номера четные, то _reg / 2 ;
    uint8_t ex = _reg / 2;
    return p.regs[ex].word32.real32;
}

void Command::set_int16(Processor &p, const int16_t &int16, const uint8_t &_reg) {
    uint8_t ex; // - Индекс внешнего массива
    uint8_t in; // - Индекс внутреннего массива
    // - Определяем внешний массив
    if (_reg % 2 == 0) ex = _reg / 2;
    else ex = _reg / 2 - 1;
    // - Определяем внутренний массив
    if (_reg % 2 == 0) in = 0;
    else in = 1;
    p.regs[ex].word16[in].int16 = int16;
}

void Command::set_uint16(Processor &p, const uint16_t &uint16, const uint8_t &_reg) {
    uint8_t ex; // - Индекс внешнего массива
    uint8_t in; // - Индекс внутреннего массива
    // - Определяем внешний массив
    if (_reg % 2 == 0) ex = _reg / 2;
    else ex = _reg / 2 - 1;
    // - Определяем внутренний массив
    if (_reg % 2 == 0) in = 0;
    else in = 1;
    p.regs[ex].word16[in].uint16 = uint16;
}

void Command::set_int32(Processor &p, const int32_t &int32, const uint8_t &_reg) {
    verify_register(_reg);
    // - Тут все проще - достаточно только определить внешний массив
    // - Так как все номера четные, то _reg / 2;
    uint8_t ex = _reg / 2;
    p.regs[ex].word32.int32 = int32;
}

void Command::set_real32(Processor &p, const float &real32, const uint8_t &_reg) {
    verify_register(_reg);
    // - Тут все проще - достаточно только определить внешний массив
    // - Так как все номера четные, то _reg / 2;
    uint8_t ex = _reg / 2;
    p.regs[ex].word32.real32 = real32;
}

void Command::verify_register(const uint8_t &_reg) {
    // - Если номер не в диапазоне [0,7] или нечетный,
    // - То кидаем исключение
    if (_reg > 7 || _reg % 2 == 1) {
        throw invalid_register("Неправильный номер 32-битного регистра!");
    }
}