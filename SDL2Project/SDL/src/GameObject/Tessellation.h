#pragma once
#include <iostream>
#include <vector>
#include <stack>
#include <random>


class MazeGenerator {
public:

    MazeGenerator(int width, int height);

    std::pair<std::pair<int, int>, std::pair<int, int>> generateMazeWithStartAndGoal();

    std::string generateMaze();

private:
    int width;
    int height;
    std::vector<std::vector<int>> maze;

    std::vector<std::pair<int, int>> getNeighbors(int x, int y) const {
        std::vector<std::pair<int, int>> neighbors;
        neighbors.push_back({ x - 2, y });
        neighbors.push_back({ x + 2, y });
        neighbors.push_back({ x, y - 2 });
        neighbors.push_back({ x, y + 2 });
        return neighbors;
    }
};
