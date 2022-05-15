#include <iostream>
#include <vector>
#include "mds_algorithm.h"

int vertex_max_degry(std::vector<int> degry) {
  int max = -1;
  int vertex = -1;
  for (int i = 0; i < degry.size(); i++) {
    if (max < degry[i]) {
      max = degry[i];
      vertex = i;
    }
  }
  return vertex;
}

std::vector<int> greedy_mds(std::vector<std::vector<int>> g) {
  int n = g.size();
  int white_count = n;
  std::vector<int> domination_set;
  std::vector<int> white_degry(n);
  std::vector<char> type(n, 'b');
  for (int i = 0; i < n; i++) {
    white_degry[i] = g[i].size();
  }
  while (white_count != 0) {
    int vertex_max_white_degry = vertex_max_degry(white_degry);
    type[vertex_max_white_degry] = 'r';
    domination_set.push_back(vertex_max_white_degry);
    for (auto x : g[vertex_max_white_degry]) {
      type[x] = 'f';
    }
    white_count = 0;
    int j = 0;
    for (auto x : g) {
      white_degry[j] = 0;
      for (auto i : x) {
        if (type[i] == 'b') {
          white_degry[j]++;
          white_count++;
        }
      }
      j++;
    }
  }
  return domination_set;
}