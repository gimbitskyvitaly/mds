#pragma once
#include <iostream>
#include <queue>
#include <vector>

int bfs_visited(std::vector<std::vector<int>> g, int s) {
  int n = g.size();
  std::vector<bool> visited(n, false);
  std::queue<int> q;
  int visited_count = 0;
  q.push(s);
  int vertex;
  visited[s] = true;
  visited_count++;
  while (!q.empty()) {
    vertex = q.front();
    q.pop();
    for (auto x : g[vertex]) {
      if (visited[x] == false) {
        visited[x] = true;
        visited_count++;
        q.push(x);
      }
    }
  }
  return visited_count;
}

bool is_tree(std::vector<std::vector<int>> g) {
  int n = g.size();
  if (bfs_visited(g, 0) != n) {
    return false;
  }
  int m = 0;
  for (auto x : g) {
    m += x.size();
  }
  return m / 2 == n - 1;
}