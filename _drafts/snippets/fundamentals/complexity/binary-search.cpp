#include <vector>

int binary_search_index(const std::vector<int>& values, int target) {
    int left = 0;
    int right = static_cast<int>(values.size()) - 1;

    while (left <= right) {
        int middle = left + (right - left) / 2;

        if (values[middle] == target) {
            return middle;
        }
        if (values[middle] < target) {
            left = middle + 1;
        } else {
            right = middle - 1;
        }
    }
    return -1;
}
