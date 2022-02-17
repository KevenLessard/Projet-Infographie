#include "import3DModel.h"

//import3DModel::Model(std::string filename)
//{
//
//}

void Model3D::modelTest() {
	model.loadModel("teapot.obj");
	file_name = "teapot.obj";
}

void Model3D::draw() {
	model.setRotation(0, 0, 0, 0, 0);
	model.setScale(1, 1, 1);
	model.drawFaces();
}

void Model3D::update() {

}