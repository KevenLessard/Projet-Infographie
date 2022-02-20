#pragma once

#include "of3dPrimitives.h"
#include "ofNode.h"
#include "ofMesh.h"
#include "ofTexture.h"

//class ofTexture;
class ofVboMesh;
//class ofRectangle;

class boxPrimitive : public of3dPrimitive {
public:

    enum BoxSides {
        SIDE_FRONT,
        SIDE_RIGHT,
        SIDE_LEFT,
        SIDE_BACK,
        SIDE_TOP,
        SIDE_BOTTOM,
        SIDES_TOTAL
    };
    boxPrimitive();
    boxPrimitive(float width, float height, float depth, int resWidth = 2,
        int resHeight = 2, int resDepth = 2);
    

    void set(float width, float height, float depth, int resWidth,
        int resHeight, int resDepth);
    void set(float width, float height, float depth);
    void set(float size); // all sides the same dimensions //

    void setWidth(float a_width);
    void setHeight(float a_height);
    void setDepth(float a_depth);

    void resizeToTexture(ofTexture& inTexture);

    std::vector<ofIndexType> getSideIndices(int sideIndex) const;
    ofMesh getSideMesh(int sideIndex) const;

    void setResolution(int res); // same resolution for all sides //
    void setResolutionWidth(int widthRes);
    void setResolutionHeight(int heightRes);
    void setResolutionDepth(int depthRes);
    void setResolution(int resWidth, int resHeight, int resDepth);

    void setMode(ofPrimitiveMode mode);
    void setSideColor(int sideIndex, ofColor color);

    int getResolutionWidth() const;
    int getResolutionHeight() const;
    int getResolutionDepth() const;
    glm::vec3 getResolution() const;

    float getWidth() const;
    float getHeight() const;
    float getDepth() const;
    glm::vec3 getSize() const;

    ~boxPrimitive();

protected:
    glm::vec3 size;
    glm::vec3 resolution;
    // indices strides for faces //
    int strides[6][2];
    int vertices[6][2];