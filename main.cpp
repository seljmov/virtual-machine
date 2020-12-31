#include <iostream>
#include <filesystem>
#include "Processor.h"
#include "Loader.h"

using namespace std;

string getPath()
{
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
    string filename = getPath() + "/demo/move.txt";

    Loader::upload(filename, processor);
    processor.run();

    return 0;
}