#pragma once

#include "RenderResource.h"
#include "Model.h"
#include "ShaderSettings.h"
#include "Shaders.h"
#include "ConstantBuffer.h"
#include "ModelSlice.h"

#include <vector>

enum EntityStatusFlags : unsigned char {
	ES_NORMAL = 0x0,
	ES_SETTINGS = 0x1,
	ES_DISABLED = 0x2,
	ES_DELETED = 0x4,
};

class Entity
{
public:
	Entity(EntityStatusFlags stat, PixelShader ps, VertexShader vs, ShaderSettings ss, Model m, ModelSlice ms, ConstantBuffer* os);
	~Entity();

	void Draw(ID3D11Device* device, ID3D11DeviceContext* device_context);
	void Prepare(ID3D11Device* device, ID3D11DeviceContext* device_context);

	EntityStatusFlags status;

private:
	PixelShader pixel_shader;
	VertexShader vertex_shader;
	ShaderSettings shader_settings;
	Model model;
	ModelSlice model_slice;
	ConstantBuffer* object_settings;
};
