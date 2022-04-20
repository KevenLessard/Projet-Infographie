#include "ofMain.h"
#include "application.h"
#include "viewWindowApp.h"

//========================================================================
int main( ){


	ofGLFWWindowSettings windowSettings;

	// r�solution de la fen�tre d'affichage
	windowSettings.setSize(1024, 768);

	// s�lection de la version de OpenGL
	windowSettings.setGLVersion(3, 3);

	// cr�ation de la fen�tre
	shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(windowSettings);

	//Fenetre 2
	windowSettings.setSize(600, 600);
	windowSettings.setPosition(glm::vec2(1048, 300));
	windowSettings.resizable = false;
	shared_ptr<ofAppBaseWindow> viewWindow = ofCreateWindow(windowSettings);

	shared_ptr<ofApp> mainApp(new ofApp);
	shared_ptr<viewWindowApp> viewApp(new viewWindowApp);
	mainApp->guiViewWindow = viewApp;
		
		
		ofRunApp(viewWindow, viewApp);
	ofRunApp(mainWindow, mainApp);
	ofRunMainLoop();
	
}
