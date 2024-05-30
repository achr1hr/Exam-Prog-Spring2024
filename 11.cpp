#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include <queue>
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
                  std::vector<int64_t> weights)
      : n_verts_(n_vertices - 1), adj_list_(n_vertices), is_vis_(n_vertices, false) {
    for (size_t i = 0; i < edges.size(); ++i) {
      adj_list_[edges[i].first - 1].emplace_back(edges[i].second - 1, weights[i]);
      adj_list_[edges[i].second - 1].emplace_back(edges[i].first - 1, weights[i]);
    }
  }
  size_t Prima();

  int64_t Extractmin() {
    int64_t ans = 0;
    while (!ans && !available_.empty()) {
      if (!is_vis_[available_.top().second]) {
        ans = available_.top().second;
        len_ += available_.top().first;
        available_.pop();
      } else {
        available_.pop();
      }
    }
    return ans;
  }
  int64_t n_verts_;
  size_t len_ = 0;
  std::vector<std::vector<Edge>> adj_list_;
  std::priority_queue<std::pair<int64_t, int64_t>, std::vector<std::pair<int64_t, int64_t>>,
                      std::greater<std::pair<int64_t, int64_t>>>
      available_;
  std::vector<bool> is_vis_;
};

int main() {
  int64_t n = 0;
  int64_t m = 0;
  int64_t weight = 0;
  std::cin >> n >> m;
  if (!m) {
    std::cout << 0;
    return 0;
  }
  std::vector<std::pair<int64_t, int64_t>> edges;
  std::vector<int64_t> weights;
  for (int64_t i = 0; i < m; ++i) {
    int64_t from = 0;
    int64_t to = 0;
    std::cin >> from >> to >> weight;
    edges.emplace_back(from, to);
    weights.emplace_back(weight);
  }
  DirGraphAdjList graph(n, edges, weights);
  std::cout << graph.Prima();
  return 0;
}

size_t DirGraphAdjList::Prima() {
  int64_t vert = 0;
  is_vis_[0] = true;
  while (n_verts_) {
    for (auto& to : adj_list_[vert]) {
      if (!is_vis_[to.to]) {
        available_.emplace(to.weight, to.to);
      }
    }
    vert = Extractmin();
    is_vis_[vert] = true;
    n_verts_ -= 1;
  }
  return len_;
}
/*Изи алгоритм. Заходим в нулевую вершину. Собираем всех детей в приоритетную очередь. 
Берём того, до которого расстояние наименьшее (и если не посещён). Переходим к нему, добавляя расстояние в переменную. 
Как только количество пос. вершин станет равным количеству вершин графа, вырубаем цикл и выводим число. Профит.
*/