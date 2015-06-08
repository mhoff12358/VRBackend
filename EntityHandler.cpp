#include "EntityHandler.h"


EntityHandler::EntityHandler()
{
}


EntityHandler::~EntityHandler()
{
}

void EntityHandler::Initialize(ResourcePool* rp) {
	resource_pool = rp;

	current_edit_group = entity_buffers.Initialize();
}

RenderGroup* EntityHandler::GetRenderGroupForDrawing() {
	return entity_buffers.ConsumerFinish();
}

void EntityHandler::FinishUpdate() {
	current_edit_group = entity_buffers.ProducerFinish();
}

unsigned int EntityHandler::AddEntity(Entity new_entity) {
	current_edit_group->entities.push_back(new_entity);
	entity_map.push_back(current_edit_group->entities.size() - 1);
	return entity_map.size() - 1;
}

void EntityHandler::RemoveEntity(unsigned int entity_id) {
	unsigned int entity_offset = entity_map[entity_id];
	current_edit_group->entities[entity_offset].status = (EntityStatusFlags)(ES_DELETED | current_edit_group->entities[entity_offset].status);
}