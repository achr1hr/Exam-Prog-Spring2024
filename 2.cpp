#include <math.h>

#include <iostream>

class Hashtable {
 public:
  Hashtable();
  void add(std::string str);
  void del(std::string str);
  void find(std::string str);
  size_t Poly(const std::string& str);
  size_t Rhash(const size_t& key);
  ~Hashtable();

 private:
  std::string* list_;
  size_t size_ = 1000000;
};

Hashtable::Hashtable() { list_ = new std::string[size_]; }
Hashtable::~Hashtable() { delete[] list_; }
void Hashtable::add(std::string str) {
  size_t first_hash = Poly(str);
  for (size_t i = 0; i < size_; ++i) {
    if (list_[(first_hash + Rhash(first_hash) * i) % size_] == "\0") {
      list_[(first_hash + Rhash(first_hash) * i) % size_] = str;
      return;
    }
  }
}
void Hashtable::del(std::string str) {
  size_t first_hash = Poly(str);
  for (size_t i = 0; i < size_; ++i) {
    if (list_[(first_hash + Rhash(first_hash) * i) % size_] == str) {
      list_[(first_hash + Rhash(first_hash) * i) % size_] = "\0";
      std::cout << "TRUE\n";
      return;
    }
    if (list_[(first_hash + Rhash(first_hash) * i) % size_] == "\0") {
      std::cout << "FALSE\n";
      return;
    }
  }
  std::cout << "FALSE\n";
}
void Hashtable::find(std::string str) {
  size_t first_hash = Poly(str);
  for (size_t i = 0; i < size_; ++i) {
    if (list_[(first_hash + Rhash(first_hash) * i) % size_] == str) {
      std::cout << "TRUE\n";
      return;
    }
    if (list_[(first_hash + Rhash(first_hash) * i) % size_] == "\0") {
      std::cout << "FALSE\n";
      return;
    }
  }
  std::cout << "FALSE\n";
}

int main() {
  Hashtable hash;
  std::string command, str;
  size_t commands;
  std::cin >> commands;
  for (size_t i = 0; i < commands; ++i) {
    std::cin >> command;
    if (command == "push") {
      std::cin >> str;
      hash.add(str);
    }
    if (command == "pop") {
      std::cin >> str;
      hash.del(str);
    }
    if (command == "search") {
      std::cin >> str;
      hash.find(str);
    }
  }
}
size_t Hashtable::Poly(const std::string& str) {
  const static __INT64_TYPE__ p = 1000000007;
  const static __INT64_TYPE__ x = 263;
  __INT64_TYPE__ sum = 0;
  __INT64_TYPE__ x_pow = 1;
  for (__INT64_TYPE__ i = 0; i < str.length(); ++i) {
    sum = (sum + (str[i] * x_pow % p)) % p;
    x_pow = (x_pow * x) % p;
  }
  return sum;
}
size_t Hashtable::Rhash(const size_t& key) {
  const float Koreman = (pow(5, 0.5) - 1) / 2;
  return static_cast<size_t>(
      size_ * ((key * Koreman) - static_cast<int>(key * Koreman)));
}