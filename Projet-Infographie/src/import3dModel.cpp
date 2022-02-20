#include "import3dModel.h"

import3dModel::import3dModel(std::string _file_name) {
	model3D.loadModel(_file_name);
	file_name = _file_name;
}

import3dModel::import3dModel() {
	model3D.loadModel("teapot.obj");
	cout << "YOLO";
}

void draw() {

}

void update() {

}