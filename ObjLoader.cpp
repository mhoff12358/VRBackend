#include "ObjLoader.h"

Model ObjLoader::CreateModel(ID3D11Device* device, ID3D11DeviceContext* device_context, std::string filename) {
	ObjLoader loader(filename);
	return loader.DumpModel(device, device_context);
}

VertexType ObjLoader::vertex_type = VertexType(std::vector<D3D11_INPUT_ELEMENT_DESC>({
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
}));

ObjLoader::ObjLoader(std::string filename)
	: input_file(filename) {

}

Model ObjLoader::DumpModel(ID3D11Device* device, ID3D11DeviceContext* device_context) {
	std::string line;

	ModelGenerator generator(ObjLoader::vertex_type, D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	while (std::getline(input_file, line)) {
		std::istringstream line_stream(line);

		std::string identifier;
		line_stream >> identifier;

		if (identifier == "v") {
			std::string x_str, y_str, z_str;
			line_stream >> x_str >> y_str >> z_str;
			locations.push_back(std::array<float, 3>({ { atof(x_str.c_str()), atof(y_str.c_str()), atof(z_str.c_str()) } }));
		}
		else if (identifier == "vn") {
			std::string x_str, y_str, z_str;
			line_stream >> x_str >> y_str >> z_str;
			normals.push_back(std::array<float, 3>({ { atof(x_str.c_str()), atof(y_str.c_str()), atof(z_str.c_str()) } }));
		}
		else if (identifier == "vt") {
			std::string u_str, v_str;
			line_stream >> u_str >> v_str;
			texture_coords.push_back(std::array<float, 2>({ { atof(u_str.c_str()), atof(v_str.c_str()) } }));
		}
		else if (identifier == "f") {
			std::vector<std::string> vertex_ids;
			std::string test_vertex_id;
			while (line_stream >> test_vertex_id) {
				vertex_ids.push_back(test_vertex_id);
			}
			for (int i = 1; i < vertex_ids.size() - 1; i++) {
				generator.AddVertex(CreateVertex(vertex_ids[0]));
				generator.AddVertex(CreateVertex(vertex_ids[i]));
				generator.AddVertex(CreateVertex(vertex_ids[i+1]));
				/*generator.AddVertex(Vertex(ObjLoader::vertex_type, { -1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f }));
				generator.AddVertex(Vertex(ObjLoader::vertex_type, { 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f }));
				generator.AddVertex(Vertex(ObjLoader::vertex_type, { -1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f }));
				generator.AddVertex(Vertex(ObjLoader::vertex_type, { 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f }));
				generator.AddVertex(Vertex(ObjLoader::vertex_type, { 1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f }));
				generator.AddVertex(Vertex(ObjLoader::vertex_type, { -1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f }));*/
			}
		}
	}

	Model new_model = generator.DumpModel(device, device_context);
	return new_model;
}

Vertex ObjLoader::CreateVertex(std::string vertex_id) {
	std::string location_id_str("");
	std::string tex_coord_id_str("");
	std::string normal_id_str("");

	size_t first_slash = vertex_id.find("/");
	if (first_slash == std::string::npos) {
		location_id_str = vertex_id;
	}
	else {
		location_id_str = vertex_id.substr(0, first_slash);
		size_t second_slash = vertex_id.find("/", first_slash + 1);
		if (second_slash == std::string::npos) {
			tex_coord_id_str = vertex_id.substr(first_slash + 1, vertex_id.length() - first_slash - 1);
		}
		else {
			tex_coord_id_str = vertex_id.substr(first_slash + 1, second_slash - first_slash - 1);
			normal_id_str = vertex_id.substr(second_slash + 1, vertex_id.length() - second_slash - 1);
		}
	}
	return CreateVertex(location_id_str, tex_coord_id_str, normal_id_str);
}

Vertex ObjLoader::CreateVertex(std::string location_str, std::string texture_coords_str, std::string normal_str) {
	if (texture_coords_str == "") {
		if (normal_str == "") {
			return CreateVertexFromLocation(atoi(location_str.c_str())-1);
		}
		return CreateVertexFromNormal(atoi(location_str.c_str())-1, atoi(normal_str.c_str())-1);
	}
	if (normal_str == "") {
		return CreateVertexFromTexture(atoi(location_str.c_str())-1, atoi(texture_coords_str.c_str())-1);
	}
	return CreateVertexFromAll(atoi(location_str.c_str())-1, atoi(texture_coords_str.c_str())-1, atoi(normal_str.c_str())-1);
}

Vertex ObjLoader::CreateVertexFromAll(int location_ref, int texture_coords_ref, int normal_ref) {
	std::vector<float> vector_data;
	vector_data.insert(vector_data.end(), locations[location_ref].begin(), locations[location_ref].end());
	vector_data.insert(vector_data.end(), texture_coords[texture_coords_ref].begin(), texture_coords[texture_coords_ref].end());
	vector_data.insert(vector_data.end(), normals[normal_ref].begin(), normals[normal_ref].end());
	return Vertex(ObjLoader::vertex_type, vector_data);
}

Vertex ObjLoader::CreateVertexFromTexture(int location_ref, int texture_coords_ref) {
	std::vector<float> vector_data;
	vector_data.insert(vector_data.end(), locations[location_ref].begin(), locations[location_ref].end());
	vector_data.insert(vector_data.end(), texture_coords[texture_coords_ref].begin(), texture_coords[texture_coords_ref].end());
	return Vertex(ObjLoader::vertex_type, vector_data);
}

Vertex ObjLoader::CreateVertexFromNormal(int location_ref, int normal_ref) {
	std::vector<float> vector_data;
	vector_data.insert(vector_data.end(), locations[location_ref].begin(), locations[location_ref].end());
	vector_data.insert(vector_data.end(), normals[normal_ref].begin(), normals[normal_ref].end());
	return Vertex(ObjLoader::vertex_type, vector_data);
}

Vertex ObjLoader::CreateVertexFromLocation(int location_ref) {
	std::vector<float> vector_data;
	vector_data.insert(vector_data.end(), locations[location_ref].begin(), locations[location_ref].end());
	return Vertex(ObjLoader::vertex_type, vector_data);
}