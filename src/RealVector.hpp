#pragma once

class RealVector {
    public: 
        float x, y;

        RealVector();
        RealVector(float x, float y);
        
        RealVector add(RealVector &vec);
        RealVector sub(RealVector &vec);
        RealVector mult(float num);
        RealVector limit(float min_speed, float max_speed);

        float getMag();
        float angleOf();
};