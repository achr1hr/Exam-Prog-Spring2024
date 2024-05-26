#include <iostream>
class Hashtable {
 private:
  class TLList {
   private:
    struct Node {
      Node* prev = nullptr;
      Node* next = nullptr;
      std::string name;
      size_t num;
    };

   public:
    TLList();
    void PushB(std::string name, size_t num);
    void Remove(size_t num);
    void Find(size_t num);
    ~TLList();

   private:
    size_t size_;
    Node* top;
    Node* back;
  };

 public:
  Hashtable();
  void add(size_t num, std::string name);
  void del(size_t num);
  void find(size_t num);
  ~Hashtable();

 private:
  TLList* list_;
  size_t size_ = 10000000;
};

Hashtable::TLList::TLList() {
  top = nullptr;
  back = nullptr;
  size_ = 0;
}
Hashtable::TLList::~TLList() {
  Node* runner = top;
  while (runner) {
    Node* node = runner;
    runner = runner->next;
    delete node;
  }
}
void Hashtable::TLList::Find(size_t num) {
  if (size_) {
    Node* runner = top;
    while (runner) {
      if (runner->num == num) {
        std::cout << runner->name << '\n';
        return;
      }
      runner = runner->next;
    }
  }
  std::cout << "not found" << '\n';
}
void Hashtable::TLList::PushB(std::string name, size_t num) {
  if (!size_) {
    Node* new_node = new Node{nullptr, nullptr, name, num};
    top = new_node;
    back = new_node;
    size_ = 1;
    return;
  }
  Node* runner = top;
  Node* prev = runner;
  while (runner) {
    if (runner->num == num) {
      runner->name = name;
      return;
    }
    prev = runner;
    runner = runner->next;
  }
  runner = new Node{prev, nullptr, name, num};
  runner->prev->next = runner;
  size_ += 1;
}
void Hashtable::TLList::Remove(size_t num) {
  Node* runner = top;
  if (size_) {
    while (runner) {
      if (runner->num == num) {
        if (runner->prev) {
          runner->prev->next = runner->next;
          delete runner;
        } else {
          top = runner->next;
          delete runner;
        }
        size_ -= 1;
        return;
      }
      runner = runner->next;
    }
  }
}
Hashtable::Hashtable() { list_ = new TLList[size_]; }
Hashtable::~Hashtable() { delete[] list_; }
void Hashtable::add(size_t num, std::string name) {
  list_[num % size_].PushB(name, num);
}
void Hashtable::del(size_t num) { list_[num % size_].Remove(num); }
void Hashtable::find(size_t num) { list_[num % size_].Find(num); }

int main() {
  Hashtable hash;
  std::string command, name;
  size_t commands, number;
  std::cin >> commands;
  for (size_t i = 0; i < commands; ++i) {
    std::cin >> command;
    if (command == "add") {
      std::cin >> number >> name;
      hash.add(number, name);
    }
    if (command == "del") {
      std::cin >> number;
      hash.del(number);
    }
    if (command == "find") {
      std::cin >> number;
      hash.find(number);
    }
  }
}
