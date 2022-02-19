#include "import3DModel.h"

Model3D::Model3D(std::string _file_name){
	model3D.loadModel(_file_name);
	file_name = _file_name;
}

Model3D::Model3D() {
	model3D.loadModel("teapot.obj");
	file_name = "teapot.obj";
}



void Model3D::draw() {
	ofSetColor(255);
	model3D.setPosition(ofGetWidth()/2, ofGetHeight()/2, 0);
	model3D.setRotation(0, 0, 0, 0, 0);
	model3D.setScale(1, 1, 1);
	model3D.drawFaces();
}

void Model3D::update() {

}