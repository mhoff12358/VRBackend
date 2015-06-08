#pragma once

#include <D3D11.h>

#include "ModelSlice.h"

class Model
{
public:
	Model();
	Model(ID3D11Buffer* vb, UINT st, UINT off, UINT num_vert, D3D_PRIMITIVE_TOPOLOGY prim_type, ModelSlice ms);
	~Model();

	void Prepare(ID3D11Device* device, ID3D11DeviceContext* device_context) const;
	bool IsDummy() const;

	ModelSlice slice;

private:
	ID3D11Buffer* vertex_buffer;
	UINT stride;
	UINT offset;
	UINT num_vertices;
	D3D_PRIMITIVE_TOPOLOGY primitive_type;
};

