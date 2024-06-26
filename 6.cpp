#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include <vector>
#include <queue>
#define INF std::numeric_limits<int64_t>::max()

struct Edge {
  int64_t to;
  explicit Edge(int64_t to) : to(to) {
  }
};

class DirGraphAdjList {
 public:
  DirGraphAdjList(int64_t n_vertices, const std::vector<std::pair<int64_t, int64_t>>& edges, int64_t start, int64_t end)
      : adj_list_(n_vertices), dists_(n_vertices, INF), pred_(n_vertices, -1) {
    start_point_ = start - 1;
    end_point_ = end - 1;
    for (const auto& edge : edges) {
      adj_list_[edge.first - 1].push_back(edge.second - 1);
      adj_list_[edge.second - 1].push_back(edge.first - 1);
    }
  }

  void BFS() {
    std::queue<int64_t> queue;
    dists_[start_point_] = 0;
    queue.push(start_point_);
    while (!queue.empty()) {
      int64_t current = queue.front();
      queue.pop();
      for (int64_t to : adj_list_[current]) {
        if (dists_[to] == INF) {
          dists_[to] = dists_[current] + 1;
          pred_[to] = current;
          queue.push(to);
        }
      }
    }
  }

  void Restore() {
    if (dists_[end_point_] != INF) {
      std::vector<int64_t> path;
      for (int64_t v = end_point_; v != -1; v = pred_[v]) {
        path.push_back(v + 1);
      }
      std::reverse(path.begin(), path.end());
      std::cout << dists_[end_point_] << '\n';
      for (int64_t vertex : path) {
        std::cout << vertex << ' ';
      }
    } else {
      std::cout << -1;
    }
  }

 private:
  std::vector<std::vector<int64_t>> adj_list_;
  std::vector<int64_t> dists_;
  std::vector<int64_t> pred_;
  int64_t start_point_;
  int64_t end_point_;
};

int main() {
  int64_t n = 0;
  int64_t m = 0;
  int64_t a = 0;
  int64_t b = 0;
  std::cin >> n >> m >> a >> b;
  std::vector<std::pair<int64_t, int64_t>> edges;
  for (int64_t i = 0; i < m; ++i) {
    int64_t from = 0;
    int64_t to = 0;
    std::cin >> from >> to;
    edges.emplace_back(from, to);
  }
  DirGraphAdjList graph(n, edges, a, b);
  graph.BFS();
  graph.Restore();
  return 0;
}


//kBFS
std::vector<int> kBFS(const std::vector<std::vector<Edge>>& graph, int start) {
  std::vector<int> dist(n, INF);
  std::vector<std::queue<int>> queues; // в очереди queues[d] храню вершины с длиной d
  queues[0].push(start);
  dist[start] = 0;
  for (int d = 0; d < n * k; ++d) {
    while (!queues[d].empty()) {
      auto v = queues[d].front();
      queues[d].pop();
      if (dist[v] < d) {
        continue;
      }
      for (auto ch : graph[v]) {
        if (dist[ch.vertex] > dist[v] + ch.weight) {
          dist[ch.vertex] = dist[v] + ch.weight;
          queues[dist[ch.vertex]].push(ch.vertex);
        }
      }
    }
  }
  return dist;
}
}
/* Доказательство корректности алгоритма BFS

Алгоритм поиска в ширину (BFS - Breadth-First Search) используется для поиска кратчайшего пути в графе без весов. Рассмотрим корректность этого алгоритма.

1. **Начальная точка и первый шаг**: BFS начинает с узла \( s \), добавляя его в очередь и помечая как посещённый.

2. **Расширение**: На каждом шаге узел \( u \) извлекается из очереди, и все его непросмотренные соседние узлы добавляются в очередь. Каждому из этих узлов присваивается расстояние, которое равно расстоянию до \( u \) плюс один.

3. **Обеспечение непосещения одного узла дважды**: Каждый узел помещается в очередь не более одного раза благодаря проверке на посещение перед добавлением в очередь.

4. **Достижение всех узлов**: Если граф связный, алгоритм обходит все узлы, так как очередь исчерпывается только при отсутствии непросмотренных узлов.

5. **Кратчайший путь**: Поскольку BFS исследует узлы уровня за уровнем, он находит кратчайший путь от стартового узла \( s \) до любого другого узла \( v \), измеряемый в количестве рёбер.

### Доказательство времени работы алгоритма BFS

Рассмотрим граф \( G = (V, E) \) с \( V \) вершинами и \( E \) рёбрами.

1. **Инициализация**: Помечаем все узлы как непосещённые и добавляем начальный узел в очередь. Это занимает \( O(V) \) времени.

2. **Основной цикл**: 
   - Каждый узел добавляется в очередь один раз и извлекается один раз, следовательно, работа с узлами занимает \( O(V) \).
   - При извлечении узла все его смежные рёбра просматриваются один раз. Это занимает \( O(E) \) времени, так как каждое ребро рассматривается ровно один раз.

3. **Общая сложность**: Алгоритм выполняет \( O(V) \) операций на узлы и \( O(E) \) операций на рёбра. Следовательно, общая временная сложность BFS составляет \( O(V + E) \).

Таким образом, BFS гарантированно находит кратчайший путь в графе без весов и работает за линейное время относительно числа узлов и рёбер графа.
Асимптотика для kBFS -  O(N * K + E), где k - максимальный вес графа
*/
