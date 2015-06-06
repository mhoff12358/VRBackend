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

	unsigned int AddEntity();
	void RemoveEntity(unsigned int entity_id);
	
	//template <typename T>
	//T* 

private:
	ResourcePool* resource_pool;

	// Stores a mapping of index in the entity_map to index in the RenderGroup
	std::vector<unsigned int> entity_map;

	AsyncEntityBuffer entity_buffers;
};

