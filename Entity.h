#pragma once

#include "RenderResource.h"
#include "Model.h"
#include "ShaderSettings.h"
#include "Shaders.h"

#include <vector>

class Entity
{
public:
	Entity();
	~Entity();

	void Draw(ID3D11Device* device, ID3D11DeviceContext* device_context) const;

private:
	PixelShader pixel_shader;
	VertexShader vertex_shader;
	ShaderSettings shader_settings;
	Model model;
	ModelSlice model_slice;
};
