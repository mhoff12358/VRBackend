#pragma once

#include "Entity.h"

class RenderGroup
{
public:
	RenderGroup();
	~RenderGroup();

	void Draw(ID3D11Device* device, ID3D11DeviceContext* device_context);
	void Update(RenderGroup* other);

	void ExpandTo(unsigned int required_size);

	std::vector<Entity> entities;
};

