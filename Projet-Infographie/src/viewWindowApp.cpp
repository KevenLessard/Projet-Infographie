/*
 * GuiApp.cpp
 *
 *  Created on: Oct 28, 2014
 *      Author: arturo
 */

#include "viewWindowApp.h"


void viewWindowApp::setup() {
	//parameters.setName("parameters");
	//parameters.add(radius.set("radius", 50, 1, 100));
	//parameters.add(color.set("color", 100, ofColor(0, 0), 255));
	//gui.setup(parameters);
	//ofBackground(0);
	//ofSetVerticalSync(false);
}

void viewWindowApp::update() {

}

void viewWindowApp::draw() {

	renderer.applyLut(renderer.lutImage);
	renderer.lutImage.draw(renderer.lutPos.x, renderer.lutPos.y,0);
	
}