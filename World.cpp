#include "World.h"

World::World(ViewState* vs) : view_state(vs) {
};

void World::Initialize(InputHandler* ih, ResourcePool* rp, EntityHandler* eh) {
	input_handler = ih;
	resource_pool = rp;
	entity_handler = eh;

	player_location = { { 0.0f, 0.0f, 0.0f } };
	player_orientation = { { 0.0f, 0.0f, 0.0f, 0.0f } };

	VertexType vertex_type = common_vertex_types[1];
	ConstantBufferTyped<TransformationMatrixAndInvTransData>* object_settings = new ConstantBufferTyped<TransformationMatrixAndInvTransData>(CB_PS_VERTEX_SHADER);
	object_settings->CreateBuffer(view_state->device_interface);
	object_settings->SetBothTransformations(DirectX::XMMatrixTranslation(0, 0, -4));
	object_settings->PushBuffer(view_state->device_context);
	std::vector<Vertex> vertices;
	vertices.push_back(Vertex(vertex_type, { -1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f }));
	vertices.push_back(Vertex(vertex_type, { 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f }));
	vertices.push_back(Vertex(vertex_type, { -1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f }));
	vertices.push_back(Vertex(vertex_type, { 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f }));
	vertices.push_back(Vertex(vertex_type, { 1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f }));
	vertices.push_back(Vertex(vertex_type, { -1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f }));
	PixelShader ps = resource_pool->LoadPixelShader("shaders.hlsl");
	VertexShader vs = resource_pool->LoadVertexShader("shaders.hlsl", vertex_type.GetVertexType(), vertex_type.GetSizeVertexType());
	ShaderSettings ss(NULL);
	Model mod = resource_pool->LoadModel("square", vertices, D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	ModelSlice ms(vertices.size(), 0);
	root_render_group.entities.emplace_back(ES_NORMAL, ps, vs, ss, mod, ms, object_settings);
}

void World::UpdateLogic(int time_delta) {
	if (input_handler->IsOculusActive()) {
		ovrPosef head_pose = input_handler->GetHeadPose().ThePose;
		player_orientation = OculusHelper::ConvertQuaternionToArray(head_pose.Orientation);
	}
}

void World::Draw(RenderMode& render_mode) {
	root_render_group.Draw(view_state->device_interface, view_state->device_context);
}

std::array<float, 3> World::GetPlayerLocation() {
	return player_location;
}

std::array<float, 4> World::GetPlayerOrientation() {
	return player_orientation;
}

D3DXCOLOR World::GetScreenColor() {
	return D3DXCOLOR(0.25f, 0.5f, 1.0f, 1.0f);
}