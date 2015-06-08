#include "Model.h"
#include "ResourcePool.h"

Model::Model()
	: vertex_buffer(NULL), slice(0, 0)
{
}

Model::Model(ID3D11Buffer* vb, UINT st, UINT off, UINT num_vert, D3D_PRIMITIVE_TOPOLOGY prim_type, ModelSlice ms)
	: vertex_buffer(vb), stride(st), offset(off), num_vertices(num_vert), primitive_type(prim_type), slice(ms) {

}

Model::~Model()
{
}

void Model::Prepare(ID3D11Device* device, ID3D11DeviceContext* device_context) const {
	if (!IsDummy()) {
		device_context->IASetVertexBuffers(0, 1, &vertex_buffer, &stride, &offset);
		device_context->IASetPrimitiveTopology(primitive_type);
	}
}

bool Model::IsDummy() const {
	return vertex_buffer == NULL;
}
