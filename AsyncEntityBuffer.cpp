#include "AsyncEntityBuffer.h"


AsyncEntityBuffer::AsyncEntityBuffer()
{
	writing_group = groups;
	new_reading_group = groups + 1;
	old_reading_group = groups + 2;
}


AsyncEntityBuffer::~AsyncEntityBuffer()
{
}

RenderGroup* AsyncEntityBuffer::ProducerFinish() {
	state_ownership_lock.lock();
	// Mark W as N
	RenderGroup* previous_new_reading_group = new_reading_group;
	new_reading_group = writing_group;

	if (reader_on_new) {
		// Mark O as W and N as O
		writing_group = old_reading_group;
		old_reading_group = previous_new_reading_group;
		reader_on_new = false;
	} else {
		// Mark N as W
		writing_group = previous_new_reading_group;
	}
	state_ownership_lock.unlock();

	// Copy the contents of the old writing group (now the new reading group)
	// to the new writing group
	writing_group->Update(new_reading_group);
	return writing_group;
}

RenderGroup* AsyncEntityBuffer::ConsumerFinish() {
	state_ownership_lock.lock();
	// Claim the current new reading group
	reader_on_new = true;
	RenderGroup* returned_group = new_reading_group;
	state_ownership_lock.unlock();
	return returned_group;
}