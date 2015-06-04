#pragma once

#include "Model.h"
#include "Shaders.h"

#include <vector>

class ResourcePool
{
public:
	ResourcePool();
	~ResourcePool();

	Model CreateModel();
	PixelShader CreatePixelShader();
	VertexShader CreateVertexShader();

private:
	std::vector<Model> models;
	std::vector<PixelShader> pixel_shaders;
	std::vector<VertexShader> vertex_shaders;
};

