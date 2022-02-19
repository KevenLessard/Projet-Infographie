#pragma once

#include "object3D.h"
#include <cmath>
#include <vector>
#include "ofxAssimpModelLoader.h"

//Classe pour importer des modèles 3D. Critères 4.3

class Model3D: public Object3D {
public:
	

	Model3D(std::string _file_name);

	Model3D();

	void draw();

	void update();

	

	//~Model3D();

	ofxAssimpModelLoader model3D;
	ofNode boundBox;

	std::string file_name;


};