#include <algorithm>
#include <string>
#include <vector>

std::vector<int> odd_palindrome_radii(const std::string& text) {
  const int size = static_cast<int>(text.size());
  std::vector<int> radius(size);
  int left = 0;
  int right = -1;
  for (int center = 0; center < size; ++center) {
    int current = center > right ? 1 : std::min(radius[left + right - center], right - center + 1);
    while (center - current >= 0 && center + current < size &&
           text[center - current] == text[center + current]) {
      ++current;
    }
    radius[center] = current;
    if (center + current - 1 > right) {
      left = center - current + 1;
      right = center + current - 1;
    }
  }
  return radius;
}

std::vector<int> even_palindrome_radii(const std::string& text) {
  const int size = static_cast<int>(text.size());
  std::vector<int> radius(size);
  int left = 0;
  int right = -1;
  for (int center = 0; center < size; ++center) {
    int current = center > right ? 0 : std::min(radius[left + right - center + 1], right - center + 1);
    while (center - current - 1 >= 0 && center + current < size &&
           text[center - current - 1] == text[center + current]) {
      ++current;
    }
    radius[center] = current;
    if (center + current - 1 > right) {
      left = center - current;
      right = center + current - 1;
    }
  }
  return radius;
}
