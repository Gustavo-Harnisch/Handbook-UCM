#include <numeric>
#include <utility>
#include <vector>

class RollbackDisjointSet {
 public:
  explicit RollbackDisjointSet(int element_count)
      : parent_(element_count), size_(element_count, 1), components_(element_count) {
    std::iota(parent_.begin(), parent_.end(), 0);
  }

  int find(int element) const {
    while (parent_[element] != element) {
      element = parent_[element];
    }
    return element;
  }

  bool unite(int first, int second) {
    first = find(first);
    second = find(second);
    if (first == second) {
      history_.push_back({-1, -1});
      return false;
    }
    if (size_[first] < size_[second]) {
      std::swap(first, second);
    }
    history_.push_back({second, size_[first]});
    parent_[second] = first;
    size_[first] += size_[second];
    --components_;
    return true;
  }

  int snapshot() const { return static_cast<int>(history_.size()); }

  void rollback(int snapshot) {
    while (static_cast<int>(history_.size()) > snapshot) {
      const auto [merged_root, old_size] = history_.back();
      history_.pop_back();
      if (merged_root == -1) {
        continue;
      }
      const int new_root = parent_[merged_root];
      parent_[merged_root] = merged_root;
      size_[new_root] = old_size;
      ++components_;
    }
  }

  int component_count() const { return components_; }

 private:
  std::vector<int> parent_;
  std::vector<int> size_;
  std::vector<std::pair<int, int>> history_;
  int components_;
};
