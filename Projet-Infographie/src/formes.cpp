/* Cette classe permet de créer des formes et d'assigner des paramèetres à chacune d'elles.
Il y a l'exemple d'un cercle. Je crois qu'en procédant comme cela nous pourrons plus facilement afficher l'information 
des instances dans les panneaux d'interface dont celui de Hierarchie*/



#include "formes.h"

void Formes::setup()
{
	circleParameters.setName("Controle de cercles");
	circleParameters.add(name.set("cercle"));
	
	circleParameters.add(red.set("rouge", 255, 0, 255));
	circleParameters.add(green.set("vert", 255, 0, 255));
	circleParameters.add(blue.set("bleu", 255, 0, 255));
	circleParameters.add(alpha.set("alpha", 255, 0, 255));

	circleParameters.add(positionX.set("position X", 500, 0, 1000));
	circleParameters.add(positionY.set("position Y", 600, 0, 800));

	circleParameters.add(radius.set("Rayon", 90, 0, 1000));
	
}

void Formes::draw()
{
	ofSetColor(red, green, blue, alpha);
	ofCircle(positionX, positionY, radius);
}
