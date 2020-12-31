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

    std::swap(processor.regs[r1_i], processor.regs[r2_i]);
}

void Move::handle_reg_to_mem(Processor &processor) noexcept {
    const uint8_t r1_i = processor.get_cmd_r1();
    const address_t o2_i = processor.get_cmd_o2();

    word_t word = processor.regs[r1_i];
    processor.regs[r1_i] = processor.get_from_mem(o2_i).word;
    processor.push_to_mem({word, }, o2_i);
}

void Move::handle_mem_to_reg(Processor &processor) noexcept {
    const address_t o1_i = processor.get_cmd_o1();
    const uint8_t r2_i = processor.get_cmd_r1();

    word_t word = processor.regs[r2_i];
    processor.regs[r2_i] = processor.get_from_mem(o1_i).word;
    processor.push_to_mem({word, }, o1_i);
}

void Move::handle_mem_to_mem(Processor &processor) noexcept {
    const address_t o1_i = processor.get_cmd_o1();
    const address_t o2_i = processor.get_cmd_o2();

    word_t word_1 = processor.get_from_mem(o1_i).word;
    word_t word_2 = processor.get_from_mem(o2_i).word;
    processor.push_to_mem({word_1, }, o2_i);
    processor.push_to_mem({word_2, }, o1_i);
}