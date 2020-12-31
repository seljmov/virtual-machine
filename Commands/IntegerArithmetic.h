#ifndef INTEGERARITHMETIC_H
#define INTEGERARITHMETIC_H

#include "Command.h"

class IntegerArithmetic : public Command
{
protected:
    void operator()(Processor& processor) override;
    // - Есть команды, где второй параметр не нужен,
    // - поэтому сделаю его нулем по умолчанию
    virtual int execute(int var1, int var2 = 0) = 0;

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

// - Целочисленное сложение
class iAdd : public IntegerArithmetic
{
    int execute(int var1, int var2) final {
        return (var1 + var2);
    }
};

// - Целочисленное вычитание
class iSub : public IntegerArithmetic
{
    int execute(int var1, int var2) final {
        return (var1 - var2);
    }
};

// - Целочисленное умножение
class iMul : public IntegerArithmetic
{
    int execute(int var1, int var2) final {
        return (var1 * var2);
    }
};

// - Целочисленное деление
class iDiv : public IntegerArithmetic
{
    int execute(int var1, int var2) final {
        if (var2 == 0) {
            throw division_by_zero("Деление на ноль невозможно!");
        }
        return (var1 / var2);
    }
};

// - Остаток от деления
class iMod : public IntegerArithmetic
{
    int execute(int var1, int var2) final {
        return (var1 % var2);
    }
};

// - Инкремент
class iInc : public IntegerArithmetic
{
    int execute(int var1, int var2) final {
        return (var1 + 1);
    }
};

// - Декремент
class iDec : public IntegerArithmetic
{
    int execute(int var1, int var2) final {
        return (var1 - 1);
    }
};

// - Логическое И
class iAnd : public IntegerArithmetic
{
    int execute(int var1, int var2) final {
        return (var1 & var2);
    }
};

// - Логическое ИЛИ
class iOr : public IntegerArithmetic
{
    int execute(int var1, int var2) final {
        return (var1 | var2);
    }
};

// - Логическое НЕ
class iNot : public IntegerArithmetic
{
    int execute(int var1, int var2) final {
        return (~var1);
    }
};

#endif // INTEGERARITHMETIC_H