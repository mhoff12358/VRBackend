#pragma once

#include <D3D11.h>
#include <DirectXMath.h>

#define PER_FRAME_CONSTANT_BUFFER_REGISTER 0
#define PER_MODEL_CONSTANT_BUFFER_REGISTER 1
// Per batch constant buffers can use registers 2+
#define PER_BATCH_CONSTANT_BUFFER_REGISTER 2

enum CB_PIPELINE_STAGES : unsigned char {
	CB_PS_VERTEX_SHADER = 0x1,
	CB_PS_PIXEL_SHADER = 0x2,
};

struct TransformationMatrixData {
	DirectX::XMFLOAT4X4 transformation;
};

struct TransformationMatrixAndInvTransData {
	DirectX::XMFLOAT4X4 transformation;
	DirectX::XMFLOAT4X4 transformation_inv_trans;
};

class ConstantBuffer
{
public:
	ConstantBuffer(CB_PIPELINE_STAGES stages);
	~ConstantBuffer();

	void SetPipelineStages(CB_PIPELINE_STAGES stages);

	void CreateBuffer(ID3D11Device* device_interface);
	void PushBuffer(ID3D11DeviceContext* device_context);

	virtual void* GetBufferData() = 0;
	virtual unsigned int GetBufferDataSize() = 0;

	void Prepare(ID3D11Device* device, ID3D11DeviceContext* device_context, int buffer_register) const;

private:
	ID3D11Buffer* const_buffer;
	CB_PIPELINE_STAGES pipeline_stages;
};


template <typename ConstantBufferData>
class ConstantBufferTypedTemp : public ConstantBuffer {
public:
	ConstantBufferTypedTemp(CB_PIPELINE_STAGES stages) : ConstantBuffer(stages) {}

	void* GetBufferData();
	unsigned int GetBufferDataSize();
	ConstantBufferData& GetBufferDataRef();

protected:
	ConstantBufferData buffer_data;
};

template <typename ConstantBufferData>
ConstantBufferData& ConstantBufferTypedTemp<ConstantBufferData>::GetBufferDataRef() {
	return buffer_data;
}

template <typename ConstantBufferData>
unsigned int ConstantBufferTypedTemp<ConstantBufferData>::GetBufferDataSize() {
	return sizeof(ConstantBufferData);
}

template <typename ConstantBufferData>
void* ConstantBufferTypedTemp<ConstantBufferData>::GetBufferData() {
	return (void*)&buffer_data;
}

template <typename ConstantBufferData>
class ConstantBufferTyped : public ConstantBufferTypedTemp < ConstantBufferData > {

};

template <>
class ConstantBufferTyped<TransformationMatrixData> : public ConstantBufferTypedTemp<TransformationMatrixData>{
public:
	ConstantBufferTyped(CB_PIPELINE_STAGES stages) : ConstantBufferTypedTemp(stages) {}

	void XM_CALLCONV SetTransformation(DirectX::FXMMATRIX new_transformation);
};

template <>
class ConstantBufferTyped<TransformationMatrixAndInvTransData> : public ConstantBufferTypedTemp<TransformationMatrixAndInvTransData>{
public:
	ConstantBufferTyped(CB_PIPELINE_STAGES stages) : ConstantBufferTypedTemp(stages) {}

	void XM_CALLCONV SetBothTransformations(DirectX::FXMMATRIX new_transformation);
	void XM_CALLCONV SetTransformation(DirectX::FXMMATRIX new_transformation);
	void XM_CALLCONV SetTransformationInvTrans(DirectX::FXMMATRIX new_transformation_inv_trans);
};