#include <functional>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

using Distance = long long;
using Edge = std::pair<int, int>;  // {destination, weight}
using Graph = std::vector<std::vector<Edge>>;

std::vector<Distance> dijkstra(int source, const Graph& graph) {
    constexpr Distance INF = std::numeric_limits<Distance>::max() / 4;
    using State = std::pair<Distance, int>;  // {distance, vertex}

    std::vector<Distance> distance(graph.size(), INF);
    std::priority_queue<State, std::vector<State>, std::greater<State>> pending;

    distance[source] = 0;
    pending.push({0, source});

    while (!pending.empty()) {
        auto [current_distance, vertex] = pending.top();
        pending.pop();

        if (current_distance != distance[vertex]) {
            continue;
        }

        for (auto [neighbor, weight] : graph[vertex]) {
            Distance candidate = current_distance + weight;
            if (candidate < distance[neighbor]) {
                distance[neighbor] = candidate;
                pending.push({candidate, neighbor});
            }
        }
    }
    return distance;
}
