#pragma once
#include <iostream>
#include <queue>
#include <set>
#include <vector>

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

std::vector<int> mds_tree(std::vector<std::vector<int>> g) {
  int n = g.size();
  std::vector<char> type(n, 'b');
  std::vector<int> domination_set;
  std::vector<bool> vis(n, false);
  int list;
  for (int k = 0; k < n - 1; k++) {
    for (int i = 0; i < n; i++) {
      if (g[i].size() == 1) {
        list = i;
        break;
      }
    }
    if (type[list] == 'b') {
      type[g[list][0]] = 'r';
    } else if (type[list] == 'r') {
      if (type[g[list][0]] != 'r') {
        type[g[list][0]] = 'f';
      }
      domination_set.push_back(list);
    }
    std::vector<int>::iterator it;
    for (int i = 0; i < n; i++) {
      it = std::find(g[i].begin(), g[i].end(), list);
      if (it != g[i].end()) {
        g[i].erase(it);
      }
    }
    g[list].clear();
    vis[list] = true;
  }
  for (int i = 0; i < n; i++) {
    if (vis[i] == false) {
      if (type[i] != 'f') {
        domination_set.push_back(i);
      }
    }
  }
  return domination_set;
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

std::vector<int> accurate_mds(std::vector<std::vector<int>> g) {
  int n = g.size();
  int count = n / 4;
  int left = 0;
  int right = n / 2 + 1;
  std::vector<int> is_dominated(n + 1);
  std::vector<int> domination_set;
  int max_count = std::pow(2, n + 1);
  int buff_count;
  std::vector<bool> dominated_set(n, false);
  int visited_count;
  std::vector<int> permutation(n);
  while (true) {
    permutation = std::vector<int>(n, 0);
    for (int i = n - 1; i >= n - count; i--) {
      permutation[i] = 1;
    }
    while (std::next_permutation(permutation.begin(), permutation.end())) {
      if (permutation[1] == 1 && permutation[3] == 1 && permutation[4] == 1 &&
          permutation[7] == 1 && permutation[8] == 1 && permutation[12] == 1 &&
          permutation[15] == 1 && permutation[16] == 1 &&
          permutation[20] == 1) {
        std::cout << "domination" << std::endl;
      }
      domination_set.clear();
      dominated_set = std::vector<bool>(n, false);
      for (int i = 0; i < n; i++) {
        if (permutation[i] == 1) {
          domination_set.push_back(i);
          dominated_set[i] = true;
          for (auto x : g[i]) {
            dominated_set[x] = true;
          }
        }
      }
      visited_count = 0;
      for (int i = 0; i < n; i++) {
        if (dominated_set[i] == true) {
          visited_count++;
        }
      }
      if (visited_count == n) {
        if (count == 0 || is_dominated[count - 1] == -1) {
          return domination_set;
        } else {
          is_dominated[count] = 1;
          right = count;
          break;
        }
      } else {
        is_dominated[count] = -1;
      }
    }
    if (is_dominated[count] == -1) {
      left = count + 1;
    }
    count = (left + right) / 2;
  }
  return domination_set;
}