#pragma once
#include <exception>
#include "allocator.hpp"
#include "iterator.hpp"


template <class T, class Alloc = Allocator<T>>
class vector {
    public:
        vector(size_t n = 0): size_(0), capacity_(n)
        {
            data = alloc.allocate(n);
        }

        ~vector()
        {
            if (data != nullptr)
            {
                alloc.deallocate(data);
                data = nullptr;
                size_=capacity_=0;
            }
        }

        void push_back(T&& value)
        {
            if (size_==capacity_)
            {
                reserve(2*(capacity_ + 1) - 1);
            }
            data[size_++] = value;
        }

        void pop_back()
        {
            if (empty())
            {
                throw std::out_of_range("Vector is empty");
            }
            size_--;
        }

        template <class... Args>
        void emplace_back(Args&&... args) {
        if (size_ == capacity_)
            reserve(2 * (capacity_ + 1) - 1);
        new (data + size_) T(std::forward<Args>(args)...);
        size_++;
    }

        void reserve(size_t new_capacity)
        {
            if (new_capacity > capacity_)
            {
                T* new_data = alloc.allocate(new_capacity);
                for (size_t i=0; i< size_; i++)
                {
                    new_data[i] = data[i];
                }
                alloc.deallocate(data);
                data = new_data;
                capacity_ = new_capacity;
            }
        }
        size_t size() const noexcept 
        {
            return size_;
        }

        T& operator[](size_t i) 
        {
            if ((i >= size_) || (i < 0))
            {
                throw std::out_of_range("Index out of range");
            }
            return data[i];
        }

        bool empty() const 
        {
            return size_ == 0;
        }

        void clear()
        {
            for (size_t i=0; i<size_; i++)
            {
                (data+i)->~T();
            }
            size_=0;
        }

        Iterator<T> begin()
        {
            return Iterator<T>(data, false);
        }

        Iterator<T> end()
        {
            return Iterator<T>(data+size_, false);
        }

        Iterator<T> rbegin()
        {
            return Iterator<T>(data+size_-1, true);
        }

        Iterator<T> rend()
        {
            return Iterator<T>(data-1, true);
        }

        size_t capacity() const noexcept 
        {
            return capacity_;
        }

        void resize(size_t new_size)
        {
            if (new_size>capacity_)
            {
                reserve(2*(capacity_ + 1) - 1);
            }
            for (size_t i = size_; i<new_size; i++)
            {
                data[i] = 0;
            }
            size_=new_size;
        }

        void resize(size_t new_size, const T&  value)
        {
            if (new_size>capacity_)
            {
                reserve(2*(capacity_ + 1) - 1);
            }
            for (size_t i = size_; i<new_size; i++)
            {
                data[i] = value;
            }
            size_=new_size;
        }

    private:
        T* data;
        Alloc alloc;
        size_t size_;
        size_t capacity_;
};