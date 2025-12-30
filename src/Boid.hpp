#pragma once
#include "RealVector.hpp"
#include "raylib.h"
#include <vector>
using std::vector;

class Boid {
    public:
        RealVector position, velocity;
        float danger_zone, sight_zone, size;
        Color color;
        
        Boid();
        Boid(float x, float y, float vx, float vy, float _danger_zone, float _sight_zone, float _size);

        void move_boid();
        void show_boid();
        // void bound_boid(Boid &boid, double turn_factor, float turn_padding, int sw, int sh);
        // void limit_speed(Boid &boid, float min_speed, float max_speed);
};

void limit_speed(Boid &boid, float min_speed, float max_speed);
void bound_boid(Boid &boid, double turn_factor, float turn_padding, int sw, int sh);
void alter_boid_path(vector<Boid> &boids, int boid_idx, double avoidance_factor, double matching_factor, double centering_factor);