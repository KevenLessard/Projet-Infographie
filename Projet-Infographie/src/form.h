/* Cette classe permet de créer des formes et d'assigner des paramèetres à chacune d'elles.
Il y a l'exemple d'un cercle. Je crois qu'en procédant comme cela nous pourrons plus facilement afficher l'information
des instances dans les panneaux d'interface dont celui de Hierarchie*/

#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class Form
{
public:
	Form();


	void setup();
	void draw();
	

// Parametre pour un cercle
	ofParameterGroup Parameters;
	ofParameter<ofColor> colorPickerCercle;
	ofColor getHue();

	ofParameter<int> positionX;
	ofParameter<int> positionY;
	ofParameter<int> hue;
	ofParameter<int> brightness;
	ofParameter<int> saturation;
	ofParameter<string> name;
	ofxIntSlider floatSlider;


	vector<Form>FormList;

};

class Circle : public Form
{
	Circle();
	ofParameter<int> radius;
};

class Rectangle : public Form
{
	Rectangle();
};

class Triangle : public Form
{
};

