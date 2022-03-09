#include "application.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetWindowTitle("2D/3D engine");
	ofLog() << "<app::setup>";

	renderer.setup();
	
	
	is_verbose = false;

	//3D
		//Panneau de propriete des objets     
	//Plusieurs outils ou sliders répertoriés la dedans. Pas tous utiles pour le moment, mais donner des idées.
	guiProperties3D.setup();
	guiProperties3D.setPosition(ofGetWindowWidth() - guiProperties3D.getWidth(), 0);
	guiProperties3D.add(labelProperties3D.setup("Panel", "Properties"));

	proportionGroup.setName("Proportion");
	proportionGroup.add(proportionX.set("x", 1, 0, 100));
	proportionGroup.add(proportionY.set("y", 1, 0, 100));
	proportionGroup.add(proportionZ.set("z", 1, 0, 100));
	guiProperties3D.add(proportionGroup);
	guiProperties3D.add(positionSlider.setup("Position", ofVec3f(0, 0, 0), ofVec3f(-1920, -1080, 0), ofVec3f(1920, 1080, 1000)));
	guiProperties3D.add(rotationSlider.setup("Rotation", ofVec3f(0, 0, 0), ofVec3f(0, 0, 0), ofVec3f(360, 360, 360)));
	guiProperties3D.add(renderer.colorPicker.set("Color", ofColor(31), ofColor(0, 0), ofColor(255, 255)));
	guiProperties3D.add(HSBDisplayButton.setup("HSB"));
	HSBDisplayButton.addListener(this, &ofApp::getHsb);

	//Informations de sauvegarde dynamique
	guiProperties3D.add(intSliderTakes.setup("nombre de prises", 1, 1, 24));
	guiProperties3D.add(floatSliderTime.setup("temps sauvegarde (secondes)", 5.0, 1.0, 30.0));

	//panneau de hierarchie des objets ** À développer **
	guiHierarchy.setup();
	guiHierarchy.setPosition(0, 0);
	guiHierarchy.add(labelHierarchy.setup("Panel", "Hierarchy"));

	//Panneau d'ajout d'objects 3D
	guiObjects3D.setup();
	guiObjects3D.setPosition(ofGetWindowWidth() - guiObjects3D.getWidth(), ofGetWindowHeight()- guiObjects3D.getHeight());
	guiObjects3D.add(labelNewObject.setup("Panel", "New object 3D"));
	guiObjects3D.add(newObjectName);
	guiObjects3D.add(newObjectButton.setup("New 3DObject"));
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
	guiCamera3D.add(cameraObjectIndex.setup("Camera pointe vers: ", 0, 0, 100));
	cameraObjectIndex.addListener(this, &ofApp::cameraLookAt);
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

	proportionGroup.setName("Proportion");
	proportionGroup.add(proportionX2D.set("x", 1, 0, 100));
	proportionGroup.add(proportionY2D.set("y", 1, 0, 100));
	guiProperties2D.add(proportionGroup2D);
	guiProperties2D.add(positionSlider2D.setup("Position", ofVec2f(0, 0), ofVec2f(-1920, -1080), ofVec2f(360,360)));
	guiProperties2D.add(rotationSlider2D.setup("Rotation", ofVec2f(0, 0), ofVec2f(0, 0), ofVec2f(360, 360)));
	guiProperties2D.add(renderer.colorPicker.set("Color", ofColor(31), ofColor(0, 0), ofColor(255, 255)));
	guiProperties2D.add(HSBDisplayButton.setup("HSB"));
	HSBDisplayButton.addListener(this, &ofApp::getHsb);

	//Panneau d'ajout d'objects 2D

	guiObjects2D.setup();
	guiObjects2D.setPosition(ofGetWindowWidth() - guiObjects2D.getWidth(), ofGetWindowHeight() - guiObjects2D.getHeight());
	guiObjects2D.add(newObjectName);
	guiObjects2D.add(labelNewObject.setup("Panel", "New object 2D"));
	guiObjects2D.add(newRectangleButton.setup("New Rectangle"));
	guiObjects2D.add(newCircleButton.setup("New Circle"));
	guiObjects2D.add(newTriangleButton.setup("New Triangle"));
	guiObjects2D.add(newEllipseButton.setup("New Ellipse"));
	guiObjects2D.add(newLineButton.setup("New Line"));
	guiObjects2D.add(newStarButton.setup("New Star"));
	guiObjects2D.add(newHouseButton.setup("New House"));
		
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
}

//--------------------------------------------------------------
void ofApp::update(){
	renderer.is_camera_move_left = is_key_press_left;
	renderer.is_camera_move_right = is_key_press_right;

	renderer.is_camera_move_up = is_key_press_up;
	renderer.is_camera_move_down = is_key_press_down;

	for (int i : selectedObjects) {
		ofVec3f newProportion(proportionX, proportionY, proportionZ);
		renderer.proportionateObject(i, newProportion);
		ofVec3f newPosition(positionSlider);
		renderer.moveObject(i, newPosition);
		ofVec3f newRotation(rotationSlider);
		renderer.rotateObject(i, newRotation);
		renderer.setObjectColor(i);
	}
	updateHierarchy();
	renderer.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	renderer.draw();

	if (mode3D==true) {
		guiProperties3D.draw();
		guiObjects3D.draw();
		guiCamera3D.draw();
		guiHierarchy.draw();
	}

	if (mode3D==false) {
		guiProperties2D.draw();
		guiObjects2D.draw();
		guiHierarchy.draw();
	}

	//dessin de l'image chargée dans le buffer loadedImages.
	ofDrawBitmapString("Press F3 to open an image, F2 to save, TAB to switch between 2D and 3D.", guiHierarchy.getWidth(), 10);
	for (unsigned int i = 0; i < loadedImages.size(); i++) {
		loadedImages[i].draw(0, 20);
	}
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
//Fonction pour rechercher dans le réseau local une image
void ofApp::actionResearchImages() {

	//Open the Open File Dialog
	ofFileDialogResult openFileResult = ofSystemLoadDialog("choisir une image (JPG ou PNG)");

	//Check if the user opened a file
	if (openFileResult.bSuccess) {

		ofLog()<<"file selected";

		//ouvrir l'image choisie
		openFileSelection(openFileResult);
	}
	else {
		ofLog()<<"operation canceled by user";
	}
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key)
	{
	case OF_KEY_LEFT: // touche ←
		is_key_press_left = true;
		break;

	case OF_KEY_UP: // touche ↑
		is_key_press_up = true;
		break;

	case OF_KEY_RIGHT: // touche →
		is_key_press_right = true;
		break;

	case OF_KEY_DOWN: // touche ↓
		is_key_press_down = true;
		break;

	default:
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

	switch (key)
	{
	case 49://curseur en croix
		renderer.crossCursor_enabled = true;
		renderer.circleCursor_enabled = false;
		renderer.arrowCursor_enabled = false;
		renderer.handCursor_enabled = false;
		renderer.resizeCursor_enabled = false;
		
		ofLog() << "curseur en croix";

		break;

	case 50://curseur en cercle
		renderer.crossCursor_enabled = false;
		renderer.circleCursor_enabled = true;
		renderer.arrowCursor_enabled = false;
		renderer.handCursor_enabled = false;
		renderer.resizeCursor_enabled = false;
		
		ofLog() << "curseur en cercle";
		
		break;

	case 51://curseur en main
		renderer.crossCursor_enabled = false;
		renderer.circleCursor_enabled = false;
		renderer.arrowCursor_enabled = false;
		renderer.handCursor_enabled = true;
		renderer.resizeCursor_enabled = false;

		ofLog() << "curseur en main";
		break;

	case 52://curseur en fleche
		renderer.arrowCursor_enabled = true;
		renderer.crossCursor_enabled = false;
		renderer.circleCursor_enabled = false;
		renderer.handCursor_enabled = false;
		renderer.resizeCursor_enabled = false;
		ofLog() << "curseur en fleche";
		break;
	
	case 53://resize horizontal
		renderer.crossCursor_enabled = false;
		renderer.circleCursor_enabled = false;
		renderer.arrowCursor_enabled = false;
		renderer.handCursor_enabled = false;
		renderer.resizeCursor_enabled = true;
		ofLog() << "curseur de resize";
		
		break;
		
	case 57346: // touche F3 pour rechercher une image
		
		ofLog() << " recherche image";
		actionResearchImages();
			
		break;

	case 57345: // touche F2 pour sauvegarde dynamique de la scene

		ofLog() << "Touche S activé et relachee";
		nbTakes = intSliderTakes;
		timeByTakes = (floatSliderTime / nbTakes);
		i = 0;
		while (i != nbTakes)
		{
			ofResetElapsedTimeCounter();
			timePassed = ofGetElapsedTimef();
			while (timePassed < timeByTakes)
			{
				//ofLog() << "timeBytakes" << timeByTakes;
				timePassed = ofGetElapsedTimef();
				//ofLog() << "timePassed" << timePassed;
			}
			renderer.image_export("serie", "png");
			ofLog() << "image" << i << "exporte";
			ofResetElapsedTimeCounter();
			i++;
		}
		break;

	case 9: // touche TAB pour changer mode 2d 3d
		if (mode3D)
			mode3D = false;
		else
			mode3D = true;
		break;
	case OF_KEY_LEFT: // touche ←
		is_key_press_left = false;
		break;

	case OF_KEY_UP: // touche ↑
		is_key_press_up = false;
		break;

	case OF_KEY_RIGHT: // touche →
		is_key_press_right = false;
		break;

	case OF_KEY_DOWN: // touche ↓
		is_key_press_down = false;
		break;

	default:
		ofLog() << key;
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
		guiProperties3D.setPosition(ofGetWindowWidth() - guiProperties3D.getWidth(), 0);
		guiCamera3D.setPosition(0, ofGetWindowHeight() - guiCamera3D.getHeight());
		guiObjects3D.setPosition(ofGetWindowWidth() - guiObjects3D.getWidth(), ofGetWindowHeight() - guiObjects3D.getHeight());
	}
	//2D
	if (!mode3D) {
		guiHierarchy.setPosition(0, 0);
		guiProperties2D.setPosition(ofGetWindowWidth() - guiProperties2D.getWidth(), 0);
		//guiCamera3D.setPosition(0, ofGetWindowHeight() - guiCamera3D.getHeight());
		guiObjects2D.setPosition(ofGetWindowWidth() - guiObjects2D.getWidth(), ofGetWindowHeight() - guiObjects2D.getHeight());
	}
	
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}
//--------------------------------------------------------------
void ofApp::getHsb()
{
	ofColor myRGBColor;
	myRGBColor.set(renderer.colorPicker);
	ofLog() << "Couleur active " << myRGBColor;

	ofColor h = myRGBColor.getHue();
	ofColor s = myRGBColor.getSaturation();
	ofColor b = myRGBColor.getBrightness();

	ofLog() << "HSB :" << "Hue :" << h << "Saturation :" << s << "Brightness :"<< b;

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}


//3D

void ofApp::addNewObject() {
	renderer.addNew3dObject(newObjectName);
	newToggleObject();
}

void ofApp::addNewSphere() {
	renderer.addNewSphere(newObjectName);
	newToggleObject();
}

void ofApp::addNewBox() {
	renderer.addNewBox(newObjectName);
	newToggleObject();
}

void ofApp::addNewCone() {
	renderer.addNewCone(newObjectName);
	newToggleObject();
}

void ofApp::addNewCylinder() {
	renderer.addNewCylinder(newObjectName);
	newToggleObject();
}

void ofApp::addNewTeapot() {
	renderer.import3dModel("teapot.obj");
	newToggleObject();
}

void ofApp::addNewGlasses() {
	renderer.import3dModel("glasses.3DS");
	newToggleObject();
}

void ofApp::addNewTV() {
	renderer.import3dModel("tv.fbx");
	newToggleObject();
}

void ofApp::addAnimatedWolf() {
	renderer.import3dModel("Wolf_dae.dae");
	newToggleObject();
}

void ofApp::deleteObject() {
	for (int o : selectedObjects) {
		renderer.deleteObject(o);
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
}

void ofApp::updateSelection() {
	selectedObjects.clear();
	for (int i = 0; i < objectsToggle.size(); i++) {
		if (objectsToggle[i].get()) {
			selectedObjects.push_back(i);
		}
	}
}

void ofApp::cameraLookAt(int& index) {
	renderer.cameraLookAt(index - 1);
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
//__________________________________________-


//2D

void ofApp::addNewRectangle() {
	renderer.addNewRectangle(newObjectName);
	newToggleObject();
}

void ofApp::addNewCircle(){
	renderer.addNewCircle(newObjectName);
	newToggleObject();
}

void ofApp::addNewTriangle() {
	renderer.addNewTriangle(newObjectName);
	newToggleObject();
}

void ofApp::addNewEllipse() {
	renderer.addNewEllipse(newObjectName);
	newToggleObject();
}

void ofApp::addNewLine() {
	renderer.addNewLine(newObjectName);
	newToggleObject();
}

void ofApp::addNewStar() {
	renderer.addNewStar(newObjectName);
	newToggleObject();
}

void ofApp::addNewHouse() {
	renderer.addNewHouse(newObjectName);
	newToggleObject();
}
