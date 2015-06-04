#pragma once

#include "Entity.h"

class RenderGroup
{
public:
	RenderGroup();
	~RenderGroup();

	void Draw(ID3D11Device* device, ID3D11DeviceContext* device_context) const;

private:
	std::vector<Entity> entities;
	std::vector<RenderGroup> render_groups;
};

