#include "Movements.h"

void Move::operator()(Processor &processor) noexcept {
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
}

void Move::handle_reg_to_reg(Processor &processor) noexcept {
    const uint8_t r1_i = processor.cmd.r1;
    const uint8_t r2_i = processor.cmd.r2;
    const uint8_t s = processor.cmd.s;
    // - Если 16 бит
    if (s == 0)
    {
        // - Перемещаем 16-битные данные
        set_int16(processor, get_int16(processor, r1_i), r2_i);
        set_uint16(processor, get_uint16(processor, r1_i), r2_i);
    }
    // - Если 32 бит
    else
    {
        // - Перемещаем 32-битные данные
        set_int32(processor, get_int32(processor, r1_i), r2_i);
        set_real32(processor, get_real32(processor, r1_i), r2_i);
    }
}

void Move::handle_reg_to_mem(Processor &processor) noexcept {
    const uint8_t r1_i = processor.cmd.r1;
    const address_t o2_i = processor.cmd.o2;
    const uint8_t s = processor.cmd.s;

    word_t word;
    if (s == 0)
    {
        word.word16->int16 = get_int16(processor, r1_i);
        word.word16->uint16 = get_int16(processor, r1_i);
    }
    else
    {
        word.word32.int32 = get_int32(processor, r1_i);
        word.word32.real32 = get_real32(processor, r1_i);
    }

    processor.memory[o2_i] = {word};
}

void Move::handle_mem_to_reg(Processor &processor) noexcept {
    const address_t o1_i = processor.cmd.o1;
    const uint8_t r2_i = processor.cmd.r2;
    const uint8_t s = processor.cmd.s;

    word_t from_mem = processor.memory[o1_i].word;
    if (s == 0)
    {
        set_int16(processor, from_mem.word16->int16, r2_i);
        set_uint16(processor, from_mem.word16->uint16, r2_i);
    }
    else
    {
        set_int32(processor, from_mem.word32.int32, r2_i);
        set_real32(processor, from_mem.word32.real32, r2_i);
    }
}

void Move::handle_mem_to_mem(Processor &processor) noexcept {
    const address_t o1_i = processor.cmd.o1;
    const address_t o2_i = processor.cmd.o2;

    word_t word_1 = processor.memory[o1_i].word;
    processor.memory[o2_i] = {word_1};
}