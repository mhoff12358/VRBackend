#pragma once

#include "RenderGroup.h"
#include "AsyncEntityBuffer.h"
#include "Entity.h"
#include "ResourcePool.h"

class EntityHandler
{
public:
	EntityHandler();
	~EntityHandler();

	void Initialize(ResourcePool* rp);

	// Rendering accessors
	RenderGroup* GetRenderGroupForDrawing();

	// Update loop updaters
	void FinishUpdate();

	unsigned int AddEntity(Entity new_entity);
	void RemoveEntity(unsigned int entity_id);
	
	template <typename T>
	void SetEntityObjectSettings(unsigned int entity_id, const T& new_settings);

	template <typename T>
	ConstantBufferTyped<T>* GetEntityObjectSettings(unsigned int entity_id);

private:
	ResourcePool* resource_pool;

	// Stores a mapping of index in the entity_map to index in the RenderGroup
	std::vector<unsigned int> entity_map;

	AsyncEntityBuffer entity_buffers;
	RenderGroup* current_edit_group;
};

template <typename T>
ConstantBufferTyped<T>* EntityHandler::GetEntityObjectSettings(unsigned int entity_id) {
	return dynamic_cast<ConstantBufferTyped<T>*>(current_edit_group->entities[entity_id].object_settings);
}

template <typename T>
void EntityHandler::SetEntityObjectSettings(unsigned int entity_id, const T& new_settings) {
	*dynamic_cast<T*>(current_edit_group->entities[entity_id].object_settings->EditBufferData()) = new_settings;
}