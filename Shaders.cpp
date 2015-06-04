#include "Shaders.h"

void VertexShader::Prepare(ID3D11Device* device, ID3D11DeviceContext* device_context) {
	device_context->VSSetShader(vertex_shader, NULL, 0);
	device_context->IASetInputLayout(input_layout);
}

void PixelShader::Prepare(ID3D11Device* device, ID3D11DeviceContext* device_context) {
	device_context->PSSetShader(pixel_shader, NULL, 0);
}
