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
