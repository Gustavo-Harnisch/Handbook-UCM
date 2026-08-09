#include <algorithm>
#include <limits>
#include <queue>
#include <vector>

class Dinic {
 public:
  struct Edge {
    int to;
    int reverse_index;
    long long capacity;
  };

  explicit Dinic(int vertex_count)
      : graph_(vertex_count), level_(vertex_count), next_edge_(vertex_count) {}

  void add_edge(int from, int to, long long capacity) {
    Edge forward{to, static_cast<int>(graph_[to].size()), capacity};
    Edge backward{from, static_cast<int>(graph_[from].size()), 0};
    graph_[from].push_back(forward);
    graph_[to].push_back(backward);
  }

  long long max_flow(int source, int sink) {
    long long flow = 0;
    while (build_levels(source, sink)) {
      std::fill(next_edge_.begin(), next_edge_.end(), 0);
      while (long long pushed = send_flow(source, sink,
                                         std::numeric_limits<long long>::max())) {
        flow += pushed;
      }
    }
    return flow;
  }

 private:
  bool build_levels(int source, int sink) {
    std::fill(level_.begin(), level_.end(), -1);
    std::queue<int> pending;
    level_[source] = 0;
    pending.push(source);
    while (!pending.empty()) {
      const int vertex = pending.front();
      pending.pop();
      for (const Edge& edge : graph_[vertex]) {
        if (edge.capacity > 0 && level_[edge.to] == -1) {
          level_[edge.to] = level_[vertex] + 1;
          pending.push(edge.to);
        }
      }
    }
    return level_[sink] != -1;
  }

  long long send_flow(int vertex, int sink, long long available) {
    if (vertex == sink) {
      return available;
    }
    for (int& edge_index = next_edge_[vertex];
         edge_index < static_cast<int>(graph_[vertex].size()); ++edge_index) {
      Edge& edge = graph_[vertex][edge_index];
      if (edge.capacity == 0 || level_[edge.to] != level_[vertex] + 1) {
        continue;
      }
      const long long pushed =
          send_flow(edge.to, sink, std::min(available, edge.capacity));
      if (pushed == 0) {
        continue;
      }
      edge.capacity -= pushed;
      graph_[edge.to][edge.reverse_index].capacity += pushed;
      return pushed;
    }
    return 0;
  }

  std::vector<std::vector<Edge>> graph_;
  std::vector<int> level_;
  std::vector<int> next_edge_;
};
