#pragma once

#include "Vertices.h"
#include "Model.h"

class ModelGenerator {
public:
	ModelGenerator(VertexType v_type, D3D_PRIMITIVE_TOPOLOGY p_type);
	virtual ~ModelGenerator() {};

	void AddVertex(Vertex new_vertex);
	void AddVertexBatch(std::vector<Vertex>& new_vertexes);

	Model DumpModel(ID3D11Device* device, ID3D11DeviceContext* device_context);

private:
	std::vector<Vertex> vertices;
	ID3D11Buffer* vertex_buffer;
	VertexType vertex_type;
	D3D_PRIMITIVE_TOPOLOGY primitive_type;

	void InitializeVertexBuffer(ID3D11Device* device, ID3D11DeviceContext* device_context);
};