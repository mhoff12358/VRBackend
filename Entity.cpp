#include "Entity.h"


Entity::Entity(PixelShader ps, VertexShader vs, ShaderSettings ss, Model m, ModelSlice ms, ConstantBuffer* os)
	: object_settings(os), pixel_shader(ps), vertex_shader(vs),
	  shader_settings(ss), model(m), model_slice(ms)
{

}


Entity::~Entity()
{
}

void Entity::Draw(ID3D11Device* device, ID3D11DeviceContext* device_context) const {
	pixel_shader.Prepare(device, device_context);
	vertex_shader.Prepare(device, device_context);
	shader_settings.Prepare(device, device_context);
	model.Prepare(device, device_context);

	if (object_settings != NULL) {
		object_settings->Prepare(device, device_context, PER_MODEL_CONSTANT_BUFFER_REGISTER);
	}

	if (model_slice.length != 0) {
		device_context->Draw(model_slice.length, model_slice.start);
	}
}