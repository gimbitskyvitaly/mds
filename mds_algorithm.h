#pragma once
#include <iostream>

int vertex_max_degry(std::vector<int> degry);

std::vector<int> mds_tree(std::vector<std::vector<int>> g);

std::vector<int> greedy_mds(std::vector<std::vector<int>> g);

std::vector<int> accurate_mds(std::vector<std::vector<int>> g);