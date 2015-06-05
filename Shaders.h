#pragma once

#include <D3D11.h>

class VertexShader
{
public:
	VertexShader();
	VertexShader(ID3D11InputLayout* il, ID3D11VertexShader* vs);

	void Prepare(ID3D11Device* device, ID3D11DeviceContext* device_context) const;
	bool IsDummy() const;

private:
	ID3D11InputLayout* input_layout;
	ID3D11VertexShader* vertex_shader;
};

class PixelShader
{
public:
	PixelShader();
	PixelShader(ID3D11PixelShader* ps);

	void Prepare(ID3D11Device* device, ID3D11DeviceContext* device_context) const;
	bool IsDummy() const;

private:
	ID3D11PixelShader* pixel_shader;
};
