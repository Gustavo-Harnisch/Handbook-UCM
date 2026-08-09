#include <array>
#include <cstdint>

using Unsigned64 = std::uint64_t;
Unsigned64 multiply_modulo(Unsigned64 first, Unsigned64 second, Unsigned64 modulus) {
  Unsigned64 result = 0;
  while (second > 0) {
    if (second & 1U) {
      result = result >= modulus - first ? result - (modulus - first) : result + first;
    }
    first = first >= modulus - first ? first - (modulus - first) : first + first;
    second >>= 1U;
  }
  return result;
}

Unsigned64 power_modulo(Unsigned64 base, Unsigned64 exponent, Unsigned64 modulus) {
  Unsigned64 result = 1;
  while (exponent > 0) {
    if (exponent & 1U) {
      result = multiply_modulo(result, base, modulus);
    }
    base = multiply_modulo(base, base, modulus);
    exponent >>= 1U;
  }
  return result;
}

bool is_prime(Unsigned64 number) {
  if (number < 2) {
    return false;
  }
  for (const Unsigned64 prime : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
    if (number % prime == 0) {
      return number == prime;
    }
  }
  Unsigned64 odd_part = number - 1;
  int exponent = 0;
  while ((odd_part & 1U) == 0) {
    odd_part >>= 1U;
    ++exponent;
  }
  constexpr std::array<Unsigned64, 7> witnesses{
      2ULL, 325ULL, 9375ULL, 28178ULL, 450775ULL, 9780504ULL, 1795265022ULL};
  for (const Unsigned64 witness : witnesses) {
    if (witness % number == 0) {
      continue;
    }
    Unsigned64 value = power_modulo(witness % number, odd_part, number);
    if (value == 1 || value == number - 1) {
      continue;
    }
    bool reached_minus_one = false;
    for (int iteration = 1; iteration < exponent; ++iteration) {
      value = multiply_modulo(value, value, number);
      if (value == number - 1) {
        reached_minus_one = true;
        break;
      }
    }
    if (!reached_minus_one) {
      return false;
    }
  }
  return true;
}
