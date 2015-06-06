#include "RenderGroup.h"


RenderGroup::RenderGroup()
{
}

RenderGroup::~RenderGroup()
{
}

void RenderGroup::Update(RenderGroup* other) {
	entities = other->entities;
}

void RenderGroup::Draw(ID3D11Device* device, ID3D11DeviceContext* device_context) {
	for (Entity& entity : entities) {
		entity.Draw(device, device_context);
	}
}