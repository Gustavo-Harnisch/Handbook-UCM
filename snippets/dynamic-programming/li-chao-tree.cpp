#include <algorithm>
#include <limits>
#include <vector>

class LiChaoTree {
 public:
  LiChaoTree(long long left, long long right)
      : left_(left), right_(right), tree_(4) {}

  void add_line(long long slope, long long intercept) {
    add_line(Line{slope, intercept}, 1, left_, right_);
  }

  long long minimum(long long coordinate) const {
    return minimum(coordinate, 1, left_, right_);
  }

 private:
  struct Line {
    long long slope = 0;
    long long intercept = std::numeric_limits<long long>::max() / 4;

    long long value(long long coordinate) const {
      return slope * coordinate + intercept;
    }
  };

  void add_line(Line line, int node, long long left, long long right) {
    if (node >= static_cast<int>(tree_.size())) {
      tree_.resize(node + 1);
    }
    const long long middle = left + (right - left) / 2;
    bool better_left = line.value(left) < tree_[node].value(left);
    const bool better_middle = line.value(middle) < tree_[node].value(middle);
    if (better_middle) {
      std::swap(line, tree_[node]);
    }
    if (left == right) {
      return;
    }
    if (better_left != better_middle) {
      add_line(line, node * 2, left, middle);
    } else {
      add_line(line, node * 2 + 1, middle + 1, right);
    }
  }

  long long minimum(long long coordinate, int node, long long left,
                    long long right) const {
    if (node >= static_cast<int>(tree_.size())) {
      return std::numeric_limits<long long>::max() / 4;
    }
    const long long current = tree_[node].value(coordinate);
    if (left == right) {
      return current;
    }
    const long long middle = left + (right - left) / 2;
    if (coordinate <= middle) {
      return std::min(current, minimum(coordinate, node * 2, left, middle));
    }
    return std::min(current, minimum(coordinate, node * 2 + 1, middle + 1, right));
  }

  long long left_;
  long long right_;
  std::vector<Line> tree_;
};
