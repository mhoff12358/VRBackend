#include "World.h"

World::World(ViewState* vs) : view_state(vs) {
};

void World::Initialize(InputHandler* ih, ResourcePool* rp, EntityHandler* eh) {
	input_handler = ih;
	resource_pool = rp;
	entity_handler = eh;

	player_location = { { 0.0f, 0.0f, 0.0f } };
	player_orientation = { { 0.0f, 0.0f, 0.0f, 0.0f } };
}

void World::UpdateLogic(int time_delta) {
	if (input_handler->IsOculusActive()) {
		ovrPosef head_pose = input_handler->GetHeadPose().ThePose;
		player_orientation = OculusHelper::ConvertQuaternionToArray(head_pose.Orientation);
	}
}

void World::Draw(RenderMode& render_mode) {
	root_render_group.Draw(view_state->device_interface, view_state->device_context);
	for (Entity& entity : entity_handler->GetRenderGroupForDrawing()->entities) {
		entity.Draw(view_state->device_interface, view_state->device_context);
	}
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