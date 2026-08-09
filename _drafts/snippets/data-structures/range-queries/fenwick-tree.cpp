#include <vector>

class FenwickTree {
public:
    explicit FenwickTree(int size) : size_(size), tree_(size + 1, 0) {}

    void add(int index, long long delta) {
        for (; index <= size_; index += index & -index) {
            tree_[index] += delta;
        }
    }

    [[nodiscard]] long long sum_prefix(int index) const {
        long long answer = 0;
        for (; index > 0; index -= index & -index) {
            answer += tree_[index];
        }
        return answer;
    }

    [[nodiscard]] long long sum_range(int left, int right) const {
        return sum_prefix(right) - sum_prefix(left - 1);
    }

private:
    int size_;
    std::vector<long long> tree_;
};
