
#include "renderer.h"

void Renderer::setup()
{
        ofSetFrameRate(60);
        
		mouse_press_x = mouse_press_y = mouse_current_x = mouse_current_y = 0;

		is_mouse_button_pressed = false;
        mainCamera.setPosition(0, 0, 500);
        mainCamera.setFov(60.0f);

        is_camera_move_left = false;
        is_camera_move_right = false;
        is_camera_move_up = false;
        is_camera_move_down = false;
        is_camera_move_forward = false;
        is_camera_move_backward = false;
        speed_delta = 250.0f;
}

void Renderer::update()
{
    center_x = ofGetWidth() / 2.0f;
    center_y = ofGetHeight() / 2.0f;

    time_current = ofGetElapsedTimef();
    time_elapsed = time_current - time_last;
    time_last = time_current;

    speed_translation = speed_delta * time_elapsed;
    speed_rotation = speed_translation / 8.0f;

    if (is_camera_move_left)
        mainCamera.truck(-speed_translation);
    if (is_camera_move_right)
        mainCamera.truck(speed_translation);

    if (is_camera_move_up)
        mainCamera.boom(speed_translation);
    if (is_camera_move_down)
        mainCamera.boom(-speed_translation);

    if (is_camera_move_forward)
        mainCamera.dolly(-speed_translation);
    if (is_camera_move_backward)
        mainCamera.dolly(speed_translation);
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
    ofEnableDepthTest();

    for (object3D* object : objects3d) {
        ofPushMatrix();
        object->draw();
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
    //2D
    if (squareDraw) {
        objects2D.setColor(0x00FFFF);
        objects2D.disableCenterRect();
        objects2D.rect(240, 50, 60, 60);
    }
}

void Renderer::addNew3dObject(string name) {
    if (nameAlreadyExists(name)) {
        return;
    }
    if (name == "") {
        name = "Object " + to_string(objects3d.size());
    }
    object3D* object = new object3D(name);
    object->setPosition(ofVec3f(0, 0, 0));
    object->setProportion(ofVec3f(1, 1, 1));
    objects3d.push_back(object);
}

void Renderer::addNewSphere(string name) {
    if (nameAlreadyExists(name)) {
        return;
    }
    if (name == "") {
        name = "Sphere " + to_string(objects3d.size());
    }
    object3D* sphere = new object3D(name, 2);
    sphere->setRadius(10);
    objects3d.push_back(sphere);
}

void Renderer::addNewBox(string name) {
    if (nameAlreadyExists(name)) {
        return;
    }
    if (name == "") {
        name = "Box " + to_string(objects3d.size());
    }
    object3D* box = new object3D(name, 3);
    objects3d.push_back(box);
}

void Renderer::addNewCylinder(string name) {
    if (nameAlreadyExists(name)) {
        return;
    }
    if (name == "") {
        name = "Cylinder " + to_string(objects3d.size());
    }
    object3D* cylinder = new object3D(name, 4);
    objects3d.push_back(cylinder);
}

void Renderer::addNewCone(string name) {
    if (nameAlreadyExists(name)) {
        return;
    }
    if (name == "") {
        name = "Cone " + to_string(objects3d.size());
    }
    object3D* cone = new object3D(name, 5);
    objects3d.push_back(cone);
}


void Renderer::import3dModel(std::string file_name) {
    object3D* model3D = new object3D(file_name);
    objects3d.push_back(model3D);
}

void Renderer::deleteObject(int index) {
    if (index >= objects3d.size() || index == -1) {
        return;
    }
    objects3d.erase(objects3d.begin() + index);
}

void Renderer::proportionateObject(int index, ofVec3f newProportion) {
    if (index >= objects3d.size() || index == -1) {
        return;
    }
    objects3d[index]->setProportion(newProportion);
}

void Renderer::moveObject(int index, ofVec3f newPosition) {
    if (index >= objects3d.size() || index == -1) {
        return;
    }
    objects3d[index]->setPosition(newPosition);
}

void Renderer::rotateObject(int index, ofVec3f newRotation) {
    if (index >= objects3d.size() || index == -1) {
        return;
    }
    //ofQuaternion actualRotation(newRotation);
    objects3d[index]->setRotation(newRotation);
}

void Renderer::setObjectColor(int index) {
    if (index >= objects3d.size() || index == -1) {
        return;
    }
    ofColor newColor(colorPicker);
    objects3d[index]->setColor(newColor);
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

string Renderer::getObjectName(int index) {
    if (index >= objects3d.size() || index == -1) {
        return "";
    }
    return objects3d[index]->getName();
}

void Renderer::reset() {

}

//Camera

void Renderer::cameraLookAt(int index) {
    if (index >= objects3d.size() || index == -1) {
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

void Renderer::cameraZoom() {

}

//2D

void Renderer::addNewSquare() {
    cout << "square";

    if (squareDraw==false) {
        cout << "true";
        squareDraw = true;
    }
    else {
        cout << "false";
        squareDraw = false;
    }
}

//util

bool Renderer::nameAlreadyExists(string name) {
    for (object3D* o : objects3d) {
        if (o->getName() == name) {
            ofLog() << "Name already exists.";
            return true;
        }
    }
    return false;
}