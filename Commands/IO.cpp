#include "IO.h"

void Input::operator()(Processor &processor) {
    const uint8_t dd = processor.cmd.dd;
    // - Ввод только в регистр!
    // - 1 операнд - регистр/адрес - тип ввода
    // - 2 операнд - регистр - приемник
    // - Разрешенные форматы: регистр-регистр и память-регистр
    if (dd != 0 && dd != 2) {
        throw invalid_io_operation("Неправильный формат операции ввода/вывода!");
    }

    // - Тип ввода
    enum in_mode : uint8_t {
        input_int16 = 0,
        input_uint16 = 1,
        input_int32 = 2,
        input_real32 = 3,
    };

    // - Регистр, в который вводим число
    const uint8_t r2_i = processor.cmd.r2;
    // - Узнаем тип ввода
    address_t mode;
    // - Тип может лежать в регистре или в памяти
    if (dd == 0) {
        // - Если в регистре
        const uint8_t r1_i = processor.cmd.r1;
        mode = get_int16(processor, r1_i);
    } else {
        // - Если в памяти
        const address_t o1_i = processor.cmd.o1;
        mode = processor.memory[o1_i].word.word16->int16;
    }

    // - Ввод числа
    switch (mode) {
        case input_int16: {
            int16_t number = 0;
            std::cout << "int16: ";
            std::cin >> number;
            set_int16(processor, number, r2_i);
            break;
        }
        case input_uint16: {
            uint16_t number = 0;
            std::cout << "uint16: ";
            std::cin >> number;
            set_uint16(processor, number, r2_i);
            break;
        }
        case input_int32: {
            int32_t number = 0;
            std::cout << "int32: ";
            std::cin >> number;
            set_int32(processor, number, r2_i);
            break;
        }
        case input_real32: {
            float number = 0;
            std::cout << "real32: ";
            std::cin >> number;
            set_real32(processor, number, r2_i);
            break;
        }
    }
}

void Output::operator()(Processor &processor) {
    const uint8_t dd = processor.cmd.dd;
    // - Вывод только из регистра!
    // - 1 операнд - регистр/адрес - тип ввода
    // - 2 операнд - регистр - что выводим
    // - Разрешенные форматы: регистр-регистр и память-регистр
    if (dd != 0 && dd != 2) {
        throw invalid_io_operation("Неправильный формат операции ввода/вывода!");
    }

    // - Тип вывода
    enum in_mode : uint8_t {
        output_int16 = 0,
        output_uint16 = 1,
        output_int32 = 2,
        output_real32 = 3,
    };

    // - Регистр, из которого выводим число
    const uint8_t r2_i = processor.cmd.r2;
    // - Узнаем тип вывода
    address_t mode;
    // - Тип может лежать в регистре или в памяти
    if (dd == 0) {
        // - Если в регистре
        const uint8_t r1_i = processor.cmd.r1;
        mode = get_int16(processor, r1_i);
    } else {
        // - Если в памяти
        const address_t o1_i = processor.cmd.o1;
        mode = processor.memory[o1_i].word.word16->int16;
    }

    // - Вывод числа
    switch (mode) {
        case output_int16: {
            int16_t number = get_int16(processor, r2_i);
            std::cout << "int16: " << number << "\n";
            break;
        }
        case output_uint16: {
            uint16_t number = get_uint16(processor, r2_i);
            std::cout << "uint16: " << number << "\n";
            break;
        }
        case output_int32: {
            int32_t number = get_int32(processor, r2_i);
            std::cout << "int32: " << number << "\n";
            break;
        }
        case output_real32: {
            float number = get_real32(processor, r2_i);
            std::cout << "real32: " << number << "\n";
            break;
        }
    }
}