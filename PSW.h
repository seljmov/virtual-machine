#ifndef PSW_H
#define PSW_H

#include <iostream>

class PSW
{
public:
    uint8_t ZF : 1;             // - Флаг нуля
    uint8_t SF : 1;             // - Флаг знака
    uint16_t reserved : 14;     // - В резерве
    uint16_t IP;                // - Указатель инструкции

    PSW() : ZF(0), SF(0), IP(0) {}

    // - Если 1, то число == 0, иначе если 0, то число != 0
    inline void set_ZF(int32_t i) noexcept { ZF = (i == 0); }
    // - Если 1, то число < 0, иначе если 0, то число >= 0
    inline void set_SF(int32_t i) noexcept { SF = (i < 0); }

    inline void reset_flags() noexcept { ZF = SF = 0; }
};

#endif // PSW_H