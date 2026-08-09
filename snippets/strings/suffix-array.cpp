#include <algorithm>
#include <numeric>
#include <string>
#include <vector>

std::vector<int> suffix_array(const std::string& text) {
  const int size = static_cast<int>(text.size());
  std::vector<int> order(size);
  std::iota(order.begin(), order.end(), 0);
  std::vector<int> rank(size);
  for (int index = 0; index < size; ++index) {
    rank[index] = static_cast<unsigned char>(text[index]);
  }
  for (int length = 1; length < size; length *= 2) {
    const auto compare = [&](int first, int second) {
      if (rank[first] != rank[second]) {
        return rank[first] < rank[second];
      }
      const int first_next = first + length < size ? rank[first + length] : -1;
      const int second_next = second + length < size ? rank[second + length] : -1;
      return first_next < second_next;
    };
    std::sort(order.begin(), order.end(), compare);
    std::vector<int> next_rank(size);
    for (int index = 1; index < size; ++index) {
      next_rank[order[index]] = next_rank[order[index - 1]] +
                                (compare(order[index - 1], order[index]) ? 1 : 0);
    }
    rank.swap(next_rank);
    if (rank[order.back()] == size - 1) {
      break;
    }
  }
  return order;
}

std::vector<int> lcp_array(const std::string& text, const std::vector<int>& order) {
  std::vector<int> rank(text.size());
  for (int index = 0; index < static_cast<int>(order.size()); ++index) {
    rank[order[index]] = index;
  }
  std::vector<int> lcp(text.size() > 0 ? text.size() - 1 : 0);
  int common = 0;
  for (int index = 0; index < static_cast<int>(text.size()); ++index) {
    if (rank[index] == static_cast<int>(text.size()) - 1) {
      common = 0;
      continue;
    }
    const int following = order[rank[index] + 1];
    while (index + common < static_cast<int>(text.size()) &&
           following + common < static_cast<int>(text.size()) &&
           text[index + common] == text[following + common]) {
      ++common;
    }
    lcp[rank[index]] = common;
    common = std::max(0, common - 1);
  }
  return lcp;
}
