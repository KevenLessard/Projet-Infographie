#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "object3D.h"
#include "object2D.h"
#include "sphere.h"
#include "SkyBox.h"
//#include "ofxCubeMap.h"

#include "ofxVectorGraphics.h"




class Renderer
{
public:
	
	

	bool isMode3D;
	// declaration des variables pour la fonction du curseur draw_cursor.
	int mouse_press_x;
	int mouse_press_y;
	int mouse_current_x;
	int mouse_current_y;

	float center_x;
	float center_y;

	bool is_mouse_button_pressed;
	bool crossCursor_enabled;
	bool circleCursor_enabled;
	bool arrowCursor_enabled;
	bool handCursor_enabled;
	bool resizeCursor_enabled;
	bool resizeCursorUpDown_enabled;
	bool magnifyingGlassEnabled;

	int cursor_width;
	int cursor_height;



	//Vecteur d'objet 3D
	vector<object3D*> objects3d;

	
	//Vecteur d'objet 2D
	vector<Object2D*> objects2D;
	//vector<Form*> shapes;

	
	
	//Test Cam
	ofEasyCam mainCamera;

	//ofCamera mainCamera;
	bool is_camera_ortho = false;
	bool is_camera_move_left;
	bool is_camera_move_right;
	bool is_camera_move_up;
	bool is_camera_move_down;
	bool is_camera_move_forward;
	bool is_camera_move_backward;

	bool is_camera_tilt_x_right;
	bool is_camera_tilt_x_left;
	bool is_camera_pan_y_forward;
	bool is_camera_pan_y_backward;
	bool is_camera_roll_z_right;
	bool is_camera_roll_z_left;



	float speed_delta;
	float speed_translation;
	float speed_rotation;

	float time_current;
	float time_last;
	float time_elapsed;
	void setup();
	void update();
	void draw();
	void reset();

	void draw_CrossCursor(int x, int y);
	void draw_CircleCursor(float x, float y) const;
	void draw_ArrowCursor(float x, float y) const;
	void draw_ResizeCursor(float x, float y) const;
	void draw_HandCursor(float x, float y) const;
	void draw_ResizeCursorUpDown(float x, float y) const;
	void draw_MagnifyingGlass(float x, float y) const;

	//3D
	void addNew3dObject(string name);
	void addNewSphere(string name);
	void addNewBox(string name);
	void addNewCylinder(string name);
	void addNewCone(string name);
	void addNewSurface(string name);
	void addNewQuad(string name);
	void addNewDelauney(string name);
	void deleteObject(int index);
	void proportionateObject(int index, ofVec3f newProportion);
	void moveObject(int index, ofVec3f newPosition);
	void rotateObject(int index, ofVec3f newRotation);
	void image_export(const string name, const string extension) const;
	void import3dModel(std::string file_name);
	void cameraLookAt(int index);
	void switchProjectionMode();
	void setObjectColor(int index, ofColor newColor);
	void setMetallic(int index, float value);
	void setRoughness(int index, float value);



	string getObject3dName(int index);
	string getObject2dName(int index);
	void setAnimation(int index);
	void toggleRotation(int index);
	void drawBoundingBox(int index);
	void addNewLight(int index);
	void lightingOn();
	void lightingOff();
	void setTexture(int index);
	void shaderActive(int index, string type);
	void setMaterial(int index, string material);

	//2D

	void addNewCircle(string name);
	void addNewRectangle(string name);
	void addNewTriangle(string name);
	void addNewLine(string name);
	void addNewEllipse(string name);
	void addNewStar(string name);
	void addNewHouse(string name);
	void addNewCurve(string name, int type);
	void moveCurve(int index, int pointIndex, ofVec3f newPosition);


	void addNewImage(string name, string keypressed);
	bool squareDraw = false;
	bool circleDraw = false;
	bool RectangleDraw = false;
	bool TriangleDraw = false;
	bool LineDraw = false;
	bool BezierCurveDraw = false;
	bool EllipseDraw = false;

	ofParameter<ofColor> color_picker;
	ofLight light;

	ofColor light_ambient;

	ofLight light_directional;
	ofLight light_point;
	ofLight light_spot;

	ofQuaternion orientation_directional;
	ofQuaternion orientation_spot;

	float oscillation;
	float oscillation_frequency;
	float oscillation_amplitude;
	float oscillate(float time, float frequency, float amplitude);
	float camera_offset;
	Skybox skybox;
	


	bool light_ambientOn;
	bool light_directionalOn;
	bool light_pointOn;
	bool light_spotOn;

private:
	bool nameAlreadyExists(string name);

};
