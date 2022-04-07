#include "ofMain.h"
#include "ofxVectorGraphics.h"

#pragma once

class Object2D
{

public:

	
	Object2D();

	virtual string getName();
	virtual void setName(string newObjectName);
	
	ofVec3f getPosition();
	ofVec3f getRotation();
	ofVec3f getProportion();
	
	void setColor(ofColor newColor);
	ofColor getColor();
	void setPosition(ofVec3f newPosition);
	void setRotation(ofVec3f newRotation);
	void setProportion(ofVec3f newProportion);
	

	virtual void draw()=0;

	virtual ~Object2D();


	

private:

	ofVec3f m_position;
	ofVec3f m_rotation;
	ofVec3f m_proportion;
	string m_name;
	ofColor color;

};

class Circle2D : public Object2D
{
public: 
	
	Circle2D();
	float getRadius();
	void setRadius(float newRadius);
	string getName();
	void setName(string newCircleName);

	void draw();

private:

	float m_radius;
	string m_name;

};

class Rectangle2D : public Object2D
{
public:

	Rectangle2D();
	float getRectangleHeight();
	string getName();
	float getRectanglewidth();

	void setRectanglewidth(float newRectangleWidth);
	void setRectangleHeight(float newRectangleHeight);
	void setName(string newRectangleName);

	void draw();

private:

	float m_height;
	float m_width;
	string m_name;

};

class Triangle2D : public Object2D
{
public:

	Triangle2D();
	ofVec3f getTriangleCoordA();
	ofVec3f getTriangleCoordB();
	ofVec3f getTriangleCoordC();
	string getName();
	

	void setTriangleCoordA(ofVec3f newTriangleCoordA);
	void setTriangleCoordB(ofVec3f newTriangleCoordB);
	void setTriangleCoordC(ofVec3f newTriangleCoordC);
	void setName(string newTriangleName);

	void draw();

private:

	ofVec3f m_TriangleCoordA;
	ofVec3f m_TriangleCoordB;
	ofVec3f m_TriangleCoordC;
	string m_name;

};

class Ellipse2D : public Object2D
{
public:

	Ellipse2D();
	float getEllipseHeight();
	string getName();
	float getEllipsewidth();

	void setEllipsewidth(float newEllipseWidth);
	void setEllipseHeight(float newEllipseHeight);
	void setName(string newEllipseName);

	void draw();

private:

	float m_ellipseHeight;
	float m_ellipseWidth;
	string m_name;

};

class Line2D : public Object2D
{
public:

	Line2D();
	ofVec2f getLinePtA();
	string getName();
	ofVec2f getLinePtB();

	void setLinePtA(float x,float y);
	void setLinePtB(float x, float y);
	void setName(string newLineName);

	void draw();

private:

	ofVec2f m_linePtA;
	ofVec2f m_linePtB;
	string m_name;

};

class Star2D : public Object2D
{
public:

	Star2D();
	
	string getName();

	void setName(string newTriangleName);

	void draw();

private:

	string m_name;

};

class House2D : public Object2D
{
public:

	House2D();

	string getName();

	void setName(string newTriangleName);

	void draw();

private:

	string m_name;

};

typedef vector<glm::vec3> Curve;

class Curve2D : public Object2D {
public: 
	vector<glm::vec3> cps;
	vector<glm::vec3> line;

	Curve2D(int curveType);

	Curve coreBezier(glm::vec3& p0,
		glm::vec3& p1,
		glm::vec3& p2,
		glm::vec3& p3,
		unsigned steps);

	Curve evalBezier(vector<glm::vec3>& P, unsigned steps);

	Curve evalBspline(vector<glm::vec3>& P, unsigned steps);

	Curve evalCR(vector<glm::vec3>& P, unsigned steps);

	void draw();
};

class GestionImages : public Object2D
{
public:
	GestionImages();

	string getName();

	void setName(string newImageName);;
	void draw();

	vector<ofImage>loadedImages;
	vector<ofImage>processedImages;
	string originalFileExtension;

	ofImage image;

	void actionResearchImages(string keypressed);


	void loadImage(ofFileDialogResult openFileResult, string keypressed);



private:
	string m_name;

};
