#include <iostream>
#include <chrono>
#include <cmath>
#include <omp.h>

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::milliseconds;

int main() {
    const int N = 800000000;
    double dx = 1.0 / N;

    // ==============================
    // 🚀 Serial Version
    // ==============================
    auto start_serial = high_resolution_clock::now();

    double sum_serial = 0.0;
    for (int i = 0; i < N; ++i) {
        double x = i * dx;
        sum_serial += 4.0 / (1.0 + x * x) * dx;
    }

    auto stop_serial = high_resolution_clock::now();
    auto duration_serial = duration_cast<milliseconds>(stop_serial - start_serial);

    std::cout << "==== SERIAL VERSION ====\n";
    std::cout << "Result: " << sum_serial << std::endl;
    std::cout << "Time for " << N << " iterations: " << duration_serial.count() << " ms\n\n";

    // ==============================
    // 🚀 Parallel Version (Fixed)
    // ==============================
    auto start_parallel = high_resolution_clock::now();

    double sum_parallel = 0.0;
    #pragma omp parallel for reduction(+:sum_parallel)
    for (int i = 0; i < N; ++i) {
        double x = i * dx;
        sum_parallel += 4.0 / (1.0 + x * x) * dx;
    }

    auto stop_parallel = high_resolution_clock::now();
    auto duration_parallel = duration_cast<milliseconds>(stop_parallel - start_parallel);

    std::cout << "==== PARALLEL VERSION ====\n";
    std::cout << "Result: " << sum_parallel << std::endl;
    std::cout << "Time for " << N << " iterations: " << duration_parallel.count() << " ms\n";

    // ==============================
    // 🚀 Speedup Calculation
    // ==============================
    double speedup = static_cast<double>(duration_serial.count()) / duration_parallel.count();
    std::cout << "\nSpeedup: " << speedup << "x\n";

    return 0;
}
