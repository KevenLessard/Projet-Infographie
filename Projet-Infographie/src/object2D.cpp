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

void Object2D::movePoint(int pointIndex, glm::vec3 newPosition) {
} 

void Object2D::changeFilter(int filter) {

}
void Object2D::change_gamma(float newGamma) {

}
void Object2D::change_exposure(float newExposure) {

}
vector<ofVec2f> Object2D::getPoints() {
    return vector<ofVec2f>();
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

void Rectangle2D::applyTexture()
{
    ofLoadImage(form2Dtextures, "castleWall.jpg");
    points[0].x = getPosition().x; points[0].y = getPosition().y;
    points[1].x = getPosition().x + getRectanglewidth(); points[1].y = getPosition().y;
    points[2].x = getPosition().x + getRectanglewidth(); points[2].y = getPosition().y + getRectangleHeight();
    points[3].x = getPosition().x; points[3].y = getPosition().y + getRectangleHeight();
    
    form2Dtextures.draw(points[0], points[1], points[2], points[3]);
}

void Rectangle2D::draw()
{
	ofSetColor(getColor());
	ofVec3f proportion = getProportion();
	ofDrawRectangle( getPosition(), getRectanglewidth()*proportion.x, getRectangleHeight()*proportion.y);
    applyTexture();
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

//--------------------------------------------------------------------------------------
// 
//Curve2D

Curve2D::Curve2D(int curveType) {
    isCurve = true;
    cps.push_back(glm::vec3(400.0, 150.0, 0.0));
    cps.push_back(glm::vec3(200.0, 900.0, 0.0));
    cps.push_back(glm::vec3(300.0, 650.0, 0.0));
    cps.push_back(glm::vec3(450.0, 400.0, 0.0));
    cps.push_back(glm::vec3(500.0, 750.0, 0.0));
    cps.push_back(glm::vec3(700.0, 222.0, 0.0));
    cps.push_back(glm::vec3(800.0, 500.0, 0.0));

    switch (curveType) {
    case 0:
        isBezier = false;
        line = evalCR(cps, 1000);
        break;
    case 1:
        isBezier = true;
        line = evalBspline(cps, 1000);
        break;
    }
}

Curve Curve2D::coreBezier(glm::vec3& p0,
    glm::vec3& p1,
    glm::vec3& p2,
    glm::vec3& p3,
    unsigned steps) {
    Curve R(steps + 1);

    //Basis Matrix.
    glm::mat4 B;

    glm::vec4 x = glm::vec4(1, 0, 0, 0);
    glm::vec4 y = glm::vec4(-3, 3, 0, 0);
    glm::vec4 z = glm::vec4(3, -6, 3, 0);
    glm::vec4 w = glm::vec4(-1, 3, -3, 1);


    B = glm::mat4(x, y, z, w);

    //Control Points;
    glm::mat4 controlPoints;

    glm::vec4 cx = glm::vec4(p0.x, p0.y, p0.z, 1);
    glm::vec4 cy = glm::vec4(p1.x, p1.y, p1.z, 1);
    glm::vec4 cz = glm::vec4(p2.x, p2.y, p2.z, 1);
    glm::vec4 cw = glm::vec4(p3.x, p3.y, p3.z, 1);

    controlPoints = glm::mat4(cx, cy, cz, cw);

    for (unsigned i = 0; i <= steps; ++i) {
        // ...
        float t = float(i) / float(steps);

        glm::vec4 tempVertex = controlPoints * B * glm::vec4(1, t, pow(t, 2), pow(t, 3));
        R[i] = glm::vec3(tempVertex);

    }
    return R;
}

Curve Curve2D::evalBezier(vector<glm::vec3> &P, unsigned steps) {
    bool run;

    if (P.size() < 4 || P.size() % 3 != 1) {
        cout << "Error: evalBezier must be called with 3n + 1 control points" << endl;
        run = false;
    }
    else {
        run = true;
    }

    Curve bezier;

    if (run) {
        for (unsigned i = 0; i < P.size() - 3; ++i) {
            Curve smallBez = coreBezier(P[3 * i], P[3 * i + 1], P[3 * i + 2], P[3 * i + 3], steps);
            bezier.insert(bezier.end(), smallBez.begin(), smallBez.end());
        }
    }

    return bezier;
}

Curve Curve2D::evalBspline(vector<glm::vec3>& P, unsigned steps) {
    bool run;

    if (P.size() < 4 || P.size() % 3 != 1) {
        cout << "Error: evalBspline must be called with 3n + 1 control points" << endl;
        run = false;
    }
    else {
        run = true;
    }

    Curve bSpline;

    if (run) {
        for (unsigned i = 0; i < P.size() - 3; ++i) {

            //Control Points
            glm::mat4 cPoint;

            glm::vec4 cx = glm::vec4(P[i].x, P[i].y, P[i].z, 1);
            glm::vec4 cy = glm::vec4(P[i + 1].x, P[i + 1].y, P[i + 1].z, 1);
            glm::vec4 cz = glm::vec4(P[i + 2].x, P[i + 2].y, P[i + 2].z, 1);
            glm::vec4 cw = glm::vec4(P[i + 3].x, P[i + 3].y, P[i + 3].z, 1);

            cPoint = glm::mat4(cx, cy, cz, cw);

            //Basis Matrix for Bspline
            glm::mat4 bSplineB;

            glm::vec4 basisbx = glm::vec4(1.0, 4.0, 1.0, 0.0);
            glm::vec4 basisby = glm::vec4(-3.0, 0.0, 3.0, 0.0);
            glm::vec4 basisbz = glm::vec4(3.0, -6.0, 3.0, 0.0);
            glm::vec4 basisbw = glm::vec4(-1.0, 3.0, -3.0, 1.0);

            bSplineB = glm::mat4(basisbx, basisby, basisbz, basisbw);

            bSplineB = bSplineB / float(6);

            //Basis Matrix of Bezier
            glm::mat4 B;

            glm::vec4 x = glm::vec4(1, 0, 0, 0);
            glm::vec4 y = glm::vec4(-3, 3, 0, 0);
            glm::vec4 z = glm::vec4(3, -6, 3, 0);
            glm::vec4 w = glm::vec4(-1, 3, -3, 1);

            B = glm::mat4(x, y, z, w);

            //Matrix Conversion
            glm::mat4 newPointsM;

            newPointsM = cPoint * bSplineB * glm::inverse(B);

            glm::vec4 p0_4 = newPointsM[0];
            glm::vec4 p1_4 = newPointsM[1];
            glm::vec4 p2_4 = newPointsM[2];
            glm::vec4 p3_4 = newPointsM[3];

            glm::vec3 p0 = glm::vec3(p0_4);
            glm::vec3 p1 = glm::vec3(p1_4);
            glm::vec3 p2 = glm::vec3(p2_4);
            glm::vec3 p3 = glm::vec3(p3_4);

            vector<glm::vec3> newPoints;

            newPoints.push_back(p0); newPoints.push_back(p1); newPoints.push_back(p2); newPoints.push_back(p3);
            Curve smallbSpline = evalBezier(newPoints, steps);

            bSpline.insert(bSpline.end(), smallbSpline.begin(), smallbSpline.end());
        }
    }
    return bSpline;
}

Curve Curve2D::evalCR(vector<glm::vec3>& P, unsigned steps) {
    bool run;

    if (P.size() < 4 || P.size() % 3 != 1) {
        cout << "Error: evalCRmust be called with 3n + 1 control points" << endl;
        run = false;
    }
    else {
        run = true;
    }

    Curve Cr;

    if (run) {
        for (unsigned i = 0; i < P.size() - 1; ++i) {

            //Control Points
            glm::mat4 cPoint;

            glm::vec4 cx = glm::vec4(P[(i - 1) % P.size()].x, P[(i - 1) % P.size()].y, P[(i - 2) % P.size()].z, 1);
            glm::vec4 cy = glm::vec4(P[(i) % P.size()].x, P[(i) % P.size()].y, P[(i) % P.size()].z, 1);
            glm::vec4 cz = glm::vec4(P[(i + 1) % P.size()].x, P[(i + 1) % P.size()].y, P[(i + 1) % P.size()].z, 1);
            glm::vec4 cw = glm::vec4(P[(i + 2) % P.size()].x, P[(i + 2) % P.size()].y, P[(i + 2) % P.size()].z, 1);

            cPoint = glm::mat4(cx, cy, cz, cw);

            //Catmull-Rom Basis Matrix
            glm::mat4 CR;

            glm::vec4 crx = glm::vec4(0.0, 2.0, 0.0, 0.0);
            glm::vec4 cry = glm::vec4(-1.0, 0.0, 1.0, 0.0);
            glm::vec4 crz = glm::vec4(2.0, -5.0, 4.0, -1.0);
            glm::vec4 crw = glm::vec4(-1.0, 3.0, -3.0, 1.0);

            CR = glm::mat4(crx, cry, crz, crw);

            CR = CR / float(2);

            //Basis Matrix of Bezier
            glm::mat4 B;

            glm::vec4 x = glm::vec4(1, 0, 0, 0);
            glm::vec4 y = glm::vec4(-3, 3, 0, 0);
            glm::vec4 z = glm::vec4(3, -6, 3, 0);
            glm::vec4 w = glm::vec4(-1, 3, -3, 1);

            B = glm::mat4(x, y, z, w);

            //Matrix Conversion
            glm::mat4 newPointsM;

            newPointsM = cPoint * CR * glm::inverse(B);

            glm::vec4 p0_4 = newPointsM[0];
            glm::vec4 p1_4 = newPointsM[1];
            glm::vec4 p2_4 = newPointsM[2];
            glm::vec4 p3_4 = newPointsM[3];

            glm::vec3 p0 = glm::vec3(p0_4);
            glm::vec3 p1 = glm::vec3(p1_4);
            glm::vec3 p2 = glm::vec3(p2_4);
            glm::vec3 p3 = glm::vec3(p3_4);

            vector<glm::vec3> newPoints;

            newPoints.push_back(p0); newPoints.push_back(p1); newPoints.push_back(p2); newPoints.push_back(p3);
            Curve smallCr = evalBezier(newPoints, steps);

            Cr.insert(Cr.end(), smallCr.begin(), smallCr.end());
        }
    }

    return Cr;
}

void Curve2D::draw() {
    ofSetColor(getColor());
    for (int i = 0; i < line.size(); i++) {
        ofDrawCircle(line[i], 2);
    }
}

void Curve2D::movePoint(int pointIndex, glm::vec3 newPosition) {
    cps[pointIndex] = newPosition;
    if (isBezier)
        line = evalBspline(cps, 1000);
    else
        line = evalCR(cps, 1000);
}

vector<ofVec2f> Curve2D::getPoints() {
    vector<ofVec2f> result;
    for (int i = 0; i < 7; i++) {
        ofVec2f v(cps[i].x, cps[i].y);
        result.push_back(v);
    }
    return result;
}
//----------------------------------------------------------------------

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
    shader.begin();
    // passer les attributs uniformes au shader
    shader.setUniformTexture("image", filteredImage.getTexture(), 1);
    shader.setUniform1f("tone_mapping_exposure", tone_mapping_exposure);
    shader.setUniform1f("tone_mapping_gamma", tone_mapping_gamma);
    shader.setUniform1f("tone_mapping_toggle", false);
	filteredImage.draw(getPosition().x, getPosition().y, filteredImage.getWidth() * getProportion().x, filteredImage.getHeight() * getProportion().y);
    shader.end();
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

            image_width = image.getWidth();
            image_height = image.getHeight();

            filteredImage.allocate(image_width, image_height, OF_IMAGE_COLOR);
            kernel_type = ConvolutionKernel::identity;
            filter();
            setProportion(ofVec3f(1, 1, 0));
            isImage = true;
            tone_mapping_exposure = 1.0f;
            tone_mapping_gamma = 2.2f;
            shader.load("shader/tone_mapping_330_vs.glsl", "shader/tone_mapping_330_fs.glsl");
		}
}

void GestionImages::filter() {
      // résolution du kernel de convolution
  const int kernel_size = 3;

  // décalage à partir du centre du kernel
  const int kernel_offset = kernel_size / 2;

  // nombre de composantes de couleur (RGB)
  const int color_component_count = 3;

  // indices de l'image
  int x, y;

  // indices du kernel
  int i, j;

  // indices d'échantillonnage;
  int xi, yj;

  // index des composantes de couleur
  int c;

  // index du pixel de l'image source utilisé pour le filtrage
  int pixel_index_img_src;

  // index du pixel de l'image de destination en cours de filtrage
  int pixel_index_img_dst;

  // index du pixel de l'image de destination en cours de filtrage
  int kernel_index;

  // valeur à un des indices du kernel de convolution
  float kernel_value;

  // extraire les pixels de l'image source
  ofPixels pixel_array_src = image.getPixels();

  // extraire les pixels de l'image de destination
  ofPixels pixel_array_dst = filteredImage.getPixels();

  // couleur du pixel lu dans l'image source
  ofColor pixel_color_src;

  // couleur du pixel à écrire dans l'image de destination
  ofColor pixel_color_dst;

  // somme du kernel appliquée à chaque composante de couleur d'un pixel
  float sum[color_component_count];

  // itération sur les rangées des pixels de l'image source
  for (y = 0; y < image_height; ++y)
  {
    // itération sur les colonnes des pixels de l'image source
    for (x = 0; x < image_width; ++x)
    {
      // initialiser le tableau où les valeurs de filtrage sont accumulées
      for (c = 0; c < color_component_count; ++c)
        sum[c] = 0;

      // déterminer l'index du pixel de l'image de destination
      pixel_index_img_dst = (image_width * y + x) * color_component_count;

      // itération sur les colonnes du kernel de convolution
      for (j = -kernel_offset; j <= kernel_offset; ++j)
      {
        // itération sur les rangées du kernel de convolution
        for (i = -kernel_offset; i <= kernel_offset; ++i)
        {
          // calculer les indices d'échantillonnage
          xi = x - i;
          yj = y - j;

          // traitement de la bordure
          if (xi < 0 || xi > image_width || yj < 0 || yj > image_height)
            continue;

          // déterminer l'index du pixel de l'image source à lire
          pixel_index_img_src = (image_width * yj + xi) * color_component_count;

          // lire la couleur du pixel de l'image source
          pixel_color_src = pixel_array_src.getColor(pixel_index_img_src);

          // déterminer l'indice du facteur à lire dans le kernel de convolution
          kernel_index = kernel_size * (j + kernel_offset) + (i + kernel_offset);

          // extraction de la valeur à cet index du kernel
          switch (kernel_type)
          {
            case ConvolutionKernel::identity:
              kernel_value = convolution_kernel_identity.at(kernel_index);
              break;

            case ConvolutionKernel::emboss:
              kernel_value = convolution_kernel_emboss.at(kernel_index);
              break;

            case ConvolutionKernel::sharpen:
              kernel_value = convolution_kernel_sharpen.at(kernel_index);
              break;

            case ConvolutionKernel::edge_detect:
              kernel_value = convolution_kernel_edge_detect.at(kernel_index);
              break;

            case ConvolutionKernel::blur:
              kernel_value = convolution_kernel_blur.at(kernel_index);
              break;

            default:
              kernel_value = convolution_kernel_identity.at(kernel_index);
              break;
          }

          // itération sur les composantes de couleur
          for (c = 0; c < color_component_count; ++c)
          {
            // accumuler les valeurs de filtrage en fonction du kernel de convolution
            sum[c] = sum[c] + kernel_value * pixel_color_src[c];
          }
        }
      }

      // déterminer la couleur du pixel à partir des valeurs de filtrage accumulées pour chaque composante
      for (c = 0; c < color_component_count; ++c)
      {
        // conversion vers entier et validation des bornes de l'espace de couleur
        pixel_color_dst[c] = (int) ofClamp(sum[c], 0, 255);
      }

      // écrire la couleur à l'index du pixel en cours de filtrage
      pixel_array_dst.setColor(pixel_index_img_dst, pixel_color_dst);
    }
  }

  // écrire les pixels dans l'image de destination
  filteredImage.setFromPixels(pixel_array_dst);
}

void GestionImages::changeFilter(int newFilter) {
    switch (newFilter) {
    case 0:
        kernel_type = identity;
        break;
    case 1: 
        kernel_type = emboss;
        break;
    case 2:
        kernel_type = sharpen;
        break;
    case 3:
        kernel_type = edge_detect;
        break;
    case 4:
        kernel_type = blur;
        break;
    }
    filter();
}

void GestionImages::change_gamma(float newGamma) {
    tone_mapping_gamma = newGamma;
}

void GestionImages::change_exposure(float newExposure) {
    tone_mapping_exposure = newExposure;
}

//------------------------------------------------------------------------------
//GESTION TEXTURES
