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
	objectType = importation;
	objectImport.loadModel(fileName);

	//Évite que le modèle apparaissent à l'envers
	objectImport.setRotation(0, 180, 1, 0, 0);
	//Enlève les matériaux de base pour faire marcher le shader
	objectImport.disableMaterials();
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
	else if (objectType == importation) {
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
	else if (objectType == importation) {
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
	else if(objectType == importation) {
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
	else if (objectType == importation) {
		objectImport.setPosition(newPosition.x, newPosition.y, newPosition.z);
	}
	else if (objectType == box3d) {
		box.setPosition(newPosition);
	}
	else if (objectType == cylinder3d) {
		cylinder.setPosition(newPosition);
	}
	else if (objectType == cone3d) {
		cone.setPosition(newPosition);
	}
}

void object3D::setRotation(ofVec3f newRotation) {
	if (objectType == primitive3d) {
		primitive.setOrientation(newRotation);
	}
	else if (objectType == sphere3d) {
		sphere.setOrientation(newRotation);
	}
	else if(objectType == importation) {
		//Permet de faire la rotation des modèle 3D
		objectImport.setRotation(0, newRotation.x + 180, 1, 0, 0);
		objectImport.setRotation(1, newRotation.y, 0, 1, 0);
		objectImport.setRotation(2, newRotation.z, 0, 0, 1);
	}
	else if (objectType == box3d) {
		box.setOrientation(newRotation);
	}
	else if (objectType == cylinder3d) {
		cylinder.setOrientation(newRotation);
	}
	else if (objectType == cone3d) {
		cone.setOrientation(newRotation);
	}
}

void object3D::setProportion(ofVec3f newProportion) {
	if (objectType == primitive3d) {
		primitive.setScale(newProportion);
	}
	else if (objectType == sphere3d) {
		sphere.setScale(newProportion);
	}
	else if(objectType==importation) {
		objectImport.setScale(newProportion.x, newProportion.y, newProportion.z);
	}
	else if (objectType == box3d) {
		box.setScale(newProportion);
	}
	else if (objectType == cylinder3d) {
		cylinder.setScale(newProportion);
	}
	else if (objectType == cone3d) {
		cone.setScale(newProportion);
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

void object3D::setAnimation() {
	if (animation == true){
		animation = false;


	}
	else if (animation == false) {
		animation = true;

	}

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
		sphere.draw(OF_MESH_FILL);
		sphere.drawAxes(10);
	}
	else if (objectType == importation) {
		if (animation == true)
		{

			objectImport.setLoopStateForAllAnimations(OF_LOOP_NORMAL);
			objectImport.playAllAnimations();
			objectImport.update();
			objectImport.draw(OF_MESH_FILL);

		}

		if (animation == false)
		{
			objectImport.stopAllAnimations();
			objectImport.update();
			objectImport.draw(OF_MESH_FILL);
		}
	}
	else if (objectType == box3d) {
		box.draw(OF_MESH_FILL);
	}
	else if (objectType == cylinder3d) {
		cylinder.draw(OF_MESH_FILL);
	}
	else if (objectType == cone3d) {
		cone.draw(OF_MESH_FILL);
	}
	ofPopMatrix();
}