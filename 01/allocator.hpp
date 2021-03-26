#pragma once

#include <stdio.h>

class Allocator
{
private:
	char* buf = nullptr;
	size_t offset;
	size_t capacity;


public:
	void makeAllocator(size_t maxSize);
	char* alloc(size_t size);
	void reset();
	~Allocator();
};