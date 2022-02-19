#include "application.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetWindowTitle("Moteur de rendu 2d/3d");
	ofLog() << "<app::setup>";

	renderer.setup();
	//gestionImages.setup();

	is_verbose = false;
	
// Panneau de propriete des objets     
//Plusieurs outils ou sliders répertoriés la dedans. Pas tous utiles pour le moment, mais donner des idées.
	guiProperties.setup();
	guiProperties.setPosition(ofGetWindowWidth() - guiProperties.getWidth(), 0);
	guiProperties.add(labelProperties.setup("Panneau", "Propriete"));
	guiProperties.add(intSlider.setup("intSlider", 64, 3, 64));
	guiProperties.add(floatSlider.setup("floatSlider", 30.0, 0.0, 300.0));
	guiProperties.add(toggle.setup("toggle", false));
	guiProperties.add(button.setup("button"));
	
	guiProperties.add(intField.setup("int field", 100, 0, 100));
	guiProperties.add(floatField.setup("float field", 100.0, 0.0, 100.0));
	guiProperties.add(textField.setup("text field", "text"));

	guiProperties.add(vec2Slider.setup("vec2 slider", ofVec2f(0, 0), ofVec2f(0, 0), ofVec2f(ofGetWidth(),ofGetHeight())));
	guiProperties.add(vec3Slider.setup("vec3 slider", ofVec3f(100, 150,90), ofVec3f(0, 0,0), ofVec3f(255,255,255)));
	guiProperties.add(vec4Slider.setup("Couleur RGBA", ofVec4f(100, 100, 100,100), ofVec4f(0, 0, 0,0), ofVec4f(255,255, 255, 255)));

	//panneau de hierarchie des objets ** À développer **
	guiHierarchy.setup();
	guiHierarchy.setPosition(0, 0);
	guiHierarchy.add(labelHierarchy.setup("Panneau", "Hierarchie"));
	guiHierarchy.add(newObjectButton.setup("New object"));

	//panneau de contrôle de formes. 
// Avec L'idée de créer une classe forme, nous pouvons avoir des panneaux qui apparaissent en fonction des formes que nous générerons.
	//Certaines choses se recoupent entre les deux sections (panneau de propriété) mais nous ferons des choix.
	

	circleGroup.setup();
	parameterGroup.add(circleGroup.Parameters);

	guiForms.setup(parameterGroup);
	guiForms.add(RGBtoHSV.setup("RGB to HSV"));
	guiForms.setPosition(0, ofGetWindowHeight() - guiForms.getHeight());
}

//--------------------------------------------------------------
void ofApp::update(){
	renderer.update();
	//gestionImages.update();
}

//--------------------------------------------------------------
void ofApp::draw(){

	
	// Assignation des sliders pour set la couleur, la position ou la resolution d'un cercle.
	ofSetCircleResolution(intSlider);
	ofSetColor(vec4Slider->r,vec4Slider->g, vec4Slider->b, vec4Slider->a);
	ofDrawCircle(vec2Slider->x, vec2Slider->y, 128);
	

	//Apparition des fenêtres de l'interface
	guiProperties.draw();
	guiHierarchy.draw();
	circleGroup.draw();
	guiForms.draw();

	renderer.draw();
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

	case 49: // creation d'un cercle

		ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, 120);

		break;



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
