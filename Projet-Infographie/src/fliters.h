#pragma once

#include "ofMain.h"
#include <array>

//Types de kernel de convolution

enum class ConvolutionKernel
{
	identity,
	emboss,
	sharpen,
	edge_detect,
	blur
};
//Kernel d'identité:

class Filter
{
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

	void filter();
};