#include <algorithm>
#include <vector>

class NumberTheoreticTransform {
 public:
  static constexpr int modulus = 998244353;
  static constexpr int primitive_root = 3;

  std::vector<int> convolve(std::vector<int> first, std::vector<int> second) const {
    if (first.empty() || second.empty()) {
      return {};
    }
    const int result_size = static_cast<int>(first.size() + second.size() - 1);
    int transform_size = 1;
    while (transform_size < result_size) {
      transform_size *= 2;
    }
    first.resize(transform_size);
    second.resize(transform_size);
    transform(first, false);
    transform(second, false);
    for (int index = 0; index < transform_size; ++index) {
      first[index] = multiply(first[index], second[index]);
    }
    transform(first, true);
    first.resize(result_size);
    return first;
  }

 private:
  static int multiply(long long first, long long second) {
    return static_cast<int>(first * second % modulus);
  }

  static int power(int base, int exponent) {
    int result = 1;
    while (exponent > 0) {
      if (exponent & 1) {
        result = multiply(result, base);
      }
      base = multiply(base, base);
      exponent >>= 1;
    }
    return result;
  }

  static void transform(std::vector<int>& values, bool invert) {
    const int size = static_cast<int>(values.size());
    for (int index = 1, reversed = 0; index < size; ++index) {
      int bit = size >> 1;
      for (; reversed & bit; bit >>= 1) {
        reversed ^= bit;
      }
      reversed ^= bit;
      if (index < reversed) {
        std::swap(values[index], values[reversed]);
      }
    }
    for (int block_size = 2; block_size <= size; block_size *= 2) {
      int root = power(primitive_root, (modulus - 1) / block_size);
      if (invert) {
        root = power(root, modulus - 2);
      }
      for (int start = 0; start < size; start += block_size) {
        int current_root = 1;
        for (int offset = 0; offset < block_size / 2; ++offset) {
          const int first = values[start + offset];
          const int second = multiply(values[start + offset + block_size / 2], current_root);
          values[start + offset] = first + second < modulus ? first + second : first + second - modulus;
          values[start + offset + block_size / 2] = first - second >= 0 ? first - second : first - second + modulus;
          current_root = multiply(current_root, root);
        }
      }
    }
    if (invert) {
      const int inverse_size = power(size, modulus - 2);
      for (int& value : values) {
        value = multiply(value, inverse_size);
      }
    }
  }
};
