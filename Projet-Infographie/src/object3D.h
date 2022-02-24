#include "ofMain.h"
#include "ofxAssimpModelLoader.h"

#pragma once

enum ObjectType { importation, primitive3d, sphere3d, box3d };

class object3D
{
public:
	object3D();
	object3D(int type);
	object3D(string fileName);

	void loadModel();

	ofVec3f getPosition();
	//return a quaternion?? 
	ofVec3f getRotation();
	ofVec3f getProportion();
	float getRadius();

	void setPosition(ofVec3f newPosition);
	//Take a quaternion??
	void setRotation(ofVec3f newRotation);
	void setProportion(ofVec3f newProportion);
	void setRadius(float newRadius);
	
	void draw();


private:
	ObjectType objectType;
	ofVec3f position;
	ofVec3f rotation;
	ofVec3f proportion;

	ofxAssimpModelLoader objectImport;
	of3dPrimitive primitive;
	ofSpherePrimitive sphere;
	ofBoxPrimitive box;
};

