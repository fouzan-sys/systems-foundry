#include <iostream>
#include <cstdint>


int main() {
    alignas(64) int32_t a = 42;
    alignas(64) int32_t b = 99;


    std::cout << "Value of a: " << a << " | Memory Address: " << &a << "\n";
    std::cout << "Value of b: " << b << " | Memory Address: " << &b << "\n";
    std::cout << "Distance in bytes: " << reinterpret_cast<uintptr_t>(&b) - reinterpret_cast<uintptr_t>(&a) << "\n";
    return 0;
}

