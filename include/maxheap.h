#ifndef _INCLUDE_MAXHEAP_H_
#define _INCLUDE_MAXHEAP_H_

#include <vector>
#include <functional>

template <typename T>
void swap(T *x, T *y);

template <typename T>
class MaxHeap
{
    std::vector<T> base_vector;

    std::size_t parent(std::size_t i) { return (i - 1) / 2; }

    // to get index of left child of node at index i
    std::size_t left(std::size_t i) { return (2 * i + 1); }

    // to get index of right child of node at index i
    std::size_t right(std::size_t i) { return (2 * i + 2); }

    // increase the value at index i with
    std::size_t increase_value(std::size_t i, T new_val)
    {
        base_vector[i] = new_val;
        while (i != 0 && less_than(base_vector[parent(i)], base_vector[i]))
        {
            swap(&base_vector[i], &base_vector[parent(i)]);
            i = parent(i);
        }

        return i;
    }

    std::size_t decrease_value(std::size_t i, T new_val)
    {
        base_vector[i] = new_val;

        T *left_ptr = this->at(left(i));
        T *right_ptr = this->at(right(i));

        while ((left_ptr && !less_than(*left_ptr, base_vector[i])) || (right_ptr && !less_than(*right_ptr, base_vector[i])))
        {
            if (left_ptr && right_ptr)
            {
                if (!less_than(*left_ptr, *right_ptr))
                {
                    swap(left_ptr, &base_vector[i]);
                    i = left(i);
                }
                else
                {
                    swap(right_ptr, &base_vector[i]);
                    i = right(i);
                }
            }
            else if (left_ptr)
            {
                swap(left_ptr, &base_vector[i]);
                i = left(i);
            }
            else
            {
                swap(right_ptr, &base_vector[i]);
                i = right(i);
            }
            T *left_ptr = this->at(left(i));
            T *right_ptr = this->at(right(i));
        }

        return i;
    }

    std::function<bool(const T &, const T &)> less_than;

  public:
    MaxHeap(std::function<bool(const T &, const T &)> less_than = [](const T &a, const T &b) { return a < b; }) : less_than(less_than)
    {
    }

    MaxHeap() : less_than([](const T &a, const T &b) { return a < b; })
    {
    }

    std::size_t push(T t)
    {
        base_vector.push_back(t);
        std::size_t index = base_vector.size() - 1;

        while (index != 0 && less_than(base_vector[parent(index)], base_vector[i]))
        {
            swap(&base_vector[index], &base_vector[parent(index)]);
            index = parent(index);
        }

        return index;
    }

    bool empty() const
    {
        return base_vector.empty();
    }

    T &front()
    {
        return base_vector.front();
    }

    T *at(std::size_t i)
    {
        if (i < base_vector.size())
        {
            return &base_vector[i];
        }

        return nullptr;
    }

    std::size_t modify(std::size_t i, T new_value)
    {
        if (less_than(base_vector[i], new_value))
        {
            return increase_value(i, new_value);
        }
        else
        {
            return decrease_value(i, new_value);
        }
    }
};

// A utility function to swap two elements - TODO move to utilities
template <typename T>
void swap(T *x, T *y)
{
    T temp = *x;
    *x = *y;
    *y = temp;
}

#endif