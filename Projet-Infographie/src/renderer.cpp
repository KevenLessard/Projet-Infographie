

#include "renderer.h"

void Renderer::setup()
{
	{
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

    ofDrawLine(x + offset, y, x + offset + length, y);
    ofDrawLine(x - offset, y, x - offset - length, y);
    ofDrawLine(x, y + offset, x, y + offset + length);
    ofDrawLine(x, y - offset, x, y - offset - length);

}

void Renderer::draw()
{
	// épaisseur du trait
	ofSetLineWidth(2);

	// afficher le curseur
	draw_cursor(mouse_current_x, mouse_current_y);
}