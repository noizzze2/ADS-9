// Copyright 2022 NNTU-CS
#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include "tree.h"

int main() {
  std::srand(static_cast<unsigned>(std::time(nullptr)));

  for (int n = 2; n <= 8; n++) {
    std::vector<char> input;
    for (int i = 0; i < n; i++) input.push_back('a' + i);

    PMTree tree(input);
    int total = 1;
    for (int i = 2; i <= n; i++) total *= i;

    int rnd = std::rand() % total + 1;

    auto start = std::chrono::high_resolution_clock::now();
    getAllPerms(tree);
    auto end = std::chrono::high_resolution_clock::now();
    double tAll = std::chrono::duration<double>(end - start).count();

    start = std::chrono::high_resolution_clock::now();
    getPerm1(tree, rnd);
    end = std::chrono::high_resolution_clock::now();
    double t1 = std::chrono::duration<double>(end - start).count();

    start = std::chrono::high_resolution_clock::now();
    getPerm2(tree, rnd);
    end = std::chrono::high_resolution_clock::now();
    double t2 = std::chrono::duration<double>(end - start).count();

    std::cout << n << " " << tAll << " " << t1 << " " << t2 << std::endl;
  }

  return 0;
}
