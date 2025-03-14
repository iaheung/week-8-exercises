#include <iostream>

int main()
{
    // fib
    int f0 = 1;
    int f1 = 1;

    #pragma omp parallel for
    for (int i = 0; i < 10; i++)
    {
        // new fib value
        int f2 = f1 + f0;
        // update old values
        f0 = f1;
        f1 = f2;
    }
    std::cout << f0 << " " << f1 << std::endl;

    return 0;
}