#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#include "renderer.h"
#include "form.h"
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

		void getHsb();


		ofxIntSlider intSlider;
		ofxFloatSlider floatSlider;
		ofxIntSlider intSliderTakes;
		ofxFloatSlider floatSliderTime;
		ofxToggle toggle;
		ofxButton button;
		ofxButton newObjectButton;
		ofxButton HSBDisplayButton;
		ofxButton newCubeButton;
		ofxLabel labelProperties;
		ofxLabel labelHierarchy;

		ofxFloatField floatField;
		ofxIntField intField;
		ofxTextField textField;

		ofParameterGroup proportionGroup;
		ofParameter<float> proportionX;
		ofParameter<float> proportionY;
		ofParameter<float> proportionZ;

		ofxVec3Slider positionSlider;
		ofxVec3Slider rotationSlider;

		float timeByTakes;
		int i = 0;
		int nbTakes;
		float timePassed;

		ofParameterGroup colorGroup;
		

private:
	void addNewObject();
	void addNewSphere();
		
		
		void openFileSelection(ofFileDialogResult openFileResult);

		void actionResearchImages();

		vector<ofImage>loadedImages;
		vector<ofImage>processedImages;
		string originalFileExtension;
		
};
