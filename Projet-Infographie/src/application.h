#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#include "renderer.h"

//#include "gestionImages.h"

class ofApp : public ofBaseApp {

	Renderer renderer;
	//GestionImages gestionImages;
	ofxPanel guiProperties;
	ofxPanel guiHierarchy;
	ofxPanel guiCamera;

	ofParameterGroup parameterGroup;

	bool is_verbose;
	bool cursor_enabled;

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

		ofxButton newObjectButton;
		ofxButton newSphereButton;
		ofxButton deleteButton;
		ofxButton newTeapotButton;
		ofxButton newGlassesButton;
		ofxButton newTVButton;

		ofxButton HSBDisplayButton;
		ofxButton newCubeButton;
		ofxLabel labelProperties;
		ofxLabel labelHierarchy;

		ofxIntField indexField;

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

		ofParameter<ofColor> colorPicker;

		ofxIntField cameraObjectIndex;
		ofxButton projectionModeButton;
		bool is_key_press_up;
		bool is_key_press_down;
		bool is_key_press_left;
		bool is_key_press_right;
		bool is_key_press_e;
		bool is_key_press_q;
private:
	void addNewObject();
	void addNewSphere();
	//Hugo
	void addNewTeapot();
	void addNewGlasses();
	void addNewTV();
	void deleteObject();
	void switchCurrentObject(int& index);
	void selection(int x, int y);
	void cameraLookAt(int& index);
	void switchProjectionMode();
		
		void openFileSelection(ofFileDialogResult openFileResult);

		void actionResearchImages();

		vector<ofImage>loadedImages;
		vector<ofImage>processedImages;
		string originalFileExtension;

		vector<int> selectedObject;
		
};
