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
    // - 16-битные данные
    union word16_t
    {
        int16_t int16;      // - Целое знаковое (1 слово)
        uint16_t uint16;    // - Целое беззнаковое (1 слово)
    };

    // - 32-битные данные
    union word32_t
    {
        int32_t int32;      // - Целое знаковое (2 слова)
        float real32;       // - Дробное (2 слова)
    };

    word16_t word16[2];
    word32_t word32;
};

// - Тип данных, из которого состоит память
// - Тут можно выравнять, чтобы не занимать лишние 2 байта
#pragma pack(push, 1)
union data_t
{
    word_t word;            // - Слово
    cmd_t cmd;              // - Команда
};
#pragma pack(pop)

#endif // TYPES_H