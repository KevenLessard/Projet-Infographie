#include "application.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetWindowTitle("Moteur de rendu 2d/3d");
	ofLog() << "<app::setup>";

	renderer.setup();
	//gestionImages.setup();

	is_verbose = false;
	
	//Panneau de propriete des objets     
	//Plusieurs outils ou sliders répertoriés la dedans. Pas tous utiles pour le moment, mais donner des idées.
	guiProperties.setup();
	guiProperties.setPosition(ofGetWindowWidth() - guiProperties.getWidth(), 0);
	guiProperties.add(labelProperties.setup("Panneau", "Propriete"));
	
	indexField.addListener(this, &ofApp::switchCurrentObject);
	guiProperties.add(indexField.setup("index objet", 0, 0, 100));
	proportionGroup.setName("Proportion");
	proportionGroup.add(proportionX.set("x", 1, 0, 100));
	proportionGroup.add(proportionY.set("y", 1, 0, 100));
	proportionGroup.add(proportionZ.set("z", 1, 0, 100));
	guiProperties.add(proportionGroup);
	guiProperties.add(positionSlider.setup("Position", ofVec3f(0, 0,0), ofVec3f(-1920, -1080,0), ofVec3f(1920,1080,1000)));
	guiProperties.add(rotationSlider.setup("Rotation", ofVec3f(0, 0, 0), ofVec3f(0, 0, 0), ofVec3f(360,360, 360)));
	guiProperties.add(colorPicker.set("Color", ofColor(31), ofColor(0, 0), ofColor(255, 255)));

	//Informations de sauvegarde dynamique
	guiProperties.add(intSliderTakes.setup("nombre de prises", 1, 1, 24));
	guiProperties.add(floatSliderTime.setup("temps sauvegarde (secondes)", 5.0, 1.0, 30.0));

	//panneau de hierarchie des objets ** À développer **
	guiHierarchy.setup();
	guiHierarchy.setPosition(0, 0);
	guiHierarchy.add(labelHierarchy.setup("Panneau", "Hierarchie"));
	guiHierarchy.add(newObjectButton.setup("New 3DObject"));
	guiHierarchy.add(newSphereButton.setup("New sphere"));
	guiHierarchy.add(newTeapotButton.setup("Teapot.obj"));
	guiHierarchy.add(newGlassesButton.setup("glasses.3DS"));
	guiHierarchy.add(newTVButton.setup("tv.fbx"));
	guiHierarchy.add(deleteButton.setup("Delete object"));
	newObjectButton.addListener(this, &ofApp::addNewObject);
	newSphereButton.addListener(this, &ofApp::addNewSphere);
	newTeapotButton.addListener(this, &ofApp::addNewTeapot);
	newGlassesButton.addListener(this, &ofApp::addNewGlasses);
	newTVButton.addListener(this, &ofApp::addNewTV);
	deleteButton.addListener(this, &ofApp::deleteObject);


	//panneau de contrôle de formes. 
	//Avec L'idée de créer une classe forme, nous pouvons avoir des panneaux qui apparaissent en fonction des formes que nous générerons.
	//Certaines choses se recoupent entre les deux sections (panneau de propriété) mais nous ferons des choix.

	guiCamera.setup();
	guiCamera.setPosition(0, ofGetWindowHeight() - guiCamera.getHeight());
	guiCamera.add(cameraObjectIndex.setup("Camera pointe vers: ", 0, 0, 100));
	cameraObjectIndex.addListener(this, &ofApp::cameraLookAt);
	guiCamera.add(projectionModeButton.setup("Switch projection mode"));
	projectionModeButton.addListener(this, &ofApp::switchProjectionMode);
}

//--------------------------------------------------------------
void ofApp::update(){
	renderer.is_camera_move_forward = is_key_press_up;
	renderer.is_camera_move_backward = is_key_press_down;

	renderer.is_camera_move_left = is_key_press_left;
	renderer.is_camera_move_right = is_key_press_right;

	renderer.is_camera_move_up = is_key_press_q;
	renderer.is_camera_move_down = is_key_press_e;

	ofVec3f newProportion(proportionX, proportionY, proportionZ);
	renderer.proportionateObject(indexField - 1, newProportion);
	ofVec3f newPosition(positionSlider);
	renderer.moveObject(indexField - 1, newPosition);
	ofVec3f newRotation(rotationSlider);
	renderer.rotateObject(indexField - 1, newRotation);

	renderer.update();
	//gestionImages.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	renderer.draw();

	//Apparition des fenêtres de l'interface
	guiProperties.draw();
	guiHierarchy.draw();
	guiCamera.draw();
	//gestionImages.draw();

	//dessin de l'image chargée dans le buffer loadedImages.
	ofDrawBitmapString("Camera movement: ↑ ↓ ← → q e", ofGetWidth() / 2, 15);
	ofDrawBitmapString("Press r to open an image, v to switch verbose mode", ofGetWidth()/2, ofGetHeight() -10);
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
	case 101: // touche e
		is_key_press_e = true;
		break;
	case 113: // touche q
		is_key_press_q = true;
		break;
	case OF_KEY_LEFT: // touche ←
		renderer.cameraTruck(-1);
		break;

	case OF_KEY_UP: // touche ↑
		renderer.cameraDolly(1);
		break;

	case OF_KEY_RIGHT: // touche →
		renderer.cameraTruck(1);
		break;

	case OF_KEY_DOWN: // touche ↓
		renderer.cameraDolly(-1);
		break;
	default:
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

	switch (key)
	{

	case 101: // touche e
		is_key_press_e = false;
		break;
	case 113: // touche q
		is_key_press_q = false;
		break;
	case 114: // touche r pour rechercher une image
		
		ofLog() << " recherche image";
		actionResearchImages();
			
		break;

	case 115: // touche s pour sauvegarde dynamique de la scene

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
		
	case 118: // touche v pour verbose
		is_verbose = !is_verbose;
		ofLog() << "<verbose mode: " << is_verbose << ">";
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
		ofSetBackgroundAuto(!ofGetBackgroundAuto());
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

	selection(x, y);

	ofLog() << "ofApp::mousePressed   at: ( x :" << x << ", y:" << y << ")";

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

	renderer.is_mouse_button_pressed = false;

	renderer.mouse_current_x = x;
	renderer.mouse_current_y = y;

	ofLog() << "ofApp::mouseReleased   at: ( x :" << x << ", y:" << y << ")";
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
	guiProperties.setPosition(ofGetWindowWidth() - guiProperties.getWidth(), 0);
	guiCamera.setPosition(0, ofGetWindowHeight() - guiCamera.getHeight());
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::addNewObject() {
	renderer.addNew3dObject();
}

void ofApp::addNewSphere() {
	renderer.addNewSphere();
}
void ofApp::deleteObject() {
	renderer.deleteObject(indexField - 1);
}
void ofApp::switchCurrentObject(int& index) {
	
}
void ofApp::selection(int x, int y) {

}
//Hugo
void ofApp::addNewTeapot() {
	renderer.import3dModel("teapot.obj");
}

void ofApp::addNewGlasses() {
	renderer.import3dModel("glasses.3DS");
}

void ofApp::addNewTV() {
	renderer.import3dModel("tv.fbx");
}

void ofApp::cameraLookAt(int& index) {
	renderer.cameraLookAt(index - 1);
}

void ofApp::switchProjectionMode() {
	renderer.switchProjectionMode();
}