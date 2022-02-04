#pragma once

#include "ofMain.h"

class Renderer
{
public:
	// declaration des variables pour la fonction du curseur draw_cursor.
	int mouse_press_x;
	int mouse_press_y;
	int mouse_current_x;
	int mouse_current_y;

	bool is_mouse_button_pressed;



	void setup();
	void update();
	void draw();

	void draw_cursor(float x, float y) const;

};