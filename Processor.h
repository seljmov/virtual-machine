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
    input = 16,       // - Ввод чисел
    output = 17,      // - Вывод чисел

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

    data_t get_from_mem(const address_t& addr) const noexcept;
    void push_to_mem(const data_t& data, const address_t& addr) noexcept;

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
    class Command* command[32]{nullptr};
};

#endif // PROCESSOR_H