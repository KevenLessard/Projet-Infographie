#pragma once

#include "of3dPrimitives.h"

class spherePrimitive : public of3dPrimitive {
public:

    spherePrimitive();

	spherePrimitive(float radius, int res, ofPrimitiveMode mode=OF_PRIMITIVE_TRIANGLE_STRIP);



    void set(float radius, int resolution,
        ofPrimitiveMode mode = OF_PRIMITIVE_TRIANGLE_STRIP);
    void setResolution(int res);
    void setRadius(float radius);
    void setMode(ofPrimitiveMode mode);

    float getRadius() const;
    int getResolution() const;

    ~spherePrimitive();

protected:
    float radius;
    int resolution;
};