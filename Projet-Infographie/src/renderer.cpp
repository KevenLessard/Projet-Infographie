
#include "renderer.h"

void Renderer::setup()
{
	
        ofSetFrameRate(60);
        
		mouse_press_x = mouse_press_y = mouse_current_x = mouse_current_y = 0;

		is_mouse_button_pressed = false;

        ofDisableArbTex();
	
}

void Renderer::update()
{
    center_x = ofGetWidth() / 2.0f;
    center_y = ofGetHeight() / 2.0f;
}

// fonction de dessin du curseur
void Renderer::draw_CrossCursor(int x, int y)
{
    // paramètres de dessin
    float length = 10.0f;
    float offset = 5.0f;

    // dessiner le curseur en vert si un des boutons du périphérique de pointage est appuyé
    if (is_mouse_button_pressed)
        ofSetColor(0, 255, 0);
    else
        ofSetColor(255);

    ofDrawLine(x + offset, y, x + offset + length, y);
    ofDrawLine(x - offset, y, x - offset - length, y);
    ofDrawLine(x, y + offset, x, y + offset + length);
    ofDrawLine(x, y - offset, x, y - offset - length);
}

void Renderer::draw_CircleCursor(float x, float y) const
{  
    ofNoFill();
    ofDrawCircle(x, y, 20);
    ofDrawCircle(x, y, 1);
    ofColor(0);
    
}

void Renderer::draw_ArrowCursor(float x, float y) const
{
   int cursor_width = 32;
   int cursor_height = 32;


   ofImage arrowCursor;
   arrowCursor.load("arrowCursor.png");

   arrowCursor.draw(x, y, cursor_width, cursor_height);

}

void Renderer::draw_ResizeCursor(float x, float y) const
{
    int cursor_width = 32;
    int cursor_height = 32;

    ofImage resizeCursor;
    resizeCursor.load("resizeCursor.png");

    resizeCursor.draw(x, y, cursor_width, cursor_height);
}

void Renderer::draw_HandCursor(float x, float y) const
{
    int cursor_width = 32;
    int cursor_height = 32;


    ofImage handCursor;
    handCursor.load("handCursor.png");

    handCursor.draw(x, y, cursor_width, cursor_height);

}

void Renderer::draw()
{
    //Ajouter une section pour le draw du 2D
    ofPushMatrix();
    ofTranslate(center_x, center_y, 0);
    ofEnableDepthTest();
    for (of3dPrimitive* object : objects) {
        ofPushMatrix();
        ofFill();
        ofSetColor(colorPicker);
        object->drawAxes(100);
        object->draw(OF_MESH_WIREFRAME);
        ofPopMatrix();
    }
    ofDisableDepthTest();
    ofPopMatrix();

    //Dessin des curseurs en fonction de l'état:
    if (crossCursor_enabled)
        draw_CrossCursor(mouse_current_x, mouse_current_y );
    if (circleCursor_enabled)
        draw_CircleCursor(mouse_current_x, mouse_current_y);
    if (arrowCursor_enabled)
        draw_ArrowCursor(mouse_current_x, mouse_current_y);
    if (handCursor_enabled)
        draw_HandCursor(mouse_current_x, mouse_current_y);
    if (resizeCursor_enabled)
        draw_ResizeCursor(mouse_current_x, mouse_current_y);


        

}



void Renderer::addNew3dObject() {
    of3dPrimitive* object = new of3dPrimitive();
    if (objects.size() == 0)
        object->setScale(3, 3, 3);
    if (objects.size() >= 1) {
        object->setParent(*objects[objects.size() - 1]);
        object->setScale(1, 1, 1);
    }
    object->setPosition(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()), 0);
    objects.push_back(object);
}



void Renderer::addNewSphere() {
    ofSpherePrimitive* sphere = new ofSpherePrimitive();
    sphere->setRadius(10);
    objects.push_back(sphere);
}

void Renderer::proportionateObject(int index, ofVec3f newProportion) {
    if (index >= objects.size()) {
        return;
    }
    objects[index]->setScale(newProportion);
}

void Renderer::moveObject(int index, ofVec3f newPosition) {
    if (index >= objects.size()) {
        return;
    }
    objects[index]->setPosition(newPosition);
}

void Renderer::rotateObject(int index, ofVec3f newRotation) {
    if (index >= objects.size()) {
        return;
    }
    ofQuaternion actualRotation(newRotation);

    objects[index]->setOrientation(newRotation);
}

void Renderer::image_export(const string name, const string extension) const
{
    ofImage image;

    string time_stamp = ofGetTimestampString("-%y%m%d-%H%M%S-%i");
    string file_name = name + time_stamp + "." + extension;

    image.grabScreen(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
    image.save(file_name);

    ofLog() << "export image:" << file_name;
}