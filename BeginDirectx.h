
#pragma once

#include <string>
#include <iostream>

#include "Oculus.h"
#include "RenderingPipeline.h"
#include "InputHandler.h"
#include "ViewState.h"
#include "EntityHandler.h"

struct VRBackendBasics {
	Oculus* oculus;
	InputHandler* input_handler;
	RenderingPipeline* render_pipeline;
	ViewState* view_state;
	ResourcePool* resource_pool;
	EntityHandler* entity_handler;
	World* world;
	PerspectiveCamera* player_camera;
} typedef VRBackendBasics;

VRBackendBasics BeginDirectx(bool use_oculus, std::string resource_location);