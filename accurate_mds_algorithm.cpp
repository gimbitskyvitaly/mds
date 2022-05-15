#include <iostream>
#include <queue>
#include <set>
#include <vector>

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