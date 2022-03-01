#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "renderer.h"

//#include "gestionImages.h"

class ofApp : public ofBaseApp {

	Renderer renderer;
	//GestionImages gestionImages;

	//3D
	ofxPanel guiProperties3D;
	ofxPanel guiObjects3D;
	ofxPanel guiCamera3D;
	ofxPanel guiHierarchy;

	//Hierarchy
	vector<ofParameter<bool>> objectsToggle;
	vector<int> selectedObjects;

	//Newobject
	ofParameter<string> newObjectName;
	ofxButton newObjectButton;
	ofxButton newSphereButton;
	ofxButton deleteButton;
	ofxButton newBoxButton;
	ofxButton newCylinderButton;
	ofxButton newConeButton;
	ofxButton newTeapotButton;
	ofxButton newGlassesButton;
	ofxButton newTVButton;
	ofxButton newWolfButton;

	//___________________________

	//2D
	ofxPanel guiProperties2D;
	ofxPanel guiObjects2D;
	ofxPanel guiCamera2D;

	ofxButton newCircleButton;
	ofxButton newSquareButton;
	ofxButton newTriangleButton;
	//___________________________


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
		void mouseScrolled(int x, int y, float scrollX, float scrollY);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		void getHsb();


		ofxIntSlider intSlider;
		ofxFloatSlider floatSlider;
		ofxIntSlider intSliderTakes;
		ofxFloatSlider floatSliderTime;



		ofxButton HSBDisplayButton;
		ofxLabel labelProperties;
		ofxLabel labelHierarchy;
		ofxLabel labelNewObject;

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
		bool is_mouse_wheel_up;
		bool is_mouse_wheel_down;

		bool mode3D = true;


private:

	//3D
	void addNewObject();
	void addNewSphere();
	void addNewBox();
	void addNewCylinder();
	void addNewCone();
	void addNewTeapot();
	void addNewGlasses();
	void addNewTV();
	void addAnimatedWolf();
	void deleteObject();
	void cameraLookAt(int& index);
	void switchProjectionMode();
	void newToggleObject();
	void updateHierarchy();
	void toggleListener(bool& value);
	void updateSelection();

	//2D
	void addNewSquare();
	void addNewTriangle();
	void addNewCircle();
		
	void openFileSelection(ofFileDialogResult openFileResult);

	void actionResearchImages();

	vector<ofImage>loadedImages;
	vector<ofImage>processedImages;
	string originalFileExtension;

	vector<int> selectedObject;
		
};
