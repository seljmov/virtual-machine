#include "IMath.h"

void IMath::operator()(Processor &processor) {
    // - Узнает формат операндов
    const uint8_t dd = processor.cmd.dd;
    // - Обрабатываем команду в зависимости от формата
    switch (dd) {
        // - Регистр-Регистр (dd = 00/0)
        case 0: handle_reg_to_reg(processor); break;
            // - Регистр-Память (dd = 01/1)
        case 1: handle_reg_to_mem(processor); break;
            // - Память-Регистр (dd = 10/2)
        case 2: handle_mem_to_reg(processor); break;
            // - Память-Память (dd = 11/3)
        case 3: handle_mem_to_mem(processor); break;
    }
    // - Устанавливаем флаги
    set_flags(processor);
}

void IMath::set_flags(Processor &processor) noexcept {
    // - Узнаем размер операндов
    const uint8_t s = processor.cmd.s;
    // - Узнаем индекс второго регистра, участвовавшего в команде,
    // - так как результат лежит во втором регистре
    const uint8_t r2_i = processor.cmd.r2;
    int32_t result;
    // - Если размер операнда - 1 слово
    if (s == 0)
    {
        // - Узнаем результат
        result = get_int16(processor, r2_i);
    }
    // - Иначе размер операнда - 2 слова
    else
    {
        // - Узнаем результат
        result = get_int32(processor, r2_i);
    }
    // - Устанавливаем флаги
    processor.psw.set_ZF(result);
    processor.psw.set_SF(result);
}

void IMath::handle_reg_to_reg(Processor &processor) noexcept {
    // - Узнаем размер операндов
    const uint8_t s = processor.cmd.s;
    // - Узнаем индексы регистров
    const uint8_t r1_i = processor.cmd.r1;
    const uint8_t r2_i = processor.cmd.r2;
    // - Если размер операнда - 1 слово
    if (s == 0)
    {
        // - Определяем переменные
        auto var1 = get_int16(processor, r1_i);
        auto var2 = get_int16(processor, r2_i);
        // - Вычисляем
        int16_t int16 = execute(var1, var2);
        // - Записываем результат
        set_int16(processor, int16, r2_i);
    }
    // - Иначе размер операнда - 2 слова
    else
    {
        // - Определяем переменные
        auto var1 = get_int32(processor, r1_i);
        auto var2 = get_int32(processor, r2_i);
        // - Вычисляем
        int32_t int32 = execute(var1, var2);
        // - Записываем результат
        set_int32(processor, int32, r2_i);
    }
}

void IMath::handle_reg_to_mem(Processor &processor) noexcept {
    // - Узнаем размер операндов
    const uint8_t s = processor.cmd.s;
    // - Узнаем индекс регистра и адрес памяти
    const uint8_t r1_i = processor.cmd.r1;
    const address_t o2_i = processor.cmd.o2;
    // - Потому что сохраняем в память
    data_t new_data;
    // - Берем требуемые данные из памяти
    data_t from_mem = processor.memory[o2_i];
    // - Если размер операнда - 1 слово
    if (s == 0)
    {
        // - Определяем переменные
        auto var1 = get_int16(processor, r1_i);
        auto var2 = from_mem.word.word16->int16;
        // - Вычисляем
        new_data.word.word16->int16 = execute(var1, var2);
    }
    // - Иначе размер операнда - 2 слова
    else
    {
        // - Определяем переменные
        auto var1 = get_int32(processor, r1_i);
        auto var2 = from_mem.word.word32.int32;
        // - Вычисляем
        new_data.word.word32.int32 = execute(var1, var2);
    }
    // - Отправляем результат по адресу
    processor.memory[o2_i] = new_data;
}

void IMath::handle_mem_to_reg(Processor &processor) noexcept {
    // - Узнаем размер операндов
    const uint8_t s = processor.cmd.s;
    // - Узнаем индекс регистра и адрес памяти
    const address_t o1_i = processor.cmd.o1;
    const uint8_t r2_i = processor.cmd.r2;
    // - Берем требуемые данные из памяти
    data_t from_mem = processor.memory[o1_i];
    // - Если размер операнда - 1 слово
    if (s == 0)
    {
        // - Определяем переменные
        auto var1 = from_mem.word.word16->int16;
        auto var2 = get_int16(processor, r2_i);
        // - Вычисляем
        int16_t int16 = execute(var1, var2);
        // - Записываем результат
        set_int16(processor, int16, r2_i);
    }
    // - Иначе размер операнда - 2 слова
    else
    {
        // - Определяем переменные
        auto var1 = from_mem.word.word32.int32;
        auto var2 = get_int32(processor, r2_i);
        // - Вычисляем
        int32_t int32 = execute(var1, var2);
        // - Записываем результат
        set_int32(processor, int32, r2_i);
    }
}

void IMath::handle_mem_to_mem(Processor &processor) noexcept {
    // - Узнаем размер операндов
    const uint8_t s = processor.cmd.s;
    // - Узнаем адреса памяти
    const address_t o1_i = processor.cmd.o1;
    const address_t o2_i = processor.cmd.o2;
    // - Потому что сохраняем в память
    data_t new_data;
    // - Берем требуемые данные из памяти
    data_t from_mem_1 = processor.memory[o1_i];
    data_t from_mem_2 = processor.memory[o2_i];
    // - Если размер операнда - 1 слово
    if (s == 0)
    {
        // - Определяем переменные
        auto var1 = from_mem_1.word.word16->int16;
        auto var2 = from_mem_2.word.word16->int16;
        // - Вычисляем
        new_data.word.word16->int16 = execute(var1, var2);
    }
    // - Иначе размер операнда - 2 слова
    else
    {
        // - Определяем переменные
        auto var1 = from_mem_1.word.word32.int32;
        auto var2 = from_mem_2.word.word32.int32;
        // - Вычисляем
        new_data.word.word32.int32 = execute(var1, var2);
    }
    // - Отправляем результат по адресу
    processor.memory[o2_i] = new_data;
}