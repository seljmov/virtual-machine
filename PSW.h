#ifndef PSW_H
#define PSW_H

#include <iostream>

class PSW
{
    uint8_t ZF : 1;             // - Флаг нуля
    uint8_t SF : 1;             // - Флаг знака
    uint16_t reserved : 14;     // - В резерве
    uint16_t IP;                // - Указатель инструкции

public:
    PSW() : ZF(0), SF(0), IP(0) {}

    inline uint16_t get_IP() const noexcept { return IP; }
    inline uint8_t get_ZF() const noexcept { return ZF; }
    inline uint8_t get_SF() const noexcept { return SF; }

    inline void set_IP(uint16_t addr) noexcept { IP = addr; };
    inline void set_ZF(int8_t i) noexcept { ZF = (i != 0); }
    inline void set_SF(int8_t i) noexcept { SF = (i != 0); }

    inline void reset_flags() noexcept { ZF = SF = 0; }
};

#endif // PSW_H