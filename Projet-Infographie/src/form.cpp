/* Cette classe permet de créer des formes et d'assigner des paramèetres à chacune d'elles.
Il y a l'exemple d'un cercle. Je crois qu'en procédant comme cela nous pourrons plus facilement afficher l'information 
des instances dans les panneaux d'interface dont celui de Hierarchie*/



#include "form.h"

Form::Form()
{
}

void Form::setup()
{
	Parameters.setName("Controle de forme");
	Parameters.add(name.set("cercle"));

	Parameters.add(colorPickerCercle.set("couleur du cercle", ofColor(31), ofColor(0, 0), ofColor(255, 255)));
	Parameters.add(positionX.set("position X", 500, 0, 1000));
	Parameters.add(positionY.set("position Y", 600, 0, 800));
	//circleParameters.add(hue.set("HUE", getHue(), 0, 255));

	
}

void Form::draw()
{
	ofSetColor(colorPickerCercle);
	
	
}

Circle::Circle()
{
	Parameters.add(radius.set("Rayon", 90, 0, 1000));
	ofCircle(positionX, positionY, radius);

}
Rectangle::Rectangle()
{
}
