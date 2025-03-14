#include <iostream>
#include <random>
#include <vector>
#include <omp.h>

using namespace std;

// Function to add two vectors element-wise
void addVectors(vector<int> &vout, vector<int> &vin) {
    for (size_t i = 0; i < vout.size(); i++) {
        vout[i] += vin[i];
    }
}

// Declare OpenMP custom reduction for std::vector<int>
#pragma omp declare reduction(vectorSum : vector<int> : addVectors(omp_out, omp_in)) \
    initializer(omp_priv = vector<int>(omp_orig.size(), 0))

int main()
{
    mt19937_64 rng(42);
    normal_distribution<double> dist(0, 1);

    const int N = 100000;
    vector<double> rand_list(N);
    
    for(int i = 0; i < N; i++) {
        rand_list[i] = dist(rng);
    }

    const unsigned int bins = 101;
    vector<int> histogram(bins, 0); // Use std::vector<int> instead of C array

    // Parallel loop with OpenMP custom reduction
    #pragma omp parallel for reduction(vectorSum:histogram)
    for (int i = 0; i < N; i++)
    {
        double x = rand_list[i];
        if (x < -3 || x >= 3) {
            continue;
        }

        int idx = static_cast<int>(((x + 3) / 6) * bins);
        histogram[idx]++;
    }

    // Print histogram
    for(size_t i = 0; i < bins; i++) {
        cout << (-3 + (i + 0.5) * (6.0 / bins)) << " " << histogram[i] << endl;
    }

    return 0;
}
