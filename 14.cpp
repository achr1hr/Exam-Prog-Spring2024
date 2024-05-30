#include <algorithm>
#include <cstdint>
#include <functional>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

#define INF std::numeric_limits<int64_t>::max()

struct Edge {
  int64_t from;
  int64_t to;
  int64_t weight;
  Edge() : Edge(0, 0, 0) {
  }
  Edge(int64_t from, int64_t to, int64_t weight) : from(from), to(to), weight(weight) {
  }
};

class DirGraphAdjList {
 private:
  enum Color { WHITE, GREY, BLACK };

 public:
  DirGraphAdjList(int64_t n_vertices, const std::vector<std::pair<int64_t, int64_t>> &edges,
                  const std::vector<int64_t> &weights)
      : start_(0)
      , finish_(n_vertices - 1)
      , n_vertices_(n_vertices)
      , adj_matrix_(n_vertices, std::vector<Edge>(n_vertices)) {
    for (int64_t i = 0; i < n_vertices_; ++i) {
      for (int64_t j = 0; j < n_vertices_; ++j) {
        adj_matrix_[i][j].from = i; //ВОТ ЭТИ ДВЕ СТРОКИ ВАЖНЫ БЛЯТЬ ОЧЕНЬ, ИНАЧЕ ВА НА 9.
        adj_matrix_[i][j].to = j;
      }
    }
    for (size_t i = 0; i < edges.size(); ++i) {
      adj_matrix_[edges[i].first - 1][edges[i].second - 1] = {edges[i].first - 1, edges[i].second - 1, weights[i]};
    }
  }
  int64_t BFS(std::vector<int64_t> &path);
  void EK();

 private:
  int64_t start_;
  int64_t finish_;
  int64_t n_vertices_;
  std::vector<std::vector<Edge>> adj_matrix_;
};

int main() {
  int n = 0;
  int v = 0;
  std::cin >> n >> v;
  std::vector<std::pair<int64_t, int64_t>> edges;
  std::vector<int64_t> weights;
  int64_t first = 0;
  int64_t second = 0;
  for (int i = 0; i < v; ++i) {
    std::cin >> first;
    std::cin >> second;
    edges.emplace_back(first, second);
    std::cin >> first;
    weights.emplace_back(first);
  }
  DirGraphAdjList graph(n, edges, weights);
  graph.EK();
}

void DirGraphAdjList::EK() {
  int64_t flow = 1;
  int64_t res = 0;
  std::vector<int64_t> path(1, start_);
  while (flow) {
    flow = BFS(path);
    for (size_t i = 0; i + 1 < path.size(); ++i) {
      size_t from = path[i];
      size_t to = path[i + 1];
      adj_matrix_[from][to].weight -= flow;
      adj_matrix_[to][from].weight += flow;
    }
    path.resize(1);
    res += flow;
  }
  std::cout << res;
}

int64_t DirGraphAdjList::BFS(std::vector<int64_t> &path) {
  std::vector<int64_t> dists(n_vertices_, INF);
  std::vector<int64_t> parents(n_vertices_, -1);
  std::queue<int64_t> queue;
  dists[path.front()] = 0;
  queue.emplace(path.back());
  while (!queue.empty()) {
    int64_t cur = queue.front();
    queue.pop();
    for (auto &edge : adj_matrix_[cur]) {
      if (edge.weight > 0 && dists[edge.to] > dists[cur] + 1) {
        dists[edge.to] = dists[cur] + 1;
        queue.emplace(edge.to);
        parents[edge.to] = cur;
      }
    }
  }
  if (dists[finish_] == INF) {
    return 0;
  }
  path.clear();
  path.emplace_back(finish_);
  int64_t res = INF;
  int64_t cur = finish_;
  while (cur != start_) {
    path.push_back(parents[cur]);
    res = std::min(res, adj_matrix_[parents[cur]][cur].weight);
    cur = parents[cur];
  }
  std::reverse(path.begin(), path.end());
  return res;
}

//Форд Фалкерсон
void DirGraphAdjList::MaxFlowFordFulkerson() {
  std::vector<int64_t> path(1, start_);
  int64_t flow;
  int64_t res = 0;
  while (flow = Dfs(path, INF)) {
    for (size_t i = 0; i + 1 < path.size(); ++i) {
      size_t from = path[i];
      size_t to = path[i + 1];
      adj_matrix_[from][to].weight -= flow;
      adj_matrix_[to][from].weight += flow;
    }
    path.resize(1);
    visited_.assign(adj_matrix_.size(), WHITE);
    res += flow;
  }
  std::cout << res;
}

int64_t DirGraphAdjList::Dfs(std::vector<int64_t>& path, int64_t min_flow) {
  const int& v = path.back();
  if (v == finish_) {
    return min_flow;
  }
  visited_[v] = true;
  for (Edge& e : adj_matrix_[v]) {
    if ((!visited_[e.to]) && (e.weight > 0)) {
      path.emplace_back(e.to);
      if (Dfs(path, std::min(min_flow, e.weight))) {
        return std::min(min_flow, e.weight);
      }
      path.pop_back();
    }
  }
  return 0;
}