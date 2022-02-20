#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"

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

	vector<of3dPrimitive*> objects;
	vector<ofxAssimpModelLoader*> models3D;

	void setup();
	void update();
	void draw();

	void draw_cursor(float x, float y) const;
	void addNew3dObject();
	void addNewSphere();
	void proportionateObject(int index, ofVec3f newProportion);
	void moveObject(int index, ofVec3f newPosition);
	void rotateObject(int index, ofVec3f newRotation);
	void image_export(const string name, const string extension) const;

	//Hugo
	void import3dModel(std::string file_name);

};