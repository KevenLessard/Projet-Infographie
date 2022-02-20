#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "primitives3D.h"

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
	//vector<Form*> shapes;

	ofParameter<ofColor> colorPicker;

	
	
	ofCamera mainCamera;
	bool is_camera_ortho = false;

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
	//void addNew2DObject();
	void addNewSphere();
	void deleteObject(int index);
	void proportionateObject(int index, ofVec3f newProportion);
	void moveObject(int index, ofVec3f newPosition);
	void rotateObject(int index, ofVec3f newRotation);
	void image_export(const string name, const string extension) const;

	//Hugo
	void import3dModel(std::string file_name);

	void cameraLookAt(int index);
	void switchProjectionMode();
};