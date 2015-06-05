#pragma once

#include "Model.h"
#include "Shaders.h"
#include "Vertices.h"
#include "ModelGenerator.h"

#include <vector>
#include <utility>
#include <map>

class ResourcePool
{
public:
	ResourcePool();
	~ResourcePool();

	void Initialize(ID3D11Device* dev, ID3D11DeviceContext* dev_con);

	Model LoadModel(std::string file_name);
	Model LoadModel(std::string model_name, std::vector<Vertex> vertices, D3D_PRIMITIVE_TOPOLOGY primitive_type);

	PixelShader LoadPixelShader(std::string file_name);
	PixelShader LoadPixelShader(std::string file_name, std::string function_name);

	VertexShader LoadVertexShader(std::string file_name, D3D11_INPUT_ELEMENT_DESC ied[], int ied_size);
	VertexShader LoadVertexShader(std::string file_name, std::string function_name, D3D11_INPUT_ELEMENT_DESC ied[], int ied_size);

private:
	ID3D11Device* device_interface;
	ID3D11DeviceContext* device_context;

	std::vector<Model> models;
	std::map<std::string, unsigned int> model_lookup;
	std::vector<PixelShader> pixel_shaders;
	std::map<std::string, unsigned int> pixel_shader_lookup;
	std::vector<VertexShader> vertex_shaders;
	std::map<std::string, unsigned int> vertex_shader_lookup;
};

