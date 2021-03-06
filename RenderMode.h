#ifndef __RENDER_MODE_H_INCLUDED__
#define __RENDER_MODE_H_INCLUDED__

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")

#include <string>
#include <vector>
#include <array>
#include "Model.h"
#include "ConstantBuffer.h"

class RenderMode {
public:
	void Initialize(ID3D11Device* dev, ID3D11DeviceContext* dev_con, ID3D11RenderTargetView* rend_tar_view, ID3D11DepthStencilView* dep_sten_view, D3D11_VIEWPORT view);
	void Initialize(ID3D11Device* dev, ID3D11DeviceContext* dev_con, ID3D11RenderTargetView* rend_tar_view, ID3D11DepthStencilView* dep_sten_view);
	void SetViewport(D3D11_VIEWPORT view);
	void SetViewport(std::array<int, 2> offset, std::array<int, 2> size, std::array<float, 2> depth_range);
	void SetViewport(std::array<int, 2> size, std::array<float, 2> depth_range);
	void SetViewport(int xoff, int yoff, int width, int height, float min_depth, float max_depth);
	void SetViewport(int width, int height, float min_depth, float max_depth);

	void Cleanup();

	void Prepare();

	void Clear(D3DXCOLOR color);

private:
	ID3D11Device* device;
	ID3D11DeviceContext* device_context;

	ID3D11RenderTargetView* render_target_view;
	ID3D11DepthStencilView* depth_stencil_view;
	D3D11_VIEWPORT viewport;
};

#endif