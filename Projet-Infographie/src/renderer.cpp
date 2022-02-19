
#include "renderer.h"

void Renderer::setup()
{
    ofSetBackgroundColor(31);

    //Pour3D
    speed = 100.0f;
    is_flip_axis_y = false;

    offset_x = 0.0f;
    offset_z = 0.0f;

    delta_x = speed;
    delta_z = speed;


}

void Renderer::update()
{

}

// fonction de dessin du curseur
void Renderer::draw_cursor(float x, float y) const
{
    // param�tres de dessin
    float length = 10.0f;
    float offset = 5.0f;
    

    // dessiner le curseur en vert si un des boutons du p�riph�rique de pointage est appuy�
    if (is_mouse_button_pressed)
        ofSetColor(0, 255, 0);
    else
        ofSetColor(255);

    // dessiner la forme vectorielle
    // Proposition d'une autre forme:
    //Curseur Circulaire. Cependant, le No Fill enleve le remplissage partout. Comment faire pour qu'il n'agisse que sur le curseur est-ce avec un begin() et un end()?

    ofDrawCircle(x, y, 20);
    ofDrawCircle(x, y, 1);
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
    ofTranslate(center_x + offset_x, is_flip_axis_y ? -center_y : center_y, offset_z);
    for (Object3D* obj : objects3D) {
        obj->draw();
    }
	// �paisseur du trait
	ofSetLineWidth(2);

	// afficher le curseur
	draw_cursor(mouse_current_x, mouse_current_y);
}

void Renderer::add_Model3D(){
    Model3D *model3D = new Model3D();
    objects3D.push_back(model3D);
}