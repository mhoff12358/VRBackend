#include "RenderGroup.h"


RenderGroup::RenderGroup()
{
}

RenderGroup::~RenderGroup()
{
}

void RenderGroup::Draw(ID3D11Device* device, ID3D11DeviceContext* device_context) const {
	for (const RenderGroup& child_group : render_groups) {
		child_group.Draw(device, device_context);
	}
	for (const Entity& child_entity : entities) {
		child_entity.Draw(device, device_context);
	}
}