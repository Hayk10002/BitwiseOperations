#include "bit_op.hpp"
#include <iostream>
#include <cassert>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>

int generateRandomNumber(int min, int max) {
    static std::random_device rd;
    static std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(mt);
}


void test_is_power_of_two()
{
    assert(is_power_of_two(1u));
    assert(is_power_of_two(2u));
    assert(is_power_of_two(4u));
    assert(is_power_of_two(8u));
    assert(!is_power_of_two(3u));
    assert(!is_power_of_two(5u));
    assert(!is_power_of_two(6u));
    assert(!is_power_of_two(7u));
}

void test_get_endianness() {
    Endianness e = get_endianness();
    assert(e == Endianness::LittleEndian || e == Endianness::BigEndian);
    // Print for manual verification
    std::cout << "System endianness: " << (e == Endianness::LittleEndian ? "LittleEndian" : "BigEndian") << '\n';
}

void test_xor_swap_unchecked() {
    int a = 5, b = 10;
    xor_swap_unchecked(a, b);
    assert(a == 10 && b == 5);

    // Test for inability to swap with itself
    int x = -3;
    xor_swap_unchecked(x, x);
    assert(x == 0);
}

void test_xor_swap() {
    int a = 5, b = 10;
    xor_swap(a, b);
    assert(a == 10 && b == 5);

    // Test for swap with itself
    int x = -3;
    xor_swap(x, x);
    assert(x == -3);
}

void benchmark_xor_swap_vs_std_swap(int iteration_count) {
    const int size = 1000000;
    std::vector<int> vec1(size);
    std::vector<int> vec2(size);

    volatile int dummy = 0; 

    std::ranges::generate(vec1, []() { return generateRandomNumber(1, 100); });
    std::ranges::generate(vec2, []() { return generateRandomNumber(1, 100); });
    std::chrono::nanoseconds duration_xor{0}, duration_xor_unchecked{0}, duration_std{0};

    for (int i = 0; i < iteration_count; i++)
    {
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < size; ++i) 
            xor_swap(vec1[i], vec2[i]);
        duration_xor += std::chrono::high_resolution_clock::now() - start;

        dummy = vec1[generateRandomNumber(0, size - 1)] + vec2[generateRandomNumber(0, size - 1)]; 
        
        start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < size; ++i) 
        xor_swap_unchecked(vec1[i], vec2[i]);
        duration_xor_unchecked += std::chrono::high_resolution_clock::now() - start;
        
        dummy = vec1[generateRandomNumber(0, size - 1)] + vec2[generateRandomNumber(0, size - 1)]; 
        
        start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < size; ++i) 
        std::swap(vec1[i], vec2[i]);
        duration_std += std::chrono::high_resolution_clock::now() - start;
        
        dummy = vec1[generateRandomNumber(0, size - 1)] + vec2[generateRandomNumber(0, size - 1)]; 
    }
    
    std::cout << "XOR           swap time: " << std::chrono::duration_cast<std::chrono::milliseconds>(duration_xor)           << '\n';
    std::cout << "XOR unchecked swap time: " << std::chrono::duration_cast<std::chrono::milliseconds>(duration_xor_unchecked) << '\n';
    std::cout << "std           swap time: " << std::chrono::duration_cast<std::chrono::milliseconds>(duration_std)           << '\n';
}

int main(int argc, char* argv[])
{
    int iteration_count = 10;
    if (argc > 1) {
        iteration_count = std::stoi(argv[1]);
    }

    test_is_power_of_two();
    test_get_endianness();
    test_xor_swap_unchecked();
    test_xor_swap();

    std::cout << "All tests passed!\n";
    std::cout << "Running benchmarks with iteration count: " << iteration_count << "\n";

    benchmark_xor_swap_vs_std_swap(iteration_count);

    std::cout << "All benchmarks passed!\n";
    return 0;
}
