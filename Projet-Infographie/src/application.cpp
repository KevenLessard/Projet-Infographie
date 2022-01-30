#include "application.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetWindowTitle("Moteur de rendu 2d/3d");
	ofLog() << "<app::setup>";

	renderer.setup();
	
// Panneau de propriete des objets     
//Plusieurs outils ou sliders répertoriés la dedans. Pas tous utiles pour le moment, mais donner des idées.
	guiPropriete.setup();
	guiPropriete.setPosition(ofGetWindowWidth() - guiPropriete.getWidth(), 0);
	guiPropriete.add(labelPropriete.setup("Panneau", "Propriete"));
	guiPropriete.add(intSlider.setup("intSlider", 64, 3, 64));
	guiPropriete.add(floatSlider.setup("floatSlider", 30.0, 0.0, 300.0));
	guiPropriete.add(toggle.setup("toggle", false));
	guiPropriete.add(button.setup("button"));
	
	guiPropriete.add(intField.setup("int field", 100, 0, 100));
	guiPropriete.add(floatField.setup("float field", 100.0, 0.0, 100.0));
	guiPropriete.add(textField.setup("text field", "text"));

	guiPropriete.add(vec2Slider.setup("vec2 slider", ofVec2f(0, 0), ofVec2f(0, 0), ofVec2f(ofGetWidth(),ofGetHeight())));
	guiPropriete.add(vec3Slider.setup("vec3 slider", ofVec3f(100, 150,90), ofVec3f(0, 0,0), ofVec3f(255,255,255)));
	guiPropriete.add(vec4Slider.setup("Couleur RGBA", ofVec4f(100, 100, 100,100), ofVec4f(0, 0, 0,0), ofVec4f(255,255, 255, 255)));

	//panneau de hierarchie des objets ** À développer **
	guiHierarchie.setup();
	guiHierarchie.setPosition(0, 0);
	guiHierarchie.add(labelHierarchie.setup("Panneau", "Hierarchie"));

	//panneau de contrôle de formes. 
// Avec L'idée de créer une classe forme, nous pouvons avoir des panneaux qui apparaissent en fonction des formes que nous générerons.
	//Certaines choses se recoupent entre les deux sections (panneau de propriété) mais nous ferons des choix.
	

	circleGroup.setup();
	parameterGroup.add(circleGroup.circleParameters);

	guiFormes.setup(parameterGroup);
	guiFormes.setPosition(0, ofGetWindowHeight() - guiFormes.getHeight());

	
}

//--------------------------------------------------------------
void ofApp::update(){

	renderer.update();

}

//--------------------------------------------------------------
void ofApp::draw(){

	//Test de fonctionnement d'un bouton dans le gui de propriété
	if (button)
	{
		ofSetColor(ofRandom(vec3Slider->x), ofRandom(vec3Slider->y), ofRandom(vec3Slider->z));
	}

	ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, 120);

	// Assignation des sliders pour set la couleur, la position ou la resolution d'un cercle.
	ofSetCircleResolution(intSlider);
	ofSetColor(vec4Slider->r,vec4Slider->g, vec4Slider->b, vec4Slider->a);
	ofDrawCircle(vec2Slider->x, vec2Slider->y, 128);

	//Apparition des fenêtres de l'interface
	guiPropriete.draw();
	guiHierarchie.draw();
	circleGroup.draw();
	guiFormes.draw();

	renderer.draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
	guiPropriete.setPosition(ofGetWindowWidth() - guiPropriete.getWidth(), 0);
	guiFormes.setPosition(0, ofGetWindowHeight() - guiFormes.getHeight());
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
