#include "Movements.h"

void Move::operator()(Processor &processor) noexcept {
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
}

void Move::handle_reg_to_reg(Processor &processor) noexcept {
    const uint8_t r1_i = processor.get_cmd_r1();
    const uint8_t r2_i = processor.get_cmd_r2();
    const uint8_t s = processor.get_cmd_s();
    // - Если 16 бит
    if (s == 0)
    {
        // - Перемещаем 16-битные данные
        processor.set_int16(processor.get_int16(r1_i), r2_i);
        processor.set_uint16(processor.get_uint16(r1_i), r2_i);
    }
    // - Если 32 бит
    else
    {
        // - Перемещаем 32-битные данные
        processor.set_int32(processor.get_int32(r1_i), r2_i);
        processor.set_real32(processor.get_real32(r1_i), r2_i);
    }
}

void Move::handle_reg_to_mem(Processor &processor) noexcept {
    const uint8_t r1_i = processor.get_cmd_r1();
    const address_t o2_i = processor.get_cmd_o2();
    const uint8_t s = processor.get_cmd_s();

    word_t word;
    if (s == 0)
    {
        word.word16->int16 = processor.get_int16(r1_i);
        word.word16->uint16 = processor.get_int16(r1_i);
    }
    else
    {
        word.word32.int32 = processor.get_int32(r1_i);
        word.word32.real32 = processor.get_real32(r1_i);
    }

    processor.memory[o2_i] = {word};
}

void Move::handle_mem_to_reg(Processor &processor) noexcept {
    const address_t o1_i = processor.get_cmd_o1();
    const uint8_t r2_i = processor.get_cmd_r2();
    const uint8_t s = processor.get_cmd_s();

    word_t from_mem = processor.memory[o1_i].word;
    if (s == 0)
    {
        processor.set_int16(from_mem.word16->int16, r2_i);
        processor.set_uint16(from_mem.word16->uint16, r2_i);
    }
    else
    {
        processor.set_int32(from_mem.word32.int32, r2_i);
        processor.set_real32(from_mem.word32.real32, r2_i);
    }
}

void Move::handle_mem_to_mem(Processor &processor) noexcept {
    const address_t o1_i = processor.get_cmd_o1();
    const address_t o2_i = processor.get_cmd_o2();

    word_t word_1 = processor.memory[o1_i].word;
    processor.memory[o2_i] = {word_1};
}