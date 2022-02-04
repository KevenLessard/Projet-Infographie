/* Cette classe permet de cr�er des formes et d'assigner des param�etres � chacune d'elles.
Il y a l'exemple d'un cercle. Je crois qu'en proc�dant comme cela nous pourrons plus facilement afficher l'information
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
	ofParameter<ofColor> colorPickerCercle;

	ofParameter<int> positionX;
	ofParameter<int> positionY;
	ofParameter<string> name;
	ofParameter<int> radius;

};

