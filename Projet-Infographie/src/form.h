/* Cette classe permet de créer des formes et d'assigner des paramèetres à chacune d'elles.
Il y a l'exemple d'un cercle. Je crois qu'en procédant comme cela nous pourrons plus facilement afficher l'information
des instances dans les panneaux d'interface dont celui de Hierarchie*/

#pragma once

#include "ofMain.h"
class Form
{
public:
	void setup();
	void draw();

// Parametre pour un cercle
	ofParameterGroup circleParameters;
	ofParameter<int> red;
	ofParameter<int> green;
	ofParameter<int>blue;
	ofParameter<int>alpha;

	ofParameter<int> positionX;
	ofParameter<int> positionY;
	ofParameter<string> name;
	ofParameter<int> radius;

};

