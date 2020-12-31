#ifndef LOADER_H
#define LOADER_H

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <utility>
#include <cstring>
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
    void read_address(std::istringstream& strm, address_t& addr) const noexcept;
    // - Чтение целого числа и запись в память
    void read_integer(std::istringstream& strm, Processor& proc, address_t& addr) const noexcept;
    // - Чтение вещественного числа и запись в память
    void read_real(std::istringstream& strm, Processor& proc, address_t& addr) const noexcept;
    // - Чтение команды и запись в память
    void read_command(std::istringstream& strm, Processor& proc, address_t& addr) const noexcept;
    // - Чтение последней команды и запись в память
    void read_last(std::istringstream& strm, Processor& proc, address_t& addr) const noexcept;

    // - Разделение строки на вектор строк
    std::vector<std::string> split(const std::string& str, char delim) const;
    // - Удаление комментария из вектора
    void remove_comment(std::vector<std::string>& cmd) const;
};

#endif // LOADER_H