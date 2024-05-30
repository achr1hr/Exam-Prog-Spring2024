#include <cstdint>
#include <iostream>
#include <vector>

class DSU {
 public:
  explicit DSU(int64_t n_verts) : belong_list_(n_verts, -1), sizes_(n_verts, 1), n_verts_(n_verts) {
  }
  void Addedge(int64_t from, int64_t to, int64_t weight);
  int64_t Find(int64_t ind) {
    if (belong_list_[ind] == -1) {
      return ind;
    }
    return belong_list_[ind] = Find(belong_list_[ind]);
  }
  int64_t Weightout() {
    return weight_;
  }

 private:
  int64_t weight_ = 0;
  std::vector<int64_t> belong_list_;
  std::vector<int64_t> sizes_;
  bool flag_ = false;
  int64_t n_verts_;
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int64_t n_verts = 0;
  uint64_t n_calls = 0;
  std::cin >> n_verts >> n_calls;
  DSU dsu(n_verts);
  int64_t from = 0;
  int64_t to = 0;
  int64_t weight = 0;
  for (uint64_t i = 0; i < n_calls; ++i) {
    std::cin >> from >> to >> weight;
    dsu.Addedge(from - 1, to - 1, weight);
  }
  std::cout << dsu.Weightout();
}

void DSU::Addedge(int64_t from, int64_t to, int64_t weight) {
  if (flag_) {
    return;
  }
  int64_t from_root = Find(from);
  int64_t to_root = Find(to);
  if (from_root == to_root) {
    return;
  }
  if (sizes_[from_root] >= sizes_[to_root]) {
    belong_list_[to_root] = from_root;
    sizes_[from_root] += sizes_[to_root];
    weight_ += weight;
    if (sizes_[from_root] == n_verts_) {
      flag_ = true;
    }
  } else {
    belong_list_[from_root] = to_root;
    sizes_[to_root] += sizes_[from_root];
    weight_ += weight;
    if (sizes_[to_root] == n_verts_) {
      flag_ = true;
    }
  }
}
