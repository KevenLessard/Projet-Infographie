#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "bezierSurface.h"

#pragma once

enum ObjectType { importation, primitive3d, sphere3d, box3d, cylinder3d, cone3d, surfaceBezier };
// énumération des types de shader
enum class ShaderType { color_fill, lambert, gouraud, phong, blinn_phong };


class object3D
{
public:
	object3D(string name);
	object3D(string name, int type);
	object3D(string name, string fileName);

	ofVec3f getPosition();
	ofVec3f getRotation();
	ofVec3f getProportion();
	float getRadius();
	string getName();
	ofNode getNode();
	ofColor getColor();

	void setPosition(ofVec3f newPosition);
	void setRotation(ofVec3f newRotation);
	void setProportion(ofVec3f newProportion);
	void setRadius(float newRadius);
	void setColor(ofColor newColor);
	void setName(string newName);
	void setAnimation();
	void setTexture(ofFileDialogResult openFileResult);
	void updateShader(ofLight light);

	//Materiel test

	void updateMaterial();

	void toggleRotation();
	void draw();
	void drawBoundingBox();
	void changeShader(string type);

	float oscillate(float time, float frequency, float amplitude);
	void setSelected(bool b);
	bool getSelected();

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
	ofxBezierSurface surface;

	string shader_name;
	ofShader shader_color_fill;
	ofShader shader_lambert;
	ofShader shader_gouraud;
	ofShader shader_phong;
	ofShader shader_blinn_phong;
	ofShader shader;
	ofLight light;
	float oscillation;
	float oscillation_frequency;
	float oscillation_amplitude;

	ofMaterial material1;
	ofMaterial material2;
	ofMaterial material3;
	ofMaterial material4;
	int materialNumber;

	ofTexture texture1;
	ofPoint points[4];
	int cornerIndex = 0;
	bool textureOn;
	bool isSelected;
};

