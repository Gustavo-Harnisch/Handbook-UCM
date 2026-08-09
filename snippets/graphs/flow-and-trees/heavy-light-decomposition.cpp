#include <algorithm>
#include <utility>
#include <vector>

class HeavyLightDecomposition {
 public:
  HeavyLightDecomposition(const std::vector<std::vector<int>>& adjacency, int root = 0)
      : adjacency_(adjacency), parent_(adjacency.size(), -1),
        depth_(adjacency.size()), subtree_size_(adjacency.size()),
        heavy_child_(adjacency.size(), -1), head_(adjacency.size()),
        position_(adjacency.size()) {
    compute_subtrees(root);
    int next_position = 0;
    decompose(root, root, next_position);
  }

  int position(int vertex) const { return position_[vertex]; }

  std::vector<std::pair<int, int>> path_segments(int first, int second,
                                                  bool edge_values = false) const {
    std::vector<std::pair<int, int>> segments;
    while (head_[first] != head_[second]) {
      if (depth_[head_[first]] < depth_[head_[second]]) {
        std::swap(first, second);
      }
      segments.push_back({position_[head_[first]], position_[first]});
      first = parent_[head_[first]];
    }
    if (depth_[first] < depth_[second]) {
      std::swap(first, second);
    }
    const int start = position_[second] + (edge_values ? 1 : 0);
    if (start <= position_[first]) {
      segments.push_back({start, position_[first]});
    }
    return segments;
  }

  std::pair<int, int> subtree_segment(int vertex) const {
    return {position_[vertex], position_[vertex] + subtree_size_[vertex] - 1};
  }

 private:
  int compute_subtrees(int vertex) {
    subtree_size_[vertex] = 1;
    int largest_child_size = 0;
    for (const int neighbour : adjacency_[vertex]) {
      if (neighbour == parent_[vertex]) {
        continue;
      }
      parent_[neighbour] = vertex;
      depth_[neighbour] = depth_[vertex] + 1;
      const int child_size = compute_subtrees(neighbour);
      subtree_size_[vertex] += child_size;
      if (child_size > largest_child_size) {
        largest_child_size = child_size;
        heavy_child_[vertex] = neighbour;
      }
    }
    return subtree_size_[vertex];
  }

  void decompose(int vertex, int chain_head, int& next_position) {
    head_[vertex] = chain_head;
    position_[vertex] = next_position++;
    if (heavy_child_[vertex] != -1) {
      decompose(heavy_child_[vertex], chain_head, next_position);
    }
    for (const int neighbour : adjacency_[vertex]) {
      if (neighbour != parent_[vertex] && neighbour != heavy_child_[vertex]) {
        decompose(neighbour, neighbour, next_position);
      }
    }
  }

  const std::vector<std::vector<int>>& adjacency_;
  std::vector<int> parent_;
  std::vector<int> depth_;
  std::vector<int> subtree_size_;
  std::vector<int> heavy_child_;
  std::vector<int> head_;
  std::vector<int> position_;
};
