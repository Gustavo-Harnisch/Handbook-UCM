#include <vector>

class PersistentSegmentTree {
 public:
  explicit PersistentSegmentTree(const std::vector<long long>& values)
      : size_(static_cast<int>(values.size())) {
    roots_.push_back(build(0, size_ - 1, values));
  }

  int update(int version, int position, long long value) {
    roots_.push_back(update(roots_[version], 0, size_ - 1, position, value));
    return static_cast<int>(roots_.size()) - 1;
  }

  long long sum(int version, int left, int right) const {
    return sum(roots_[version], 0, size_ - 1, left, right);
  }

 private:
  struct Node {
    long long sum;
    int left_child;
    int right_child;
  };

  int make_node(long long sum, int left_child = -1, int right_child = -1) {
    nodes_.push_back({sum, left_child, right_child});
    return static_cast<int>(nodes_.size()) - 1;
  }

  int build(int left, int right, const std::vector<long long>& values) {
    if (left == right) {
      return make_node(values[left]);
    }
    const int middle = left + (right - left) / 2;
    const int left_child = build(left, middle, values);
    const int right_child = build(middle + 1, right, values);
    return make_node(nodes_[left_child].sum + nodes_[right_child].sum,
                     left_child, right_child);
  }

  int update(int node, int left, int right, int position, long long value) {
    if (left == right) {
      return make_node(value);
    }
    const int middle = left + (right - left) / 2;
    int left_child = nodes_[node].left_child;
    int right_child = nodes_[node].right_child;
    if (position <= middle) {
      left_child = update(left_child, left, middle, position, value);
    } else {
      right_child = update(right_child, middle + 1, right, position, value);
    }
    return make_node(nodes_[left_child].sum + nodes_[right_child].sum,
                     left_child, right_child);
  }

  long long sum(int node, int left, int right, int query_left,
                int query_right) const {
    if (query_right < left || right < query_left) {
      return 0;
    }
    if (query_left <= left && right <= query_right) {
      return nodes_[node].sum;
    }
    const int middle = left + (right - left) / 2;
    return sum(nodes_[node].left_child, left, middle, query_left, query_right) +
           sum(nodes_[node].right_child, middle + 1, right, query_left,
               query_right);
  }

  int size_;
  std::vector<Node> nodes_;
  std::vector<int> roots_;
};
