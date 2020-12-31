#ifndef REALARITHMETIC_H
#define REALARITHMETIC_H

#include "Command.h"

// - Дробная арифметика отличается тем, что в структуре
// - команды не требуется узнавать формат операндов (s)

class RealArithmetic : public Command
{
protected:
    void operator()(Processor& processor) override;
    virtual float execute(float var1, float var2) = 0;

private:
    // - Устновка флагов
    static void set_flags(Processor& processor) noexcept;
    // - Обработка команды типа Регистр-Регистр (dd = 00/0)
    void handle_reg_to_reg(Processor& processor) noexcept;
    // - Обработка команды типа Регистр-Память (dd = 01/1)
    void handle_reg_to_mem(Processor& processor) noexcept;
    // - Обработка команды типа Память-Регистр (dd = 10/2)
    void handle_mem_to_reg(Processor& processor) noexcept;
    // - Обработка команды типа Память-Память (dd = 11/3)
    void handle_mem_to_mem(Processor& processor) noexcept;
};

// - Вещественное сложение
class rAdd : public RealArithmetic
{
    float execute(float var1, float var2) final {
        return (var1 + var2);
    }
};

// - Вещественное вычитание
class rSub : public RealArithmetic
{
    float execute(float var1, float var2) final {
        return (var1 - var2);
    }
};

// - Вещественное умножение
class rMul : public RealArithmetic
{
    float execute(float var1, float var2) final {
        return (var1 * var2);
    }
};

// - Вещественное деление
class rDiv : public RealArithmetic
{
    float execute(float var1, float var2) final {
        if (var2 == 0) {
            throw division_by_zero("Деление на ноль невозможно!");
        }
        return (var1 / var2);
    }
};

#endif // REALARITHMETIC_H