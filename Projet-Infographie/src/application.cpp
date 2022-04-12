#include "application.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetWindowTitle("2D/3D engine");
	ofLog() << "<app::setup>";

	renderer.setup();
	
	is_verbose = false;

	isRGBA = false;
	//3D
	//Panneau de propriete des objets     
	//Plusieurs outils ou sliders répertoriés la dedans. Pas tous utiles pour le moment, mais donner des idées.
	guiProperties3D.setup();
	guiProperties3D.setPosition(ofGetWindowWidth() - guiProperties3D.getWidth(), 0);
	guiProperties3D.add(labelProperties3D.setup("Panel", "Properties"));
	guiProperties3D.add(proportionSlider.setup("Proportion", ofVec3f(1, 1, 1), ofVec3f(0, 0, 0), ofVec3f(100, 100, 100)));
	guiProperties3D.add(positionSlider.setup("Position", ofVec3f(0, 0, 0), ofVec3f(-1920, -1080, 0), ofVec3f(1920, 1080, 1000)));
	guiProperties3D.add(rotationSlider.setup("Rotation", ofVec3f(0, 0, 0), ofVec3f(0, 0, 0), ofVec3f(360, 360, 360)));
	guiProperties3D.add(colorPicker.set("Color", ofColor(31), ofColor(0, 0), ofColor(255, 255)));
	guiProperties3D.add(HSBDisplayButton.setup("HSB"));
	HSBDisplayButton.addListener(this, &ofApp::refreshProperties);

	//Informations de sauvegarde dynamique
	guiProperties3D.add(intSliderTakes.setup("Nombre de prises", 1, 1, 24));
	guiProperties3D.add(intSliderFrames.setup("Nombre de frames par prises", 5, 1, 500));

	//panneau de hierarchie des objets ** À développer **
	guiHierarchy.setup();
	guiHierarchy.setPosition(0, 0);
	guiHierarchy.add(labelHierarchy.setup("Panel", "Hierarchy"));

	//Panneau de lumières
	guiLights.setup();
	guiLights.setPosition(ofGetWindowWidth() - guiLights.getWidth(), guiProperties3D.getHeight());
	guiLights.add(labelLight.setup("Panel", "Lights"));
	guiLights.add(newLight1.setup("Ambient Light"));
	guiLights.add(newLight2.setup("Pulsing Light"));
	guiLights.add(newLight3.setup("Cursor Light"));
	guiLights.add(newLight4.setup("SpotLight"));
	newLight1.addListener(this, &ofApp::addNewLight1);
	newLight2.addListener(this, &ofApp::addNewLight2);
	newLight3.addListener(this, &ofApp::addNewLight3);
	newLight4.addListener(this, &ofApp::addNewLight4);

	//Panneau d'ajout d'objects 3D
	guiObjects3D.setup();
	guiObjects3D.setPosition(ofGetWindowWidth() - guiObjects3D.getWidth(), ofGetWindowHeight()- guiObjects3D.getHeight());
	guiObjects3D.add(labelNewObject3D.setup("Panel", "New object 3D"));
	guiObjects3D.add(newObjectName);
	guiObjects3D.add(newSphereButton.setup("New sphere"));
	guiObjects3D.add(newBoxButton.setup("New Box"));
	guiObjects3D.add(newConeButton.setup("New Cone"));
	guiObjects3D.add(newCylinderButton.setup("New Cylinder"));
	guiObjects3D.add(newTeapotButton.setup("Teapot.obj"));
	guiObjects3D.add(newGlassesButton.setup("glasses.3DS"));
	guiObjects3D.add(newTVButton.setup("tv.fbx"));
	guiObjects3D.add(newWolfButton.setup("Animated Wolf"));
	guiObjects3D.add(deleteButton.setup("Delete object"));

	newObjectName.set("Name: ", "");
	newObjectButton.addListener(this, &ofApp::addNewObject);
	newSphereButton.addListener(this, &ofApp::addNewSphere);
	newBoxButton.addListener(this, &ofApp::addNewBox);
	newConeButton.addListener(this, &ofApp::addNewCone);
	newCylinderButton.addListener(this, &ofApp::addNewCylinder);
	newTeapotButton.addListener(this, &ofApp::addNewTeapot);
	newGlassesButton.addListener(this, &ofApp::addNewGlasses);
	newTVButton.addListener(this, &ofApp::addNewTV);
	newWolfButton.addListener(this, &ofApp::addAnimatedWolf);
	deleteButton.addListener(this, &ofApp::deleteObject);


	//panneau de contrôle de formes. 
	//Avec L'idée de créer une classe forme, nous pouvons avoir des panneaux qui apparaissent en fonction des formes que nous générerons.
	//Certaines choses se recoupent entre les deux sections (panneau de propriété) mais nous ferons des choix.

	guiCamera3D.setup();
	guiCamera3D.setPosition(0, ofGetWindowHeight() - guiCamera3D.getHeight());
	guiCamera3D.add(cameraLookAtButton.setup("Camera look at"));
	cameraLookAtButton.addListener(this, &ofApp::cameraLookAt);
	guiCamera3D.add(projectionModeButton.setup("Switch projection mode"));
	projectionModeButton.addListener(this, &ofApp::switchProjectionMode);
	guiCamera3D.add(setAnimationButton.setup("Animation"));
	setAnimationButton.addListener(this, &ofApp::setAnimation);
	guiCamera3D.add(toggleRotationButton.setup("Rotate 3D models"));
	toggleRotationButton.addListener(this, &ofApp::toggleRotation);
	//____________________________________________________________________

	//Panneau de proprietes 2D
	guiProperties2D.setup();
	guiProperties2D.setPosition(ofGetWindowWidth() - guiProperties2D.getWidth(), 0);
	guiProperties2D.add(labelProperties2D.setup("Panel", "Properties 2D"));
	guiProperties2D.add(proportionSlider2D.setup("Proportion", ofVec2f(1, 1), ofVec2f(0, 0), ofVec2f(100, 100)));
	guiProperties2D.add(positionSlider2D.setup("Position", ofVec2f(0, 0), ofVec2f(-1920, -1080), ofVec2f(1920,1080)));
	//guiProperties2D.add(rotationSlider2D.setup("Rotation", ofVec2f(0, 0), ofVec2f(0, 0), ofVec2f(360, 360)));
	guiProperties2D.add(colorPicker.set("Color", ofColor(31), ofColor(0, 0), ofColor(255, 255)));
	guiProperties2D.add(HSBDisplayButton.setup("HSB"));

	//Panneau d'ajout d'objects 2D

	guiObjects2D.setup();
	guiObjects2D.setPosition(ofGetWindowWidth() - guiObjects2D.getWidth(), ofGetWindowHeight() - guiObjects2D.getHeight());
	guiObjects2D.add(newObjectName);
	guiObjects2D.add(labelNewObject2D.setup("Panel", "New object 2D"));
	guiObjects2D.add(newRectangleButton.setup("New Rectangle"));
	guiObjects2D.add(newCircleButton.setup("New Circle"));
	guiObjects2D.add(newTriangleButton.setup("New Triangle"));
	guiObjects2D.add(newEllipseButton.setup("New Ellipse"));
	guiObjects2D.add(newLineButton.setup("New Line"));
	guiObjects2D.add(newStarButton.setup("New Star"));
	guiObjects2D.add(newHouseButton.setup("New House"));
	guiObjects2D.add(deleteButton.setup("Delete object"));
		
	newObjectName.set("Name: ", "");
	newRectangleButton.addListener(this, &ofApp::addNewRectangle);
	newCircleButton.addListener(this, &ofApp::addNewCircle);
	newTriangleButton.addListener(this, &ofApp::addNewTriangle);
	newEllipseButton.addListener(this, &ofApp::addNewEllipse);
	newLineButton.addListener(this, &ofApp::addNewLine);
	newStarButton.addListener(this, &ofApp::addNewStar);
	newHouseButton.addListener(this, &ofApp::addNewHouse);


	is_key_press_up = false;
	is_key_press_down = false;
	is_key_press_left = false;
	is_key_press_right = false;
	is_key_press_w = false;
	is_key_press_a = false;
	is_key_press_s = false;
	is_key_press_d = false;
}

//--------------------------------------------------------------
void ofApp::update(){

	renderer.is_camera_move_left = is_key_press_left;
	renderer.is_camera_move_right = is_key_press_right;

	renderer.is_camera_move_up = is_key_press_up;
	renderer.is_camera_move_down = is_key_press_down;

	renderer.is_camera_pan_y_forward = is_key_press_a;
	renderer.is_camera_pan_y_backward = is_key_press_d;
	renderer.is_camera_tilt_x_right = is_key_press_w;
	renderer.is_camera_tilt_x_left = is_key_press_s;



	if (otherCursorInUse == false) {
		if (mode3D == true) {
			renderer.crossCursor_enabled = false;
			renderer.circleCursor_enabled = false;
			renderer.arrowCursor_enabled = true;
			renderer.handCursor_enabled = false;
			renderer.resizeCursor_enabled = false;
			renderer.resizeCursorUpDown_enabled = false;
		}
		if (mode3D == false) {
			renderer.crossCursor_enabled = false;
			renderer.circleCursor_enabled = false;
			renderer.arrowCursor_enabled = false;
			renderer.handCursor_enabled = true;
			renderer.resizeCursor_enabled = false;
			renderer.resizeCursorUpDown_enabled = false;
		}
	}

	for (int i : selectedObjects) {

		if (otherCursorInUse == false) {
			renderer.crossCursor_enabled = true;
			renderer.circleCursor_enabled = false;
			renderer.arrowCursor_enabled = false;
			renderer.handCursor_enabled = false;
			renderer.resizeCursor_enabled = false;
			renderer.resizeCursorUpDown_enabled = false;
		}
		ofVec3f newProportion;
		ofVec3f newPosition;
		ofVec3f newRotation;
		if (mode3D) {
			newProportion = ofVec3f(proportionSlider);
			newPosition = ofVec3f(positionSlider);
			newRotation = ofVec3f(rotationSlider);
		}
		else {
			ofVec3f newProportion2D(proportionSlider2D);
			newProportion = ofVec3f(newProportion2D.x, newProportion2D.y, 1);
			newPosition = ofVec3f(positionSlider2D);
			newRotation = ofVec3f(rotationSlider2D);
		}
		renderer.proportionateObject(i, newProportion);
		renderer.moveObject(i, newPosition);
		renderer.rotateObject(i, newRotation);
		if (isRGBA) {
			renderer.setObjectColor(i, colorPicker);
		}
		else {
			ofVec3f hsb = hsbColorPicker;
			float h = (hsb.x * 255) / 360;
			float s = (hsb.y * 255) / 100;
			float b = (hsb.z * 255) / 100;
			ofColor myRGBColor;
			myRGBColor = myRGBColor.fromHsb(h, s, b);
			renderer.setObjectColor(i, myRGBColor);
		}
		renderer.drawBoundingBox(i);
	}
	updateHierarchy();
	renderer.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	renderer.draw();

	exportImage();

	if (mode3D==true) {
		ofDrawBitmapString("Press F2 to save, TAB to switch between 2D and 3D.", guiHierarchy.getWidth(), 10);
		guiProperties3D.draw();
		guiObjects3D.draw();
		guiCamera3D.draw();
		guiLights.draw();
	}

	if (mode3D==false) {
		ofDrawBitmapString("Press F3 to open an image, F2 to save, TAB to switch between 2D and 3D.", guiHierarchy.getWidth(), 10);
		ofDrawBitmapString("Press F4 to open TopLeft of an image, F5 for TopRight, F6 for DownLeft and F7 for DownRight.", guiHierarchy.getWidth(), 30);
		guiProperties2D.draw();
		guiObjects2D.draw();
	}

	guiHierarchy.draw();
}

//---------------------------------------------------------------
//Sort function for stl::sort http://www.cplusplus.com/reference/algorithm/sort/
bool sortColorFunction(ofColor i, ofColor j) {
	return (i.getBrightness() < j.getBrightness());
}

//--------------------------------------------------------------
//Fonction pour charger un fichier choisi lors de la recherche dans le réseau local.
void ofApp::openFileSelection(ofFileDialogResult openFileResult) {

	ofLog()<<"getName(): " + openFileResult.getName();
	ofLog()<<"getPath(): " + openFileResult.getPath();

	ofFile file(openFileResult.getPath());

	if (file.exists()) {
		//présentement, nous chargons une seule image à la fois
		loadedImages.clear();

		ofLog()<<"The file exists - now checking the type via file extension";
		string fileExtension = ofToUpper(file.getExtension());

		if (fileExtension == "JPG" || fileExtension == "PNG") {

			// Conserver l'extention pour la sauvegarde future
			originalFileExtension = fileExtension;

			//Load l'image choisie
			ofImage image;
			image.load(openFileResult.getPath());
			if (image.getWidth() > ofGetWidth() || image.getHeight() > ofGetHeight())
			{
				image.resize(image.getWidth() / 2, image.getHeight() / 2);
			}

			loadedImages.push_back(image);
			ofLog() << "loading completed";
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key)
	{
	case OF_KEY_LEFT: // touche ←
		is_key_press_left = true;
		renderer.crossCursor_enabled = false;
		renderer.circleCursor_enabled = false;
		renderer.arrowCursor_enabled = false;
		renderer.handCursor_enabled = false;
		renderer.resizeCursorUpDown_enabled = false;
		renderer.resizeCursor_enabled = true;
		otherCursorInUse = true;
		break;

	case OF_KEY_UP: // touche ↑
		is_key_press_up = true;
		renderer.crossCursor_enabled = false;
		renderer.circleCursor_enabled = false;
		renderer.arrowCursor_enabled = false;
		renderer.handCursor_enabled = false;
		renderer.resizeCursor_enabled = false;
		renderer.resizeCursorUpDown_enabled = true;
		otherCursorInUse = true;
		break;

	case OF_KEY_RIGHT: // touche →
		is_key_press_right = true;
		renderer.crossCursor_enabled = false;
		renderer.circleCursor_enabled = false;
		renderer.arrowCursor_enabled = false;
		renderer.handCursor_enabled = false;
		renderer.resizeCursorUpDown_enabled = false;
		renderer.resizeCursor_enabled = true;
		otherCursorInUse = true;
		break;

	case OF_KEY_DOWN: // touche ↓
		is_key_press_down = true;
		renderer.crossCursor_enabled = false;
		renderer.circleCursor_enabled = false;
		renderer.arrowCursor_enabled = false;
		renderer.handCursor_enabled = false;
		renderer.resizeCursor_enabled = false;
		renderer.resizeCursorUpDown_enabled = true;
		otherCursorInUse = true;
		break;

	case 119://W
		if (mode3D == true) {
			is_key_press_w = true;
		}
		break;

	case 97://A
		if (mode3D == true) {
			is_key_press_a = true;
		}
		break;

	case 115://S
		if (mode3D == true) {
			is_key_press_s = true;
		}
		break;

	case 100://D
		if (mode3D == true) {
			is_key_press_d = true;
		}
		break;

	case 32://espace Reset la caméra
		renderer.mainCamera.resetTransform();
		renderer.mainCamera.setPosition(0, 0, 500);
		renderer.mainCamera.setFov(60.0f);
		break;

	default:
		ofLog() << key;
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

	switch (key)
	{
	case 49: // touche 1
		for (int o : selectedObjects) {
			renderer.shaderActive(o , "color_fill");

		}

		ofLog() << "<shader: color fill>";
		break;

	case 50: // touche 2
		for (int o : selectedObjects) {
			renderer.shaderActive(o, "lambert");
		}
		ofLog() << "<shader: lambert>";
		break;

	case 51: // touche 3
		for (int o : selectedObjects) {
			renderer.shaderActive(o, "gouraud");
		}
		ofLog() << "<shader: gouraud>";
		break;

	case 52: // touche 4
		for (int o : selectedObjects) {
			renderer.shaderActive(o, "phong");
		}
		ofLog() << "<shader: phong>";
		break;

	case 53: // touche 5
		for (int o : selectedObjects) {
			renderer.shaderActive(o, "blinn_phong");
		}
		ofLog() << "<shader: blinn-phong>";
		break;

	case 57350: //touche f7 pour rogner l'image
		if (mode3D == false) {
			string keypressed = "f7";
			renderer.addNewImage(newObjectName, keypressed);
			cout << "test";
			newToggleObject();
			newObjectName.set("");
		}
		break;

	case 57349: //touche f6 pour rogner l'image
		if (mode3D == false) {
			string keypressed = "f6";
			renderer.addNewImage(newObjectName, keypressed);
			newToggleObject();
			newObjectName.set("");
		}
		break;

	case 57348: //touche f5 pour rogner l'image
		if (mode3D == false) {
			string keypressed = "f5";
			renderer.addNewImage(newObjectName, keypressed);
			newToggleObject();
			newObjectName.set("");
		}
		break;

	case 57347: //touche f4 pour rogner l'image
		if (mode3D == false) {
			string keypressed = "f4";
			renderer.addNewImage(newObjectName, keypressed);
			newToggleObject();
			newObjectName.set("");
		}
		break;
		
	case 57346: // touche F3 pour rechercher une image
		if (mode3D == false) {
			string keypressed = "f3";
			renderer.addNewImage(newObjectName, keypressed);
			newToggleObject();
			newObjectName.set("");
		}
			
		break;

	case 57345: // touche F2 pour sauvegarde dynamique de la scene
		nbTakes = intSliderTakes;
		nbFrames = 0;
		nbFramesPerTake = intSliderFrames;
		break;

	case 9: // touche TAB pour changer mode 2d 3d
		selectedObjects.clear();
		objectsToggle.clear();
		if (mode3D) {
			mode3D = false;
			renderer.isMode3D = false;
			renderer.crossCursor_enabled = false;
			renderer.circleCursor_enabled = false;
			renderer.arrowCursor_enabled = false;
			renderer.handCursor_enabled = true;
			renderer.resizeCursor_enabled = false;
			renderer.resizeCursorUpDown_enabled = false;
		}
		else {
			mode3D = true;
			renderer.isMode3D = true;
			renderer.crossCursor_enabled = false;
			renderer.circleCursor_enabled = false;
			renderer.arrowCursor_enabled = true;
			renderer.handCursor_enabled = false;
			renderer.resizeCursor_enabled = false;
			renderer.resizeCursorUpDown_enabled = false;
		}
		refreshHierarchy();
		windowResized(ofGetWindowWidth(), ofGetWindowHeight());
		break;
	case OF_KEY_LEFT: // touche ←
		is_key_press_left = false;
		if (mode3D == true) {
			renderer.crossCursor_enabled = false;
			renderer.circleCursor_enabled = false;
			renderer.arrowCursor_enabled = true;
			renderer.handCursor_enabled = false;
			renderer.resizeCursor_enabled = false;
			renderer.resizeCursorUpDown_enabled = false;
		}
		if (mode3D == false) {
			renderer.crossCursor_enabled = false;
			renderer.circleCursor_enabled = false;
			renderer.arrowCursor_enabled = false;
			renderer.handCursor_enabled = true;
			renderer.resizeCursor_enabled = false;
			renderer.resizeCursorUpDown_enabled = false;
		}
		otherCursorInUse = false;
		break;

	case OF_KEY_UP: // touche ↑
		is_key_press_up = false;
		if (mode3D == true) {
			renderer.crossCursor_enabled = false;
			renderer.circleCursor_enabled = false;
			renderer.arrowCursor_enabled = true;
			renderer.handCursor_enabled = false;
			renderer.resizeCursor_enabled = false;
			renderer.resizeCursorUpDown_enabled = false;
		}
		if (mode3D == false) {
			renderer.crossCursor_enabled = false;
			renderer.circleCursor_enabled = false;
			renderer.arrowCursor_enabled = false;
			renderer.handCursor_enabled = true;
			renderer.resizeCursor_enabled = false;
			renderer.resizeCursorUpDown_enabled = false;
		}
		otherCursorInUse = false;
		break;

	case OF_KEY_RIGHT: // touche →
		is_key_press_right = false;
		if (mode3D == true) {
			renderer.crossCursor_enabled = false;
			renderer.circleCursor_enabled = false;
			renderer.arrowCursor_enabled = true;
			renderer.handCursor_enabled = false;
			renderer.resizeCursor_enabled = false;
			renderer.resizeCursorUpDown_enabled = false;
		}
		if (mode3D == false) {
			renderer.crossCursor_enabled = false;
			renderer.circleCursor_enabled = false;
			renderer.arrowCursor_enabled = false;
			renderer.handCursor_enabled = true;
			renderer.resizeCursor_enabled = false;
			renderer.resizeCursorUpDown_enabled = false;
		}
		otherCursorInUse = false;
		break;

	case OF_KEY_DOWN: // touche ↓
		is_key_press_down = false;
		if (mode3D == true) {
			renderer.crossCursor_enabled = false;
			renderer.circleCursor_enabled = false;
			renderer.arrowCursor_enabled = true;
			renderer.handCursor_enabled = false;
			renderer.resizeCursor_enabled = false;
			renderer.resizeCursorUpDown_enabled = false;
		}
		if (mode3D == false) {
			renderer.crossCursor_enabled = false;
			renderer.circleCursor_enabled = false;
			renderer.arrowCursor_enabled = false;
			renderer.handCursor_enabled = true;
			renderer.resizeCursor_enabled = false;
			renderer.resizeCursorUpDown_enabled = false;
		}
		otherCursorInUse = false;
		break;

	case 119://W
		is_key_press_w = false;
		break;

	case 97://A
		is_key_press_a = false;
		break;

	case 115://S
		is_key_press_s = false;
		break;

	case 100://D
		is_key_press_d = false;
		break;

	default:
		break;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

	renderer.mouse_current_x = x;
	renderer.mouse_current_y = y;

	if (is_verbose)
		ofLog() << "ofApp::mouseMoved   at: ( x :" << x << ", y:" << y << ")";

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

	renderer.mouse_current_x = x;
	renderer.mouse_current_y = y;

	if (is_verbose)
		ofLog() << "ofApp::mouseDragged   at: ( x :" << x << ", y:" << y << ")" "button:" << button;

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

	renderer.is_mouse_button_pressed = true;

	renderer.mouse_current_x = x;
	renderer.mouse_current_y = y;

	renderer.mouse_press_x = x;
	renderer.mouse_press_y = y;

	ofLog() << "ofApp::mousePressed   at: ( x :" << x << ", y:" << y << ")";

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

	renderer.is_mouse_button_pressed = false;

	renderer.mouse_current_x = x;
	renderer.mouse_current_y = y;


	ofLog() << "ofApp::mouseReleased   at: ( x :" << x << ", y:" << y << ")";
}

void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY) {
	renderer.mainCamera.dolly(-scrollY * 100);
	//renderer.magnifyingGlassEnabled = true;
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

	renderer.mouse_current_x = x;
	renderer.mouse_current_y = y;

	ofLog() << "ofApp::mouseEntered   at: ( x :" << x << ", y:" << y << ")";

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

	renderer.mouse_current_x = x;
	renderer.mouse_current_y = y;

	ofLog() << "ofApp::mouseExited  at: ( x :" << x << ", y:" << y << ")";
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
	if (mode3D) {
		guiHierarchy.setPosition(0, 0);
		guiProperties3D.setPosition(w - guiProperties3D.getWidth(), 0);
		guiCamera3D.setPosition(0, h - guiCamera3D.getHeight());
		guiObjects3D.setPosition(w - guiObjects3D.getWidth(), h - guiObjects3D.getHeight());
	} else {
		guiHierarchy.setPosition(0, 0);
		guiProperties2D.setPosition(w - guiProperties2D.getWidth(), 0);
		//guiCamera3D.setPosition(0, ofGetWindowHeight() - guiCamera3D.getHeight());
		guiObjects2D.setPosition(w - guiObjects2D.getWidth(), h - guiObjects2D.getHeight());
	}
	
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}
//--------------------------------------------------------------
void ofApp::getHsb()
{

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}


//3D

void ofApp::addNewObject() {
	renderer.addNew3dObject(newObjectName);
	newToggleObject();
	newObjectName.set("");
}

void ofApp::addNewSphere() {
	renderer.addNewSphere(newObjectName);
	newToggleObject();
	newObjectName.set("");
}

void ofApp::addNewBox() {
	renderer.addNewBox(newObjectName);
	newToggleObject();
	newObjectName.set("");
}

void ofApp::addNewCone() {
	renderer.addNewCone(newObjectName);
	newToggleObject();
	newObjectName.set("");
}

void ofApp::addNewCylinder() {
	renderer.addNewCylinder(newObjectName);
	newToggleObject();
	newObjectName.set("");
}

void ofApp::addNewTeapot() {
	renderer.import3dModel("teapot.obj");
	newToggleObject();
	newObjectName.set("");
}

void ofApp::addNewGlasses() {
	renderer.import3dModel("glasses.3DS");
	newToggleObject();
	newObjectName.set("");
}

void ofApp::addNewTV() {
	renderer.import3dModel("tv.fbx");
	newToggleObject();
	newObjectName.set("");
}

void ofApp::addAnimatedWolf() {
	renderer.import3dModel("Wolf_dae.dae");
	newToggleObject();
	newObjectName.set("");
}

void ofApp::deleteObject() {
	for (int i = 0; i < selectedObjects.size(); i++) {
		int index = selectedObjects[i];
		index = index - i;
		renderer.deleteObject(index);
	}
	objectsToggle.clear();
	if (mode3D)
	{
		for (int i = 0; i < renderer.objects3d.size(); i++) {
			ofParameter<bool> toggle;
			
			string name = renderer.getObject3dName(i);
			toggle.set(name, false);
			toggle.addListener(this, &ofApp::toggleListener);
			objectsToggle.push_back(toggle);
		}
	}
	else {
		for (int i = 0; i < renderer.objects2D.size(); i++) {
			ofParameter<bool> toggle;
			
			string name = renderer.getObject2dName(i);
			toggle.set(name, false);
			toggle.addListener(this, &ofApp::toggleListener);
			objectsToggle.push_back(toggle);
		}

	}
	updateSelection();
}

void ofApp::toggleListener(bool& value) {
	updateSelection();
	if (selectedObjects.size() == 1) {
		if (mode3D) {
			ofVec3f proportion(renderer.objects3d[selectedObjects[0]]->getProportion());
			ofVec3f position(renderer.objects3d[selectedObjects[0]]->getPosition());
			ofVec3f rotation(renderer.objects3d[selectedObjects[0]]->getRotation());
			ofColor color = renderer.objects3d[selectedObjects[0]]->getColor();
			proportionSlider = proportion;
			positionSlider = position;
			rotationSlider = rotation;
			colorPicker = color;
		}
		else {
			ofVec3f proportion(renderer.objects2D[selectedObjects[0]]->getProportion());
			ofVec3f position(renderer.objects2D[selectedObjects[0]]->getPosition());
			ofVec3f rotation(renderer.objects2D[selectedObjects[0]]->getRotation());
			proportionSlider2D.setup("Proportion", ofVec2f(proportion.x, proportion.y), ofVec2f(0, 0), ofVec2f(100, 100));
			positionSlider2D.setup("Position", ofVec2f(position.x, position.y), ofVec2f(-1920, -1080), ofVec2f(1920, 1080));
			rotationSlider2D.setup("Rotation", ofVec2f(rotation.x, rotation.y), ofVec2f(0, 0), ofVec2f(360, 360));
			ofColor color = renderer.objects2D[selectedObjects[0]]->getColor();
			colorPicker = color;
		}
	}
}

void ofApp::updateSelection() {
	selectedObjects.clear();
	for (int i = 0; i < objectsToggle.size(); i++) {
		if (objectsToggle[i].get()) {
			selectedObjects.push_back(i);
		}
	}
}

void ofApp::cameraLookAt() {
	if (selectedObjects.size() == 1) {
		renderer.cameraLookAt(selectedObjects[0]);
	}
}

void ofApp::switchProjectionMode() {
	renderer.switchProjectionMode();
}

void ofApp::setAnimation() {
	for (int o : selectedObjects) {
		renderer.setAnimation(o);
	}
}

void ofApp::toggleRotation() {
	for (int o : selectedObjects) {
		renderer.toggleRotation(o);
	}
}

void ofApp::newToggleObject() {
	ofParameter<bool> toggle;
	if (mode3D)
	{
		string name = renderer.getObject3dName(renderer.objects3d.size() - 1);
		toggle.set(name, false);
		toggle.addListener(this, &ofApp::toggleListener);
		objectsToggle.push_back(toggle);
	}
	else
	{
		string name = renderer.getObject2dName(renderer.objects2D.size() - 1);
		toggle.set(name, false);
		toggle.addListener(this, &ofApp::toggleListener);
		objectsToggle.push_back(toggle);
	}
}

void ofApp::updateHierarchy() {
	guiHierarchy.clear();
	guiHierarchy.add(labelHierarchy.setup("Panel", "Hierarchy"));
	
	for (ofParameter<bool> toggle : objectsToggle) {
		guiHierarchy.add(toggle);
	}
}

void ofApp::exportImage() {
	if (nbTakes > 0) {
		if (nbFrames == nbFramesPerTake) {
			renderer.image_export("serie", "png");
			nbTakes--;
			nbFrames = 0;
		}
		nbFrames++;
	}
}

//Called when switching 2D/3D
void ofApp::refreshHierarchy() {
	if (mode3D) {
		for (object3D* object : renderer.objects3d) {
			ofParameter<bool> toggle;
			toggle.set(object->getName(), false);
			toggle.addListener(this, &ofApp::toggleListener);
			objectsToggle.push_back(toggle);
		}
	}
	else {
		for (Object2D* object : renderer.objects2D) {
			ofParameter<bool> toggle;
			toggle.set(object->getName(), false);
			toggle.addListener(this, &ofApp::toggleListener);
			objectsToggle.push_back(toggle);
		}
	}
}

void ofApp::refreshProperties() {
	if (!isRGBA) {
		isRGBA = true;
		ofVec3f hsb = hsbColorPicker;
		float h = (hsb.x * 255) / 360;
		float s = (hsb.y * 255) / 100;
		float b = (hsb.z * 255) / 100;
		ofColor myRGBColor;
		myRGBColor = myRGBColor.fromHsb(h, s, b);
		guiProperties3D.setup();
		guiProperties3D.setPosition(ofGetWindowWidth() - guiProperties3D.getWidth(), 0);
		guiProperties3D.add(labelProperties3D.setup("Panel", "Properties"));
		guiProperties3D.add(proportionSlider.setup("Proportion", proportionSlider, ofVec3f(0, 0, 0), ofVec3f(100, 100, 100)));
		guiProperties3D.add(positionSlider.setup("Position", positionSlider, ofVec3f(-1920, -1080, 0), ofVec3f(1920, 1080, 1000)));
		guiProperties3D.add(rotationSlider.setup("Rotation", rotationSlider, ofVec3f(0, 0, 0), ofVec3f(360, 360, 360)));
		guiProperties3D.add(colorPicker.set("Color RGBA", ofColor(myRGBColor), ofColor(0, 0, 0, 0), ofColor(255, 255, 255, 255)));
		guiProperties3D.add(HSBDisplayButton.setup("HSB"));
		guiProperties3D.add(intSliderTakes.setup("Nombre de prises", 1, 1, 24));
		guiProperties3D.add(intSliderFrames.setup("Nombre de frames par prises", 5, 1, 500));

		guiProperties2D.setup();
		guiProperties2D.setPosition(ofGetWindowWidth() - guiProperties2D.getWidth(), 0);
		guiProperties2D.add(labelProperties2D.setup("Panel", "Properties 2D"));
		guiProperties2D.add(proportionSlider2D.setup("Proportion", ofVec2f(1, 1), ofVec2f(0, 0), ofVec2f(100, 100)));
		guiProperties2D.add(positionSlider2D.setup("Position", ofVec2f(0, 0), ofVec2f(-1920, -1080), ofVec2f(1920, 1080)));
		//guiProperties2D.add(rotationSlider2D.setup("Rotation", ofVec2f(0, 0), ofVec2f(0, 0), ofVec2f(360, 360)));
		guiProperties2D.add(colorPicker.set("Color", ofColor(myRGBColor), ofColor(0, 0), ofColor(255, 255)));
		guiProperties2D.add(HSBDisplayButton.setup("HSB"));
		guiProperties2D.add(intSliderTakes.setup("Nombre de prises", 1, 1, 24));
		guiProperties2D.add(intSliderFrames.setup("Nombre de frames par prises", 5, 1, 500));
	}
	else {
		ofColor myRGBColor;
		myRGBColor.set(colorPicker);
		float h = myRGBColor.getHueAngle();
		float s = (myRGBColor.getSaturation()*100)/255;
		float b = (myRGBColor.getBrightness()*100)/255;
		isRGBA = false;
		guiProperties3D.setup();
		guiProperties3D.setPosition(ofGetWindowWidth() - guiProperties3D.getWidth(), 0);
		guiProperties3D.add(labelProperties3D.setup("Panel", "Properties"));
		guiProperties3D.add(proportionSlider.setup("Proportion", proportionSlider, ofVec3f(0, 0, 0), ofVec3f(100, 100, 100)));
		guiProperties3D.add(positionSlider.setup("Position", positionSlider, ofVec3f(-1920, -1080, 0), ofVec3f(1920, 1080, 1000)));
		guiProperties3D.add(rotationSlider.setup("Rotation", rotationSlider, ofVec3f(0, 0, 0), ofVec3f(360, 360, 360)));
		guiProperties3D.add(hsbColorPicker.setup("Color HSB", ofVec3f(h, s, b), ofVec3f(0, 0, 0), ofVec3f(360, 100, 100)));
		guiProperties3D.add(HSBDisplayButton.setup("HSB"));
		guiProperties3D.add(intSliderTakes.setup("Nombre de prises", 1, 1, 24));
		guiProperties3D.add(intSliderFrames.setup("Nombre de frames par prises", 5, 1, 500));

		guiProperties2D.setup();
		guiProperties2D.setPosition(ofGetWindowWidth() - guiProperties2D.getWidth(), 0);
		guiProperties2D.add(labelProperties2D.setup("Panel", "Properties 2D"));
		guiProperties2D.add(proportionSlider2D.setup("Proportion", ofVec2f(1, 1), ofVec2f(0, 0), ofVec2f(100, 100)));
		guiProperties2D.add(positionSlider2D.setup("Position", ofVec2f(0, 0), ofVec2f(-1920, -1080), ofVec2f(1920, 1080)));
		//guiProperties2D.add(rotationSlider2D.setup("Rotation", ofVec2f(0, 0), ofVec2f(0, 0), ofVec2f(360, 360)));
		guiProperties2D.add(hsbColorPicker.setup("Color HSB", ofVec3f(h, s, b), ofVec3f(0, 0, 0), ofVec3f(360, 100, 100)));
		guiProperties2D.add(HSBDisplayButton.setup("HSB"));
		guiProperties2D.add(intSliderTakes.setup("Nombre de prises", 1, 1, 24));
		guiProperties2D.add(intSliderFrames.setup("Nombre de frames par prises", 5, 1, 500));
	}
}
//__________________________________________-
//2D

void ofApp::addNewRectangle() {
	renderer.addNewRectangle(newObjectName);
	newToggleObject();
	newObjectName.set("");
}

void ofApp::addNewCircle(){
	renderer.addNewCircle(newObjectName);
	newToggleObject();
	newObjectName.set("");
}

void ofApp::addNewTriangle() {
	renderer.addNewTriangle(newObjectName);
	newToggleObject();
	newObjectName.set("");
}

void ofApp::addNewEllipse() {
	renderer.addNewEllipse(newObjectName);
	newToggleObject();
	newObjectName.set("");
}

void ofApp::addNewLine() {
	renderer.addNewLine(newObjectName);
	newToggleObject();
	newObjectName.set("");
}

void ofApp::addNewStar() {
	renderer.addNewStar(newObjectName);
	newToggleObject();
	newObjectName.set("");
}

void ofApp::addNewHouse() {
	renderer.addNewHouse(newObjectName);
	newToggleObject();
	newObjectName.set("");
}

void ofApp::addNewLight1() {
	renderer.addNewLight(1);
}

void ofApp::addNewLight2() {
	renderer.addNewLight(2);
}

void ofApp::addNewLight3() {
	renderer.addNewLight(3);
}

void ofApp::addNewLight4() {
	renderer.addNewLight(4);
}




