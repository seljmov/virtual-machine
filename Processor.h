#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <iostream>
#include <vector>
#include "PSW.h"
#include "Types.h"
#include "Memory.h"

// - Сделаем выравнивание, чтобы не занимать лишние 6 байта:
// - До выравнивания 304 байта, после - 298
#pragma pack(push, 1)
class Processor
{
public:
    cmd_t cmd;              // - Текущая выполняемая команда
    PSW psw;                // - PSW = IP + FLAGS
    Memory memory;          // - Память
    word_t regs[4];         // - Регистры общего назначения

    Processor();
    ~Processor();

    Processor(const Processor&) = delete;
    Processor(const Processor&&) = delete;
    Processor& operator=(const Processor&) = delete;
    Processor& operator=(const Processor&&) = delete;

    // - Загрузка текущей команды
    // - Внутри используется IP
    void load_curr_cmd() noexcept;
    // - Перезагрузка машины
    void reset() noexcept;
    // - Старт машины
    void run() noexcept;

private:
    // - Массив из указателей на команды
    class Command* commands[32]{nullptr};

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
};
#pragma pack(pop)

#endif // PROCESSOR_H