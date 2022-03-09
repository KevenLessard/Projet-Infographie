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
	ofSetColor(255, 255, 255);
	ofDrawCircle(getPosition(), getRadius());
	
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
	ofSetColor(145, 145, 145);
	ofDrawRectangle( getPosition(), getRectanglewidth(), getRectangleHeight());
}

// Classe Triangle
//----------------------------------------------------------------------

Triangle2D::Triangle2D()
{
}

ofVec2f Triangle2D::getTriangleCoordA()
{
	return m_TriangleCoordA;
}

ofVec2f Triangle2D::getTriangleCoordB()
{
	return m_TriangleCoordB;
}

ofVec2f Triangle2D::getTriangleCoordC()
{
	return m_TriangleCoordC;
}

string Triangle2D::getName()
{
	return string();
}

void Triangle2D::setTriangleCoordA(ofVec2f newTriangleCoordA)
{
	m_TriangleCoordA = newTriangleCoordA;
}

void Triangle2D::setTriangleCoordB(ofVec2f newTriangleCoordB)
{
	m_TriangleCoordB = newTriangleCoordB;
}

void Triangle2D::setTriangleCoordC(ofVec2f newTriangleCoordC)
{
	m_TriangleCoordC = newTriangleCoordC;
}

void Triangle2D::setName(string newTriangleName)
{
	m_name = newTriangleName;
}

void Triangle2D::draw()
{
	ofColor(50, 0, 125);
	ofDrawTriangle(getTriangleCoordA(), getTriangleCoordB(), getTriangleCoordC());
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
	ofColor(35, 35, 35);
	ofDrawEllipse(getPosition(), getEllipsewidth(), getEllipseHeight());
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
	ofColor(255, 0, 76);
	ofDrawLine(getLinePtA(), getLinePtB());
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
	ofSetColor(255);
	ofSetPolyMode(OF_POLY_WINDING_NONZERO);

	ofBeginShape();
	ofVertex(400, 135);
	ofVertex(215, 135);
	ofVertex(365, 25);
	ofVertex(305, 200);
	ofVertex(250, 25);
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
	ofSetColor(255);
	ofSetPolyMode(OF_POLY_WINDING_ODD);
	ofBeginShape();
	ofVertex(250, 25);
	ofVertex(365, 25);
	ofVertex(365, 135);
	ofVertex(305, 200);
	ofVertex(250, 135);
	ofEndShape();
}