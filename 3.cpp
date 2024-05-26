#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <cstdint>

struct Edge
{
    size_t from;
    size_t to;
    int64_t weight;
    Edge() : Edge(0, 0, 0) {}
    Edge(size_t from, size_t to, int64_t weight);
};

class DirGraphAdjList
{
public:
    DirGraphAdjList(size_t n_vertices, const std::vector<std::pair<size_t, size_t>> &edges, const std::vector<int64_t> &weights) : adj_list_(n_vertices)
    {
        for (size_t i = 0; i < edges.size(); ++i)
        {
            adj_list_[edges[i].first].emplace_back(edges[i].first, edges[i].second, weights[i]);
        }
    }

private:
    size_t size_;
    std::vector<std::vector<Edge>> adj_list_; // adj_list_[i][j] == структура Edge для ребра из вершины i в вершину j
};

class DirGrapfAdjMatrix
{
public:
    DirGrapfAdjMatrix(size_t n_vertices, const std::vector<std::pair<size_t, size_t>> &edges, const std::vector<int64_t> &weights) : adj_matrix_(n_vertices, std::vector<Edge>(n_vertices, Edge(0, 0, -1)))
    {

        for (size_t i = 0; i < edges.size(); ++i)
        {
            adj_matrix_[edges[i].first][edges[i].second].from = edges[i].first;
            adj_matrix_[edges[i].first][edges[i].second].to = edges[i].second;
            adj_matrix_[edges[i].first][edges[i].second].weight = weights[i];
        }
    }

private:
    size_t size_;
    std::vector<std::vector<Edge>> adj_matrix_; // adj_list_[i][j] == структура Edge для ребра из вершины i в вершину j
};

class GraphEdgeList
{
public:
    GraphEdgeList(std::vector<std::pair<size_t, size_t>> edges, std::vector<int64_t> weights)
    {
        for (size_t i = 0; i < edges.size(); ++i)
        {
            edge_list_.emplace_back(edges[i].first, edges[i].second, weights[i]);
        }
    }

private:
    std::vector<Edge> edge_list_;
};

#endif
