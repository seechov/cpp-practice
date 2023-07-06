#include <iostream>

struct Node final {
public:
  
  Node(int value): next(nullptr), value(value) {}
  
  Node* next;
  int value; 
};


Node* find(Node* head, int k) {
  Node* node_result = head;
  int i = 0;
  Node* current_node = head;
  while (current_node != nullptr)
  {
    if (++i >= k)
    {
      node_result = node_result->next;
    }
    current_node = current_node->next;
  }
  return node_result;
}


std::ostream& operator<<(std::ostream& os, Node* head) {
  while(head != nullptr) {
    os << head->value;
    head = head->next;
  }
    
  return os << '\n';
}

Node* createList(int size) {
    if (size == 0) return nullptr;
    
    auto head = new Node(size--);
    head->next = createList(size);
    
    return head;
}


int main() {
  auto head = createList(6);
  std::cout << head;

  
  auto result = find(head, 6);
  
  if (result == nullptr) std::cout << "empty";
  else std::cout << result->value;
  
	return 0;
}
