
//По сути Дейкстра, только название другое.
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include <vector>
#define INF std::numeric_limits<int64_t>::max()

struct Edge {
  int64_t to;
  int64_t weight;
  Edge(int64_t to, int64_t weight) : to(to), weight(weight) {
  }
};

class DirGraphAdjList {
 public:
  DirGraphAdjList(int64_t n_vertices, const std::vector<std::pair<int64_t, int64_t>>& edges,
                  const std::vector<int64_t>& weights, int64_t start, int64_t end)
      : adj_list_(n_vertices), dists_(n_vertices, INF) {
    start_point_ = start - 1;
    end_point_ = end - 1;
    for (size_t i = 0; i < edges.size(); ++i) {
      adj_list_[edges[i].first - 1].emplace_back(edges[i].second - 1, weights[i]);
    }
  }

  void BFS() {
    std::vector<bool> visited(adj_list_.size(), false);
    dists_[start_point_] = 0;
    for (size_t i = 0; i < adj_list_.size(); ++i) {
      int64_t current = ExtractMin(visited);
      if (current == -1) {
        break;
      }
      visited[current] = true;
      for (size_t j = 0; j < adj_list_[current].size(); ++j) {
        int64_t next = adj_list_[current][j].to;
        int64_t gweight = adj_list_[current][j].weight;
        if (!visited[next] && dists_[current] != INF && dists_[next] > dists_[current] + gweight) {
          dists_[next] = dists_[current] + gweight;
        }
      }
    }
  }

  void Restore() {
    if (dists_[end_point_] != INF) {
      std::cout << dists_[end_point_];
    } else {
      std::cout << -1;
    }
  }

 private:
  std::vector<std::vector<Edge>> adj_list_;
  std::vector<int64_t> dists_;
  int64_t start_point_;
  int64_t end_point_;

  int64_t ExtractMin(std::vector<bool> visited) {
    int64_t min_dist = INF;
    int64_t min_index = -1;
    for (size_t i = 0; i < dists_.size(); ++i) {
      if (!visited[i] && dists_[i] < min_dist) {
        min_dist = dists_[i];
        min_index = static_cast<int64_t>(i);
      }
    }
    return min_index;
  }
};

int main() {
  int64_t n = 0;
  int64_t m = 0;
  int64_t a = 0;
  int64_t b = 0;
  std::cin >> n >> m >> a >> b;
  std::vector<int64_t> weights;
  std::vector<std::pair<int64_t, int64_t>> edges;
  for (int64_t i = 0; i < m; ++i) {
    int64_t from = 0;
    int64_t to = 0;
    int64_t weight = 0;
    std::cin >> from >> to >> weight;
    edges.emplace_back(from, to);
    weights.emplace_back(weight);
  }
  DirGraphAdjList graph(n, edges, weights, a, b);
  graph.BFS();
  graph.Restore();
}
//Улучшение алгоритма заключается в использовании priority_queue, вместо queue. Компаратор std::greater<std::pair<int64_t,int64_t>>.
//std::priority_queue<std::pair<int64_t, int64_t>, std::vector<std::pair<int64_t, int64_t>>,
//                      std::greater<std::pair<int64_t, int64_t>>>, где 1 параметр - тип хран. перем, 2 парам. - тип контейнера, 3 парам. - компаратор.