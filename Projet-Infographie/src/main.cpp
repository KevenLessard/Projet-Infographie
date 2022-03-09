#include "ofMain.h"
#include "application.h"

//========================================================================
int main( ){

	ofGLFWWindowSettings windowSettings;

	// résolution de la fenêtre d'affichage
	windowSettings.setSize(1024, 768);

	// sélection de la version de OpenGL
	windowSettings.setGLVersion(3, 3);

	// création de la fenêtre
	ofCreateWindow(windowSettings);


	ofRunApp(new ofApp());
}
