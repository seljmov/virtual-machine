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
    virtual ~exception_with_text() override = default;

    const char* what() const noexcept final
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

// - Неправильная операция ввода\вывода
class invalid_io_operation : public exception_with_text
{
public:
    explicit invalid_io_operation(const std::string &what) : exception_with_text(what) {}
    ~invalid_io_operation() override = default;
};

// - Неправильный номер регистра
class invalid_register : public exception_with_text
{
public:
    explicit invalid_register(const std::string &what) : exception_with_text(what) {}
    ~invalid_register() override = default;
};

#endif // EXCEPTIONS_H