#include <algorithm>
#include <vector>

class LazySegmentTree {
 public:
  explicit LazySegmentTree(const std::vector<long long>& values)
      : size_(static_cast<int>(values.size())), tree_(4 * size_), lazy_(4 * size_) {
    build(1, 0, size_ - 1, values);
  }

  void add(int left, int right, long long value) {
    add(1, 0, size_ - 1, left, right, value);
  }

  long long sum(int left, int right) {
    return sum(1, 0, size_ - 1, left, right);
  }

 private:
  void build(int node, int left, int right, const std::vector<long long>& values) {
    if (left == right) {
      tree_[node] = values[left];
      return;
    }
    const int middle = left + (right - left) / 2;
    build(node * 2, left, middle, values);
    build(node * 2 + 1, middle + 1, right, values);
    tree_[node] = tree_[node * 2] + tree_[node * 2 + 1];
  }

  void apply(int node, int left, int right, long long value) {
    tree_[node] += value * (right - left + 1);
    lazy_[node] += value;
  }

  void push(int node, int left, int right) {
    if (lazy_[node] == 0 || left == right) {
      return;
    }
    const int middle = left + (right - left) / 2;
    apply(node * 2, left, middle, lazy_[node]);
    apply(node * 2 + 1, middle + 1, right, lazy_[node]);
    lazy_[node] = 0;
  }

  void add(int node, int left, int right, int query_left, int query_right,
           long long value) {
    if (query_right < left || right < query_left) {
      return;
    }
    if (query_left <= left && right <= query_right) {
      apply(node, left, right, value);
      return;
    }
    push(node, left, right);
    const int middle = left + (right - left) / 2;
    add(node * 2, left, middle, query_left, query_right, value);
    add(node * 2 + 1, middle + 1, right, query_left, query_right, value);
    tree_[node] = tree_[node * 2] + tree_[node * 2 + 1];
  }

  long long sum(int node, int left, int right, int query_left, int query_right) {
    if (query_right < left || right < query_left) {
      return 0;
    }
    if (query_left <= left && right <= query_right) {
      return tree_[node];
    }
    push(node, left, right);
    const int middle = left + (right - left) / 2;
    return sum(node * 2, left, middle, query_left, query_right) +
           sum(node * 2 + 1, middle + 1, right, query_left, query_right);
  }

  int size_;
  std::vector<long long> tree_;
  std::vector<long long> lazy_;
};
