#pragma once

#include "ofMain.h"
#include "import3DModel.h"
#include <vector>

class Renderer
{
public:
	// declaration des variables pour la fonction du curseur draw_cursor.
	int mouse_press_x;
	int mouse_press_y;
	int mouse_current_x;
	int mouse_current_y;

	bool is_mouse_button_pressed;

	std::vector<Object3D*> objects3D;

	void setup();
	void update();
	void draw();

	void add_Model3D();

	void draw_cursor(float x, float y) const;


	//Mode 3D à tester:
	float center_x;
	float center_y;

	float offset_x;
	float offset_z;

	float delta_x;
	float delta_z;

	float speed;

	bool is_flip_axis_y;
};