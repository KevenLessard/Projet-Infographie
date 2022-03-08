#include "object3D.h"

object3D::object3D(string p_name) {
	name = p_name;
	objectType = primitive3d;
	primitive = of3dPrimitive();
}

object3D::object3D(string p_name, int type) {
	name = p_name;
	switch (type) {
	case 0:
		objectImport = ofxAssimpModelLoader();
		objectType = importation;
		break;
	case 1:
		primitive = of3dPrimitive();
		objectType = primitive3d;
		break;
	case 2:
		sphere = ofSpherePrimitive();
		objectType = sphere3d;
		break;
	case 3:
		box = ofBoxPrimitive();
		objectType = box3d;
		break;
	case 4:
		cylinder = ofCylinderPrimitive();
		objectType = cylinder3d;
		break;
	case 5:
		cone = ofConePrimitive();
		objectType = cone3d;
		break;
	default:
		ofLog() << "Invalid type.";
	}
}

object3D::object3D(string p_name, string fileName) {
	name = p_name;
	cout << name <<"Yo";
	objectType = importation;
	objectImport.loadModel(fileName);
}

string object3D::getName() {
	return name;
}

ofVec3f object3D::getPosition() {
	if (objectType == primitive3d) {
		return primitive.getPosition();
	}
	else if (objectType == sphere3d) {
		return sphere.getPosition();
	}
	else {
		return objectImport.getPosition();
	}
}

//return a quaternion?? 
ofVec3f object3D::getRotation() {
	if (objectType == primitive3d) {
		return primitive.getOrientationEuler();
	}
	else if (objectType == sphere3d) {
		return sphere.getOrientationEuler();
	}
	else {
		ofLog() << objectImport.getRotationAxis(0);
		return objectImport.getRotationAxis(0);
	}
}

ofVec3f object3D::getProportion() {
	if (objectType == primitive3d) {
		return primitive.getScale();
	}
	else if (objectType == sphere3d) {
		return sphere.getScale();
	}
	else {
		return objectImport.getScale();
	}
}

float object3D::getRadius() {
	if (objectType != sphere3d) {
		return 0;
	}
	return sphere.getRadius();
}

void object3D::setName(string newName) {
	name = newName;
}

void object3D::setPosition(ofVec3f newPosition) {
	if (objectType == primitive3d) {
		primitive.setPosition(newPosition);
	}
	else if (objectType == sphere3d) {
		sphere.setPosition(newPosition);
	}
	else {
		objectImport.setPosition(newPosition.x, newPosition.y, newPosition.z);
	}
}

void object3D::setRotation(ofVec3f newRotation) {
	if (objectType == primitive3d) {
		primitive.setOrientation(newRotation);
	}
	else if (objectType == sphere3d) {
		sphere.setOrientation(newRotation);
	}
	else {
		//À voir
		objectImport.setRotation(0, 1, newRotation.x, newRotation.y, newRotation.z);
	}
}

void object3D::setProportion(ofVec3f newProportion) {
	if (objectType == primitive3d) {
		primitive.setScale(newProportion);
	}
	else if (objectType == sphere3d) {
		sphere.setScale(newProportion);
	}
	else {
		objectImport.setScale(newProportion.x, newProportion.y, newProportion.z);
	}
}

void object3D::setRadius(float newRadius) {
	if (objectType != sphere3d) {
		return;
	}
	sphere.setRadius(newRadius);
}

void object3D::setColor(ofColor newColor) {
	color = newColor;
}

void object3D::draw() {
	ofPushMatrix();
	ofSetColor(color);
	if (objectType == primitive3d) {
		ofSetColor(61, 61, 205);
		primitive.draw(OF_MESH_WIREFRAME);
		primitive.drawAxes(10);
	}
	else if (objectType == sphere3d) {
		sphere.draw(OF_MESH_WIREFRAME);
		sphere.drawAxes(10);
	}
	else {
		objectImport.drawFaces();
	}
	ofPopMatrix();
}