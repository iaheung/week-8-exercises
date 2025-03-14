# OpenMP Basics

Example:
```cpp
int x = 1;

#pragma omp parallel
{ // make threads
    int y = x * 4;
} // join threads

// y is destroyed after the loop
```

New example with for loops, divide up work in for loop:

```cpp
N = some value;

#pragma omp parallel
{
    #pragma omp for
    for (size_t i = 0; i < N; i++)
    {
        y[i] = f(x[i]);
    }
}
```


This becomes a problem for something like this:

```cpp
int f0 = 1;
int f1 = 1;

// loop needs to be sequential
for (int i = 1; 1 < N; i++){
    int f2 = f1 + f0;

    f2 = f1
    f1 = f0
}
```


# Data Races
What happens when parallel processes want to write to same location at the same time? Things can overwrite each other?

Reduction: General Example
Sums or products are typical examples

This would be quite slow actually, and would likely give the wrong answer. 
Threads compete and overwrite and read from outdated data.
Lots of clashes in resources.

```cpp
const size_t n = 100000000;
vector<double> v(N,1e-6);

double sum = 0;

#pragma omp parallel for
for (size_t i =0; i < N; i++;)
{
    sum += x[i];
}
```

How to resolve data race problems? Can state code block only can be executed one thread at a time manually.
This prevents data races. 

```cpp
const size_t n = 100000000;
vector<double> v(N,1e-6);

double sum = 0;

#pragma omp parallel for
for (size_t i =0; i < N; i++;)
{
    #pragma omp atomic
    sum += x[i];
}
```
This gives us the right answer, but it has these access overheads that serial behaviour already does, and it can slow our code down.

OpenMP can help this with reduction:

+ sign indicates addition, change to other symbol if needed
reduction(+:variable_to_update)

```cpp
const size_t n = 100000000;
vector<double> v(N,1e-6);

double sum = 0;

#pragma omp parallel for reduction(+:sum)
for (size_t i =0; i < N; i++;)
{
    sum += x[i];
}
```

How does it do this? It is similiar to batches? 

```cpp
const size_t N = 100000000;
vector<double> v(N,1e-6);

double sum = 0;

#pragma omp parallel
{
    double partial_sum;
    #pragma omp for
    for (size_t i = 0; i < N; i++){
        partial_sum += v[i];
    }

    #pragma omp atomic
    sum += partial_sum;
}
```

We have to be proactive in preventing data races and what stuff we give our threads access to.

What is static, dynamic, guided schedule clause for pragma omp in OpenMP?

When using #pragma omp for, OpenMP allows us to control how loop iterations are distributed among threads using the schedule clause. The three most common scheduling strategies are:
- Static Scheduling (schedule(static, chunk_size))
- Dynamic Scheduling (schedule(dynamic, chunk_size))
- Guided Scheduling (schedule(guided, chunk_size))

# Nested Loops and Collapse
```cpp
#pragma omp parallel for collapse(2)
for (int i = 0; i < N; i++){
    for (int j = 0; j < N; j++){
        // stuff in loop
    }
}
```

# Scaling of Performance
Number of threads should theoretically be linearly related to computation speed (eg. 4 threads 2 times faster than 2 threads), but this is not physically true. 

# Different Parallization and Combination Methods:
| **Feature**                       | **OpenMP Array Reduction (`reduction(+:)`)** | **Manual Local Histogram (`#pragma omp critical`)** | **Custom OpenMP Reduction (`vectorSum`)** |
|-----------------------------------|----------------------------------------------|------------------------------------------------|------------------------------------------|
| **Histogram Storage**              | Threads keep **private arrays**, merge at end | Threads keep **local histograms**, merge **one by one** | Threads keep **local histograms**, merge **progressively** |
| **Merging Strategy**               | **All threads finish first**, then merge | **Each thread merges individually** when done | **Threads merge in parallel** while others still compute |
| **Thread Synchronization**         | Threads **must finish before merging** | Threads **must wait for critical section** | **No waiting**, OpenMP **handles merging progressively** |
| **Bottleneck?**                    | ✅ **Yes**, waiting for all threads to finish | ✅ **Yes**, only one thread can merge at a time | ❌ **No**, OpenMP merges results efficiently |
| **Performance Impact**             | **Slows down if many threads finish at different times** | **Slows down as threads queue up for merging** | **Fastest, as merging is parallelized** |
| **Ease of Implementation**         | ✅ **Easiest**, built into OpenMP | ❌ **Manual merging required** | ❌ **Requires custom OpenMP reduction function** |
| **Best for Small Data?**           | ✅ Works well | ✅ Works well | ✅ Works well |
| **Best for Large Data?**           | ❌ Not scalable (waiting time increases) | ❌ Not scalable (threads queue up) | ✅ **Best for large-scale problems** |



# Coursework 2

Week 8 and Week 9 most important
Subgrids need to communicate with each other, different sections of memory need to communicate with each other somehow with some sort of messaging (Week 9 content)

