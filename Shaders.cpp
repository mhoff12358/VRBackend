#include "Shaders.h"

VertexShader::VertexShader()
	: input_layout(NULL), vertex_shader(NULL) {

}

VertexShader::VertexShader(ID3D11InputLayout* il, ID3D11VertexShader* vs)
	: input_layout(il), vertex_shader(vs) {

}

void VertexShader::Prepare(ID3D11Device* device, ID3D11DeviceContext* device_context) const {
	if (!IsDummy()) {
		device_context->VSSetShader(vertex_shader, NULL, 0);
		device_context->IASetInputLayout(input_layout);
	}
}

bool VertexShader::IsDummy() const {
	return vertex_shader == NULL;
}

PixelShader::PixelShader()
	: pixel_shader(NULL) {

}

PixelShader::PixelShader(ID3D11PixelShader* ps)
	: pixel_shader(ps) {

}

void PixelShader::Prepare(ID3D11Device* device, ID3D11DeviceContext* device_context) const {
	if (!IsDummy()) {
		device_context->PSSetShader(pixel_shader, NULL, 0);
	}
}

bool PixelShader::IsDummy() const {
	return pixel_shader == NULL;
}