#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <string>
#include <exception>
#include <utility>

// - Базовый класс исключения с тектом
class exception_with_text : public std::exception
{
    std::string _what;
public:
    explicit exception_with_text(std::string what) : _what(std::move(what)) {}
    ~exception_with_text() override = default;

    const char* what() const noexcept override
    {
        return _what.c_str();
    }
};

// - Неверный путь к файлу
class invalid_path : public exception_with_text
{
public:
    explicit invalid_path(const std::string &what) : exception_with_text(what) {}
    ~invalid_path() override = default;
};

// - Выход за пределы памяти
class out_of_memory : public exception_with_text
{
public:
    explicit out_of_memory(const std::string &what) : exception_with_text(what) {}
    ~out_of_memory() override = default;
};

// - Деление на ноль
class division_by_zero : public exception_with_text
{
public:
    explicit division_by_zero(const std::string &what) : exception_with_text(what) {}
    ~division_by_zero() override = default;
};

// - Неправильная операция ввода\вывода
class invalid_io_operation : public exception_with_text
{
public:
    explicit invalid_io_operation(const std::string &what) : exception_with_text(what) {}
    ~invalid_io_operation() override = default;
};

#endif // EXCEPTIONS_H