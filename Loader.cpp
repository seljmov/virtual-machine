#include "Loader.h"

void Loader::upload(const std::string &filename, Processor &processor) {
    std::ifstream file;
    file.open(filename);

    if (!file.is_open()) {
        throw invalid_path("Указан неверный путь к файлу");
    }

    address_t address = 0;
    char symbol = ' ';

    while (symbol != 'e')
    {
        std::string read;
        // - Считываем строку
        getline(file, read);
        std::istringstream istring(read);
        // - Берем префикс и проверяем
        istring >> symbol;

        switch (symbol)
        {
            case 'a':
            {
                break;
            }

            case 'i':
            {
                break;
            }

            case 'r':
            {
                break;
            }

            case 'c':
            {
                break;
            }

            case 'e':
            {
                break;
            }
        }
    }

    file.clear();
    file.close();
}

bool Loader::is_register(const std::string &str) const noexcept {
    // - Максимальный номер регистра 8, поэтому вид операнда: %%8
    // - Достаточно проверить, что первые два символа = %,
    // - а третий символ = цифра
    // - Проверка префикса
    bool prefix = ((str[0] == '%') && (str[1] == '%'));
    // - Проверка цифры
    bool digit = isdigit(str[2]);
    return (prefix && digit);
}

void Loader::read_address(std::istringstream &strm, address_t &addr) const noexcept {
    strm >> addr;
}

void Loader::read_integer(std::istringstream &strm, Processor &proc, address_t &addr) const noexcept {
    word_t word;
    uint8_t s;
    strm >> s;
    // - Если размер 16 бит
    if (s == 0) strm >> word.word16->int16;
    // - Иначе 32 бита
    else strm >> word.word32.int32;
    proc.push_to_mem({word, }, addr);
    ++addr;
}

void Loader::read_real(std::istringstream &strm, Processor &proc, address_t &addr) const noexcept {
    word_t word;
    strm >> word.word32.real32;
    proc.push_to_mem({word, }, addr);
    ++addr;
}

void Loader::read_command(std::istringstream &strm, Processor &proc, address_t &addr) const noexcept {
    cmd_t command;

    // - Получаем вектор строк, где каждый элемент = элемент команды
    std::vector<std::string> _cmd = split(strm.str(), ' ');
    // - Удаляем префикс
    _cmd.erase(_cmd.begin());
    // - Удаляем комментарий, если он есть
    remove_comment(_cmd);

    command.code = uint8_t(std::stoi(_cmd[0]));
    command.s = uint8_t(std::stoi(_cmd[1]));
    command.dd = uint8_t(std::stoi(_cmd[2]));

    // - Проверка операндов
    // - %%1 - регистр
    // - %1 - память
    // - Первый операнд
    std::string f_operand = _cmd[3];
    // - Если регистр
    if (is_register(f_operand))
    {
        f_operand = f_operand.substr(2);
        command.r1 = uint8_t(std::stoi(f_operand));
    }
    // - Иначе память
    else
    {
        f_operand = f_operand.substr(1);
        command.o1 = uint8_t(std::stoi(f_operand));
    }

    // - Второй операнд
    std::string s_operand = _cmd[3];
    // - Если регистр
    if (is_register(s_operand))
    {
        s_operand = s_operand.substr(2);
        command.r1 = uint8_t(std::stoi(s_operand));
    }
    // - Иначе память
    else
    {
        s_operand = s_operand.substr(1);
        command.o1 = uint8_t(std::stoi(s_operand));
    }

    data_t to_mem;
    to_mem.cmd = command;
    proc.push_to_mem(to_mem, addr);
    ++addr;
}

void Loader::read_last(std::istringstream &strm, Processor &proc, address_t &addr) const noexcept {
    data_t data;
    data.cmd.code = 0;
    proc.push_to_mem(data, addr);
    address_t IP;
    strm >> IP;
    proc.psw.set_IP(IP);
}

std::vector<std::string> Loader::split(const std::string &str, char delim) const {
    std::vector<std::string> elems;
    std::stringstream string(str);
    std::string item;
    while (getline(string, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

void Loader::remove_comment(std::vector<std::string> &cmd) const {
    for (auto i = cmd.size()-1; i >= 0; --i) {
        if (cmd[i] == ";") {
            cmd.erase(cmd.begin()+i, cmd.end());
            break;
        }
    }
}