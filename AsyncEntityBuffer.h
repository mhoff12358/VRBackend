#pragma once

#include <mutex>

#include "RenderGroup.h"

class AsyncEntityBuffer
{
public:
	AsyncEntityBuffer();
	~AsyncEntityBuffer();

	RenderGroup* Initialize();

	// These two methods are called by the writer and consumer repsectively to
	// alert that they have finished with the RenderGroup they were using.
	RenderGroup* ProducerFinish();
	RenderGroup* ConsumerFinish();

private:
	std::mutex state_ownership_lock;

	RenderGroup groups[3];
	RenderGroup* writing_group;
	RenderGroup* new_reading_group;
	RenderGroup* old_reading_group;
	bool reader_on_new;
};

