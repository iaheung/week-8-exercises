#include <iostream>
#include <random>
#include <vector>

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

    const int bins = 101;
    vector<int> histogram(bins, 0);

    for (int i = 0; i < N; i++)
    {
        double x = rand_list[i];
        if (x < -3 || x >= 3)
        {
            continue;
        }

        int idx = static_cast<int>(((x + 3) / 6) * bins);
        histogram[idx]++;
    }

    for(int i = 0; i < bins; i++)
    {
        cout << (-3 + (i + 0.5)*(6.0/bins)) << " " <<  histogram[i] << endl;
    }

    return 0;
}