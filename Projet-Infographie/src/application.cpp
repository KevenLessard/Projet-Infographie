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
	
	guiProperties.add(intField.setup("index objet", 0, 0, 100));
	proportionGroup.setName("Proportion");
	proportionGroup.add(proportionX.set("X", 1, 0, 1000));
	proportionGroup.add(proportionX.set("Y", 1, 0, 1000));
	proportionGroup.add(proportionX.set("Z", 1, 0, 1000));
	guiProperties.add(proportionGroup);
	guiProperties.add(positionSlider.setup("Position", ofVec3f(0, 0,0), ofVec3f(-1920, -1080,0), ofVec3f(1920,1080,1000)));
	guiProperties.add(rotationSlider.setup("Rotation", ofVec3f(0, 0, 0), ofVec3f(0, 0, 0), ofVec3f(360,360, 360)));
	guiProperties.add(colorPicker.set("Color", ofColor(31), ofColor(0, 0), ofColor(255, 255)));
	//panneau de hierarchie des objets ** À développer **
	guiHierarchy.setup();
	guiHierarchy.setPosition(0, 0);
	guiHierarchy.add(labelHierarchy.setup("Panneau", "Hierarchie"));
	guiHierarchy.add(newObjectButton.setup("New 3DObject"));
	guiHierarchy.add(newCubeButton.setup("New sphere"));
	newObjectButton.addListener(this, &ofApp::addNewObject);
	newCubeButton.addListener(this, &ofApp::addNewSphere);

	//panneau de contrôle de formes. 
	//Avec L'idée de créer une classe forme, nous pouvons avoir des panneaux qui apparaissent en fonction des formes que nous générerons.
	//Certaines choses se recoupent entre les deux sections (panneau de propriété) mais nous ferons des choix.
	

	circleGroup.setup();
	parameterGroup.add(circleGroup.circleParameters);

	guiForms.setup(parameterGroup);
	guiForms.setPosition(0, ofGetWindowHeight() - guiForms.getHeight());
}

//--------------------------------------------------------------
void ofApp::update(){
	int index = intField;
	ofVec3f newProportion(proportionX, proportionY, proportionZ);
	renderer.proportionateObject(index, newProportion);
	ofVec3f newPosition(positionSlider);
	renderer.moveObject(index, newPosition);
	ofVec3f newRotation(rotationSlider);
	renderer.rotateObject(index, newRotation);
	renderer.update();
	//gestionImages.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	renderer.draw();

	//Apparition des fenêtres de l'interface
	guiProperties.draw();
	guiHierarchy.draw();
	guiForms.draw();
	//gestionImages.draw();

	//dessin de l'image chargée dans le buffer loadedImages.
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

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

	switch (key)
	{

		
	case 114: // touche r pour rechercher une image
		
		ofLog() << " recherche image";
		actionResearchImages();
			
		break;
		
	case 118: // touche v pour verbose
		is_verbose = !is_verbose;
		ofLog() << "<verbose mode: " << is_verbose << ">";
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
	guiForms.setPosition(0, ofGetWindowHeight() - guiForms.getHeight());
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