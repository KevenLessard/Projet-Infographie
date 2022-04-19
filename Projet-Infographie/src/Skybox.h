#pragma once

#include "ofMain.h"

class Skybox {
public:
	Skybox();
	void setup(const std::vector<std::string>& faces);
	void draw(const ofEasyCam& camera);

private:
	unsigned int loadCubemap(std::vector<std::string> faces);
	void setSkyboxVAO();
	ofShader m_shader;
	GLuint m_cubemapTexture;
	unsigned int m_skyboxVAO;
};
