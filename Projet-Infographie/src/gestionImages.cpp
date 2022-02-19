#include "gestionImages.h"
/*
void GestionImages::setup()
{

}

void GestionImages::update()
{}

void GestionImages::draw() {

	//dessin de l'image chargée
	ofDrawBitmapString("Press r to open an image", 20, 15);


	for (unsigned int i = 0; i < loadedImages.size(); i++) {
		loadedImages[i].draw(0, 20);
	}
}
	//Sort function for stl::sort http://www.cplusplus.com/reference/algorithm/sort/
	bool GestionImages::sortColorFunction(ofColor i, ofColor j) {
		return (i.getBrightness() < j.getBrightness());
	}

	//--------------------------------------------------------------
	void GestionImages::processOpenFileSelection(ofFileDialogResult openFileResult) {

		ofLog() << "getName(): " + openFileResult.getName();
		ofLog() << "getPath(): " + openFileResult.getPath();

		ofFile file(openFileResult.getPath());

		if (file.exists()) {
			//Limiting this example to one image so we delete previous ones
			processedImages.clear();
			loadedImages.clear();

			ofLog() << "The file exists - now checking the type via file extension";
			string fileExtension = ofToUpper(file.getExtension());

			//We only want images
			if (fileExtension == "JPG" || fileExtension == "PNG") {

				//Save the file extension to use when we save out
				originalFileExtension = fileExtension;

				//Load the selected image
				ofImage image;
				image.load(openFileResult.getPath());
				if (image.getWidth() > ofGetWidth() || image.getHeight() > ofGetHeight())
				{
					image.resize(image.getWidth() / 2, image.getHeight() / 2);
				}
				loadedImages.push_back(image);

				//Make some short variables 
				int w = image.getWidth();
				int h = image.getHeight();

				//Make a new image to save manipulation by copying the source
				ofImage processedImage = image;

				//Walk through the pixels
				for (int y = 0; y < h; y++) {

					//Create a vector to store and sort the colors
					vector<ofColor> colorsToSort;

					for (int x = 0; x < w; x++) {

						//Capture the colors for the row
						ofColor color = image.getColor(x, y);
						colorsToSort.push_back(color);
					}

					//Sort the colors for the row
					sort(colorsToSort.begin(), colorsToSort.end(), sortColorFunction);

					for (int x = 0; x < w; x++)
					{
						//Put the sorted colors back in the new image
						processedImage.setColor(x, y, colorsToSort[x]);
					}
				}
				//Store the processed image
				processedImages.push_back(processedImage);
			}
		}
	}

	void GestionImages::actionResearchImages() {

		//Open the Open File Dialog
		ofFileDialogResult openFileResult = ofSystemLoadDialog("choisir une image (JPG ou PNG");

		//Check if the user opened a file
		if (openFileResult.bSuccess) {

			ofLogVerbose("User selected a file");

			//We have a file, check it and process it
			processOpenFileSelection(openFileResult);

		}
		else {
			ofLogVerbose("User hit cancel");
		}
	}
	*/