#include<iostream>
#include<fstream>
#include<vector>
#include"graph_type_algorithm.h"
#include"mds_algorithm.h"


int main() {
  int n, m;
  std::ifstream fin("input.txt");
  fin >> n >> m;
  std::vector<std::vector<int>> g = std::vector<std::vector<int>>(n);
  int u, v;
  for (int i = 0; i < m; i++) {
    fin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  std::vector<int> domination_set;

  if (is_tree(g) == true) {
    domination_set = mds_tree(g);
  } else if (n <= 30) {
    domination_set = accurate_mds(g);
  } else {
    domination_set = greedy_mds(g);
  }

  std::ofstream fout;
  fout.open("output.txt");
  if (fout.is_open()) {
    for (int i = 0; i < domination_set.size(); i++) {
      fout << domination_set[i] << " ";
    }
  }
  return 0;
}