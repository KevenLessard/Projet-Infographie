#pragma once

#include "ofMain.h"
#include <array>
#include "ofxGui.h"
#include "renderer.h"

//#include "gestionImages.h"

class ofApp : public ofBaseApp {
	Renderer renderer;

	//3D
	ofxPanel guiProperties3D;
	ofxPanel guiObjects3D;
	ofxPanel guiCamera3D;
	ofxPanel guiHierarchy;
	ofxPanel guiLights;

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
	ofxButton newSurfaceButton;
	ofxButton newQuadButton;
	ofxButton newDelaunayButton;

	//Lumi�res
	ofxButton newLight1;
	ofxButton newLight2;
	ofxButton newLight3;
	ofxButton newLight4;

	//Mat�riaux(Classique)
	ofxLabel labelMaterialPanel;
	ofxPanel guiMaterialPanel;
	ofxButton basicMaterialButton;
	ofxButton obsidianMaterialButton;
	ofxButton bronzeMaterialButton;
	ofxButton goldMaterialButton;
	ofxButton silverMaterialButton;
	void changeMaterialBasic();
	void changeMaterialObsidian();
	void changeMaterialBronze();
	void changeMaterialGold();
	void changeMaterialSilver();

	//Mat�riaux(Shader Illumination)
	ofxLabel labelShaderPanel;
	ofxPanel guiShaderPanel;
	ofxButton color_fillButton;
	ofxButton lambertButton;
	ofxButton phongButton;
	ofxButton blinn_phongButton;
	ofxButton gouraudButton;
	//Mat�riaux(PBR)
	ofxButton pbrButton;
	void changeShaderColorFill();
	void changeShaderLambert();
	void changeShaderPhong();
	void changeShaderBlinnPhong();
	void changeShaderGouraud();
	void changeShaderPBR();
	ofParameter<float> slider_metallic;
	ofParameter<float> slider_roughness;
	float material_metallic;
	float material_roughness;


	//___________________________

	//2D
	ofxPanel guiProperties2D;
	ofxPanel guiObjects2D;
	ofxPanel guiCamera2D;
	ofxPanel guiControlPoints;
	ofxPanel guiFilter;

	ofxButton newCircleButton;
	ofxButton newSquareButton;
	ofxButton newTriangleButton;
	ofxButton newRectangleButton;
	ofxButton newEllipseButton;
	ofxButton newLineButton;
	ofxButton newStarButton;
	ofxButton newHouseButton;
	ofxButton newBezierSplineButton;
	ofxButton newCRbutton;
	ofxButton identityFilterButton;
	ofxButton embossFilterButton;
	ofxButton sharpenFilterButton;
	ofxButton edge_detectFilterButton;
	ofxButton blurFilterButton;

	vector<ofxVec2Slider*> controlPoints;

	bool curveSelected = false;
	bool imageSelected = false;
	//___________________________


	ofParameterGroup parameterGroup;

	bool is_verbose;
	bool newWindow;
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
		ofxLabel labelLight;

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

		bool isRGBA;
		ofParameter<ofColor> colorPicker;
		ofxVec3Slider hsbColorPicker;

		ofxButton cameraLookAtButton;
		ofxButton projectionModeButton;
		ofxButton setAnimationButton;
		ofxButton toggleRotationButton;
		ofxButton viewWindowButton;

		bool is_key_press_up;
		bool is_key_press_down;
		bool is_key_press_left;
		bool is_key_press_right;
		bool is_key_press_w;
		bool is_key_press_a;
		bool is_key_press_s;
		bool is_key_press_d;

		bool otherCursorInUse = false;

		bool mode3D = true;

private:

	void refreshHierarchy();
	void exportImage();
	void refreshProperties();

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
	void addBezierSurface();
	void addQuad();
	void addDelaunay();
	void deleteObject();
	void cameraLookAt();
	void switchProjectionMode();
	void setAnimation();
	void toggleRotation();
	void newToggleObject();
	void updateHierarchy();
	void toggleListener(bool& value);
	void updateSelection();
	void addNewLight1();
	void addNewLight2();
	void addNewLight3();
	void addNewLight4();

	//2D
	void addNewRectangle();
	void addNewTriangle();
	void addNewCircle();
	void addNewEllipse();
	void addNewLine();
	void addNewStar();
	void addNewHouse();
	void addNewBezierSpline();
	void addNewCR();

	void setFilterIdentity();
	void setFilterEmboss();
	void setFilterSharpen();
	void setFilterEdgeDetect();
	void setFilterBlur();
		
	void openFileSelection(ofFileDialogResult openFileResult);

	vector<ofImage>loadedImages;
	vector<ofImage>processedImages;
	string originalFileExtension;
		
};
