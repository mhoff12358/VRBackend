#include "Entity.h"


Entity::Entity(EntityStatusFlags stat, PixelShader ps, VertexShader vs, ShaderSettings ss, Model m, ConstantBuffer* os)
	: status(stat), object_settings(os), pixel_shader(ps), vertex_shader(vs),
	  shader_settings(ss), model(m)
{

}


Entity::~Entity()
{
}

void Entity::Prepare(ID3D11Device* device, ID3D11DeviceContext* device_context) {
	pixel_shader.Prepare(device, device_context);
	vertex_shader.Prepare(device, device_context);
	shader_settings.Prepare(device, device_context);
	model.Prepare(device, device_context);

	if (object_settings != NULL) {
		object_settings->PushBuffer(device_context);
		object_settings->Prepare(device, device_context, PER_MODEL_CONSTANT_BUFFER_REGISTER);
	}
}

void Entity::Draw(ID3D11Device* device, ID3D11DeviceContext* device_context) {
	// If this entity has any of the flags set that mean it shouldn't be drawn, don't draw it
	if ((status & (ES_DISABLED | ES_DELETED)) != 0) {
		return;
	}

	// Always prepare this Entity's settings
	Prepare(device, device_context);

	// Only attempt to draw the entity if its not a settings entity
	if ((status & ES_SETTINGS) == 0) {
		device_context->Draw(model.slice.length, model.slice.start);
	}
	else {

	}
}