#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofxVectorGraphics.h"
#include "sphere.h"

class Renderer
{
public:
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

	int cursor_width;
	int cursor_height;



	//Vecteur d'objet 3D
	vector<of3dPrimitive*> objects;
	vector<ofxAssimpModelLoader*> models3D;


	
	//Vecteur d'objet 2D
	vector<ofxVectorGraphics*> objects2D;


	ofParameter<ofColor> colorPicker;

	
	
	ofCamera mainCamera;
	bool is_camera_ortho = false;
	bool is_camera_move_left;
	bool is_camera_move_right;
	bool is_camera_move_up;
	bool is_camera_move_down;
	bool is_camera_move_forward;
	bool is_camera_move_backward;

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
	void addNew3dObject();
	
	void addNewSphere();
	void addNewBox();
	void addNewCylinder();
	void addNewCone();

	//void addNew2DObjects
	void addNewCircle();
	/*void addNewRectangle();
	void addNewTriangle();
	void addNewLine();
	void addNewBezierCurve();
	void addNewEllipse();
	*/


	void deleteObject(int index);
	void proportionateObject(int index, ofVec3f newProportion);
	void moveObject(int index, ofVec3f newPosition);
	void rotateObject(int index, ofVec3f newRotation);
	void image_export(const string name, const string extension) const;

	void stopAnimation();


	void import3dModel(std::string file_name);

	void cameraLookAt(int index);
	void switchProjectionMode();
	void cameraZoom();

};
