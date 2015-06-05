#pragma once

class ModelSlice
{
public:
	ModelSlice(unsigned int num_vertices, unsigned int first_vertex);

	unsigned int length;
	unsigned int start;
};