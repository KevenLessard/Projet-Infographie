#include "object3D.h"

object3D::object3D(string p_name) {
	name = p_name;
	objectType = primitive3d;
	primitive = of3dPrimitive();
	//Chargement du shader
	shader.load("lambert_330_vs.glsl", "lambert_330_fs.glsl");
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
	//Chargement du shader
	shader.load("lambert_330_vs.glsl", "lambert_330_fs.glsl");
}

object3D::object3D(string p_name, string fileName) {
	name = p_name;
	objectType = importation;
	objectImport.loadModel(fileName);
	//Évite que le modèle apparaissent à l'envers
	objectImport.setRotation(0, 180, 1, 0, 0);
	//Enlève les matériaux de base pour faire marcher le shader
	objectImport.disableMaterials();
	//Chargement du shader
	shader.load("lambert_330_vs.glsl", "lambert_330_fs.glsl");
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
	else if (objectType == box3d) {
		return box.getPosition();
	}
	else if (objectType == cylinder3d) {
		return cylinder.getPosition();
	}
	else if (objectType == cone3d) {
		return cone.getPosition();
	}
}

ofVec3f object3D::getRotation() {
	if (objectType == primitive3d) {
		return primitive.getOrientationEuler();
	}
	else if (objectType == sphere3d) {
		return sphere.getOrientationEuler();
	}
	else if (objectType == importation) {
		return objectImport.getRotationAxis(0);
	}
	else if (objectType == box3d) {
		return box.getOrientationEuler();
	}
	else if (objectType == cylinder3d) {
		return cylinder.getOrientationEuler();
	}
	else if (objectType == cone3d) {
		return cone.getOrientationEuler();
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
	else if (objectType == box3d) {
		return box.getScale();
	}
	else if (objectType == cylinder3d) {
		return cylinder.getScale();
	}
	else if (objectType == cone3d) {
		return cone.getScale();
	}
}

float object3D::getRadius() {
	if (objectType != sphere3d) {
		return 0;
	}
	return sphere.getRadius();
}

ofNode object3D::getNode() {
	if (objectType == primitive3d) {
		return primitive;
	}
	else if (objectType == sphere3d) {
		return sphere;
	}
	else if (objectType == importation) {
		ofNode node;
		node.setPosition(getPosition());
		return node;
	}
	else if (objectType == box3d) {
		return box;
	}
	else if (objectType == cylinder3d) {
		return cylinder;
	}
	else if (objectType == cone3d) {
		return cone;
	}
}

ofColor object3D::getColor() {
	return color;
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

void object3D::drawBoundingBox() {
	toggleBoundingBox = true;

	}

void object3D::toggleRotation() {
	if (rotationOn == true) {
		rotationOn = false;
	}
	else if (rotationOn == false) {
		rotationOn = true;
	}
}

void object3D::draw() {
	ofPushMatrix();
	shader.begin();

	if (objectType == primitive3d) {
		primitive.draw(OF_MESH_WIREFRAME);
		primitive.drawAxes(10);
	}
	else if (objectType == sphere3d) {

		sphere.draw(OF_MESH_FILL);
		sphere.drawAxes(10);
		if (toggleBoundingBox == true) {
			float sizeBase = sphere.getRadius() * 2 * sphere.getGlobalScale().x;
			ofNoFill();
			ofDrawBox(sphere.getPosition(), sizeBase, sizeBase, sizeBase);
		}
		toggleBoundingBox = false;
	}
	else if (objectType == importation) {

		if (rotationOn == true) {
			objectImport.setRotation(0, 180, 1, 0, 0);
			objectImport.setRotation(1, ofGetFrameNum(), 0, 1, 0);
			objectImport.setRotation(2, 0, 0, 0, 1);
		}

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
		if (toggleBoundingBox == true)
		{
			float size = box.getDepth() * box.getGlobalScale().x;
			ofNoFill();
			ofDrawBox(box.getPosition(), size + 10, size+10, size+10);
		}
		toggleBoundingBox = false;
	}
	else if (objectType == cylinder3d) {
		cylinder.draw(OF_MESH_FILL);
		if (toggleBoundingBox == true) {
			float sizeBase = cylinder.getRadius() * 2 * cylinder.getGlobalScale().x;
			ofNoFill();
			ofDrawBox(cylinder.getPosition(), sizeBase, cylinder.getHeight() * cylinder.getGlobalScale().x, sizeBase);
		}
		toggleBoundingBox = false;
	}
	else if (objectType == cone3d) {
		cone.draw(OF_MESH_FILL);
		if(toggleBoundingBox == true){
			float sizeBase = cone.getRadius() * 2 * cone.getGlobalScale().x;
			ofNoFill();
			ofDrawBox(cone.getPosition(), sizeBase, cone.getHeight() * cone.getGlobalScale().x, sizeBase);
		}
		toggleBoundingBox = false;
	}
	shader.end();
	ofPopMatrix();
}

void object3D::updateShader(ofLight light) {
	shader.begin();
	shader.setUniform3f("color_ambient", 0.1f, 0.1f, 0.1f);
	shader.setUniform3f("color_diffuse", color.r / 255.0f, color.g / 255.0f, color.b / 255.0f);
	shader.setUniform3f("light_position", glm::vec4(light.getGlobalPosition(), 0.0f) * ofGetCurrentMatrix(OF_MATRIX_MODELVIEW));
	shader.end();
}