
#include "renderer.h"

void Renderer::setup()
{
        ofSetFrameRate(60);
        isMode3D = true;
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

        is_camera_tilt_x_right = false;
        is_camera_tilt_x_left = false;
        is_camera_pan_y_forward = false;
        is_camera_pan_y_backward = false;
        is_camera_roll_z_right = false;
        is_camera_roll_z_left = false;

        speed_delta = 250.0f;

        //sphereCenter = ofVec3f(0, 0, 500);

        skybox.setup({ 
        /*"skybox/right.jpg",
        "skybox/left.jpg",
        "skybox/top.jpg",
        "skybox/bottom.jpg",
        "skybox/front.jpg",
        "skybox/back.jpg"*/

        /*"skybox/dark_rt.png",
        "skybox/dark_lf.png",
        "skybox/dark_up.png",
        "skybox/dark_dn.png",
        "skybox/dark_ft.png",
        "skybox/dark_bk.png",
        */

            "skybox/posx.jpg","skybox/negx.jpg",
            "skybox/posy.jpg","skybox/negy.jpg",
            "skybox/posz.jpg","skybox/negz.jpg"
            
         });


        camera_offset = 350.0f;
        oscillation_frequency = 7500.0f;
        oscillation_amplitude = 45.0;
        reset();

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

    if (is_camera_tilt_x_right)
        mainCamera.tiltDeg(speed_translation);
    if (is_camera_tilt_x_left)
        mainCamera.tiltDeg(-speed_translation);

    if (is_camera_pan_y_forward)
        mainCamera.panDeg(speed_translation);
    if (is_camera_pan_y_backward)
        mainCamera.panDeg(-speed_translation);

    //Useless a supprimer
    if (is_camera_roll_z_right)
        mainCamera.rollDeg(speed_translation);
    if (is_camera_roll_z_left)
        mainCamera.rollDeg(-speed_translation);


    //Light
    ofPushMatrix();
    if (light_directionalOn)
    {
        // transformer la lumière directionnelle
        orientation_directional.makeRotate(int(ofGetElapsedTimeMillis() * 0.1f) % 360, 0, 1, 0);

        light_directional.setPosition(0, 60, camera_offset * 0.75f);
        light_directional.setOrientation(orientation_directional);
    }

    if (light_pointOn)
    {
        // transformer la lumière ponctuelle
        light_point.setPosition(mouse_current_x, -mouse_current_y, camera_offset * 0.75f);
    }

    if (light_spotOn)
    {
        // transformer la lumière projecteur
        oscillation = oscillate(ofGetElapsedTimeMillis(), oscillation_frequency, oscillation_amplitude);

        orientation_spot.makeRotate(30.0f, ofVec3f(1, 0, 0), oscillation, ofVec3f(0, 1, 0), 0.0f, ofVec3f(0, 0, 1));

        light_spot.setOrientation(orientation_spot);

       //light_spot.setPosition(center_x, center_y-75.0f, camera_offset * 0.75f);
        light_spot.setPosition(0, 0, camera_offset * 0.75f);
    }
    ofPopMatrix();

    if (isMode3D) {
    for (object3D* object : objects3d) {
      object->updateMaterial();
    }
    }
    
    //Code pour envoyer lumière sur shader
    light.setPointLight();
    light.setDiffuseColor(200);
    light.setGlobalPosition(center_x, center_y, 255.0f);
    
    
    if (isMode3D) {
        for (object3D* object : objects3d) {
            object->updateShader(light);
        }
    }

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

void Renderer::draw_ResizeCursorUpDown(float x, float y) const
{
    int cursor_width = 32;
    int cursor_height = 32;

    ofImage resizeCursor;
    resizeCursor.load("resizeCursorUpDown.png");

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

void Renderer::draw_MagnifyingGlass(float x, float y)const {
    int cursor_width = 32;
    int cursor_height = 32;

    ofImage resizeCursor;
    resizeCursor.load("Loupe1.png");

    resizeCursor.draw(x, y, cursor_width, cursor_height);
}

void Renderer::draw()
{

    //Ajouter une section pour le draw du 2D
    ofPushMatrix();
    mainCamera.begin();
    ofEnableDepthTest();


    ofEnableLighting();
    lightingOn();

    light.enable();
    skybox.draw(mainCamera);

    if (isMode3D) {
        //Dessine les lumières mais marche mal
        //if (light_pointOn) {
        //    light_point.draw();
        //}
        //if (light_directionalOn) {
        //    light_directional.draw();
        //}
        if (light_spotOn) {
            light_spot.draw();
        }


        for (object3D* object : objects3d) {
            ofPushMatrix();
            if (object->objectType == 7) {
                object->draw(mainCamera.getPosition());
            }
            //Test
            else if (object->objectType == 9) {
                object->draw(mainCamera);
            }
            else {
                object->draw();
            }
            ofPopMatrix();
        }
    } else {
        for (Object2D* object : objects2D) {
            ofPushMatrix();
            ofFill();
            object->draw();
            ofPopMatrix();
        }
    }


    ofDisableLighting();
    ofDisableDepthTest();
    lightingOff();
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
    if(resizeCursorUpDown_enabled)
        draw_ResizeCursorUpDown(mouse_current_x, mouse_current_y);
    if (magnifyingGlassEnabled)
        draw_MagnifyingGlass(mouse_current_x, mouse_current_y);
   
}

//Ajout d'un cercle au vecteur 2D
void Renderer::addNewCircle(string name) {
    Circle2D* circle = new Circle2D();
    if (nameAlreadyExists(name)) {
        return;
    }
    if (name == "") {
        name = "Circle " + to_string(objects2D.size());
    }
    circle->setName(name);
    circle->setPosition(ofVec3f(0, 0, 0));
    circle->setRadius(35);
    circle->setProportion(ofVec3f(1, 1, 1));
    objects2D.push_back(circle);
}

//Ajout d'un rectangle au vecteur 2D

void Renderer::addNewRectangle(string name) {
    Rectangle2D* rectangle = new Rectangle2D();
    if (nameAlreadyExists(name)) {
        return;
    }
    if (name == "") {
        name = "Rectangle " + to_string(objects2D.size());
    }
    rectangle->setName(name);
    rectangle->setPosition(ofVec3f(0, 0, 0));
    rectangle->setRectangleHeight(100);
    rectangle->setRectanglewidth(200);
    rectangle->setProportion(ofVec3f(1, 1, 1));
    //rectangle->applyTexture();
    //ofLog() << "applyTexture appelé";
    objects2D.push_back(rectangle);
}

//Ajout d'un triangle au vecteur 2D

void Renderer::addNewTriangle(string name) {
    Triangle2D* triangle = new Triangle2D();
    if (nameAlreadyExists(name)) {
        return;
    }
    if (name == "") {
        name = "Triangle " + to_string(objects2D.size());
    }
    triangle->setName(name);
    triangle->setPosition(ofVec3f(0, 0, 0));
    triangle->setTriangleCoordA(ofVec3f(ofGetWindowWidth() / 200, ofGetWindowHeight() / 200));
    triangle->setTriangleCoordB(ofVec3f((ofGetWindowWidth() / 200) - 100, (ofGetWindowHeight() / 200) + 100));
    triangle->setTriangleCoordC(ofVec3f(((ofGetWindowWidth() / 200) + 100), (ofGetWindowHeight() / 200) + 100));
    triangle->setProportion(ofVec3f(1, 1, 1));
    objects2D.push_back(triangle);
}

//Ajout d'un Ellipse au vecteur 2D

void Renderer::addNewEllipse(string name) {
    Ellipse2D* ellipse = new Ellipse2D();
    if (nameAlreadyExists(name)) {
        return;
    }
    if (name == "") {
        name = "Ellipse " + to_string(objects2D.size());
    }
    ellipse->setName(name);
    ellipse->setPosition(ofVec3f(0, 0, 0));
    ellipse->setEllipseHeight(100);
    ellipse->setEllipsewidth(200);
    ellipse->setProportion(ofVec3f(1, 1, 1));
    objects2D.push_back(ellipse);
}

//Ajout d'un Ligne au vecteur 2D

void Renderer::addNewLine(string name) {
    Line2D* line = new Line2D();
    if (nameAlreadyExists(name)) {
        return;
    }
    if (name == "") {
        name = "Line " + to_string(objects2D.size());
    }
    line->setName(name);
    line->setPosition(ofVec3f((ofGetWidth()/200), (ofGetHeight() / 200), 0));
    line->setLinePtA(0, 0);
    line->setLinePtB(200, 0);
    line->setProportion(ofVec3f(1, 1, 1));
    objects2D.push_back(line);
}

void Renderer::addNewStar(string name) {
    Star2D* star = new Star2D();
    if (nameAlreadyExists(name)) {
        return;
    }
    if (name == "") {
        name = "Star " + to_string(objects2D.size());
    }
    star->setName(name);
    star->setPosition(ofVec3f(0, 0, 0));
    star->setProportion(ofVec3f(1, 1, 1));
    objects2D.push_back(star);
}

void Renderer::addNewHouse(string name) {
    House2D* house = new House2D();
    if (nameAlreadyExists(name)) {
        return;
    }
    if (name == "") {
        name = "House " + to_string(objects2D.size());
    }
    house->setName(name);
    house->setPosition(ofVec3f(0, 0, 0));
    house->setProportion(ofVec3f(1, 1, 1));
    objects2D.push_back(house);
}
/*
void Renderer::addNewCurve(string name, int type) {
    if (nameAlreadyExists(name)) {
        return;
    }
    if (name == "") {
        name = "Curve " + to_string(objects2D.size());
    }
    Curve2D* curve = new Curve2D(type);
    curve->setName(name);
    objects2D.push_back(curve);
}
*/
//void Renderer::textureSelection(string name, int index)
//{

//}

void Renderer::addNewCurve(string name, int type) {
    if (nameAlreadyExists(name)) {
        return;
    }
    if (name == "") {
        name = "Curve " + to_string(objects2D.size());
    }
    Curve2D* curve = new Curve2D(type);
    curve->setName(name);
    objects2D.push_back(curve);
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

void Renderer::addNewSurface(string name) {
    if (nameAlreadyExists(name)) {
        return;
    }
    if (name == "") {
        name = "Surface " + to_string(objects3d.size());
    }
    object3D* surface = new object3D(name, 6, &mainCamera);
    objects3d.push_back(surface);
}

void Renderer::addNewQuad(string name) {
    if (nameAlreadyExists(name)) {
        return;
    }
    if (name == "") {
        name = "Quad " + to_string(objects3d.size());
    }
    object3D* quad = new object3D(name, 7);
    objects3d.push_back(quad);
}

void Renderer::addNewDelauney(string name) {
    if (nameAlreadyExists(name)) {
        return;
    }
    if (name == "") {
        name = "Delaunay " + to_string(objects3d.size());
    }
    object3D* delaunay = new object3D(name, 8, &mainCamera);
    objects3d.push_back(delaunay);
}

void Renderer::addNewGlassBox(string name) {
    if (nameAlreadyExists(name)) {
        return;
    }
    if (name == "") {
        name = "GlassBox " + to_string(objects3d.size());
    }
    object3D* glassBox = new object3D(name, 9);
    objects3d.push_back(glassBox);
}


void Renderer::import3dModel(std::string file_name) {
    string name = file_name + to_string(objects3d.size());

    object3D* model3D = new object3D(name, file_name);
    objects3d.push_back(model3D);
}

void Renderer::deleteObject(int index) {
    if (isMode3D) {
        objects3d.erase(objects3d.begin() + index);
    }
    else {
        objects2D.erase(objects2D.begin() + index);
    }
}

void Renderer::proportionateObject(int index, ofVec3f newProportion) {
    if (isMode3D) {
        objects3d[index]->setProportion(newProportion);
    }
    else {
        objects2D[index]->setProportion(newProportion);
    }
}

void Renderer::moveObject(int index, ofVec3f newPosition) {
    if (isMode3D) {
        objects3d[index]->setPosition(newPosition);
    }
    else {
        objects2D[index]->setPosition(newPosition);
    }
}

void Renderer::rotateObject(int index, ofVec3f newRotation) {
    if (isMode3D) {
        objects3d[index]->setRotation(newRotation);
    }
    else {
        objects2D[index]->setRotation(newRotation);
    }
    //ofQuaternion actualRotation(newRotation);
}

void Renderer::setObjectColor(int index, ofColor newColor) {
    //if hsb, convert to rbg first
    if (isMode3D) {
        objects3d[index]->setColor(newColor);
    }
    else {
        objects2D[index]->setColor(newColor);
    }
}

void Renderer::moveCurve(int index, int pointIndex, ofVec3f newPosition) {
    glm::vec3 newPos(newPosition.x, newPosition.y, 0);
    objects2D[index]->movePoint(pointIndex, newPos);
}

void Renderer::image_export(const string name, const string extension) const
{
    ofImage image;

    string time_stamp = ofGetTimestampString("-%y%m%d-%H%M%S-%i");
    string file_name = "export/" + name + time_stamp + "." + extension;

    image.grabScreen(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
    image.save(file_name);

    ofLog() << "export image:" << file_name;
}

string Renderer::getObject3dName(int index) {
    if (index >= objects3d.size() || index == -1) {
        return "";
    }
    return objects3d[index]->getName();
}

string Renderer::getObject2dName(int index)
{
    if (index >= objects2D.size() || index == -1) {
        return "";
    }
    return objects2D[index]->getName();
}

void Renderer::reset() {


    // configurer la lumière ambiante
    light_ambient.set(127, 127, 127);

    // configurer la lumière directionnelle
    light_directional.setDiffuseColor(ofColor(191, 191, 191));
    light_directional.setSpecularColor(ofColor(191, 191, 191));
    light_directional.setOrientation(ofVec3f(0.0f, 0.0f, 0.0f));
    light_directional.setDirectional();

    // configurer la lumière ponctuelle
    light_point.setDiffuseColor(ofColor(255, 255, 255));
    light_point.setSpecularColor(ofColor(191, 191, 191));
    light_point.setPointLight();

    // configurer la lumière projecteur
    light_spot.setDiffuseColor(ofColor(191, 191, 191));
    light_spot.setSpecularColor(ofColor(191, 191, 191));
    light_spot.setOrientation(ofVec3f(0.0f, 0.0f, 0.0f));
    light_spot.setSpotConcentration(2);
    light_spot.setSpotlightCutOff(30);
    light_spot.setSpotlight();

    //S'assure d'avoir une lumière de base d'ouverte.
    light_directionalOn = true;
}

void Renderer::setAnimation(int index) {
    objects3d[index]->setAnimation();
}

void Renderer::toggleRotation(int index) {
    objects3d[index]->toggleRotation();
}

void Renderer::drawBoundingBox(int index) {
    if (isMode3D) {
        objects3d[index]->drawBoundingBox();
    }
    else {
        //drawBoundingBox for 2d objects
    }
}

void Renderer::setTexture(int index) {
    if (isMode3D) {

        ofFileDialogResult openFileResult = ofSystemLoadDialog("choisir une texture");
        objects3d[index]->setTexture(openFileResult);
    }
}

void Renderer::setMetallic(int index, float value) {
    objects3d[index]->setMetallic(value);
}

void Renderer::setRoughness(int index, float value) {
    objects3d[index]->setRoughness(value);
}

//Camera

void Renderer::cameraLookAt(int index) {
    mainCamera.lookAt(objects3d[index]->getNode());
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


void Renderer::addNewImage(string name, string keypressed) {
    GestionImages* image = new GestionImages();
    if (nameAlreadyExists(name)) {
        return;
    }
    if (name == "") {
        name = "Image " + to_string(objects2D.size());
    }
    image->setName(name);
    image->setPosition(ofVec3f(0, 0, 0));
    image->setProportion(ofVec3f(0, 0, 0));
    image->actionResearchImages(keypressed);
    objects2D.push_back(image);
}
/*
void Renderer::shaderActive(int index, string type) {
    objects3d[index]->changeShader(type);
}
*/
/*
// Fonction de flitrage par convolution
// -------------------------------------------------------------------

void Renderer::filter()
{
    // résolution du kernel de convolution
    const int kernel_size = 3;

    // décalage à partir du centre du kernel
    const int kernel_offset = kernel_size / 2;

    // nombre de composantes de couleur (RGB)
    const int color_component_count = 3;

    // indices de l'image
    int x, y;

    // indices du kernel
    int i, j;

    // index des composantes de couleur
    int c;

    // index du pixel de l'image source utilisé pour le filtrage
    int pixel_index_img_src;

    // index du pixel de l'image de destination en cours de filtrage
    int pixel_index_img_dst;

    // index du pixel de l'image de destination en cours de filtrage
    int kernel_index;

    // valeur à un des indices du kernel de convolution
    float kernel_value;

    // extraire les pixels de l'image source
    ofPixels pixel_array_src = image_source.getPixels();

    // extraire les pixels de l'image de destination
    ofPixels pixel_array_dst = image_destination.getPixels();

    // ofPixels pixel_array_dst = image_destination.getPixels();


     // couleur du pixel lu dans l'image source
    ofColor pixel_color_src;

    // couleur du pixel à écrire dans l'image de destination
    ofColor pixel_color_dst;

    // somme du kernel appliquée à chaque composante de couleur d'un pixel
    float sum[color_component_count];

    // itération sur les rangées des pixels de l'image source
    for (y = 0; y < image_height; ++y)
    {
        // itération sur les colonnes des pixels de l'image source
        for (x = 0; x < image_width; ++x)
        {
            // initialiser le tableau où les valeurs de filtrage sont accumulées
            for (c = 0; c < color_component_count; ++c)
                sum[c] = 0;

            // déterminer l'index du pixel de l'image de destination
            pixel_index_img_dst = (image_width * y + x) * color_component_count;

            // itération sur les colonnes du kernel de convolution
            for (j = -kernel_offset; j <= kernel_offset; ++j)
            {
                // itération sur les rangées du kernel de convolution
                for (i = -kernel_offset; i <= kernel_offset; ++i)
                {
                    // déterminer l'index du pixel de l'image source à lire
                    pixel_index_img_src = (image_width * (y - j) + (x - i)) * color_component_count;

                    // lire la couleur du pixel de l'image source
                    pixel_color_src = pixel_array_src.getColor(pixel_index_img_src);

                    // déterminer l'indice du facteur à lire dans le kernel de convolution
                    kernel_index = kernel_size * (j + kernel_offset) + (i + kernel_offset);

                    // extraction de la valeur à cet index du kernel
                    switch (kernel_type)
                    {
                    case ConvolutionKernel::identity:
                        kernel_value = convolution_kernel_identity.at(kernel_index);
                        break;

                    case ConvolutionKernel::emboss:
                        kernel_value = convolution_kernel_emboss.at(kernel_index);
                        break;

                    case ConvolutionKernel::sharpen:
                        kernel_value = convolution_kernel_sharpen.at(kernel_index);
                        break;

                    case ConvolutionKernel::edge_detect:
                        kernel_value = convolution_kernel_edge_detect.at(kernel_index);
                        break;

                    case ConvolutionKernel::blur:
                        kernel_value = convolution_kernel_blur.at(kernel_index);
                        break;

                    default:
                        kernel_value = convolution_kernel_identity.at(kernel_index);
                        break;
                    }

                    // itération sur les composantes de couleur
                    for (c = 0; c < color_component_count; ++c)
                    {
                        // accumuler les valeurs de filtrage en fonction du kernel de convolution
                        sum[c] = sum[c] + kernel_value * pixel_color_src[c];
                    }
                }
            }

            // déterminer la couleur du pixel à partir des valeurs de filtrage accumulées pour chaque composante
            for (c = 0; c < color_component_count; ++c)
            {
                // conversion vers entier et validation des bornes de l'espace de couleur
                pixel_color_dst[c] = (int)ofClamp(sum[c], 0, 255);
            }

            // écrire la couleur à l'index du pixel en cours de filtrage
            pixel_array_dst.setColor(pixel_index_img_dst, pixel_color_dst);
        }
    } */

void Renderer::shaderActive(int index, string type) {
    objects3d[index]->changeShader(type);
}

void Renderer::setMaterial(int index, string type) {
    objects3d[index]->setMaterial(type);
}

void Renderer::addNewLight(int light) {
    if (light == 1 && light_ambientOn == true) {
        light_ambientOn = false;
    }
    else if (light == 1 && light_ambientOn == false) {
        light_ambientOn = true;
    }

    if (light == 2 && light_directionalOn == true) {
        light_directionalOn = false;
    }
    else if (light == 2 && light_directionalOn == false) {
        light_directionalOn = true;
    }

    if (light == 3 && light_pointOn == true) {
        light_pointOn = false;
    }
    else if (light == 3 && light_pointOn == false) {
        light_pointOn = true;
    }

    if (light == 4 && light_spotOn == true) {
        light_spotOn = false;
    }
    else if (light == 4 && light_spotOn == false) {
        light_spotOn = true;
    }
}

void Renderer::lightingOn() {
    if (light_ambientOn)
        ofSetGlobalAmbientColor(light_ambient);
    else
        ofSetGlobalAmbientColor(ofColor(0, 0, 0));

    if (light_directionalOn)
        light_directional.enable();

    if (light_pointOn)
        light_point.enable();

    if (light_spotOn)
        light_spot.enable();
}

void Renderer::lightingOff() {
    ofSetGlobalAmbientColor(ofColor(0, 0, 0));
    light_directional.disable();
    light_point.disable();
    light_spot.disable();
}

// fonction d'oscillation
float Renderer::oscillate(float time, float frequency, float amplitude)
{
    return sinf(time * 2.0f * PI / frequency) * amplitude;
}
