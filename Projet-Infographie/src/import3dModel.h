#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"

class import3dModel: public of3dPrimitive{
public:

	import3dModel(std::string _file_name);
	import3dModel();

	void draw();

	void update();



	//~Model3D();

	ofxAssimpModelLoader model3D;
	ofNode boundBox;

	std::string file_name;


};