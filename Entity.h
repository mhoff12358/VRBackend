#pragma once

#include "RenderResource.h"
#include "Model.h"
#include "ShaderSettings.h"
#include "Shaders.h"
#include "ConstantBuffer.h"
#include "ModelSlice.h"

#include <vector>

class Entity
{
public:
	Entity(PixelShader ps, VertexShader vs, ShaderSettings ss, Model m, ModelSlice ms, ConstantBuffer* os);
	~Entity();

	void Draw(ID3D11Device* device, ID3D11DeviceContext* device_context) const;

private:
	PixelShader pixel_shader;
	VertexShader vertex_shader;
	ShaderSettings shader_settings;
	Model model;
	ModelSlice model_slice;
	ConstantBuffer* object_settings;
};
