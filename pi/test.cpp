#include <iostream>
#include <omp.h>

int main() {
    #ifdef _OPENMP
        std::cout << "OpenMP is supported! Version: " << _OPENMP << std::endl;
    #else
        std::cout << "OpenMP is NOT supported!" << std::endl;
    #endif

    return 0;
}
