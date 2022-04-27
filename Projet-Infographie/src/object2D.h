#include "ofMain.h"


#pragma once

class Object2D
{

public:

	
	Object2D();

	virtual string getName();
	virtual void setName(string newObjectName);
	virtual void movePoint(int pointIndex, glm::vec3 newPosition);
	virtual void changeFilter(int filter);
	virtual void change_gamma(float newGamma);
	virtual void change_exposure(float exposure);
	virtual vector<ofVec2f> getPoints();
	
	ofVec3f getPosition();
	ofVec3f getRotation();
	ofVec3f getProportion();
	
	void setColor(ofColor newColor);
	ofColor getColor();
	void setPosition(ofVec3f newPosition);
	void setRotation(ofVec3f newRotation);
	void setProportion(ofVec3f newProportion);
	bool isCurve = false;
	bool isImage = false;

	virtual void draw()=0;

	virtual ~Object2D();

	ofTexture form2Dtextures;


	

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
	void applyTexture();

	ofPoint points[4];
	int cornerIndex = 0;

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
	bool isBezier;
	Curve2D(int curveType);

	Curve coreBezier(glm::vec3& p0,
		glm::vec3& p1,
		glm::vec3& p2,
		glm::vec3& p3,
		unsigned steps);

	Curve evalBezier(vector<glm::vec3>& P, unsigned steps);

	Curve evalBspline(vector<glm::vec3>& P, unsigned steps);

	Curve evalCR(vector<glm::vec3>& P, unsigned steps);

	void movePoint(int pointIndex, glm::vec3 newPosition);
	vector<ofVec2f> getPoints();

	void draw();
};

enum ConvolutionKernel
{
	identity,
	emboss,
	sharpen,
	edge_detect,
	blur
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
	ofImage filteredImage;

	void actionResearchImages(string keypressed);

	void loadImage(ofFileDialogResult openFileResult, string keypressed);

	void changeFilter(int newFilter);
	void change_gamma(float newGamma);
	void change_exposure(float newExposure);
	void filter();

private:
	string m_name;
	ConvolutionKernel kernel_type;

	int image_width;
	int image_height;

	ofShader shader;
	float tone_mapping_exposure;
	float tone_mapping_gamma;
	
	const std::array<float, 9> convolution_kernel_identity
	{
		0.0f,  0.0f,  0.0f,
	  0.0f,  1.0f,  0.0f,
	  0.0f,  0.0f,  0.0f
	};
	// kernel de convolution (3x3) : aiguiser
	const std::array<float, 9> convolution_kernel_sharpen
	{
	  0.0f, -1.0f,  0.0f,
	 -1.0f,  5.0f, -1.0f,
	  0.0f, -1.0f,  0.0f
	};

	// kernel de convolution (3x3) : détection de bordure
	const std::array<float, 9> convolution_kernel_edge_detect
	{
	  0.0f,  1.0f,  0.0f,
	  1.0f, -4.0f,  1.0f,
	  0.0f,  1.0f,  0.0f
	};

	// kernel de convolution (3x3) : bosseler
	const std::array<float, 9> convolution_kernel_emboss
	{
	 -2.0f, -1.0f,  0.0f,
	 -1.0f,  1.0f,  1.0f,
	  0.0f,  1.0f,  2.0f
	};

	// kernel de convolution (3x3) : flou
	const std::array<float, 9> convolution_kernel_blur
	{
	  1.0f / 9.0f,  1.0f / 9.0f,  1.0f / 9.0f,
	  1.0f / 9.0f,  1.0f / 9.0f,  1.0f / 9.0f,
	  1.0f / 9.0f,  1.0f / 9.0f,  1.0f / 9.0f
	};
};
