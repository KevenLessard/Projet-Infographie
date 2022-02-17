#include "object3D.h"

void Object3D::info() {
	cout << "Pos X:" << position_x
		<< " Pos Y: " << position_y
		<< " Width: " << width
		<< " Height: " << height << endl;
}

void Object3D::translate(float x, float y, float z) {
	position_x += x;
	position_y += y;
	position_z += z;
}

void Object3D::zoomIn() {
	float old_scale = scale;
	scale += 0.25;
}

void Object3D::zoomOut() {
	if (scale > 0.25)
		scale -= 0.25;
}

void Object3D::rotate() {
	rotation += 5;
}