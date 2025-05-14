#pragma once
#include <concepts>

bool is_power_of_two(std::unsigned_integral auto n)
{
    return n && !(n & (n - 1));
}

enum class Endianness {LittleEndian, BigEndian};
using enum Endianness;
Endianness get_endianness()
{
    int num = 1;
    return Endianness(*(char*)&num != 1);
}

void xor_swap_unchecked(std::integral auto& a, std::integral auto& b)
{
    a ^= b;
    b ^= a;
    a ^= b;
}

void xor_swap(std::integral auto& a, std::integral auto& b)
{
    if (a == b) return;
    xor_swap_unchecked(a, b);
}