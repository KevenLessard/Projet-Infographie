#include "renderer.h"

void Renderer::setup()
{
	{
        ofSetFrameRate(60);
        
		mouse_press_x = mouse_press_y = mouse_current_x = mouse_current_y = 0;

		is_mouse_button_pressed = false;

	}
}

void Renderer::update()
{

}

// fonction de dessin du curseur
void Renderer::draw_cursor(float x, float y) const
{
    // paramètres de dessin
    float length = 10.0f;
    float offset = 5.0f;

    // dessiner le curseur en rouge si un des boutons du périphérique de pointage est appuyé
    if (is_mouse_button_pressed)
        ofSetColor(0, 255, 0);
    else
        ofSetColor(0);

    // dessiner la forme vectorielle
    // Proposition d'une autre forme:
    //Curseur Circulaire. Cependant, le No Fill enleve le remplissage partout. Comment faire pour qu'il n'agisse que sur le curseur est-ce avec un begin() et un end()?
/*
    ofDrawCircle(x, y, 20);
    ofDrawCircle(x, y, 1);
    ofNoFill();
    */
}

void Renderer::draw()
{
    ofEnableDepthTest();

    for (of3dPrimitive* object : objects) {
        ofPushMatrix();
        ofFill();
        ofSetColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255));
        object->drawAxes(10);
        ofPopMatrix();
    }
    ofDisableDepthTest();
}

void Renderer::addNew3dObject() {
    of3dPrimitive* object = new of3dPrimitive();
    if (objects.size() == 0)
        object->setScale(3, 3, 3);
    if (objects.size() >= 1) {
        object->setParent(*objects[objects.size() - 1]);
        object->setScale(1, 1, 1);
    }
    object->setPosition(60, 60, 0);
    objects.push_back(object);
}

void Renderer::moveObject(int index, ofVec3f newPosition) {
    if (index >= objects.size()) {
        return;
    }
        
    objects[index]->setPosition(newPosition);
    ofColor color(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255));
}

void Renderer::rotateObject(int index, ofQuaternion newRotation) {
    if (index >= objects.size()) {
        return;
    }
    
    objects[index]->setOrientation(newRotation);
}