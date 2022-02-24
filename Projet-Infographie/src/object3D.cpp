#include "object3D.h"

object3D::object3D() {
	objectType = primitive3d;
	primitive = of3dPrimitive();
}

object3D::object3D(int type) {
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
	default:
		ofLog() << "Invalid type.";
	}
}

object3D::object3D(string fileName) {
	objectType = importation;
	objectImport.loadModel(fileName);
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
		//� voir
		objectImport.setRotation(0, 1, newRotation.x, newRotation.y, newRotation.z);
	}
}

void object3D::setProportion(ofVec3f newProportion) {
	ofLog() << "object3D " << newProportion;
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

void object3D::draw() {
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
}