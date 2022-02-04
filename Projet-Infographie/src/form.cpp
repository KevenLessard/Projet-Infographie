/* Cette classe permet de créer des formes et d'assigner des paramèetres à chacune d'elles.
Il y a l'exemple d'un cercle. Je crois qu'en procédant comme cela nous pourrons plus facilement afficher l'information 
des instances dans les panneaux d'interface dont celui de Hierarchie*/



#include "form.h"

void Form::setup()
{
	circleParameters.setName("Controle de cercles");
	circleParameters.add(name.set("cercle"));
	

	circleParameters.add(colorPickerCercle.set("couleur du cercle", ofColor(31), ofColor(0, 0), ofColor(255, 255)));
	circleParameters.add(positionX.set("position X", 500, 0, 1000));
	circleParameters.add(positionY.set("position Y", 600, 0, 800));

	circleParameters.add(radius.set("Rayon", 90, 0, 1000));
	
}

void Form::draw()
{
	ofSetColor(colorPickerCercle);
	ofCircle(positionX, positionY, radius);
}
