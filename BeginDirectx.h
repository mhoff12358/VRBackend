
#pragma once

#include <string>
#include <iostream>

#include "Oculus.h"
#include "RenderingPipeline.h"
#include "InputHandler.h"
#include "ViewState.h"

struct VRBackendBasics {
	Oculus* oculus;
	InputHandler* input_handler;
	RenderingPipeline* render_pipeline;
	ViewState* view_state;
	ResourcePool* resource_pool;
	World* world;
	PerspectiveCamera* player_camera;
} typedef VRBackendBasics;

VRBackendBasics BeginDirectx(bool use_oculus, std::string resource_location);