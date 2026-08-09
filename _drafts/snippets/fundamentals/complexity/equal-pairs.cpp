#include <cstdint>
#include <vector>

std::int64_t count_equal_pairs(const std::vector<int>& values) {
    std::int64_t pairs = 0;
    const int n = static_cast<int>(values.size());

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (values[i] == values[j]) {
                ++pairs;
            }
        }
    }
    return pairs;
}
