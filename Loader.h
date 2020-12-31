#ifndef LOADER_H
#define LOADER_H

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <utility>
#include "Processor.h"

class Loader
{
public:
    static void upload(const std::string& filename, Processor& processor);

private:
    // - Проверка на то, является ли операнд регистром,
    // - Если нет, то это память
    bool is_register(const std::string& str) const noexcept;

    // - Чтение адреса
    void read_address(address_t& addr);
    // - Чтение целого числа и запись в память
    void read_integer(Processor& processor, address_t& address);
    // - Чтение вещественного числа и запись в память
    void read_real(Processor& processor, address_t& address);
    // - Чтение команды и запись в память
    void read_command(Processor& processor, address_t& address);
    // - Чтение последней команды и запись в память
    void read_last(Processor& processor, address_t& address);

    // - Разделение строки на вектор строк
    std::vector<std::string> split(const std::string &s, char delim) const;
    // - Удаление комментария из вектора
    void remove_comment(std::vector<std::string> &code) const;
};

#endif // LOADER_H