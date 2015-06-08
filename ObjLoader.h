#pragma once

#include <fstream>
#include <vector>
#include <array>

#include "Model.h"
#include "ModelGenerator.h"
#include "Vertices.h"

class ObjLoader
{
public:
	static Model CreateModel(ID3D11Device* device, ID3D11DeviceContext* device_context, std::string filename);
	static VertexType vertex_type;

	ObjLoader(std::string filename);

	Model DumpModel(ID3D11Device* device, ID3D11DeviceContext* device_context);

	Vertex CreateVertex(std::string vertex_id);
	Vertex CreateVertex(std::string location_str, std::string texture_coords_str, std::string normal_str);
	Vertex CreateVertexFromAll(int location_ref, int texture_coords_ref, int normal_ref);
	Vertex CreateVertexFromTexture(int location_ref, int texture_coords_ref);
	Vertex CreateVertexFromNormal(int location_ref, int normal_ref);
	Vertex CreateVertexFromLocation(int location_ref);

private:
	std::ifstream input_file;

	std::vector<std::array<float, 3>> locations;
	std::vector<std::array<float, 2>> texture_coords;
	std::vector<std::array<float, 3>> normals;
};

