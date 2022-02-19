#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#include "renderer.h"
#include "form.h"

class ofApp : public ofBaseApp{

	Renderer renderer;
	ofxPanel guiProperties;
	ofxPanel guiHierarchy;
	ofxPanel guiForms;

	ofParameterGroup parameterGroup;
	Form circleGroup;

	bool is_verbose;

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
		ofxButton newObjectButton;
		ofxButton newCubeButton;
		ofxLabel labelProperties;
		ofxLabel labelHierarchy;

		ofxFloatField floatField;
		ofxIntField intField;
		ofxTextField textField;

		ofxVec3Slider proportionSlider;
		ofxVec3Slider positionSlider;
		ofxVec3Slider rotationSlider;

private:
	void addNewObject();
	void addNewSphere();
};
