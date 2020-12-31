#include "RealArithmetic.h"

void RealArithmetic::operator()(Processor &processor) {
    // - Узнает формат операндов
    const uint8_t dd = processor.get_cmd_dd();
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

void RealArithmetic::set_flags(Processor &processor) noexcept {
    // - Узнаем индекс второго регистра, участвовавшего в команде,
    // - так как результат лежит во втором регистре
    const uint8_t r2_i = processor.get_cmd_r2();
    // - Узнаем результат
    int32_t result = processor.get_real32(r2_i);
    // - Устанавливаем флаги
    processor.psw.set_ZF(result);
    processor.psw.set_SF(result);
}

void RealArithmetic::handle_reg_to_reg(Processor &processor) noexcept {
    // - Узнаем индексы регистров
    const uint8_t r1_i = processor.get_cmd_r1();
    const uint8_t r2_i = processor.get_cmd_r2();
    // - Вычисляем
    float real32 = execute(processor.get_real32(r1_i), processor.get_real32(r2_i));
    // - Записываем результат
    processor.set_real32(real32, r2_i);
}

void RealArithmetic::handle_reg_to_mem(Processor &processor) noexcept {
    // - Узнаем индекс регистра и адрес памяти
    const uint8_t r1_i = processor.get_cmd_r1();
    const address_t o2_i = processor.get_cmd_o2();
    // - Потому что сохраняем в память
    data_t new_data;
    // - Берем требуемые данные из памяти
    data_t from_mem = processor.get_from_mem(o2_i);
    // - Вычисляем
    new_data.word.word32.real32 = execute(
            processor.get_real32(r1_i), from_mem.word.word32.real32
    );
    // - Отправляем результат по адресу
    processor.push_to_mem(new_data, o2_i);
}

void RealArithmetic::handle_mem_to_reg(Processor &processor) noexcept {
    // - Узнаем индекс регистра и адрес памяти
    const address_t o1_i = processor.get_cmd_o1();
    const uint8_t r2_i = processor.get_cmd_r2();
    // - Берем требуемые данные из памяти
    data_t from_mem = processor.get_from_mem(o1_i);
    // - Вычисляем
    float real32 = execute(from_mem.word.word32.real32, processor.get_real32(r2_i));
    // - Записываем результат
    processor.set_real32(real32, r2_i);
}

void RealArithmetic::handle_mem_to_mem(Processor &processor) noexcept {
    // - Узнаем адреса памяти
    const address_t o1_i = processor.get_cmd_o1();
    const address_t o2_i = processor.get_cmd_o2();
    // - Потому что сохраняем в память
    data_t new_data;
    // - Берем требуемые данные из памяти
    data_t from_mem_1 = processor.get_from_mem(o1_i);
    data_t from_mem_2 = processor.get_from_mem(o2_i);
    // - Вычисляем
    new_data.word.word32.real32 = execute(
            from_mem_1.word.word32.real32, from_mem_2.word.word32.real32
    );
    // - Отправляем результат по адресу
    processor.push_to_mem(new_data, o2_i);
}