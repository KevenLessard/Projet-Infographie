#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "bezierSurface.h"
#include "Quad.h"
#include "ofxDelaunay.h"
#include "ofxReflectionRefraction.h"


#pragma once

enum ObjectType { importation, primitive3d, sphere3d, box3d, cylinder3d, cone3d, surfaceBezier, quad3d, delaunayTriangle, GBox};
// énumération des types de shader
enum class ShaderType { color_fill, lambert, gouraud, phong, blinn_phong };


class object3D
{
public:
	object3D(string name);
	object3D(string name, int type);
	object3D(string name, int type, ofEasyCam *p_cam);
	object3D(string name, string fileName);

	ObjectType objectType;

	ofVec3f getPosition();
	ofVec3f getRotation();
	ofVec3f getProportion();
	float getRadius();
	string getName();
	ofNode getNode();
	ofColor getColor();

	void setPosition(ofVec3f newPosition);
	void setRotation(ofVec3f newRotation);
	void setProportion(ofVec3f newProportion);
	void setRadius(float newRadius);
	void setColor(ofColor newColor);
	void setName(string newName);
	void setAnimation();
	void setTexture(ofFileDialogResult openFileResult);
	void updateShader(ofLight light);
	void switchMaterialShader(string type);

	void mouseReleased(ofMouseEventArgs& mouseArgs);
	void setTopologie();

	//Materiel
	void updateMaterial();
	void setMaterial(string material);

	void toggleRotation();
	void draw();
	void draw(ofVec3f camPosition);
	void draw(const ofEasyCam& mainCamera);
	void drawBoundingBox();
	void changeShader(string type);

	vector<ofxReflectionRefraction> Ref;
	void setupGlassBox();

	float oscillate(float time, float frequency, float amplitude);
	void setSelected(bool b);
	bool getSelected();

	//PBR
	ofColor material_color_ambient;
	ofColor material_color_diffuse;
	ofColor material_color_specular;

	void setMetallic(float value);
	void setRoughness(float value);
	float getMetallic();
	float getRoughness();

	float material_metallic;
	float material_roughness;
	float material_occlusion;
	float material_brightness;

	glm::vec3 material_fresnel_ior;

	ofImage texture_diffuse;
	ofImage texture_metallic;
	ofImage texture_roughness;
	ofImage texture_occlusion;
	ofColor light_color;
	float light_intensity;
	bool light_motion;

	float center_x;
	float center_y;

	float tone_mapping_exposure;
	float tone_mapping_gamma;
	bool tone_mapping_toggle;

	vector<ofImage> pos;
	vector<ofImage> neg;
	ofParameter<ofVec3f> translate;

private:
	string name;
	ofVec3f position;
	ofVec3f rotation;
	ofVec3f proportion;

	bool animation = false;
	bool rotationOn = false;
	bool toggleBoundingBox = false;

	ofColor color;

	ofxAssimpModelLoader objectImport;
	of3dPrimitive primitive;
	ofSpherePrimitive sphere;
	ofBoxPrimitive box;
	ofCylinderPrimitive cylinder;
	ofConePrimitive cone;
	ofxBezierSurface surface;
	ofx::Quad quad;
	ofxDelaunay delaunay;
	ofMesh glassBox;
	string shader_name;
	ofShader shader_color_fill;
	ofShader shader_lambert;
	ofShader shader_gouraud;
	ofShader shader_phong;
	ofShader shader_blinn_phong;
	ofShader shader_pbr;
	ofShader shader;
	ofLight light;
	float oscillation;
	float oscillation_frequency;
	float oscillation_amplitude;

	ofMaterial material1;
	string materialSelected;

	ofTexture texture1;
	ofPoint points[4];
	int cornerIndex = 0;
	bool textureOn;
	bool isSelected;
	bool shaderOnMaterialOff;
	bool boolTopologie;


	void quadInit();
	ofEasyCam * cam;
};

