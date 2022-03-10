#include "ofMain.h"
#include "ofxAssimpModelLoader.h"

#pragma once

enum ObjectType { importation, primitive3d, sphere3d, box3d, cylinder3d, cone3d };

class object3D
{
public:
	object3D(string name);
	object3D(string name, int type);
	object3D(string name, string fileName);

	void loadModel();

	ofVec3f getPosition();
	//return a quaternion?? 
	ofVec3f getRotation();
	ofVec3f getProportion();
	float getRadius();
	string getName();

	void setPosition(ofVec3f newPosition);
	//Take a quaternion??
	void setRotation(ofVec3f newRotation);
	void setProportion(ofVec3f newProportion);
	void setRadius(float newRadius);
	void setColor(ofColor newColor);
	void setName(string newName);
	void setAnimation();
	void toggleRotation();
	void draw();
	void drawBoundingBox();

private:
	string name;
	ObjectType objectType;
	ofVec3f position;
	ofVec3f rotation;
	ofVec3f proportion;

	bool animation = false;
	bool rotationOn = false;
	bool toggleBoundingBox = false;

	ofColor color;

	ofxAssimpModelLoader objectImport;
	of3dPrimitive primitive;
	ofSpherePrimitive sphere;
	ofBoxPrimitive box;
	ofCylinderPrimitive cylinder;
	ofConePrimitive cone;


};

