#include "allocator.hpp"


void Allocator::makeAllocator(size_t maxSize)
{
	if (buf != nullptr)
	{
		delete[] buf;
	}
	buf = new char[maxSize];
	capacity = maxSize;
	offset = 0;
}

char* Allocator::alloc(size_t size)
{
	if ((size <= 0) || (size + offset > capacity))
	{
		return nullptr;
	}
	offset += size;
	return buf + offset - size;
}

void Allocator::reset()
{
	offset = 0;
}

Allocator::~Allocator()
{
	delete[] buf;
}