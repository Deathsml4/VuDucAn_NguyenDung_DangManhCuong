#include "PerlinNoise.h"

PerlinNoise::PerlinNoise()
{
    // Initialize permutation vector with values from 0 to 255
    for (int i = 0; i < 256; ++i)
        p[i] = i;

    // Shuffle the permutation vector
    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(std::begin(p), std::begin(p) + 256, g);

    // Duplicate the permutation vector to simplify calculation
    for (int i = 0; i < 256; ++i)
        p[256 + i] = p[i];
}

double PerlinNoise::noise(double x, double y)
{
    int X = (int)floor(x) & 255;       // Calculate X coordinate on the unit square
    int Y = (int)floor(y) & 255;       // Calculate Y coordinate on the unit square

    x -= floor(x);                      // Calculate fractional part of X
    y -= floor(y);                      // Calculate fractional part of Y

    double u = fade(x);                 // Calculate fade curves for X
    double v = fade(y);                 // Calculate fade curves for Y

    int A = p[X] + Y;                   // Calculate hash coordinates of the 4 corners
    int B = p[X + 1] + Y;
    int AA = p[A];
    int BA = p[B];
    int AB = p[A + 1];
    int BB = p[B + 1];

    double result = lerp(v, lerp(u, grad(p[AA], x, y), grad(p[BA], x - 1, y)),
        lerp(u, grad(p[AB], x, y - 1), grad(p[BB], x - 1, y - 1)));
    return (result + 1.0) / 2.0;        // Return value in the range [0, 1]
}


