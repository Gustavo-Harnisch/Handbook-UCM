#include <algorithm>
#include <queue>
#include <vector>

class HopcroftKarp {
 public:
  HopcroftKarp(int left_size, int right_size)
      : adjacency_(left_size), left_match_(left_size, -1),
        right_match_(right_size, -1), distance_(left_size) {}

  void add_edge(int left_vertex, int right_vertex) {
    adjacency_[left_vertex].push_back(right_vertex);
  }

  int maximum_matching() {
    int matching_size = 0;
    while (build_layers()) {
      for (int left_vertex = 0;
           left_vertex < static_cast<int>(adjacency_.size()); ++left_vertex) {
        if (left_match_[left_vertex] == -1 && augment(left_vertex)) {
          ++matching_size;
        }
      }
    }
    return matching_size;
  }

  const std::vector<int>& left_matching() const { return left_match_; }

 private:
  bool build_layers() {
    std::queue<int> pending;
    std::fill(distance_.begin(), distance_.end(), -1);
    for (int left_vertex = 0;
         left_vertex < static_cast<int>(adjacency_.size()); ++left_vertex) {
      if (left_match_[left_vertex] == -1) {
        distance_[left_vertex] = 0;
        pending.push(left_vertex);
      }
    }

    bool found_augmenting_path = false;
    while (!pending.empty()) {
      const int left_vertex = pending.front();
      pending.pop();
      for (const int right_vertex : adjacency_[left_vertex]) {
        const int matched_left = right_match_[right_vertex];
        if (matched_left == -1) {
          found_augmenting_path = true;
        } else if (distance_[matched_left] == -1) {
          distance_[matched_left] = distance_[left_vertex] + 1;
          pending.push(matched_left);
        }
      }
    }
    return found_augmenting_path;
  }

  bool augment(int left_vertex) {
    for (const int right_vertex : adjacency_[left_vertex]) {
      const int matched_left = right_match_[right_vertex];
      if (matched_left == -1 ||
          (distance_[matched_left] == distance_[left_vertex] + 1 &&
           augment(matched_left))) {
        left_match_[left_vertex] = right_vertex;
        right_match_[right_vertex] = left_vertex;
        return true;
      }
    }
    distance_[left_vertex] = -1;
    return false;
  }

  std::vector<std::vector<int>> adjacency_;
  std::vector<int> left_match_;
  std::vector<int> right_match_;
  std::vector<int> distance_;
};
