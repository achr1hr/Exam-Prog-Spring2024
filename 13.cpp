#include <iostream>
#include <vector>
#include <cstring>
// Теорма Бержа
/*
 Паросочетание без увеличивающих цепей является максимальным.
 */

// Алгоритм Куна
const int maxn = 100;
const int size_left = 4; // Вершин левой доли

std::vector<int> g[maxn]; // будем хранить только рёбра из левой доли в правую
int mt[maxn]; // с какой вершиной сматчена вершина правой доли (-1, если ни с какой)
bool used[maxn]; // вспомогательный массив для поиска пути DFS-ом

  // DFS возвращает, можно ли найти путь из вершины v в какую-нибудь вершину правой доли
  // если можно, то ещё и проводит чередование
bool DFS(int v) {
  if (used[v]) {
    return false; // Если вершина уже была посещена, завершаем текущий DFS
  }
  used[v] = true; // Отмечаем вершину как посещенную
  for (int u : g[v]) { // Обходим всех соседей вершины v
                       // если вершина u свободна или можно найти чередующийся путь
    if (mt[u] == -1 || DFS(mt[u])) {
      mt[u] = v; // Вершина u сматчивается с вершиной v
      return true; // Возвращаем true, так как найден чередующийся путь
    }
  }
  return false; // Если не найден чередующийся путь, возвращаем false
}

  // Теперь, для нахождения самого паросочетания нужно просто запустить этот поиск от всех вершин левой доли, откатывая состояние вспомогательного массива used
void Kun() {
  std::memset(mt, -1, sizeof(mt)); // Инициализируем mt значением -1
  size_t counter = 0; // для подсчета количества найденных паросочетаний
  for (int i = 0; i < size_left; i++) {
    std::memset(used, 0, sizeof(used)); // очищаем массив used перед каждым запуском DFS
    if (DFS(i)) {
      counter++;
    }
  }
  std::cout << "Maximum matching size: " << counter << std::endl;
}

int main() {
    // Пример использования:
    // Добавляем рёбра в граф (пример)
  g[0].push_back(1); // 0 - a
  g[0].push_back(2); // 0 - b
  g[1].push_back(1); // 1 - a
  g[1].push_back(3); // 1 - c
  g[2].push_back(2); // 2 - b
  
  std::cout<<g[0].front();
  Kun();
  
    // Выводим результаты
  for (int i = 0; i < maxn; ++i) {
    if (mt[i] != -1) {
      std::cout << "Vertex " << mt[i] << " in left part is matched with vertex " << i << " in right part." << std::endl;
    }
  }
  return 0;
}
// Асимптотика O(VE)