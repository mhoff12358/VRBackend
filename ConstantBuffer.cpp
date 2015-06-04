#include "ConstantBuffer.h"


ConstantBuffer::ConstantBuffer()
{
}


ConstantBuffer::~ConstantBuffer()
{
}

void ConstantBuffer::Prepare(ID3D11Device* device, ID3D11DeviceContext* device_context, int buffer_register) {
	if ((0x1 & pipeline_stages) != 0) {
		device_context->VSSetConstantBuffers(buffer_register, 1, &const_buffer);
	}
	if ((0x2 & pipeline_stages) != 0) {
		device_context->PSSetConstantBuffers(buffer_register, 1, &const_buffer);
	}
}