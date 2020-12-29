#ifndef TYPES_H
#define TYPES_H

#include <cinttypes>

using address_t = uint16_t;

// - Структура команды
// - Результат по второму операнду (Регистр/память)
struct cmd_t
{
    uint8_t code : 7;       // - Код операции
    uint8_t s : 1;          // - Размер операнда
    uint8_t dd : 2;         // - Формат операнда
    uint8_t r1 : 3;         // - Первый регистр
    uint8_t r2 : 3;         // - Второй регистр
    address_t o1;           // - Первый адрес
    address_t o2;           // - Второй адрес
};

// - Данные
union word_t
{
    int16_t int16;          // - Целое знаковое/беззнаковое (1 слово)
    int32_t int32;          // - Целое знаковое (2 слова)
    float real32;           // - Дробное (2 слова)
};

// - Тип данных, из которого состоит память
union data_t
{
    word_t word;            // - Слово
    cmd_t cmd;              // - Команда
};

// - Регистры общего назначения
// - В процессоре будет создан массив данного юниона, поэтому в итоге
// - получится 8 регистров int16 и оставшиеся типы по 4 регистра.
union Registers
{
    int16_t int16[2];       // - Целое знаковое/беззнаковое (1 слово)
    int32_t int32;          // - Целое знаковое (2 слова)
    float real32;           // - Дробное (2 слова)
};

#endif // TYPES_H