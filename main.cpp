#include "Processor.h"
#include "Loader.h"

using namespace std;

int main()
{
    Processor processor;
    string filename = "/demo/imath.txt";

    Loader::upload(filename, processor);
    processor.run();

    return 0;
}