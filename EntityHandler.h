#pragma once

#include "RenderGroup.h"
#include "AsyncEntityBuffer.h"
#include "Entity.h"

class EntityHandler
{
public:
	EntityHandler();
	~EntityHandler();

	// Rendering accessors
	RenderGroup* GetRenderGroupForDrawing();

	// Update loop updaters
	void AddEntity();
	void RemoveEntity();
};

