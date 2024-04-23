#pragma once

#include <iostream>
#include <vector>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include <cmath>   // For math functions

using namespace std;

// Constants
const int SWARM_SIZE = 10;
const int GRID_SIZE = 10;
const double MAX_SPEED = 1.0;
const double C1 = 2.0; // Cognitive coefficient
const double C2 = 2.0; // Social coefficient

// Structure to represent a particle (or animal)
struct Particle {
    double x, y;     // Position
    double vx, vy;   // Velocity
    double bestX, bestY; // Best position found by this particle
    double bestFitness;  // Best fitness value found by this particle
};

// Function to initialize particles
void initializeParticles(vector<Particle>& swarm) {
    for (int i = 0; i < SWARM_SIZE; ++i) {
        swarm[i].x = rand() % GRID_SIZE; // Random initial position
        swarm[i].y = rand() % GRID_SIZE;
        swarm[i].vx = (double)(rand() % 100) / 100 * MAX_SPEED; // Random initial velocity
        swarm[i].vy = (double)(rand() % 100) / 100 * MAX_SPEED;
        swarm[i].bestX = swarm[i].x; // Initially, the current position is the best
        swarm[i].bestY = swarm[i].y;
        // Calculate fitness (you may define your own fitness function based on game objectives)
        swarm[i].bestFitness = pow(swarm[i].x - GRID_SIZE / 2, 2) + pow(swarm[i].y - GRID_SIZE / 2, 2);
    }
}

// Function to update particle velocities and positions
void updateParticles(vector<Particle>& swarm, double& globalBestFitness, double& globalBestX, double& globalBestY) {
    for (int i = 0; i < SWARM_SIZE; ++i) {
        // Update velocity
        double r1 = (double)rand() / RAND_MAX;
        double r2 = (double)rand() / RAND_MAX;
        swarm[i].vx = swarm[i].vx + C1 * r1 * (swarm[i].bestX - swarm[i].x) + C2 * r2 * (globalBestX - swarm[i].x);
        swarm[i].vy = swarm[i].vy + C1 * r1 * (swarm[i].bestY - swarm[i].y) + C2 * r2 * (globalBestY - swarm[i].y);
        // Limit velocity
        swarm[i].vx = min(max(swarm[i].vx, -MAX_SPEED), MAX_SPEED);
        swarm[i].vy = min(max(swarm[i].vy, -MAX_SPEED), MAX_SPEED);
        // Update position
        swarm[i].x = swarm[i].x + swarm[i].vx;
        swarm[i].y = swarm[i].y + swarm[i].vy;
        // Update best position and fitness
        double fitness = pow(swarm[i].x - GRID_SIZE / 2, 2) + pow(swarm[i].y - GRID_SIZE / 2, 2);
        if (fitness < swarm[i].bestFitness) {
            swarm[i].bestFitness = fitness;
            swarm[i].bestX = swarm[i].x;
            swarm[i].bestY = swarm[i].y;
        }
        // Update global best position and fitness
        if (fitness < globalBestFitness) {
            globalBestFitness = fitness;
            globalBestX = swarm[i].x;
            globalBestY = swarm[i].y;
        }
    }
}

