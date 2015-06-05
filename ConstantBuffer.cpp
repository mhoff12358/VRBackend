#include "ConstantBuffer.h"


ConstantBuffer::ConstantBuffer(CB_PIPELINE_STAGES stages)
{
	SetPipelineStages(stages);
}


ConstantBuffer::~ConstantBuffer()
{
}

void ConstantBuffer::SetPipelineStages(CB_PIPELINE_STAGES stages) {
	pipeline_stages = stages;
}

void ConstantBuffer::CreateBuffer(ID3D11Device* device_interface) {
	D3D11_BUFFER_DESC const_buff_desc;
	const_buff_desc.ByteWidth = GetBufferDataSize();
	const_buff_desc.Usage = D3D11_USAGE_DYNAMIC;
	const_buff_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	const_buff_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	const_buff_desc.MiscFlags = 0;
	const_buff_desc.StructureByteStride = 0;

	// Create the subresource data that carries the buffer data
	D3D11_SUBRESOURCE_DATA sub_data;
	sub_data.pSysMem = GetBufferData();
	sub_data.SysMemPitch = 0;
	sub_data.SysMemSlicePitch = 0;

	device_interface->CreateBuffer(&const_buff_desc, &sub_data, &const_buffer);
}

void ConstantBuffer::PushBuffer(ID3D11DeviceContext* device_context) {
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));

	// Disables GPU access to the data
	device_context->Map(const_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	memcpy(mappedResource.pData, GetBufferData(), GetBufferDataSize());
	device_context->Unmap(const_buffer, 0);
}

void ConstantBuffer::Prepare(ID3D11Device* device, ID3D11DeviceContext* device_context, int buffer_register) const {
	if ((CB_PS_VERTEX_SHADER & pipeline_stages) != 0) {
		device_context->VSSetConstantBuffers(buffer_register, 1, &const_buffer);
	}
	if ((CB_PS_PIXEL_SHADER & pipeline_stages) != 0) {
		device_context->PSSetConstantBuffers(buffer_register, 1, &const_buffer);
	}
}

void XM_CALLCONV ConstantBufferTyped<TransformationMatrixData>::SetTransformation(DirectX::FXMMATRIX new_trasnformation) {
	DirectX::XMStoreFloat4x4(&buffer_data.transformation, new_trasnformation);
}

void XM_CALLCONV ConstantBufferTyped<TransformationMatrixAndInvTransData>::SetBothTransformations(DirectX::FXMMATRIX new_trasnformation) {
	DirectX::XMStoreFloat4x4(&buffer_data.transformation, new_trasnformation);
	DirectX::XMStoreFloat4x4(&buffer_data.transformation_inv_trans,
		DirectX::XMMatrixTranspose(DirectX::XMMatrixInverse(NULL, new_trasnformation)));
}

void XM_CALLCONV ConstantBufferTyped<TransformationMatrixAndInvTransData>::SetTransformation(DirectX::FXMMATRIX new_trasnformation) {
	DirectX::XMStoreFloat4x4(&buffer_data.transformation, new_trasnformation);
}

void XM_CALLCONV ConstantBufferTyped<TransformationMatrixAndInvTransData>::SetTransformationInvTrans(DirectX::FXMMATRIX new_transformation_inv_trans) {
	DirectX::XMStoreFloat4x4(&buffer_data.transformation_inv_trans, new_transformation_inv_trans);
}