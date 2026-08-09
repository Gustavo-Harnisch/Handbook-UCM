#include <array>
#include <queue>
#include <string>
#include <utility>
#include <vector>

class AhoCorasick {
 public:
  AhoCorasick() { nodes_.push_back(Node{}); }

  void add_pattern(const std::string& pattern, int pattern_id) {
    int node = 0;
    for (const char character : pattern) {
      const int letter = character - 'a';
      if (nodes_[node].next[letter] == -1) {
        nodes_[node].next[letter] = static_cast<int>(nodes_.size());
        nodes_.push_back(Node{});
      }
      node = nodes_[node].next[letter];
    }
    nodes_[node].output.push_back(pattern_id);
  }

  void build() {
    std::queue<int> pending;
    for (int letter = 0; letter < 26; ++letter) {
      const int child = nodes_[0].next[letter];
      if (child == -1) {
        nodes_[0].next[letter] = 0;
      } else {
        pending.push(child);
      }
    }
    while (!pending.empty()) {
      const int node = pending.front();
      pending.pop();
      for (int letter = 0; letter < 26; ++letter) {
        const int child = nodes_[node].next[letter];
        if (child == -1) {
          nodes_[node].next[letter] = nodes_[nodes_[node].link].next[letter];
          continue;
        }
        nodes_[child].link = nodes_[nodes_[node].link].next[letter];
        const auto& inherited_output = nodes_[nodes_[child].link].output;
        nodes_[child].output.insert(nodes_[child].output.end(),
                                    inherited_output.begin(), inherited_output.end());
        pending.push(child);
      }
    }
  }

  std::vector<std::pair<int, int>> search(const std::string& text) const {
    std::vector<std::pair<int, int>> matches;
    int node = 0;
    for (int index = 0; index < static_cast<int>(text.size()); ++index) {
      node = nodes_[node].next[text[index] - 'a'];
      for (const int pattern_id : nodes_[node].output) {
        matches.push_back({index, pattern_id});
      }
    }
    return matches;
  }

 private:
  struct Node {
    std::array<int, 26> next{};
    int link = 0;
    std::vector<int> output;

    Node() { next.fill(-1); }
  };

  std::vector<Node> nodes_;
};
