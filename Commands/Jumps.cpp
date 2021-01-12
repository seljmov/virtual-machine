#include "Jumps.h"

void Jumps::go_to(Processor &p) noexcept {
    const uint8_t s = p.cmd.s;
    const uint8_t dd = p.cmd.dd;
    address_t address = 0;

    switch (dd) {
        // - dd = 00: адрес = r1 – это косвенный переход
        case 0: {
            // - Для сокращения выделю индекс сразу
            const uint8_t idx = p.cmd.r1;
            address = get_uint16(p, idx);
            break;
        }
        // - dd = 01: адрес = o2
        case 1: {
            const address_t o2_i = p.cmd.o2;
            address = p.memory[o2_i].word.word16->int16;
            break;
        }
        // - dd = 10: адрес = r2 – это косвенный переход
        case 2: {
            // - Для сокращения выделю индекс сразу
            const uint8_t idx = p.cmd.r2;
            address = get_uint16(p, idx);
            break;
        }
        // - dd = 11: адрес = r2+o2
        case 3: {
            // - Для сокращения выделю индекс сразу
            const uint8_t idx = p.cmd.r2;
            const address_t o2_i = p.cmd.o2;
            address = get_uint16(p, idx) + p.memory[o2_i].word.word16->int16;
            break;
        }
    }

    address_t _ip = (s == 0) ? address : p.psw.IP + address;
    p.psw.IP = _ip;
}
