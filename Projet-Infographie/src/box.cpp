#include "box.h"

using namespace std;

boxPrimitive::boxPrimitive() {
    texCoords = { 0.f, 0.f, 1.f, 1.f };
    set(100, 100, 100, 2, 2, 2);
}

boxPrimitive::boxPrimitive(float width, float height, float depth, int resWidth, int resHeight, int resDepth) {
    texCoords = { 0.f, 0.f, 1.f, 1.f };
    set(width, height, depth, resWidth, resHeight, resDepth);
}

boxPrimitive::~boxPrimitive() {}

void boxPrimitive::set(float width, float height, float depth, int resWidth, int resHeight, int resDepth) {

    size.x = width;
    size.y = height;
    size.z = depth;

    resolution = { resWidth, resHeight, resDepth };

    int resX = getResolution().x;
    int resY = getResolution().y;
    int resZ = getResolution().z;

    //FRONT, resY, resX
    strides[SIDE_FRONT][0] = 0;
    strides[SIDE_FRONT][1] = (resY) * (resX) * 6;
    vertices[SIDE_FRONT][0] = 0;
    vertices[SIDE_FRONT][1] = (resX + 1) * (resY + 1);

    //RIGHT, resY, resZ
    strides[SIDE_RIGHT][0] = strides[SIDE_FRONT][0] + strides[SIDE_FRONT][1];
    strides[SIDE_RIGHT][1] = (resY) * (resZ) * 6;
    vertices[SIDE_RIGHT][0] = vertices[SIDE_FRONT][0] + vertices[SIDE_FRONT][1];
    vertices[SIDE_RIGHT][1] = (resY + 1) * (resZ + 1);

    //LEFT, resY, resZ
    strides[SIDE_LEFT][0] = strides[SIDE_RIGHT][0] + strides[SIDE_RIGHT][1];
    strides[SIDE_LEFT][1] = (resY) * (resZ) * 6;
    vertices[SIDE_LEFT][0] = vertices[SIDE_RIGHT][0] + vertices[SIDE_RIGHT][1];
    vertices[SIDE_LEFT][1] = (resY + 1) * (resZ + 1);

    //BACK, resY, resX
    strides[SIDE_BACK][0] = strides[SIDE_LEFT][0] + strides[SIDE_LEFT][1];
    strides[SIDE_BACK][1] = (resY) * (resX) * 6;
    vertices[SIDE_BACK][0] = vertices[SIDE_LEFT][0] + vertices[SIDE_LEFT][1];
    vertices[SIDE_BACK][1] = (resY + 1) * (resZ + 1);

    //TOP, resZ, resX
    strides[SIDE_TOP][0] = strides[SIDE_BACK][0] + strides[SIDE_BACK][1];
    strides[SIDE_TOP][1] = (resZ) * (resX) * 6;
    vertices[SIDE_TOP][0] = vertices[SIDE_BACK][0] + vertices[SIDE_BACK][1];
    vertices[SIDE_TOP][1] = (resY + 1) * (resZ + 1);

    //BOTTOM, resZ, resX
    strides[SIDE_BOTTOM][0] = strides[SIDE_TOP][0] + strides[SIDE_TOP][1];
    strides[SIDE_BOTTOM][1] = (resZ) * (resX) * 6;
    vertices[SIDE_BOTTOM][0] = vertices[SIDE_TOP][0] + vertices[SIDE_TOP][1];
    vertices[SIDE_BOTTOM][1] = (resY + 1) * (resZ + 1);

    getMesh() = ofMesh::box(getWidth(), getHeight(), getDepth(), getResolution().x, getResolution().y, getResolution().z);

    normalizeAndApplySavedTexCoords();
}

void boxPrimitive::set(float width, float height, float depth) {
    set(width, height, depth, getResolution().x, getResolution().y, getResolution().z);
}

void boxPrimitive::set(float size) {
    set(size, size, size);
}

void boxPrimitive::setWidth(float a_width) {
    size.x = a_width;
    set(getWidth(), getHeight(), getDepth());
}

void boxPrimitive::setHeight(float a_height) {
    size.y = a_height;
    set(getWidth(), getHeight(), getDepth());
}

void boxPrimitive::setDepth(float a_depth) {
    size.z = a_depth;
    set(getWidth(), getHeight(), getDepth());
}

void boxPrimitive::resizeToTexture(ofTexture& inTexture) {
    set(inTexture.getWidth(), inTexture.getHeight(), inTexture.getWidth());
    mapTexCoordsFromTexture(inTexture);
}


vector<ofIndexType> boxPrimitive::getSideIndices(int sideIndex) const {

    if (sideIndex < 0 || sideIndex >= SIDES_TOTAL) {
        ofLogWarning("boxPrimitive") << "getSideIndices(): faceIndex out of bounds, returning SIDE_FRONT";
        sideIndex = SIDE_FRONT;
    }

    return getIndices(strides[sideIndex][0], strides[sideIndex][0] + strides[sideIndex][1]);
}

ofMesh boxPrimitive::getSideMesh(int sideIndex) const {

    if (sideIndex < 0 || sideIndex > SIDES_TOTAL) {
        ofLogWarning("boxPrimitive") << "getSideMesh(): faceIndex out of bounds, using SIDE_FRONT";
        sideIndex = SIDE_FRONT;
    }
    int startIndex = strides[sideIndex][0];
    int endIndex = startIndex + strides[sideIndex][1];

    int startVertIndex = vertices[sideIndex][0];
    int endVertIndex = startVertIndex + vertices[sideIndex][1];

    return getMesh().getMeshForIndices(startIndex, endIndex, startVertIndex, endVertIndex);
}

void boxPrimitive::setResolution(int res) {
    setResolution(res, res, res);
}

void boxPrimitive::setResolutionWidth(int widthRes) {
    setResolution(widthRes, getResolutionHeight(), getResolutionDepth());
}

void boxPrimitive::setResolutionHeight(int heightRes) {
    setResolution(getResolutionWidth(), heightRes, getResolutionDepth());
}

void boxPrimitive::setResolutionDepth(int depthRes) {
    setResolution(getResolutionWidth(), getResolutionHeight(), depthRes);
}

void boxPrimitive::setResolution(int resWidth, int resHeight, int resDepth) {
    resolution = { resWidth, resHeight, resDepth };
    set(getWidth(), getHeight(), getDepth());
}

void boxPrimitive::setMode(ofPrimitiveMode mode) {
    // only supports triangles //
    setResolution(getResolution().x, getResolution().y, getResolution().z);
}

void boxPrimitive::setSideColor(int sideIndex, ofColor color) {
    if (sideIndex < 0 || sideIndex >= SIDES_TOTAL) {
        ofLogWarning("boxPrimitive") << "setSideColor(): sideIndex out of bounds, setting SIDE_FRONT";
        sideIndex = SIDE_FRONT;
    }
    getMesh().setColorForIndices(strides[sideIndex][0], strides[sideIndex][0] + strides[sideIndex][1], color);
}

int boxPrimitive::getResolutionWidth() const {
    return (int)resolution.x;
}

int boxPrimitive::getResolutionHeight() const {
    return (int)resolution.y;
}

int boxPrimitive::getResolutionDepth() const {
    return (int)resolution.z;
}

glm::vec3 boxPrimitive::getResolution() const {
    return resolution;
}

float boxPrimitive::getWidth() const {
    return size.x;
}

float boxPrimitive::getHeight() const {
    return size.y;
}

float boxPrimitive::getDepth() const {
    return size.z;
}

glm::vec3 boxPrimitive::getSize() const {
    return size;
}