#pragma once

#include "ofMain.h"
#include "renderer.h"

#include "ofxGui.h"

class viewWindowApp : public ofBaseApp {

	Renderer renderer;
	

	

public:
	void setup();
	void update();
	void draw();

	ofFbo fboSecondScreen;

	//ofParameterGroup parameters;
	//ofParameter<float> radius;
	//ofParameter<ofColor> color;
	//ofxPanel gui;
};