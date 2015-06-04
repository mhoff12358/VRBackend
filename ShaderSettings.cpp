#include "ShaderSettings.h"


ShaderSettings::ShaderSettings()
{
}


ShaderSettings::~ShaderSettings()
{
}

void ShaderSettings::Prepare(ID3D11Device* device, ID3D11DeviceContext* device_context) {
	constant_buffer.Prepare(device, device_context, buffer_register);
}