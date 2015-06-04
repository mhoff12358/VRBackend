#pragma once

#include <D3D11.h>

class Model
{
public:
	Model();
	~Model();

	void Prepare(ID3D11Device* device, ID3D11DeviceContext* device_context);

private:
	ID3D11Buffer* vertex_buffer;
	UINT stride;
	UINT offset;
	UINT num_vertices;
	D3D_PRIMITIVE_TOPOLOGY primitive_type;
};


class ModelSlice
{
public:
	ModelSlice(unsigned int num_vertices, unsigned int first_vertex);

	unsigned int length;
	unsigned int start;
};