#include "ofMain.h"
#include "application.h"

//========================================================================
int main( ){

	ofGLFWWindowSettings windowSettings;

	// r�solution de la fen�tre d'affichage
	windowSettings.setSize(1024, 768);

	// s�lection de la version de OpenGL
	windowSettings.setGLVersion(3, 3);

	// cr�ation de la fen�tre
	ofCreateWindow(windowSettings);


	ofRunApp(new ofApp());
}
