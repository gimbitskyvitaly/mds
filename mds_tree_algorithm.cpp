#include <iostream>
#include <vector>
#include "mds_algorithm.h"

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
