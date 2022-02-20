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

	void draw_cursor(float x, float y) const;
	void addNew3dObject();
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
	void cameraZoom();
	void cameraTruck(int direction);
	void cameraDolly(int direction);
};