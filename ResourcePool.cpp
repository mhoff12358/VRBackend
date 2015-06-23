#include "ResourcePool.h"


ResourcePool::ResourcePool()
{
}


ResourcePool::~ResourcePool()
{
}


void ResourcePool::Initialize(ID3D11Device* dev, ID3D11DeviceContext* dev_con) {
	device_interface = dev;
	device_context = dev_con;
}

Model ResourcePool::LoadModel(std::string model_name, std::vector<Vertex> vertices, D3D_PRIMITIVE_TOPOLOGY primitive_type) {
	auto existing_model = model_lookup.find(model_name);
	if (existing_model != model_lookup.end()) {
		return models[existing_model->second];
	}

	if (vertices.empty()) {
		return Model(); // Somehow return an empty model eventually
	}

	ModelGenerator generator(vertices[0].GetVertexType(), primitive_type);
	generator.AddVertexBatch(vertices);
	Model new_model = generator.DumpModel(device_interface, device_context);

	models.push_back(new_model);
	model_lookup[model_name] = models.size() - 1;
	
	return new_model;
}

Model ResourcePool::LoadModel(std::string file_name) {
	auto existing_model = model_lookup.find(file_name);
	if (existing_model != model_lookup.end()) {
		return models[existing_model->second];
	}

	Model new_model = ObjLoader::CreateModel(device_interface, device_context, file_name);
	return new_model;
}

PixelShader ResourcePool::LoadPixelShader(std::string file_name) {
	return LoadPixelShader(file_name, "PShader");
}

PixelShader ResourcePool::LoadPixelShader(std::string file_name, std::string function_name) {
	auto existing_pixel_shader = pixel_shader_lookup.find(file_name);
	if (existing_pixel_shader != pixel_shader_lookup.end()) {
		return pixel_shaders[existing_pixel_shader->second];
	}

	ID3D11PixelShader* new_dx_pixel_shader;
	ID3D10Blob* pixel_shader_blob;
	D3DX11CompileFromFile(file_name.c_str(), 0, 0, function_name.c_str(), "ps_5_0", 0, 0, 0, &pixel_shader_blob, 0, 0);
	device_interface->CreatePixelShader(pixel_shader_blob->GetBufferPointer(), pixel_shader_blob->GetBufferSize(), NULL, &new_dx_pixel_shader);

	PixelShader new_pixel_shader(new_dx_pixel_shader);

	pixel_shaders.push_back(new_pixel_shader);
	pixel_shader_lookup[file_name] = pixel_shaders.size() - 1;

	return new_pixel_shader;
}

VertexShader ResourcePool::LoadVertexShader(std::string file_name, VertexType vertex_type) {
	return LoadVertexShader(file_name, vertex_type.GetVertexType(), vertex_type.GetSizeVertexType());
}

VertexShader ResourcePool::LoadVertexShader(std::string file_name, D3D11_INPUT_ELEMENT_DESC ied[], int ied_size) {
	return LoadVertexShader(file_name, "VShader", ied, ied_size);
}

VertexShader ResourcePool::LoadVertexShader(std::string file_name, std::string function_name, D3D11_INPUT_ELEMENT_DESC ied[], int ied_size) {
	auto existing_vertex_shader = vertex_shader_lookup.find(file_name);
	if (existing_vertex_shader != vertex_shader_lookup.end()) {
		return vertex_shaders[existing_vertex_shader->second];
	}

	ID3D11VertexShader* new_dx_vertex_shader;
	ID3D11InputLayout* new_dx_input_layout;
	ID3D10Blob* vertex_shader_blob;
	D3DX11CompileFromFile(file_name.c_str(), 0, 0, function_name.c_str(), "vs_5_0", 0, 0, 0, &vertex_shader_blob, 0, 0);
	device_interface->CreateVertexShader(vertex_shader_blob->GetBufferPointer(), vertex_shader_blob->GetBufferSize(), NULL, &new_dx_vertex_shader);
	HandleHResult(device_interface->CreateInputLayout(ied, ied_size, vertex_shader_blob->GetBufferPointer(), vertex_shader_blob->GetBufferSize(), &new_dx_input_layout));

	VertexShader new_vertex_shader(new_dx_input_layout, new_dx_vertex_shader);

	vertex_shaders.push_back(new_vertex_shader);
	vertex_shader_lookup[file_name] = vertex_shaders.size() - 1;

	return new_vertex_shader;
}