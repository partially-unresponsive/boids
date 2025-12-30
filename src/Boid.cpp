#include "Boid.hpp"
#include "RealVector.hpp"
#include "raylib.h"

Boid::Boid(){}
Boid::Boid(float x, float y, float vx, float vy, float _danger_zone, float _sight_zone, float _size){
    position.x = x;
    position.y = y;
    velocity.x = vx;
    velocity.y = vy;
    this->danger_zone = _danger_zone;
    this->sight_zone = _sight_zone;
    this->size = _size;
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
    
    DrawTriangleLines(tri[0], tri[1], tri[2], PINK);
}

void limit_speed(Boid &boid, float min_speed, float max_speed){
    double speed = boid.velocity.getMag();
    if (speed != 0){
        if (speed < min_speed) boid.velocity = boid.velocity.mult(min_speed/speed);
        else if (speed > max_speed) boid.velocity = boid.velocity.mult(max_speed/speed);
    }
}

void bound_boid(Boid &boid, double turn_factor, float turn_padding, int sw, int sh){
    if (boid.position.x < turn_padding) boid.velocity.x += turn_factor;
    else if (boid.position.x > sw - turn_padding) boid.velocity.x -= turn_factor;
    if (boid.position.y < turn_padding) boid.velocity.y += turn_factor;
    else if (boid.position.y > sh - turn_padding) boid.velocity.y -= turn_factor;
}