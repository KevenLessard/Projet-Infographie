
#include "renderer.h"

void Renderer::setup()
{
	
        ofSetFrameRate(60);
        
		mouse_press_x = mouse_press_y = mouse_current_x = mouse_current_y = 0;

		is_mouse_button_pressed = false;
        mainCamera.setPosition(0, 0, 100);

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
    mainCamera.begin();
    //ofTranslate(center_x, center_y, 0);
    ofEnableDepthTest();


    for (of3dPrimitive* object : objects) {
        ofPushMatrix();
        ofFill();
        ofSetColor(colorPicker);
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
    mainCamera.end();
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
    spherePrimitive* sphere = new spherePrimitive();
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


void Renderer::deleteObject(int index) {
    if (index >= objects.size() || index == -1) {
        return;
    }
    objects.erase(objects.begin() + index);
}

void Renderer::proportionateObject(int index, ofVec3f newProportion) {
    if (index >= objects.size() || index == -1) {
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
    if (index >= objects.size() || index == -1) {
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
    if (index >= objects.size() || index == -1) {
        return;
    }
    //ofQuaternion actualRotation(newRotation);
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

void Renderer::reset() {

}

void Renderer::cameraLookAt(int index) {
    if (index >= objects.size() || index == -1) {
        return;
    }
}

void Renderer::switchProjectionMode() {
    if (is_camera_ortho) {
        mainCamera.disableOrtho();
        is_camera_ortho = false;
    }
    else {
        mainCamera.enableOrtho();
        is_camera_ortho = true;
    }
}