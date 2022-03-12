#include "object2D.h"

Object2D::Object2D()
{
}

string Object2D::getName()
{
	return m_name;
}

void Object2D::setName(string newObjectName)
{
	m_name = newObjectName;
}

ofVec3f Object2D::getPosition()
{
	return m_position;
}

ofVec3f Object2D::getRotation()
{
	return m_rotation;
}

ofVec3f Object2D::getProportion()
{
	return m_proportion;
}

void Object2D::setPosition(ofVec3f newPosition)
{
	m_position = newPosition;
}

void Object2D::setRotation(ofVec3f newRotation)
{
	m_rotation = newRotation;
}

void Object2D::setProportion(ofVec3f newProportion)
{
	m_proportion = newProportion;
}

void Object2D::setColor(ofColor newColor) {
	color = newColor;
}

ofColor Object2D::getColor() {
	return color;
}


Object2D::~Object2D()
{
}



// classe d'un cercle
//------------------------------------------------------

Circle2D::Circle2D()
{
}

float Circle2D::getRadius()
{
	return m_radius;
}

void Circle2D::setRadius(float newRadius)
{
	m_radius = newRadius;
}

string Circle2D::getName()
{
	return m_name;
}

void Circle2D::setName(string newCircleName)
{
	m_name = newCircleName;
}

void Circle2D::draw()
{
	ofVec3f proportion = getProportion();
	ofSetColor(getColor());
	ofDrawCircle(getPosition(), getRadius()*proportion.x);
	
}


// Classe Rectangle
//----------------------------------------------------------------------
Rectangle2D::Rectangle2D()
{
}

float Rectangle2D::getRectangleHeight()
{
	return m_height;
}

void Rectangle2D::setRectangleHeight(float newRectangleHeight)
{
	m_height = newRectangleHeight;
}

float Rectangle2D::getRectanglewidth()
{
	return m_width;
}

void Rectangle2D::setRectanglewidth(float newRectangleWidth)
{
	m_width = newRectangleWidth;
}

string Rectangle2D::getName()
{
	return m_name;
}

void Rectangle2D::setName(string newRectangleName)
{
	m_name = newRectangleName;
}

void Rectangle2D::draw()
{
	ofSetColor(getColor());
	ofVec3f proportion = getProportion();
	ofDrawRectangle( getPosition(), getRectanglewidth()*proportion.x, getRectangleHeight()*proportion.y);
}

// Classe Triangle
//----------------------------------------------------------------------

Triangle2D::Triangle2D()
{
}

ofVec3f Triangle2D::getTriangleCoordA()
{
	return m_TriangleCoordA;
}

ofVec3f Triangle2D::getTriangleCoordB()
{
	return m_TriangleCoordB;
}

ofVec3f Triangle2D::getTriangleCoordC()
{
	return m_TriangleCoordC;
}

string Triangle2D::getName()
{
	return m_name;
}

void Triangle2D::setTriangleCoordA(ofVec3f newTriangleCoordA)
{
	m_TriangleCoordA = newTriangleCoordA;
}

void Triangle2D::setTriangleCoordB(ofVec3f newTriangleCoordB)
{
	m_TriangleCoordB = newTriangleCoordB;
}

void Triangle2D::setTriangleCoordC(ofVec3f newTriangleCoordC)
{
	m_TriangleCoordC = newTriangleCoordC;
}

void Triangle2D::setName(string newTriangleName)
{
	m_name = newTriangleName;
}

void Triangle2D::draw()
{
	ofSetColor(getColor());
	ofVec3f position = getPosition();
	ofVec3f proportion = getProportion();

	ofDrawTriangle((getTriangleCoordA() + getPosition())*proportion, (getTriangleCoordB() + getPosition())*proportion, (getTriangleCoordC() + getPosition())*proportion);
}


// Classe Ellipse
//----------------------------------------------------------------------
Ellipse2D::Ellipse2D()
{
}

float Ellipse2D::getEllipseHeight()
{
	return m_ellipseHeight;
}

string Ellipse2D::getName()
{
	return m_name;
}

float Ellipse2D::getEllipsewidth()
{
	return m_ellipseWidth;
}

void Ellipse2D::setEllipsewidth(float newEllipseWidth)
{
	m_ellipseWidth = newEllipseWidth;
}

void Ellipse2D::setEllipseHeight(float newEllipseHeight)
{
	m_ellipseHeight = newEllipseHeight;
}

void Ellipse2D::setName(string newEllipseName)
{
	m_name = newEllipseName;
}

void Ellipse2D::draw()
{
	ofVec3f proportion = getProportion();
	ofSetColor(getColor());
	ofDrawEllipse(getPosition(), getEllipsewidth()*proportion.x, getEllipseHeight()*proportion.y);
}

// Classe Line
//----------------------------------------------------------------------


Line2D::Line2D()
{
}

ofVec2f Line2D::getLinePtA()
{
	return m_linePtA;
}

string Line2D::getName()
{
	return m_name;
}

ofVec2f Line2D::getLinePtB()
{
	return m_linePtB;
}

void Line2D::setLinePtA(float x, float y)
{
	ofVec2f newLinePtA(x, y);
	m_linePtA = newLinePtA;
}

void Line2D::setLinePtB(float x, float y)
{
	ofVec2f newLinePtB(x, y);
	m_linePtB = newLinePtB;
}

void Line2D::setName(string newLineName)
{
	m_name = newLineName;
}

void Line2D::draw() {
	ofSetColor(getColor());
	ofVec3f proportion = getProportion();
	ofDrawLine((getLinePtA() + getPosition())*getProportion(), (getLinePtB() + getPosition())*getProportion());
}
// Classe Star
//----------------------------------------------------------------------

Star2D::Star2D()
{
}

void Star2D::setName(string newStarName)
{
	m_name = newStarName;
}

string Star2D::getName()
{
	return m_name;
}

void Star2D::draw()
{
	ofSetColor(getColor());
	ofSetPolyMode(OF_POLY_WINDING_NONZERO);

	ofVec3f position = getPosition();
	ofVec3f proportion = getProportion();

	ofBeginShape();
	ofVertex((400 + position.x)*proportion.x, (135 + position.y)*proportion.y);
	ofVertex((215 + position.x)*proportion.x, (135 + position.y)*proportion.y);
	ofVertex((365 + position.x)*proportion.x, (25 + position.y)*proportion.y);
	ofVertex((305 + position.x)*proportion.x, (200 + position.y)*proportion.y);
	ofVertex((250 + position.x)*proportion.x, (25 + position.y)*proportion.y);
	ofEndShape();
}

// Classe House
//----------------------------------------------------------------------

House2D::House2D()
{
}

void House2D::setName(string newHouseName)
{
	m_name = newHouseName;
}

string House2D::getName()
{
	return m_name;
}

void House2D::draw()
{
	ofVec3f position = getPosition();
	ofVec3f proportion = getProportion();

	ofSetColor(getColor());
	ofSetPolyMode(OF_POLY_WINDING_ODD);
	ofBeginShape();
	ofVertex((0 + position.x) * proportion.x, (0 + position.y) * proportion.y);
	ofVertex((115 + position.x) * proportion.x, (0 + position.y) * proportion.y);
	ofVertex((115 + position.x) * proportion.x, (110 + position.y) * proportion.y);
	ofVertex((55 + position.x) * proportion.x, (175 + position.y) * proportion.y);
	ofVertex((0 + position.x) * proportion.x, (110 + position.y) * proportion.y);
	ofEndShape();
}

// Class gestionImage
//----------------------------------------------------------------------
GestionImages::GestionImages() {

}

void GestionImages::setName(string newImageName) {
	m_name = newImageName;
}

string GestionImages::getName() {
	return m_name;
}

void GestionImages::draw() {
	image.draw(getPosition());
}

//Fonction pour rechercher dans le réseau local une image
void GestionImages::actionResearchImages(string keypressed) {


	//Open the Open File Dialog
	ofFileDialogResult openFileResult = ofSystemLoadDialog("choisir une image (JPG ou PNG)");

	//Check if the user opened a file
	if (openFileResult.bSuccess) {

		ofLog() << "file selected";


		loadImage(openFileResult, keypressed);
	}
	else {
		ofLog() << "operation canceled by user";
	}
}

void GestionImages::loadImage(ofFileDialogResult openFileResult, string keypressed) {

		ofLog() << "getName(): " + openFileResult.getName();
		ofLog() << "getPath(): " + openFileResult.getPath();

		ofFile file(openFileResult.getPath());

		if (file.exists()) {
			//présentement, nous chargons une seule image à la fois
			loadedImages.clear();

			ofLog() << "The file exists - now checking the type via file extension";
			string fileExtension = ofToUpper(file.getExtension());

			if (fileExtension == "JPG" || fileExtension == "PNG") {

				// Conserver l'extention pour la sauvegarde future
				originalFileExtension = fileExtension;

				//Load l'image choisie
				//ofImage image;

				image.load(openFileResult.getPath());
				if (image.getWidth() > ofGetWidth() || image.getHeight() > ofGetHeight())
				{
					image.resize(image.getWidth() / 2, image.getHeight() / 2);
				}
				ofLog() << "loading completed";
			}

			//Permet d'importer l'échantillonage d'une image
			if (keypressed == "f4") {
				//TopLeft
				image.cropFrom(image, image.getWidth() * 0, image.getHeight() * 0, image.getWidth() / 2, image.getHeight() / 2);

			}
			if (keypressed == "f5") {
				//TopRight
				image.cropFrom(image, image.getWidth() / 2, image.getHeight() * 0, image.getWidth() / 2, image.getHeight() / 2);

			}
			if (keypressed == "f7") {
				//DownRight
				image.cropFrom(image, image.getWidth() / 2, image.getHeight() / 2, image.getWidth() / 2, image.getHeight() / 2);
			}

			//DownLeft
			if (keypressed == "f6") {
				image.cropFrom(image, image.getWidth() * 0, image.getHeight() / 2, image.getWidth() / 2, image.getHeight() / 2);
			}
		}
	}
