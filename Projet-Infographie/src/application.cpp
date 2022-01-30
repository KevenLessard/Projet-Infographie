#include "application.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetWindowTitle("Moteur de rendu 2d/3d");
	ofLog() << "<app::setup>";

	renderer.setup();
	
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
	parameterGroup.add(circleGroup.circleParameters);

	guiForms.setup(parameterGroup);
	guiForms.setPosition(0, ofGetWindowHeight() - guiForms.getHeight());
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
	guiProperties.draw();
	guiHierarchy.draw();
	circleGroup.draw();
	guiForms.draw();

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
	guiProperties.setPosition(ofGetWindowWidth() - guiProperties.getWidth(), 0);
	guiForms.setPosition(0, ofGetWindowHeight() - guiForms.getHeight());
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
