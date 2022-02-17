#pragma once


#include "object3D.h"
#include <cmath>
#include <vector>
#include "ofxAssimpModelLoader.h"

//Classe pour importer des modèles 3D. Critères 4.3

class Model3D {
public:
	
	//Test avec le teapot
	void modelTest();

	//Model(std::string file_name);

	void draw();

	void update();


	ofxAssimpModelLoader model;
	ofNode boundBox;

	std::string file_name;

};