#pragma once

template <class T>
class Iterator
{
    public:
        Iterator(T* ptr, bool r): iter(ptr), reversed(r) {}

        bool operator==(const Iterator& other) const
        {
            return iter == other.iter;
        }

        bool operator!=(const Iterator& other) const
        {
            return !(*this == other);
        }

        bool operator<(const Iterator& other) const
        {
            if (iter < other.iter)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        bool operator>(const Iterator& other) const
        {
            if (iter > other.iter)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        bool operator<=(const Iterator& other) const
        {
            if (iter <= other.iter)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        bool operator>=(const Iterator& other) const
        {
            if (iter >= other.iter)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        Iterator& operator--()
        {
            if (reversed == false)
            {
                iter--;
            }
            else
            {
                iter++;
            }  
            return *this;
        }

        
        Iterator operator--(int)
        {
            auto temp = iter;
            if (reversed == false)
            {
                temp--;
            }
            else
            {
                temp++;
            }
            return Iterator(temp, reversed);
        }

        Iterator& operator++()
        {
            if (reversed == false)
            {
                iter++;
            }
            else
            {
                iter--;
            }
            return *this;
        }

        
        Iterator operator++(int)
        {
            auto temp = iter;
            if (reversed == false)
            {
                temp++;
            }
            else
            {
                temp--;
            }
            return Iterator(temp, reversed);
        }
        

        int operator*() const
        {
            return *iter;
        }

    private:
        T* iter;
        bool reversed;
};