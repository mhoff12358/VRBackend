#ifndef __WORLD_H_INCLUDED__
#define __WORLD_H_INCLUDED__

#include <array>
#include <map>

#include "PerspectiveCamera.h"
#include "InputHandler.h"
#include "ViewState.h"
#include "Model.h"
#include "ConstantBuffer.h"
#include "RenderMode.h"
#include "Texture.h"
#include "Vertices.h"
#include "ResourcePool.h"
#include "RenderGroup.h"
#include "EntityHandler.h"

class World {
public:
	World(ViewState* vs);

	void Initialize(InputHandler* ih, ResourcePool* rp, EntityHandler* eh);

	void UpdateLogic(int time_delta);

	void Draw(RenderMode& render_mode);

	std::array<float, 3> GetPlayerLocation();
	std::array<float, 4> GetPlayerOrientation();

	D3DXCOLOR GetScreenColor();

private:
	ViewState* view_state;
	InputHandler* input_handler;
	ResourcePool* resource_pool;
	EntityHandler* entity_handler;

	RenderGroup root_render_group;

	std::array<float, 3> player_location;
	std::array<float, 4> player_orientation;
};

#endif