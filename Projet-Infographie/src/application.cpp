#include "application.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetWindowTitle("Moteur de rendu 2d/3d");
	ofLog() << "<app::setup>";

	renderer.setup();
	
	
	is_verbose = false;

	//3D
		//Panneau de propriete des objets     
//Plusieurs outils ou sliders répertoriés la dedans. Pas tous utiles pour le moment, mais donner des idées.
	guiProperties3D.setup();
	guiProperties3D.setPosition(ofGetWindowWidth() - guiProperties3D.getWidth(), 0);
	guiProperties3D.add(labelProperties.setup("Panneau", "Propriete"));

		indexField.addListener(this, &ofApp::switchCurrentObject);
		guiProperties3D.add(indexField.setup("index objet", 0, 0, 100));
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
		guiObjects3D.setup();
		guiObjects3D.setPosition(0, 0);
		guiObjects3D.add(labelHierarchy.setup("Panneau", "Hierarchie"));
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
		//____________________________________________________________________



		//2D

		guiObjects2D.setup();
		guiObjects2D.setPosition(0, 0);
		guiObjects2D.add(labelHierarchy.setup("Panneau", "Hierarchie"));
		guiObjects2D.add(newSquareButton.setup("New Square"));
		newSquareButton.addListener(this, &ofApp::addNewSquare);


	is_key_press_up = false;
	is_key_press_down = false;
	is_key_press_left = false;
	is_key_press_right = false;
	is_key_press_e = false;
	is_key_press_q = false;
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
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	renderer.draw();

	if (mode3D==true) {
		guiProperties3D.draw();
		guiObjects3D.draw();
		guiCamera3D.draw();
	}

	if (mode3D==false) {
		guiProperties2D.draw();
		guiObjects2D.draw();
	}


	//dessin de l'image chargée dans le buffer loadedImages.
	ofDrawBitmapString("Press r to open an image, s to save, t for 3d interface and u for 2d interface.", ofGetWidth()/2, ofGetHeight() -10);
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

	case 116: // touche t pour changer mode 2d 3d

			mode3D = true;

		break;

	case 117: // touche t pour changer mode 2d 3d

			mode3D = false;

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
	if (mode3D) {
		guiProperties3D.setPosition(ofGetWindowWidth() - guiProperties3D.getWidth(), 0);
		guiCamera3D.setPosition(0, ofGetWindowHeight() - guiCamera3D.getHeight());
	}
	//2D
	if (!mode3D) {
		guiProperties2D.setPosition(ofGetWindowWidth() - guiProperties2D.getWidth(), 0);
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
	ofLog() << "Couleur active" << myRGBColor;

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
	renderer.addNew3dObject();
}

void ofApp::addNewSphere() {
	renderer.addNewSphere();
}

void ofApp::addNewBox() {
	renderer.addNewBox();
}

void ofApp::addNewCone() {
	renderer.addNewCone();
}

void ofApp::addNewCylinder() {
	renderer.addNewCylinder();
}

void ofApp::deleteObject() {
	renderer.deleteObject(indexField - 1);
}

void ofApp::switchCurrentObject(int& index) {
	
}

void ofApp::selection(int x, int y) {

}

void ofApp::addNewTeapot() {
	renderer.import3dModel("teapot.obj");
}

void ofApp::addNewGlasses() {
	renderer.import3dModel("glasses.3DS");
}

void ofApp::addNewTV() {
	renderer.import3dModel("tv.fbx");
}

void ofApp::addAnimatedWolf() {
	renderer.import3dModel("Wolf_dae.dae");
}

void ofApp::cameraLookAt(int& index) {
	renderer.cameraLookAt(index - 1);
}

void ofApp::switchProjectionMode() {
	renderer.switchProjectionMode();
}
//__________________________________________-


//2D

void ofApp::addNewSquare() {
	renderer.addNewSquare();
}