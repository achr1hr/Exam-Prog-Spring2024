 std::vector<std::vector<int64_t>> FindDistsFloydWarshall() {
    std::vector<std::vector<int64_t>> matrix(adj_list_.size(), std::vector<int64_t>(adj_list_.size(), INF));
    for (const std::vector<Edge> &edges : adj_list_) {
      for (const Edge &edge : edges) {
        matrix[edge.from][edge.to] = edge.weight;
      }
    }
    for (size_t node = 0; node < adj_list_.size(); ++node) {
      matrix[node][node] = 0;
    }

    for (size_t new_node = 0; new_node < adj_list_.size(); ++new_node) {
      for (size_t from = 0; from < adj_list_.size(); ++from) {
        for (size_t to = 0; to < adj_list_.size(); ++to) {
          if (matrix[from][new_node] == INF || matrix[new_node][to] == INF) {
            continue;
          }
          if (matrix[from][to] > matrix[from][new_node] + matrix[new_node][to]) {
            matrix[from][to] = matrix[from][new_node] + matrix[new_node][to];
          }
        }
      }
    }
    return matrix;
  }

/*Пояснялка, почему Флойд-Уоршелл - мега изи.  По сути мы просто к ребру между двумя точками добавляем ещё одну точку
То есть у нас уже два ребра. Если сумма весов этих рёбер меньше, чем расстояние напрямую (или хотя бы существует, в отличие от ребра напрямую),
то хуярим новое расстояние, равное сумме весов рёбер. Если одного из этих двух рёбер не существует, то мы просто скипаем итерацию)