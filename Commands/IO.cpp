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
        const uint8_t r1_i = processor.get_cmd_r1();
        mode = processor.get_int16(r1_i);
    } else {
        const address_t o1_i = processor.get_cmd_o1();
        mode = processor.get_from_mem(o1_i).word.word16->int16;
    }

    switch (mode) {
        case input_int16: {
            int16_t number = 0;
            std::cin >> number;
            processor.set_int16(number, r2_i);
            break;
        }
        case input_uint16: {
            uint16_t number = 0;
            std::cin >> number;
            processor.set_uint16(number, r2_i);
            break;
        }
        case input_int32: {
            int32_t number = 0;
            std::cin >> number;
            processor.set_int32(number, r2_i);
            break;
        }
        case input_real32: {
            float number = 0;
            std::cin >> number;
            processor.set_real32(number, r2_i);
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
        const uint8_t r1_i = processor.get_cmd_r1();
        mode = processor.get_int16(r1_i);
    } else {
        const address_t o1_i = processor.get_cmd_o1();
        mode = processor.get_from_mem(o1_i).word.word16->int16;
    }

    switch (mode) {
        case output_int16: {
            int16_t number = processor.get_int16(r2_i);
            std::cout << "int16: " << number;
            break;
        }
        case output_uint16: {
            uint16_t number = processor.get_uint16(r2_i);
            std::cout << "uint16: " << number;
            break;
        }
        case output_int32: {
            int32_t number = processor.get_int32(r2_i);
            std::cout << "int32: " << number;
            break;
        }
        case output_real32: {
            float number = processor.get_real32(r2_i);
            std::cout << "real32: " << number;
            break;
        }
    }
}