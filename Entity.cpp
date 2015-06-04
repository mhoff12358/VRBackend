#include "Entity.h"


Entity::Entity()
{
}


Entity::~Entity()
{
}

void Entity::Draw(ID3D11Device* device, ID3D11DeviceContext* device_context) {
	pixel_shader.Prepare(device, device_context);
	vertex_shader.Prepare(device, device_context);
	shader_settings.Prepare(device, device_context);
	model.Prepare(device, device_context);

	device_context->Draw(model_slice.length, model_slice.start);
}