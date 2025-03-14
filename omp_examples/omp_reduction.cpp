#include <random>
#include <vector>
#include <iostream>
#include <chrono>

using std::vector;
typedef std::chrono::high_resolution_clock myClock;

double t_seconds(std::chrono::time_point<myClock> t1, std::chrono::time_point<myClock> t2)
{
    return (t2 - t1).count() / 1e9;
}

int main()
{
    const size_t N = 100'000'000;
    vector<double> v(N, 1e-6);

    double sum = 0;

    //sum it up 
    auto t1 = myClock::now();

#pragma omp parallel for
    for (size_t i = 0; i < N; i++)
    {
        sum += v[i];
    }

    auto t2 = myClock::now();

    std::cout << sum << " in " << t_seconds(t1, t2) << "s" << std::endl;
}