#ifndef LOADER_H
#define LOADER_H

#include <filesystem>
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
    // - Так как я на Linux Pop!_OS,
    // - то мне нужен абсолютный путь к файлу :)
    static std::string get_path() noexcept;

    // - Проверка на то, является ли операнд регистром,
    // - Если нет, то это память
    static bool is_register(const std::string& str) noexcept;

    // - Чтение адреса
    static void read_address(std::istringstream& strm, address_t& addr) noexcept;
    // - Чтение целого числа и запись в память
    static void read_integer(std::istringstream& strm, Processor& proc, address_t& addr) noexcept;
    // - Чтение вещественного числа и запись в память
    static void read_real(std::istringstream& strm, Processor& proc, address_t& addr) noexcept;
    // - Чтение команды и запись в память
    static void read_command(std::istringstream& strm, Processor& proc, address_t& addr) noexcept;
    // - Чтение последней команды и запись в память
    static void read_last(std::istringstream& strm, Processor& proc, address_t& addr) noexcept;

    // - Разделение строки на вектор строк
    static std::vector<std::string> split(const std::string& str, char delim);
    // - Удаление пробелов и комментария из вектора
    static void remove_trash(std::vector<std::string>& cmd);
};

#endif // LOADER_H