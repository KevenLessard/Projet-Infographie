#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#include "renderer.h"
#include "formes.h"

class ofApp : public ofBaseApp{

	Renderer renderer;
	ofxPanel guiPropriete;
	ofxPanel guiHierarchie;
	ofxPanel guiFormes;

	ofParameterGroup parameterGroup;
	Formes circleGroup;

	public:
		
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		ofxIntSlider intSlider;
		ofxFloatSlider floatSlider;
		ofxToggle toggle;
		ofxButton button;
		ofxLabel labelPropriete;
		ofxLabel labelHierarchie;

		ofxFloatField floatField;
		ofxIntField intField;
		ofxTextField textField;

		ofxVec2Slider vec2Slider;
		ofxVec3Slider vec3Slider;
		ofxVec4Slider vec4Slider;


		
};
