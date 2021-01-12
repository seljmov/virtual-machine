#include <iostream>
#include <filesystem>
#include "Processor.h"
#include "Loader.h"

using namespace std;

// - Так как я на Linux Pop!_OS,
// - то мне нужен абсолютный путь к файлу :)
string get_path()
{
    // - Получаю абсолютный путь
    string path = filesystem::current_path();
    // - Так как у меня Cmake, то исполняемый файл находится в папке
    // - cmake-build-debug, поэтому я обрезаю этот каталог из пути
    for (size_t i = path.size()-1; i >= 0; --i) {
        if (path[i] == '/') {
            path = path.substr(0, i);
            break;
        }
    }
    return path;
}

int main()
{
    Processor processor;
    string filename = get_path() + "/demo/imath.txt";

    Loader::upload(filename, processor);
    processor.run();

    return 0;
}