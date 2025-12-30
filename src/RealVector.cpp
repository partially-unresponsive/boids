#include "RealVector.hpp"
#include <cmath>

RealVector::RealVector() {}
RealVector::RealVector(float x_, float y_) {
    x = x_;
    y = y_;
}

RealVector RealVector::add(RealVector &vec){
    return RealVector(x+vec.x, y+vec.y);
}

RealVector RealVector::sub(RealVector &vec){
    return RealVector(x-vec.x, y-vec.y);
}

RealVector RealVector::mult(float num){
    return RealVector(x*num, y*num);
}

RealVector RealVector::limit(float min_speed, float max_speed){
    float mag = getMag();
    RealVector res = *this;
    if (mag == 0) return res;

    if (mag > max_speed) res = res.mult(max_speed / mag);
    else if (mag < min_speed) res = res.mult(min_speed / mag);
    return res;
}

float RealVector::getMag() {
    return sqrt(pow(x, 2) + pow(y, 2));
}

float RealVector::angleOf() {
    return atan2(y, x);
}