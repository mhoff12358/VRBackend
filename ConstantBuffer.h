#pragma once

#include <D3D11.h>

class ConstantBuffer
{
public:
	ConstantBuffer();
	~ConstantBuffer();

	void Prepare(ID3D11Device* device, ID3D11DeviceContext* device_context, int buffer_register);

private:
	ID3D11Buffer* const_buffer;
	char pipeline_stages;
};

