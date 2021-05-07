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

        void operator--()
        {
            if (reversed == false)
            {
                iter--;
            }
            else
            {
                iter++;
            }  
        }

        void operator++()
        {
            if (reversed == false)
            {
                iter++;
            }
            else
            {
                iter--;
            }
        }

        int operator*() const
        {
            return *iter;
        }

    private:
        T* iter;
        bool reversed;
};