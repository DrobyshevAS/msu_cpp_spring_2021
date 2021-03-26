#include <iostream>
#include <cassert>
#include "allocator.hpp"

using namespace std;

void empty_allocator_test()
{
	Allocator mem;
	assert(mem.alloc(10) == nullptr);
	cout << "empty allocator test: OK" << endl;
}

void overflow_test()
{
	Allocator mem;
	mem.makeAllocator(10);
	assert(mem.alloc(100) == nullptr);
	cout << "overflow allocator test: OK" << endl;
}

void reset_test()
{
	Allocator mem;
	mem.makeAllocator(10);
	char* first = mem.alloc(8);
	assert(first != nullptr);
	mem.reset();
	assert(mem.alloc(10) != nullptr);
	cout << "reset allocator test: OK" << endl;
}

void complex_alloc_test()
{
	Allocator mem;
	mem.makeAllocator(10);
	char* first = mem.alloc(5);
	char* second = mem.alloc(5);
	assert(second - first == 5);

	mem.reset();
	assert(mem.alloc(10) != nullptr);
	assert(mem.alloc(1) == nullptr);

	mem.reset();
	assert(mem.alloc(-5) == nullptr);

	cout << "complex alloc test: OK" << endl;
}

void few_makeAllocator_test()
{
	Allocator mem;
	mem.makeAllocator(10);
	assert(mem.alloc(10) != nullptr);
	mem.makeAllocator(10);
	assert(mem.alloc(10) != nullptr);
	cout << "few makeAllocator test: OK" << endl;
}


int main()
{
	empty_allocator_test();
	overflow_test();
	reset_test();
	complex_alloc_test();
	few_makeAllocator_test();
}