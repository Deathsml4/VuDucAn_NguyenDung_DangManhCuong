#include <iostream>
#include <cmath>
#include <random>
#include <string>

class PerlinNoise {
public:
    PerlinNoise();

    double noise(double x, double y);

private:
    double fade(double t) const {
        return t * t * t * (t * (t * 6 - 15) + 10);
    }

    double lerp(double t, double a, double b) const {
        return a + t * (b - a);
    }

    double grad(int hash, double x, double y) const {
        int h = hash & 7;                   // Convert low 3 bits of hash code
        double u = h < 4 ? x : y;           // into 8 gradient directions.
        double v = h < 4 ? y : x;
        return ((h & 1) ? -u : u) + ((h & 2) ? -2.0 * v : 2.0 * v);
    }

    int p[512];
};