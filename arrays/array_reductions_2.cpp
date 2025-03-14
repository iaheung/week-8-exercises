#include <iostream>
#include <random>
#include <vector>
#include <omp.h>

using namespace std;

int main()
{
    mt19937_64 rng(42);
    normal_distribution<double> dist(0, 1);

    const int N = 100000;
    vector<double> rand_list(N);
    
    for(int i = 0; i < N; i++)
    {
        rand_list[i] = dist(rng);
    }

    const unsigned int bins = 101;
    vector<int> histogram(bins, 0); // Use std::vector<int> instead of C array

    // Parallel loop
    #pragma omp parallel
    {
        vector<int> local_histogram(bins, 0); // Private histogram per thread

        #pragma omp for nowait
        for (int i = 0; i < N; i++)
        {
            double x = rand_list[i];
            if (x < -3 || x >= 3)
            {
                continue;
            }

            int idx = static_cast<int>(((x + 3) / 6) * bins);
            local_histogram[idx]++;
        }

        // Merge local histograms into the global histogram
        #pragma omp critical
        {
            for (size_t i = 0; i < bins; i++)
            {
                histogram[i] += local_histogram[i];
            }
        }
    }

    // Print histogram
    for(size_t i = 0; i < bins; i++)
    {
        cout << (-3 + (i + 0.5) * (6.0 / bins)) << " " << histogram[i] << endl;
    }

    return 0;
}
