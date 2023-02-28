#include <iostream>
#include "includes/stub/stub.h"
using namespace std;

int main(int argc, char* argv[]) {
    std::cout << "Number of arguments: " << argc << std::endl;
    std::cout << "Program name: " << argv[0] << std::endl;
    if(argc < 2)
    {
        cout << "not enough of argument" << endl;
        return 0;
    }
    for (int i = 1; i < argc; i++) {
        std::cout << "Argument " << i << ": " << argv[i] << std::endl;
    }
    stub();
    return 0;
}
