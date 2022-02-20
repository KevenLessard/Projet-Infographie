#include "primitives3D.h"

spherePrimitive::spherePrimitive() {
    texCoords = { 0.f, 0.f, 1.f, 1.f };
    radius = 20;
    setResolution(16);
}


spherePrimitive::spherePrimitive(float _radius, int res, ofPrimitiveMode mode) {
    radius = _radius;
    texCoords = { 0.f, 0.f, 1.f, 1.f };
    setResolution(res);
}

spherePrimitive::~spherePrimitive() {

}

void spherePrimitive::set(float _radius, int res, ofPrimitiveMode mode) {
    radius = _radius;
    resolution = res;

    getMesh() = ofMesh::sphere(getRadius(), getResolution(), mode);

    normalizeAndApplySavedTexCoords();
}

void spherePrimitive::setResolution(int res) {
    resolution = res;
    ofPrimitiveMode mode = getMesh().getMode();

    set(getRadius(), getResolution(), mode);
}

void spherePrimitive::setMode(ofPrimitiveMode mode) {
    ofPrimitiveMode currMode = getMesh().getMode();
    if (currMode != mode)
        set(getRadius(), getResolution(), mode);
}

void spherePrimitive::setRadius(float _radius) {
    radius = _radius;
    setResolution(getResolution());
}

float spherePrimitive::getRadius() const {
    return radius;
}

int spherePrimitive::getResolution() const {
    return resolution;
}


//Box