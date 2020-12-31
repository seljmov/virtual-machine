#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <iostream>
#include <vector>
#include "PSW.h"
#include "Types.h"
#include "Memory.h"

// - Доступные операции
enum Operations : uint8_t
{
    stop = 0,       // - Остановка работы процессора
    // - Мне достаточно иметь один mov,
    // - Так как в структуре команды присутствует dd - Формат операнда
    move = 1,       // - Пересылка данных*

    // - Целочиленная арифметика
    iAdd = 2,       // - Сложение целых чисел
    iSub = 3,       // - Вычитание целых чисел
    iMul = 4,       // - Умножение целых чисел
    iDiv = 5,       // - Деление целых чисел
    iMod = 6,       // - Остаток от деления
    iInc = 7,       // - Инкремент
    iDec = 8,       // - Декремент
    iAnd = 9,       // - Логическое И
    iOr = 10,       // - Логическое ИЛИ
    iNot = 11,      // - Логическое НЕ

    // - Вещественная арифметика
    rAdd = 12,      // - Сложение вещественных чисел
    rSub = 13,      // - Вычитание вещественных чисел
    rMul = 14,      // - Умножение вещественных чисел
    rDiv = 15,      // - Деление вещественных чисел

    // - Команды ввода/вывода
    input = 16,     // - Ввод чисел
    output = 17,    // - Вывод чисел

    // - Переходы
    jmp = 20,       // - Прямой безусловный переход
    jzf = 21,       // - Jump in ZF = 1
    jnzf = 22,      // - Jump in ZF = 0
    jsf = 23,       // - Jump in SF = 1
    jnsf = 24,      // - Jump in SF = 0

    // - Работа с подпрограммой
    call = 25,      // - Вызов подпрограммы
    ret = 26,       // - Возврат из подпрограммы
};

class Processor
{
public:
    PSW psw;                // - PSW = IP + FLAGS
    Memory memory;          // - Память
    word_t regs[4];         // - Регистры общего назначения
    // - 8(int16+uint16), 4(int32), 4(float)

    Processor();
    ~Processor();

    Processor(const Processor&) = delete;
    Processor(const Processor&&) = delete;
    Processor& operator=(const Processor&) = delete;
    Processor& operator=(const Processor&&) = delete;

    // - Работа с памятью
    // - Получить данные из памяти
    data_t get_from_mem(const address_t& addr) const noexcept;
    // - Положить данные в память
    void push_to_mem(const data_t& data, const address_t& addr) noexcept;

    // - Работа с регистрами
    // - Получить из указанного регистра int16
    int16_t get_int16(const uint8_t& _reg) const;
    // - Получить из указанного регистра uint16
    uint16_t get_uint16(const uint8_t& _reg) const;
    // - Получить из указанного регистра int32
    int32_t get_int32(const uint8_t& _reg) const;
    // - Получить из указанного регистра real32
    float get_real32(const uint8_t& _reg) const;

    // - Положить в указанный регистр int16
    void set_int16(const int16_t& int16, const uint8_t& _reg);
    // - Положить в указанный регистр uint16
    void set_uint16(const uint16_t& uint16, const uint8_t& _reg);
    // - Положить в указанный регистр int32
    void set_int32(const int32_t& int32, const uint8_t& _reg);
    // - Положить в указанный регистр real32
    void set_real32(const float& real32, const uint8_t& _reg);

    // - Получить код команды
    inline uint8_t   get_cmd_code() const noexcept { return cmd.code; }
    // - Получить размер операнда
    inline uint8_t   get_cmd_s() const noexcept { return cmd.s; }
    // - Получить формат операндов
    inline uint8_t   get_cmd_dd() const noexcept { return cmd.dd; }
    // - Получить номер первого регистра
    inline uint8_t   get_cmd_r1() const noexcept { return cmd.r1; }
    // - Получить номер второго регистра
    inline uint8_t   get_cmd_r2() const noexcept { return cmd.r2; }
    // - Получить адрес первой ячейки памяти
    inline address_t get_cmd_o1() const noexcept { return cmd.o1; }
    // - Получить адрес второй ячейки памяти
    inline address_t get_cmd_o2() const noexcept { return cmd.o2; }

    // - Загрузка текущей команды
    // - Внутри используется IP
    void load_curr_cmd() noexcept;
    // - Перезагрузка машины
    void reset() noexcept;
    // - Старт машины
    void run() noexcept;

private:
    // - Текущая выполняемая команда
    cmd_t cmd;
    // - Массив из указателей на команды
    class Command* commands[32]{nullptr};

    // - Методы проверки кидают исключения
    // - Проверка номера 16-битного регистра
    static void verify_register_16bit(const uint8_t& _reg);
    // - Проверка номера 32-битного регистра
    static void verify_register_32bit(const uint8_t& _reg);
};

#endif // PROCESSOR_H