#include "IO.h"

void Input::operator()(Processor &processor) {
    const uint8_t dd = processor.get_cmd_dd();
    // - Ввод только в регистр!
    // - 1 операнд - регистр/адрес - тип ввода
    // - 2 операнд - регистр - приемник
    // - Разрешенные форматы: регистр-регистр и память-регистр
    if (dd != 0 && dd != 2) {
        throw invalid_io_operation("Неправильный формат операции ввода/вывода!");
    }

    enum in_mode : uint8_t {
        input_int16 = 0,
        input_uint16 = 1,
        input_int32 = 2,
        input_real32 = 3,
    };

    const uint8_t r2_i = processor.get_cmd_r2();
    address_t mode = 0;
    if (dd == 0) {
        mode = processor.get_cmd_o1();
    } else {
        mode = processor.get_cmd_r1();
    }

    switch (mode) {
        case input_int16: {
            int16_t number = 0;
            std::cin >> number;
            processor.regs[r2_i/2-1].word16[r2_i%2].int16 = number;
            break;
        }
        case input_uint16: {
            uint16_t number = 0;
            std::cin >> number;
            processor.regs[r2_i/2-1].word16[r2_i%2].uint16 = number;
            break;
        }
        case input_int32: {
            int32_t number = 0;
            std::cin >> number;
            processor.regs[r2_i/2-1].word32.int32 = number;
            break;
        }
        case input_real32: {
            float number = 0;
            std::cin >> number;
            processor.regs[r2_i/2-1].word32.real32 = number;
            break;
        }
    }
}

void Output::operator()(Processor &processor) {
    const uint8_t dd = processor.get_cmd_dd();
    // - Вывод только из регистра!
    // - 1 операнд - регистр/адрес - тип ввода
    // - 2 операнд - регистр - что выводим
    // - Разрешенные форматы: регистр-регистр и память-регистр
    if (dd != 0 && dd != 2) {
        throw invalid_io_operation("Неправильный формат операции ввода/вывода!");
    }

    enum in_mode : uint8_t {
        output_int16 = 0,
        output_uint16 = 1,
        output_int32 = 2,
        output_real32 = 3,
    };

    const uint8_t r2_i = processor.get_cmd_r2();
    address_t mode = 0;
    if (dd == 0) {
        mode = processor.get_cmd_o1();
    } else {
        mode = processor.get_cmd_r1();
    }

    switch (mode) {
        case output_int16: {
            int16_t number = processor.regs[r2_i/2-1].word16[r2_i%2].int16;
            std::cout << "int16: " << number;
            break;
        }
        case output_uint16: {
            uint16_t number = processor.regs[r2_i/2-1].word16[r2_i%2].uint16;
            std::cout << "uint16: " << number;
            break;
        }
        case output_int32: {
            int32_t number = processor.regs[r2_i/2-1].word32.int32;
            std::cout << "int32: " << number;
            break;
        }
        case output_real32: {
            float number = processor.regs[r2_i/2-1].word32.real32;
            std::cout << "real32: " << number;
            break;
        }
    }
}