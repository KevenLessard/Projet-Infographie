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
	ofxButton newRectangleButton;
	ofxButton newEllipseButton;
	ofxButton newLineButton;
	ofxButton newStarButton;
	ofxButton newHouseButton;
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
		ofxIntSlider intSliderFrames;

		ofxButton HSBDisplayButton;
		ofxLabel labelProperties3D;
		ofxLabel labelProperties2D;
		ofxLabel labelHierarchy;
		ofxLabel labelNewObject3D;
		ofxLabel labelNewObject2D;

		ofxVec3Slider proportionSlider;
		ofxVec2Slider proportionSlider2D;
		ofxVec3Slider positionSlider;
		ofxVec2Slider positionSlider2D;
		ofxVec3Slider rotationSlider;
		ofxVec2Slider rotationSlider2D;

		int nbFramesPerTake;
		int i = 0;
		int nbTakes;
		int nbFrames;

		ofParameter<ofColor> colorPicker;

		ofxButton cameraLookAtButton;
		ofxButton projectionModeButton;
		ofxButton setAnimationButton;
		ofxButton toggleRotationButton;
		bool is_key_press_up;
		bool is_key_press_down;
		bool is_key_press_left;
		bool is_key_press_right;

		bool otherCursorInUse = false;

		bool mode3D = true;


private:

	void refreshHierarchy();
	void exportImage();

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
	void cameraLookAt();
	void switchProjectionMode();
	void setAnimation();
	void toggleRotation();
	void newToggleObject();
	void updateHierarchy();
	void toggleListener(bool& value);
	void updateSelection();

	//2D
	void addNewRectangle();
	void addNewTriangle();
	void addNewCircle();
	void addNewEllipse();
	void addNewLine();
	void addNewStar();
	void addNewHouse();
		
	void openFileSelection(ofFileDialogResult openFileResult);

	vector<ofImage>loadedImages;
	vector<ofImage>processedImages;
	string originalFileExtension;
		
};
