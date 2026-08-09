#include <limits>
#include <optional>
#include <utility>

long long add_modulo(long long first, long long second, long long modulus) {
  if (modulus == 1) {
    return 0;
  }
  return first >= modulus - second ? first - (modulus - second) : first + second;
}

long long multiply_modulo(long long first, long long second, long long modulus) {
  long long result = 0;
  while (second > 0) {
    if (second & 1LL) {
      result = add_modulo(result, first, modulus);
    }
    first = add_modulo(first, first, modulus);
    second >>= 1LL;
  }
  return result;
}

long long extended_gcd(long long first, long long second, long long& coefficient_first,
                       long long& coefficient_second) {
  if (second == 0) {
    coefficient_first = first >= 0 ? 1 : -1;
    coefficient_second = 0;
    return first >= 0 ? first : -first;
  }
  long long next_first = 0;
  long long next_second = 0;
  const long long divisor = extended_gcd(second, first % second, next_first, next_second);
  coefficient_first = next_second;
  coefficient_second = next_first - (first / second) * next_second;
  return divisor;
}

std::optional<std::pair<long long, long long>> chinese_remainder(
    long long first_remainder, long long first_modulus, long long second_remainder,
    long long second_modulus) {
  if (first_modulus <= 0 || second_modulus <= 0) {
    return std::nullopt;
  }
  first_remainder = (first_remainder % first_modulus + first_modulus) % first_modulus;
  second_remainder = (second_remainder % second_modulus + second_modulus) % second_modulus;
  long long inverse = 0;
  long long unused = 0;
  const long long divisor =
      extended_gcd(first_modulus, second_modulus, inverse, unused);
  const long long difference = second_remainder - first_remainder;
  if (difference % divisor != 0) {
    return std::nullopt;
  }
  const long long reduced_modulus = second_modulus / divisor;
  if (first_modulus / divisor >
      std::numeric_limits<long long>::max() / second_modulus) {
    return std::nullopt;
  }
  const long long lcm = first_modulus / divisor * second_modulus;
  const long long normalized_difference =
      ((difference / divisor) % reduced_modulus + reduced_modulus) % reduced_modulus;
  const long long normalized_inverse =
      (inverse % reduced_modulus + reduced_modulus) % reduced_modulus;
  const long long multiplier =
      multiply_modulo(normalized_difference, normalized_inverse, reduced_modulus);
  const long long increment = first_modulus * multiplier;
  return std::pair<long long, long long>{add_modulo(first_remainder, increment, lcm),
                                         lcm};
}
