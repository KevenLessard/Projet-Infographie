#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#include "renderer.h"
#include "form.h"
#include "import3DModel.h"
//#include "gestionImages.h"

class ofApp : public ofBaseApp{

	Renderer renderer;
	//GestionImages gestionImages;
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
		ofxIntSlider intSliderTakes;
		ofxFloatSlider floatSliderTime;
		ofxToggle toggle;
		ofxButton button;
		ofxButton new3DObjectButton;
		ofxLabel labelProperties;
		ofxLabel labelHierarchy;

		ofxFloatField floatField;
		ofxIntField intField;
		ofxTextField textField;

		ofxVec2Slider vec2Slider;
		ofxVec3Slider vec3Slider;
		ofxVec4Slider vec4Slider;
		
		
		void openFileSelection(ofFileDialogResult openFileResult);

		void actionResearchImages();

		vector<ofImage>loadedImages;
		vector<ofImage>processedImages;
		string originalFileExtension;

		float timeByTakes;
		int i = 0;
		int nbTakes;
		float timePassed;
		
};
