
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
    center_x = ofGetWidth() / 2.0f;
    center_y = ofGetHeight() / 2.0f;
}

// fonction de dessin du curseur
void Renderer::draw_cursor(float x, float y) const
{
    // paramètres de dessin
    float length = 10.0f;
    float offset = 5.0f;
    

    // dessiner le curseur en vert si un des boutons du périphérique de pointage est appuyé
    if (is_mouse_button_pressed)
        ofSetColor(0, 255, 0);
    else
        ofSetColor(255);

    // dessiner la forme vectorielle
    // Proposition d'une autre forme:
    //Curseur Circulaire. Cependant, le No Fill enleve le remplissage partout. Comment faire pour qu'il n'agisse que sur le curseur est-ce avec un begin() et un end()?

    ofDrawCircle(x, y, 20);
    ofDrawCircle(x, y, 1);
    ofNoFill();
//ofNoFill();
    
/*
    ofDrawLine(x + offset, y, x + offset + length, y);
    ofDrawLine(x - offset, y, x - offset - length, y);
    ofDrawLine(x, y + offset, x, y + offset + length);
    ofDrawLine(x, y - offset, x, y - offset - length);
    */
}

void Renderer::draw()
{
    ofPushMatrix();
    ofTranslate(center_x, center_y, 0);
    ofEnableDepthTest();


    for (of3dPrimitive* object : objects) {
        ofPushMatrix();
        ofFill();
        ofSetColor(61, 61, 205);
        object->drawAxes(100);
        object->draw(OF_MESH_WIREFRAME);
        ofPopMatrix();
    }

    for (ofxAssimpModelLoader* object : models3D) {
        ofPushMatrix();
        ofFill();
        ofSetColor(61, 61, 205);
        object->draw(OF_MESH_WIREFRAME);
        ofPopMatrix();
    }
    ofDisableDepthTest();
    ofPopMatrix();
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

//Hugo


void Renderer::import3dModel(std::string file_name) {
    ofxAssimpModelLoader* model3D = new ofxAssimpModelLoader();
    model3D->loadModel(file_name);

    if (models3D.size() == 0)
        model3D->setScale(1, 1, 1);

    if (models3D.size() >= 1) {
        model3D->setScale(0.2, 0.2, 0.2);
    }
    models3D.push_back(model3D);
}


void Renderer::proportionateObject(int index, ofVec3f newProportion) {
    if (index >= objects.size()) {
        return;
    }
    objects[index]->setScale(newProportion);
    

    ////Import model3D
    //if (index >= models3D.size()) {
    //    return;
    //}
    //models3D[index]->setScale(newProportion.x, newProportion.y, newProportion.z);

}

void Renderer::moveObject(int index, ofVec3f newPosition) {
    if (index >= objects.size()) {
        return;
    }
    objects[index]->setPosition(newPosition);

    ////Import3dModel
    //if (index >= models3D.size()) {
    //    return;
    //}
    //models3D[index]->setPosition(newPosition.x, newPosition.y, newPosition.z);
}

void Renderer::rotateObject(int index, ofVec3f newRotation) {
    if (index >= objects.size()) {
        return;
    }
    ofQuaternion actualRotation(newRotation);

    objects[index]->setOrientation(newRotation);

    ////Import3dModel
    //if (index >= models3D.size()) {
    //    return;
    //}
    //Pas capable de faire de rotation
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