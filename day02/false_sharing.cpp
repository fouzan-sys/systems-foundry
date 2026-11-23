#include <iostream>
#include <thread>
#include <chrono>
#include <cstdint>


struct PackedCounters {
    volatile int64_t a = 0;
    volatile int64_t b = 0;
};


struct AlignedCounters {
    alignas(64) volatile int64_t a = 0;
    alignas(64) volatile int64_t b = 0;
};


template <typename T>
long long benchmark(const char* label) {
    T counters;
    auto start = std::chrono::high_resolution_clock::now();


    std::thread t1([&]() { for (int i = 0; i < 100'000'000; ++i) counters.a++; });
    std::thread t2([&]() { for (int i = 0; i < 100'000'000; ++i) counters.b++; });


    t1.join();
    t2.join();


    auto end = std::chrono::high_resolution_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << label << ": " << ms << " ms\n";
    return ms;
}


int main() {
    benchmark<PackedCounters>("1. Packed (False Sharing) ");
    benchmark<AlignedCounters>("2. Aligned (alignas(64)) ");
    return 0;
}
