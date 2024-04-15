#pragma once
#include <iostream>
#include <vector>
#include <stack>
#include <random>


class MazeGenerator {
public:

    MazeGenerator(int width, int height) : width(width), height(height) {
        maze.resize(height, std::vector<int>(width, 1)); // Initialize maze with all walls
    }

    std::pair<std::pair<int, int>, std::pair<int, int>> generateMazeWithStartAndGoal() {
        // Generate the maze
        generateMaze();

        // Initialize random number generator
        std::random_device rd;
        std::mt19937 gen(rd());

        // Choose random start and goal positions
        int startX = std::uniform_int_distribution<int>(1, width - 2)(gen);
        int startY = std::uniform_int_distribution<int>(1, height - 2)(gen);
        int goalX = std::uniform_int_distribution<int>(1, width - 2)(gen);
        int goalY = std::uniform_int_distribution<int>(1, height - 2)(gen);

        // Ensure start and goal positions are not walls
        while (maze[startY][startX] == 1 || maze[goalY][goalX] == 1) {
            startX = std::uniform_int_distribution<int>(1, width - 2)(gen);
            startY = std::uniform_int_distribution<int>(1, height - 2)(gen);
            goalX = std::uniform_int_distribution<int>(1, width - 2)(gen);
            goalY = std::uniform_int_distribution<int>(1, height - 2)(gen);
        }

        // Convert maze to string
        std::string mazeString;
        for (const auto& row : maze) {
            for (int cell : row) {
                mazeString += (cell == 1) ? '7' : '0';
            }
        }

        return { {startX, startY}, {goalX, goalY} };
    }

    std::string generateMaze() {
        // Initialize random number generator
        std::random_device rd;
        std::mt19937 gen(rd());

        // Choose a random starting point
        int startX = std::uniform_int_distribution<int>(1, width - 2)(gen);
        int startY = std::uniform_int_distribution<int>(1, height - 2)(gen);

        // Create a stack to store visited cells
        std::stack<std::pair<int, int>> cellStack;
        cellStack.push({ startX, startY });
        maze[startY][startX] = 0; // Set starting cell to empty space

        while (!cellStack.empty()) {
            int x = cellStack.top().first;
            int y = cellStack.top().second;
            cellStack.pop();

            std::vector<std::pair<int, int>> neighbors = getNeighbors(x, y);
            std::shuffle(neighbors.begin(), neighbors.end(), gen);

            for (const auto& neighbor : neighbors) {
                int nx = neighbor.first;
                int ny = neighbor.second;

                if (nx > 0 && nx < width - 1 && ny > 0 && ny < height - 1 && maze[ny][nx] == 1) {
                    maze[ny][nx] = 0; // Set cell to empty space
                    maze[(y + ny) / 2][(x + nx) / 2] = 0; // Set wall between current cell and neighbor to empty space
                    cellStack.push({ nx, ny });
                }
            }
        }

        // Choose a random position for the goal
        int goalX = std::uniform_int_distribution<int>(1, width - 2)(gen);
        int goalY = std::uniform_int_distribution<int>(1, height - 2)(gen);
        maze[goalY][goalX] = 2; // Set goal position

        // Convert maze to string
        std::string mazeString;
        for (const auto& row : maze) {
            for (int cell : row) {
                mazeString += (cell == 1) ? '7' : (cell == 2) ? '8' : '0'; // Walls, Goal, Empty Space
            }
        }

        return mazeString;
    }

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
