#include "Model.h"
#include "ResourcePool.h"

Model::Model()
{
}

Model::~Model()
{
}

void Model::Prepare(ID3D11Device* device, ID3D11DeviceContext* device_context) {
	device_context->IASetVertexBuffers(0, 1, &vertex_buffer, &stride, &offset);
	device_context->IASetPrimitiveTopology(primitive_type);
}
