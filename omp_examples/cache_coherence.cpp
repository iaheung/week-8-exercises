#include <iostream>
#include <vector>
#include <cmath>
#include "timer.hpp"
#include <omp.h>

using namespace std;

int main() {
  const long N =   1'000'000'000;
  const double dx = 1.0f/(N-1);
  const int num_threads = omp_get_max_threads();

  double sum = 0.;

  vector<double> partial_sums(num_threads, 0.0);

  Timer timer;

  #pragma omp parallel
  {
    int n = omp_get_thread_num();

    #pragma omp for
    for(long i=0; i<N; ++i) {
      double x = i*dx;
      partial_sums[n] += 4.0f/(1.0f + x*x)*dx;
    }
  }

  for(int i = 0; i < num_threads; i++)
  {
    sum += partial_sums[i];
  }

  double elapsed = timer.elapsed();

  std::cout << "Time: " << elapsed << '\n';
  std::cout << "Result: " << sum << '\n';

  return 0;
}
