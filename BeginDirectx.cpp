#include "BeginDirectx.h"


VRBackendBasics BeginDirectx(bool use_oculus, std::string resource_location) {
	VRBackendBasics graphics_objects;
	graphics_objects.oculus = new Oculus;
	graphics_objects.input_handler = new InputHandler;
	graphics_objects.view_state = new ViewState;
	graphics_objects.resource_pool = new ResourcePool;
	graphics_objects.world = new World(graphics_objects.view_state);
	graphics_objects.player_camera = new PerspectiveCamera;
	graphics_objects.entity_handler = new EntityHandler;

	// Initialize the oculus resources and inject them
	if (use_oculus) {
		graphics_objects.oculus->Initialize();
		graphics_objects.input_handler->SetOculusState(graphics_objects.oculus);
		graphics_objects.render_pipeline = new ToOculusRenderingPipeline;
	}
	else {
		graphics_objects.render_pipeline = new ToScreenRenderingPipeline;
	}

	graphics_objects.input_handler->Initialize();
	graphics_objects.view_state->Initialize(GetModuleHandle(NULL), SW_SHOW);
	graphics_objects.resource_pool->Initialize(graphics_objects.view_state->device_interface, graphics_objects.view_state->device_context);
	graphics_objects.entity_handler->Initialize(graphics_objects.resource_pool);

	if (use_oculus) {
		dynamic_cast<ToOculusRenderingPipeline*>(graphics_objects.render_pipeline)->Initialize(graphics_objects.view_state, graphics_objects.world, graphics_objects.input_handler, resource_location, graphics_objects.oculus);
	}
	else {
		graphics_objects.render_pipeline->Initialize(graphics_objects.view_state, graphics_objects.world, graphics_objects.input_handler, resource_location);
	}

	graphics_objects.player_camera->vertical_fov = 120.0f / 180.0f * 3.1415f;
	graphics_objects.player_camera->aspect_ratio = ((float)graphics_objects.view_state->window_details.screen_size[0]) / graphics_objects.view_state->window_details.screen_size[1];

	graphics_objects.world->Initialize(graphics_objects.input_handler, graphics_objects.resource_pool, graphics_objects.entity_handler);

	
	return graphics_objects;
}
