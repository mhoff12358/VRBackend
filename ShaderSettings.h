#pragma once

#include <D3D11.h>

#include "ConstantBuffer.h"

class ShaderSettings
{
public:
	ShaderSettings();
	ShaderSettings(ConstantBuffer* buffer);
	~ShaderSettings();

	void Prepare(ID3D11Device* device, ID3D11DeviceContext* device_context) const;
	bool IsDummy() const;

private:
	ConstantBuffer* constant_buffer;

	static const int buffer_register = 2;
};
