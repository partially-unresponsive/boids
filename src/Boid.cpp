#include "Boid.hpp"
#include "RealVector.hpp"
#include "raylib.h"
#include <vector>
using std::vector;

Boid::Boid(){}
Boid::Boid(float x, float y, float vx, float vy, float _danger_zone, float _sight_zone, float _size){
    position.x = x;
    position.y = y;
    velocity.x = vx;
    velocity.y = vy;
    this->danger_zone = _danger_zone;
    this->sight_zone = _sight_zone;
    this->size = _size;
    this->color = PINK;
}

void Boid::move_boid(){
    int h = GetScreenHeight();
    int w = GetScreenWidth();
    position = position.add(velocity);
    position.x = position.x > w ? w : position.x < 0 ? 0 : position.x;
    position.y = position.y > h ? h : position.y < 0 ? 0 : position.y;
}

void Boid::show_boid(){
    float mag = velocity.getMag();

    RealVector u;
    if (mag == 0) u = RealVector(0, -size); // Points up
    else u = velocity.mult(size/mag); // Makes our vector the size of the boid

    RealVector move_to_middle(-u.x/2, -u.y/2);

    Vector2 tri[3];
    tri[0] = (Vector2){position.x + u.x + move_to_middle.x, position.y + u.y + move_to_middle.y};
    u = RealVector(u.y, -u.x); // 90 degree rotation
    tri[1] = (Vector2){position.x + u.x + move_to_middle.x, position.y + u.y + move_to_middle.y};
    u = RealVector(-u.x, -u.y); // 180 degree rotation
    tri[2] = (Vector2){position.x + u.x + move_to_middle.x, position.y + u.y + move_to_middle.y};
    
    DrawTriangleLines(tri[0], tri[1], tri[2], color);
}

void limit_speed(Boid &boid, float min_speed, float max_speed){
    double speed = boid.velocity.getMag();
    if (speed != 0){
        if (speed < min_speed) boid.velocity = boid.velocity.mult(min_speed/speed);
        else if (speed > max_speed) boid.velocity = boid.velocity.mult(max_speed/speed);
    }
}

void bound_boid(Boid &boid, double turn_factor, float turn_padding, int sw, int sh){
    if (boid.position.x < turn_padding) {
        boid.velocity.x += turn_factor;
        boid.color = PURPLE;
    } else if (boid.position.x > sw - turn_padding) {
        boid.velocity.x -= turn_factor;
        boid.color = PURPLE;
    }
    if (boid.position.y < turn_padding) {
        boid.velocity.y += turn_factor;
        boid.color = PURPLE;
    } else if (boid.position.y > sh - turn_padding) {
        boid.velocity.y -= turn_factor;
        boid.color = PURPLE;
    }
}

void alter_boid_path(vector<Boid> &boids, int boid_idx, double avoidance_factor, double matching_factor, double centering_factor){
    int neighbors = 0;
    RealVector vel_avg(0, 0);
    RealVector pos_avg(0, 0);
    RealVector close_d(0, 0);

    for (int i = 0; i < boids.size(); i++){
        if (boid_idx == i) continue;

        RealVector diff = boids[boid_idx].position.sub(boids[i].position);

        float dis = diff.getMag();
        if (dis < boids[boid_idx].danger_zone){
            if (dis == 0) boids[boid_idx].move_boid();
            close_d = close_d.add(diff);
        } else if (dis < boids[boid_idx].sight_zone){
            vel_avg = vel_avg.add(boids[i].velocity);
            pos_avg = pos_avg.add(boids[i].position);
            neighbors++;
        }
    }
    if (neighbors > 0){
        vel_avg = vel_avg.mult(1.0f/neighbors);
        pos_avg = pos_avg.mult(1.0f/neighbors);

        // Alignment
        RealVector change_vel = vel_avg.sub(boids[boid_idx].velocity).mult(matching_factor);
        boids[boid_idx].velocity = boids[boid_idx].velocity.add(change_vel);

        // Cohesion
        RealVector change_pos = pos_avg.sub(boids[boid_idx].position).mult(centering_factor);
        boids[boid_idx].velocity = boids[boid_idx].velocity.add(change_pos);
    }

    // Separation
    boids[boid_idx].velocity = boids[boid_idx].velocity.add(close_d.mult(avoidance_factor));
}