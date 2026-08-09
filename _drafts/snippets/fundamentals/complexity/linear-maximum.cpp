#include <algorithm>
#include <vector>

int maximum_value(const std::vector<int>& values) {
    int answer = values.front();
    for (int value : values) {
        answer = std::max(answer, value);
    }
    return answer;
}
