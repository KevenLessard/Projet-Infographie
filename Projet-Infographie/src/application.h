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
		ofxButton newBoxButton;
		ofxButton newCylinderButton;
		ofxButton newConeButton;
		ofxButton newTeapotButton;
		ofxButton newGlassesButton;
		ofxButton newTVButton;
		ofxButton newWolfButton;

		ofParameterGroup objects2Dgroup;
		ofxButton newCircleButton;
		ofxButton newRectangleButton;
		ofxButton newTriangleButton;
		ofxButton newLineButton;
		ofxButton newBezierButton;
		ofxButton newEllipseButton;

		ofxButton HSBDisplayButton;
		ofxLabel labelProperties;
		ofxLabel labelHierarchy;
		ofxLabel labelobjects3D;
		ofxLabel labelobjects2D;

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
	// Ajout des objects 3D
	void addNewObject();
	void addNewSphere();
	void addNewBox();
	void addNewCylinder();
	void addNewCone();
	void addNewTeapot();
	void addNewGlasses();
	void addNewTV();
	void addAnimatedWolf();

	// Ajout des objects 2D
	void addNewCircle();
	/*void addNewRectangle();
	void addNewTriangle();
	void addNewLine();
	void addNewBezierCurve();
	void addNewEllipse();
	*/
	//Fonctions utilitaires
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
