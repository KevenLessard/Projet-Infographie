#include "object3D.h"
#include "renderer.h"

object3D::object3D(string p_name) {
	name = p_name;
	objectType = primitive3d;
	primitive = of3dPrimitive();

	//Chargement du shader
	shader_color_fill.load(
		"shader/color_fill_330_vs.glsl",
		"shader/color_fill_330_fs.glsl");

	shader_lambert.load(
		"shader/lambert_330_vs.glsl",
		"shader/lambert_330_fs.glsl");

	shader_gouraud.load(
		"shader/gouraud_330_vs.glsl",
		"shader/gouraud_330_fs.glsl");

	shader_phong.load(
		"shader/phong_330_vs.glsl",
		"shader/phong_330_fs.glsl");

	shader_blinn_phong.load(
		"shader/blinn_phong_330_vs.glsl",
		"shader/blinn_phong_330_fs.glsl");

	shader = shader_lambert;
	shaderOnMaterialOff = true;
	boolTopologie = false;
	textureOn = false;
	material_metallic = 0.5f;
	material_roughness = 0.5f;

	isSelected = false;

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
	case 7:
		quad = ofx::Quad();
		objectType = quad3d;
		quadInit();
		break;
	case 8:
		delaunay = ofxDelaunay();
		objectType = delaunayTriangle;
		ofAddListener(ofEvents().mouseReleased, this, &object3D::mouseReleased);
		break;
	case 9:
		glassBox = ofMesh();
		objectType = GBox;
		setupGlassBox();

	default:
		ofLog() << "Invalid type.";
	}

	
	//Chargement du shader
	shader_color_fill.load(
		"shader/color_fill_330_vs.glsl",
		"shader/color_fill_330_fs.glsl");

	shader_lambert.load(
		"shader/lambert_330_vs.glsl",
		"shader/lambert_330_fs.glsl");

	shader_gouraud.load(
		"shader/gouraud_330_vs.glsl",
		"shader/gouraud_330_fs.glsl");

	shader_phong.load(
		"shader/phong_330_vs.glsl",
		"shader/phong_330_fs.glsl");

	shader_blinn_phong.load(
		"shader/blinn_phong_330_vs.glsl",
		"shader/blinn_phong_330_fs.glsl");

	shader_pbr.load(
		"shader/pbr_330_vs.glsl",
		"shader/pbr_330_fs.glsl");
	shader = shader_lambert;

	// charger les textures du matériau
	texture_diffuse.load("texture/metal_plate_diffuse_1k.jpg");
	texture_metallic.load("texture/metal_plate_metallic_1k.jpg");
	texture_roughness.load("texture/metal_plate_roughness_1k.jpg");
	texture_occlusion.load("texture/metal_plate_ao_1k.jpg");


	// paramètres des textures du matériau
	texture_diffuse.getTexture().setTextureWrap(GL_REPEAT, GL_REPEAT);
	texture_metallic.getTexture().setTextureWrap(GL_REPEAT, GL_REPEAT);
	texture_roughness.getTexture().setTextureWrap(GL_REPEAT, GL_REPEAT);
	texture_occlusion.getTexture().setTextureWrap(GL_REPEAT, GL_REPEAT);

	setColor(ofColor(200, 200, 200));

	ofDisableArbTex();

	shader = shader_lambert;
	shaderOnMaterialOff = true;
	boolTopologie = false;
	textureOn = false;
	material_metallic = 0.5f;
	material_roughness = 0.5f;

	isSelected = false;

}

object3D::object3D(string p_name, int type, ofEasyCam *p_cam) {
	name = p_name;
	if (type == 8) {
		delaunay = ofxDelaunay();
		objectType = delaunayTriangle;
		ofAddListener(ofEvents().mouseReleased, this, &object3D::mouseReleased);
		cam = p_cam;
	}
	else if (type == 6) {
		surface = ofxBezierSurface(p_cam);
		objectType = surfaceBezier;
		surface.setup(200, 200, 10, 10);
	}
	isSelected = false;
}

object3D::object3D(string p_name, string fileName) {
	name = p_name;
	objectType = importation;
	objectImport.loadModel(fileName);
	//�vite que le mod�le apparaissent � l'envers
	objectImport.setRotation(0, 180, 1, 0, 0);
	ofDisableArbTex();
	//Enl�ve les mat�riaux de base pour faire marcher le shader
	objectImport.disableMaterials();


	//Chargement des shaders
	shader_color_fill.load(
		"shader/color_fill_330_vs.glsl",
		"shader/color_fill_330_fs.glsl");

	shader_lambert.load(
		"shader/lambert_330_vs.glsl",
		"shader/lambert_330_fs.glsl");

	shader_gouraud.load(
		"shader/gouraud_330_vs.glsl",
		"shader/gouraud_330_fs.glsl");

	shader_phong.load(
		"shader/phong_330_vs.glsl",
		"shader/phong_330_fs.glsl");

	shader_blinn_phong.load(
		"shader/blinn_phong_330_vs.glsl",
		"shader/blinn_phong_330_fs.glsl");

	shader_pbr.load(
		"shader/pbr_330_vs.glsl",
		"shader/pbr_330_fs.glsl");

	// charger les textures du matériau
	texture_diffuse.load("texture/metal_plate_diffuse_1k.jpg");
	texture_metallic.load("texture/metal_plate_metallic_1k.jpg");
	texture_roughness.load("texture/metal_plate_roughness_1k.jpg");
	texture_occlusion.load("texture/metal_plate_ao_1k.jpg");

	// paramètres des textures du matériau
	texture_diffuse.getTexture().setTextureWrap(GL_REPEAT, GL_REPEAT);
	texture_metallic.getTexture().setTextureWrap(GL_REPEAT, GL_REPEAT);
	texture_roughness.getTexture().setTextureWrap(GL_REPEAT, GL_REPEAT);
	texture_occlusion.getTexture().setTextureWrap(GL_REPEAT, GL_REPEAT);

	setColor(ofColor(200, 200, 200));
	isSelected = false;

	shader = shader_lambert;
	shaderOnMaterialOff = true;
	boolTopologie = false;
	textureOn = false;
	material_metallic = 0.5f;
	material_roughness = 0.5f;

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
	else if (objectType == surfaceBezier) {
		return surface.getPosition();
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
		ofVec3f rotation(objectImport.getRotationAngle(0), objectImport.getRotationAngle(1), objectImport.getRotationAngle(2));
		return rotation;
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
	else if (objectType == surfaceBezier) {
		return surface.getProportion();
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

float object3D::getMetallic() {
	return material_metallic;
}

float object3D::getRoughness() {
	return material_roughness;
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
	else if (objectType == surfaceBezier) {
		surface.setPosition(newPosition);
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
		//Permet de faire la rotation des mod�le 3D
		objectImport.setRotation(0, newRotation.x, 1, 0, 0);
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
	else if (objectType == surfaceBezier) {
		surface.setProportion(newProportion);
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

void object3D::changeShader(string type) {
	if (type == "color_fill") {
		shader = shader_color_fill;
	}

	if (type == "lambert") {
		shader = shader_lambert;
	}

	if (type == "gouraud") {
		shader = shader_gouraud;
	}

	if (type == "phong") {
		shader = shader_phong;
	}
	if (type == "blinn_phong") {
		shader = shader_blinn_phong;
	}

	shaderOnMaterialOff = 1;
	boolTopologie = 0;
	textureOn = 0;

	//Shader pbr à son shader à part shader_pbr

	shader_name = type;
}

void object3D::setMaterial(string material) {
	//basic (couleur modifiable)
	//obsidian
	//bronze
	//gold
	//silver
	materialSelected = material;

	shaderOnMaterialOff = 0;
	boolTopologie = 0;
	textureOn = false;
}

void object3D::setMetallic(float value) {
	material_metallic = value;
}

void object3D::setRoughness(float value) {
	material_roughness = value;
}

void object3D::setTopologie() {
	boolTopologie = 1;
}

void object3D::switchMaterialShader(string type) {
	if (type == "shader") {
		shaderOnMaterialOff = 1;
	}

	if (type == "material") {
		shaderOnMaterialOff = 0;
	}
}

void object3D::draw(const ofEasyCam& mainCamera) {

	if (objectType == GBox) {
		ofEnableDepthTest();
		glEnable(GL_CULL_FACE);

		Ref[0].drawMeshGlass(mainCamera, ofVec3f(100, 0, 0));
		glDisable(GL_CULL_FACE);
		ofDisableDepthTest();
	}

}

void object3D::draw() {

	if (boolTopologie) {
		materialSelected = "basic";
		material1.begin();
	}

	if (shaderOnMaterialOff && boolTopologie == false)
	{
		if (shader_name == "pbr")
		{
			shader_pbr.begin();
		}
		else {
			shader.begin();
		}
	}

	if (shaderOnMaterialOff == false && boolTopologie == false && textureOn == false) {
		updateMaterial();
		material1.begin();
	}

	if (shaderOnMaterialOff == false && boolTopologie == false && textureOn == true) {
		updateMaterial();
		material1.begin();
		texture1.bind();
	}
	


	ofPushMatrix();
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
		ofPushMatrix();
		cone.draw(OF_MESH_FILL);
		if(toggleBoundingBox == true){
			float sizeBase = cone.getRadius() * 2 * cone.getGlobalScale().x;
			ofNoFill();
			ofDrawBox(cone.getPosition(), sizeBase, cone.getHeight() * cone.getGlobalScale().x, sizeBase);
		}
		toggleBoundingBox = false;
		ofPopMatrix();
	}
	else if (objectType == surfaceBezier) {

		ofPushMatrix();
		ofFill();
		if (isSelected) {
			surface.drawControls();
			surface.drawWireframe();
		}
		else {
			surface.draw();
		}
		ofPopMatrix();

	}
	else if (objectType == quad3d) {
		if (isSelected) {
			quad.drawWireframe();
		}
		else {
			quad.draw();
		}
	}

	else if (objectType == delaunayTriangle) {
		if (isSelected) {
			ofNoFill();
			delaunay.draw();
			ofFill();
		}
		else {
			delaunay.draw();
		}
	}

	ofPopMatrix();
	material1.end();
	texture1.unbind();
	shader_pbr.end();
	shader.end();
	
}

void object3D::draw(ofVec3f camPosition) {


		material1.begin();
		double distance = abs(camPosition.x) + abs(camPosition.y) + abs(camPosition.z);
		int nbIteration = 0;
		if (distance > 2000) {
			nbIteration = 0;
		}
		else if (distance > 1500) {
			nbIteration = 1;
		}
		else if (distance > 1000) {
			nbIteration = 2;
		}
		else if (distance <= 1000) {
			nbIteration = 4;
		}
		if (isSelected) {
			quad.subdivide(nbIteration).drawWireframe();
		}
		else {
			quad.subdivide(nbIteration).draw();
		}
		material1.end();

}

void object3D::updateShader(ofLight light) {

	//Vieux code pu utilis�
	oscillation_amplitude = 32.0f;
	oscillation_frequency = 7500.0f;
	float oscillation = oscillate(5124, oscillation_frequency, oscillation_amplitude) + oscillation_amplitude;

	if (shader_name == "color_fill") {
		shader.begin();
		shader.setUniform3f("color", color.r / 255.0f, color.g / 255.0f, color.b / 255.0f);
		shader.end();
	}

	else if (shader_name == "pbr") {
		
		//-----------------

		material_color_ambient = ofColor(63, 63, 63);
		material_color_diffuse = ofColor(255, 255, 255);
		material_color_specular = ofColor(255, 255, 255);
		light_color = ofColor(255, 255, 255);
		light_motion = true;//Pas sûr que c'est obligatoire
		tone_mapping_toggle = true;//Pas sûr lui aussi

		// passer les attributs uniformes au shader de sommets
		shader_pbr.begin();

		shader_pbr.setUniform3f("material_color_ambient", material_color_ambient.r / 255.0f, material_color_ambient.g / 255.0f, material_color_ambient.b / 255.0f);
		shader_pbr.setUniform3f("material_color_diffuse", material_color_diffuse.r / 255.0f, material_color_diffuse.g / 255.0f, material_color_diffuse.b / 255.0f);
		shader_pbr.setUniform3f("material_color_specular", material_color_specular.r / 255.0f, material_color_specular.g / 255.0f, material_color_specular.b / 255.0f);

		shader_pbr.setUniform1f("material_brightness", 1.0f);
		shader_pbr.setUniform1f("material_metallic", material_metallic);
		shader_pbr.setUniform1f("material_roughness", material_roughness);
		shader_pbr.setUniform1f("material_occlusion", 1.0f);

		shader_pbr.setUniform3f("material_fresnel_ior", glm::vec3(0.04f, 0.04f, 0.04f));

		shader_pbr.setUniformTexture("texture_diffuse", texture_diffuse.getTexture(), 1);
		shader_pbr.setUniformTexture("texture_metallic", texture_metallic.getTexture(), 2);
		shader_pbr.setUniformTexture("texture_roughness", texture_roughness.getTexture(), 3);
		shader_pbr.setUniformTexture("texture_occlusion", texture_occlusion.getTexture(), 4);

		shader_pbr.setUniform1f("light_intensity", 1.0f);
		shader_pbr.setUniform3f("light_color", light_color.r / 255.0f, light_color.g / 255.0f, light_color.b / 255.0f);
		shader_pbr.setUniform3f("light_position", light.getGlobalPosition());

		shader_pbr.setUniform1f("tone_mapping_exposure", 1.0f);
		shader_pbr.setUniform1f("tone_mapping_gamma", 2.2f);
		//shader_pbr.setUniform1f("tone_mapping_gamma", tone_mapping_gamma);
		shader_pbr.setUniform1i("tone_mapping_toggle", tone_mapping_toggle);

		shader_pbr.end();
	}


	else {
		shader.begin();
		shader.setUniform3f("color_ambient", 0.1f, 0.1f, 0.1f);
		shader.setUniform3f("color_diffuse", color.r / 255.0f, color.g / 255.0f, color.b / 255.0f);
		shader.setUniform3f("color_specular", 1.0f, 1.0f, 0.0f);
		shader.setUniform1f("brightness", oscillation);
		shader.setUniform3f("light_position", light.getGlobalPosition());
		//shader.setUniform3f("light_position", glm::vec4(light.getGlobalPosition(), 0.0f) * ofGetCurrentMatrix(OF_MATRIX_MODELVIEW));
		shader.end();
	}
}



void object3D::updateMaterial() {

	//Materiel basic avec couleur modifiable
	if (materialSelected == "basic") {
		material1.setAmbientColor(ofColor(63, 63, 63));
		material1.setDiffuseColor(ofColor(200, 200, 200));
		material1.setEmissiveColor(ofColor(color.r, color.g, color.b));
		material1.setSpecularColor(ofColor(127, 127, 127));
		material1.setShininess(16.0f);
	}

	//Obsidian
	if (materialSelected == "obsidian") {
		material1.setAmbientColor(ofFloatColor(0.05375, 0.05, 0.06625));
		material1.setDiffuseColor(ofFloatColor(0.18275, 0.17, 0.22525));
		material1.setSpecularColor(ofFloatColor(0.332741, 0.328634, 0.346435));
		material1.setEmissiveColor(ofFloatColor(0.01, 0.01, 0));
		material1.setShininess(30.0f);
	}
	//Bronze
	if (materialSelected == "bronze") {
		material1.setAmbientColor(ofFloatColor(0.2125, 0.1275, 0.054));
		material1.setDiffuseColor(ofFloatColor(0.714, 0.4284, 0.18144));
		material1.setSpecularColor(ofFloatColor(0.393548, 0.271906, 0.166721));
		material1.setEmissiveColor(ofFloatColor(0.1, 0, 0));
		material1.setShininess(20.0f);
	}

	//Gold
	if (materialSelected == "gold") {
		material1.setAmbientColor(ofFloatColor(0.24725, 0.1995, 0.0745));
		material1.setDiffuseColor(ofFloatColor(0.75164, 0.60648, 0.22648));
		material1.setSpecularColor(ofFloatColor(0.628281, 0.555802, 0.366065));
		material1.setEmissiveColor(ofFloatColor(0.1, 0.05, 0));
		material1.setShininess(40.0f);
	}

	//Silver
	if (materialSelected == "silver") {
		material1.setAmbientColor(ofFloatColor(0.19225, 0.19225, 0.19225));
		material1.setDiffuseColor(ofFloatColor(0.50754, 0.50754, 0.50754));
		material1.setSpecularColor(ofFloatColor(0.508273, 0.508273, 0.508273));
		material1.setEmissiveColor(ofFloatColor(0.1, 0.1, 0.1));
		material1.setShininess(40.0f);
	}


}

void object3D::setTexture(ofFileDialogResult openFileResult) {
	ofLoadImage(texture1, openFileResult.getPath());
	shaderOnMaterialOff = false;
	boolTopologie = false;
	textureOn = true;
}

// fonction d'oscillation
float object3D::oscillate(float time, float frequency, float amplitude)
{
	return sinf(time * 2.0f * PI / frequency) * amplitude;
}

bool object3D::getSelected() {
	return isSelected;
}

void object3D::setSelected(bool b) {
	isSelected = b;
	if (isSelected && objectType == surfaceBezier) {
		surface.addListeners();
	}
	else {
		surface.removeListeners();
	}
}

void object3D::quadInit() {
	auto v0 = quad.addVertex({ 100.0, -100.0, 100.0 });
	auto v1 = quad.addVertex({ 100.0, 100.0, 100.0 });
	auto v2 = quad.addVertex({ -100.0, 100.0, 100.0 });
	auto v3 = quad.addVertex({ -100.0, -100.0, 100.0 });
	auto v4 = quad.addVertex({ 100.0, -100.0, -100.0 });
	auto v5 = quad.addVertex({ -100.0, -100.0, -100.0 });
	auto v6 = quad.addVertex({ -100.0, 100.0, -100.0 });
	auto v7 = quad.addVertex({ 100.0, 100.0, -100.0 });

	quad.addFace(v0, v1, v2, v3);
	quad.addFace(v4, v5, v6, v7);
	quad.addFace(v0, v4, v7, v1);
	quad.addFace(v3, v2, v6, v5);
	quad.addFace(v1, v7, v6, v2);
	quad.addFace(v0, v3, v5, v4);
}

void object3D::mouseReleased(ofMouseEventArgs& mouseArgs) {
	if (isSelected) {
		ofPoint point(mouseArgs.x, mouseArgs.y);
		ofPoint actualPoint = cam->screenToWorld(point);
		delaunay.addPoint(actualPoint);
		delaunay.triangulate();
	}
}

void object3D::setupGlassBox() {
	ofImage px("skybox/posx.jpg"); pos.push_back(px);
	ofImage py("skybox/posy.jpg"); pos.push_back(py);
	ofImage pz("skybox/posz.jpg"); pos.push_back(pz);
	ofImage nx("skybox/negx.jpg"); neg.push_back(nx);
	ofImage ny("skybox/negy.jpg"); neg.push_back(ny);
	ofImage nz("skybox/negz.jpg"); neg.push_back(nz);
	ofxReflectionRefraction r1;
	glassBox = ofMesh::box(100, 100, 100, 1, 1, 1);
	r1.setup(glassBox, pos, neg, false);
	Ref.push_back(r1);

}