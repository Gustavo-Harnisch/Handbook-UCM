#include <string>
#include <vector>

std::vector<int> prefix_function(const std::string& text) {
  std::vector<int> prefix(text.size());
  for (int index = 1; index < static_cast<int>(text.size()); ++index) {
    int candidate = prefix[index - 1];
    while (candidate > 0 && text[index] != text[candidate]) {
      candidate = prefix[candidate - 1];
    }
    if (text[index] == text[candidate]) {
      ++candidate;
    }
    prefix[index] = candidate;
  }
  return prefix;
}

std::vector<int> kmp_search(const std::string& text, const std::string& pattern) {
  if (pattern.empty()) {
    return {};
  }
  const std::vector<int> prefix = prefix_function(pattern);
  std::vector<int> matches;
  int matched = 0;
  for (int index = 0; index < static_cast<int>(text.size()); ++index) {
    while (matched > 0 && text[index] != pattern[matched]) {
      matched = prefix[matched - 1];
    }
    if (text[index] == pattern[matched]) {
      ++matched;
    }
    if (matched == static_cast<int>(pattern.size())) {
      matches.push_back(index - matched + 1);
      matched = prefix[matched - 1];
    }
  }
  return matches;
}
