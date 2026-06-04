// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <utility>
#include <vector>

class PMTree {
 private:
  struct Node {
    char value;
    std::vector<Node*> children;
    explicit Node(char v) : value(v) {}
  };

  Node* root;
  int permCount;

  Node* buildTree(Node* parent, std::vector<char> remaining) {
    if (remaining.empty()) return nullptr;
    Node* node = new Node(remaining[0]);
    if (parent) parent->children.push_back(node);
    std::vector<char> next(remaining.begin() + 1, remaining.end());
    for (size_t i = 0; i < next.size(); i++) {
      std::vector<char> newRemaining = next;
      buildTree(node, newRemaining);
      if (!next.empty()) {
        char tmp = next[0];
        next.erase(next.begin());
        next.push_back(tmp);
      }
    }
    return node;
  }

  void deleteTree(Node* node) {
    if (!node) return;
    for (Node* child : node->children) deleteTree(child);
    delete node;
  }

  void collectPerms(Node* node, std::vector<char>& current,
                    std::vector<std::vector<char>>& result) {
    current.push_back(node->value);
    if (node->children.empty()) {
      result.push_back(current);
    } else {
      for (Node* child : node->children) {
        collectPerms(child, current, result);
      }
    }
    current.pop_back();
  }

 public:
  explicit PMTree(const std::vector<char>& input) : root(nullptr), permCount(0) {
    if (input.empty()) return;
    std::vector<char> sorted = input;
    for (size_t i = 0; i < sorted.size() - 1; i++) {
      for (size_t j = i + 1; j < sorted.size(); j++) {
        if (sorted[i] > sorted[j]) std::swap(sorted[i], sorted[j]);
      }
    }
    root = new Node(0);
    permCount = 1;
    for (size_t i = 2; i <= sorted.size(); i++) permCount *= i;
    std::vector<char> remaining = sorted;
    for (size_t i = 0; i < sorted.size(); i++) {
      buildTree(root, remaining);
      if (!remaining.empty()) {
        char tmp = remaining[0];
        remaining.erase(remaining.begin());
        remaining.push_back(tmp);
      }
    }
  }

  ~PMTree() { deleteTree(root); }

  std::vector<std::vector<char>> getAllPerms() {
    std::vector<std::vector<char>> result;
    if (!root) return result;
    for (Node* child : root->children) {
      std::vector<char> current;
      collectPerms(child, current, result);
    }
    return result;
  }

  std::vector<char> getPerm1(int num) {
    if (num < 1 || num > permCount) return {};
    auto all = getAllPerms();
    return all[num - 1];
  }

  std::vector<char> getPerm2(int num) {
    if (num < 1 || num > permCount) return {};
    num--;
    Node* current = root;
    std::vector<char> result;
    while (!current->children.empty()) {
      int fact = 1;
      int depth = 0;
      Node* tmp = current->children[0];
      while (!tmp->children.empty()) {
        depth++;
        tmp = tmp->children[0];
      }
      for (int i = 2; i <= depth; i++) fact *= i;
      int idx = num / fact;
      num %= fact;
      current = current->children[idx];
      result.push_back(current->value);
    }
    return result;
  }
};

std::vector<std::vector<char>> getAllPerms(PMTree& tree);
std::vector<char> getPerm1(PMTree& tree, int num);
std::vector<char> getPerm2(PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
