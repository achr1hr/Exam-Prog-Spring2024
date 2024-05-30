#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>
struct Edge {
  size_t from;
  size_t to;
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
      : adj_list_(n_vertices), reverse_adj_list_(n_vertices), colors_(n_vertices, WHITE), components_(n_vertices) {
    for (size_t i = 0; i < edges.size(); ++i) {
      adj_list_[edges[i].first - 1].emplace_back(edges[i].first, edges[i].second);
      reverse_adj_list_[edges[i].second - 1].emplace_back(edges[i].second, edges[i].first);
    }
  }
  void DFS() {
    for (size_t i = 0; i < adj_list_.size(); ++i) {
      if (!adj_list_[i].empty() && colors_[i] == WHITE) {
        StartDFS(i);
      }
    }
  }
  void Kosaraju() {
    counter_ = 0;
    std::reverse(order_.begin(), order_.end());
    for (size_t i = 0; i < order_.size(); ++i) {
      if (colors_[order_[i]] == GREY) {
        counter_ += 1;
        EndDFS(order_[i]);
      }
    }
    size_t max_el = *std::max_element(components_.begin(), components_.end());
    std::cout << max_el << '\n';
    for (size_t i = 0; i < components_.size(); ++i) {
      std::cout << components_[i] << ' ';
    }
  }

 private:
  void StartDFS(size_t start) {
    colors_[start] = GREY;
    for (size_t i = 0; i < adj_list_[start].size(); ++i) {
      if (colors_[adj_list_[start][i].to - 1] == WHITE) {
        StartDFS(adj_list_[start][i].to - 1);
      }
    }
    order_.push_back(start);
  };
  void EndDFS(size_t start) {
    components_[start] = counter_;
    colors_[start] = BLACK;
    for (size_t i = 0; i < reverse_adj_list_[start].size(); ++i) {
      if (colors_[reverse_adj_list_[start][i].to - 1] == GREY) {
        EndDFS(reverse_adj_list_[start][i].to - 1);
      }
    }
  }
  std::vector<std::vector<Edge>> adj_list_;
  std::vector<std::vector<Edge>> reverse_adj_list_;
  std::vector<Color> colors_;
  std::vector<size_t> order_;
  std::vector<size_t> components_;
  size_t counter_ = 0;
};

int main() {
  size_t n_verts = 0;
  size_t n_pairs = 0;
  std::cin >> n_verts >> n_pairs;
  std::vector<std::pair<int64_t, int64_t>> edges;
  std::pair<int64_t, int64_t> pair;
  for (size_t i = 0; i < n_pairs; ++i) {
    std::cin >> pair.first >> pair.second;
    edges.emplace_back(pair);
  }
  DirGraphAdjList list(n_verts, edges);
  list.DFS();
  list.Kosaraju();
}
