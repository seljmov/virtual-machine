#include "Conversions.h"

void Jmp::go_to(Processor &processor) noexcept {
    const uint8_t s = processor.get_cmd_s();
    const uint8_t dd = processor.get_cmd_dd();
    address_t address = 0;

    switch (dd) {
        // - dd = 00: адрес = r1 – это косвенный переход
        case 0: {
            // - Для сокращения выделю индекс сразу
            const uint8_t idx = processor.get_cmd_r1();
            address = processor.get_uint16(idx);
            break;
        }
        // - dd = 01: адрес = o2
        case 1: {
            const address_t o2_i = processor.get_cmd_o2();
            address = processor.get_from_mem(o2_i).word.word16->int16;
            break;
        }
        // - dd = 10: адрес = r2 – это косвенный переход
        case 2: {
            // - Для сокращения выделю индекс сразу
            const uint8_t idx = processor.get_cmd_r2();
            address = processor.get_uint16(idx);
            break;
        }
        // - dd = 11: адрес = r2+o2
        case 3: {
            // - Для сокращения выделю индекс сразу
            const uint8_t idx = processor.get_cmd_r2();
            const address_t o2_i = processor.get_cmd_o2();
            address = processor.get_uint16(idx) + processor.get_from_mem(o2_i).word.word16->int16;
            break;
        }
    }

    address_t _ip = (s == 0) ? address : processor.psw.get_IP() + address;
    processor.psw.set_IP(_ip);
}