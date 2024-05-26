#include <cstdint>
#include <iostream>
#include <vector>

//Просто DFS
struct Edge {
  int64_t from;
  int64_t to;
  Edge() : Edge(0, 0) {}
  Edge(int64_t from, int64_t to) : from(from), to(to) {}
};

class DirGraphAdjList {
 private:
  enum Color { WHITE, GREY, BLACK };

 public:
  DirGraphAdjList(size_t n_vertices,
                  const std::vector<std::pair<int64_t, int64_t>> &edges)
      : adj_list_(n_vertices), colors_(n_vertices, WHITE) {
    for (size_t i = 0; i < edges.size(); ++i) {
      adj_list_[edges[i].first - 1].emplace_back(edges[i].first,
                                                 edges[i].second);
    }
  }
  void DFS() {
    for (size_t i = 0; i < adj_list_.size(); ++i) {
      if (!adj_list_[i].empty() && colors_[i] == WHITE) {
        InnerDFS(i);
      }
    }
    return;
  }

 private:
  void InnerDFS(size_t start) {
    colors_[start] = GREY;
    for (size_t i = 0; i < adj_list_[start].size(); ++i) {
      if (colors_[adj_list_[start][i].to - 1] == WHITE) {
        InnerDFS(adj_list_[start][i].to - 1);
      }
    }
    colors_[start] = BLACK;
    return;
  };
  std::vector<std::vector<Edge>> adj_list_;
  std::vector<Color> colors_;
};

int main() {
  size_t n_verts = 0;
  size_t n_pairs = 0;
  std::cin >> n_verts >> n_pairs;
  if (n_verts < 2) {
    std::cout << "NO";
    return 0;
  }
  std::vector<std::pair<int64_t, int64_t>> edges;
  std::pair<int64_t, int64_t> pair;
  for (size_t i = 0; i < n_pairs; ++i) {
    std::cin >> pair.first >> pair.second;
    edges.emplace_back(pair);
  }
  DirGraphAdjList list(n_verts, edges);
  list.DFS();
}

//Проверка на цикличность.
#include <cstdint>
#include <iostream>
#include <vector>

struct Edge {
  int64_t from;
  int64_t to;
  Edge() : Edge(0, 0) {
  }
  Edge(int64_t from, int64_t to) : from(from), to(to) {
  }
};

class DirGraphAdjList {
 private:
  enum Color { WHITE, GREY, BLACK };

 public:
  DirGraphAdjList(size_t n_vertices, const std::vector<std::pair<int64_t, int64_t>> &edges)
      : adj_list_(n_vertices), colors_(n_vertices, WHITE) {
    for (size_t i = 0; i < edges.size(); ++i) {
      adj_list_[edges[i].first - 1].emplace_back(edges[i].first, edges[i].second);
    }
  }
  bool DFS() {
    for (size_t i = 0; i < adj_list_.size(); ++i) {
      if (!adj_list_[i].empty() && colors_[i] == WHITE) {
        if (InnerDFS(i)) {
          return true;
        }
      }
    }
    return false;
  }

 private:
  bool InnerDFS(size_t start) {
    colors_[start] = BLACK;
    for (size_t i = 0; i < adj_list_[start].size(); ++i) {
      if (colors_[adj_list_[start][i].to - 1] == BLACK) {
        std::cout << "YES\n";
        CheckDFS(adj_list_[start][i].to - 1, adj_list_[start][i].to - 1);
        return true;
      }
      if (colors_[adj_list_[start][i].to - 1] == WHITE) {
        if (InnerDFS(adj_list_[start][i].to - 1)) {
          return true;
        }
      }
    }
    colors_[start] = GREY;
    return false;
  };
  bool CheckDFS(int64_t start, int64_t current) {
    std::cout << current + 1 << " ";
    for (size_t i = 0; i < adj_list_[current].size(); ++i) {
      if (colors_[adj_list_[current][i].to - 1] == BLACK && adj_list_[current][i].to - 1 == start) {
        return true;
      }
    }
    for (size_t i = 0; i < adj_list_[current].size(); ++i) {
      if (colors_[adj_list_[current][i].to - 1] == BLACK) {
        if (CheckDFS(start, adj_list_[current][i].to - 1)) {
          return true;
        }
      }
    }
    return false;
  }
  std::vector<std::vector<Edge>> adj_list_;
  std::vector<Color> colors_;
};

int main() {
  size_t n_verts = 0;
  size_t n_pairs = 0;
  std::cin >> n_verts >> n_pairs;
  if (n_verts < 2) {
    std::cout << "NO";
    return 0;
  }
  std::vector<std::pair<int64_t, int64_t>> edges;
  std::pair<int64_t, int64_t> pair;
  for (size_t i = 0; i < n_pairs; ++i) {
    std::cin >> pair.first >> pair.second;
    edges.emplace_back(pair);
  }
  DirGraphAdjList list(n_verts, edges);
  if (!list.DFS()) {
    std::cout << "NO\n";
  }
}

// Жадная функция для раскраски графа
void GreedyColoring() {
  int result[maxn];                                    // Хранение цвета для каждой вершины
  bool available[maxn];                                // Доступные цвета
  std::memset(result, -1, sizeof(result));             // Инициализация вершин как нераскрашенных
  result[0] = 0;                                       // Назначаем первый цвет первой вершине
  std::memset(available, true, sizeof(available));     // Инициализация всех цветов как доступных
  
  for (int u = 1; u < size; u++) {                     // Раскраска остальных вершин
    for (int i : g[u]) {                               // Помечаем цвета смежных вершин как недоступные
      if (result[i] != -1) {
        available[result[i]] = false;
      }
    }
    int cr;                                            // Находим первый доступный цвет
    for (cr = 0; cr < size; cr++) {
      if (available[cr]) break;
    }
    result[u] = cr;                                   // Присваиваем найденный цвет вершине
    std::memset(available, true, sizeof(available));  // Сброс доступных цветов для следующей итерации
  }
  
    // Вывод результата
  for (int u = 0; u < size; u++) {
    std::cout << "Vertex " << u << " ---> Color " << result[u] << std::endl;
  }
}


// Поиск эйлерового цикла
/*
 Эйлеров путь — это путь в графе, проходящий через все его рёбра.
 Эйлеров цикл — это эйлеров путь, являющийся циклом.
 */

std::set<int> g_euler[maxn];

bool IsEulerian() {
  for (int i = 0; i < maxn; ++i) {
    if (!g_euler[i].empty() && (g_euler[i].size() % 2 != 0)) {
      return false; // Возвращаем false, если нашли вершину с нечетной степенью
    }
  }
  return true; // Все вершины с рёбрами имеют четные степени
}

void Euler(int v) {
  while (!g_euler[v].empty()) {
    auto u = *g_euler[v].begin();
    g_euler[v].erase(u);
    g_euler[u].erase(v); // если граф ориентированный, обратное ребро удалять не надо
    Euler(u);
  }
  std::cout << v <<  " ";
}
/*
Depth-First Search (DFS):
Временная сложность: 
O(V+E), где 
V - количество вершин, а 
E - количество ребер.
Пространственная сложность: 
O(V) для хранения стека вызовов и меток посещенных вершин.

Проверка на связность:
Алгоритм, основанный на DFS или BFS.
Временная сложность: 
O(V+E).
Пространственная сложность: 
O(V).

Проверка на ацикличность:
Алгоритм, основанный на DFS с обнаружением обратных ребер (для ориентированных графов) или ребер цикла (для неориентированных графов).
Временная сложность: 
O(V+E).
Пространственная сложность: 
O(V).
Правильная раскраска графа жадным алгоритмом:
Временная сложность: 
O(V^2+E) в худшем случае (если используем для проверки каждого ребра).
Пространственная сложность: 
O(V).
Поиск Эйлерова цикла:
Алгоритм Флёри или алгоритм с использованием иерархии (Hierholzer's algorithm).
Временная сложность: 
O(V+E).
Пространственная сложность: 
O(V+E).

*/