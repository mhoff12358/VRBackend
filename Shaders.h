#pragma once

#include <D3D11.h>

class VertexShader
{
public:
	void Prepare(ID3D11Device* device, ID3D11DeviceContext* device_context);

private:
	ID3D11InputLayout* input_layout;
	ID3D11VertexShader* vertex_shader;
};

class PixelShader
{
public:
	void Prepare(ID3D11Device* device, ID3D11DeviceContext* device_context);

private:
	ID3D11PixelShader* pixel_shader;
};
