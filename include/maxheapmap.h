#ifndef _INCLUDE_MAXHEAPMAP_H_
#define _INCLUDE_MAXHEAPMAP_H_

#include <map>
#include <algorithm>
#include <vector>
#include <tuple>
#include "maxheap.h"

//Sacrifices memory on the key type
template <typename T, typename S>
class MaxHeapMap
{
  public:
    MaxHeapMap() : heap([](const std::tuple<T, S> &a, const std::tuple<T, S> &b) { return std::get<1>(a) < std::get<1>(b) }) {};

    void push(T t, S s)
    {
        map[t] = heap.push({t,s});
    };

    std::tuple<T, S> &MaxPair()
    {
        return heap.front();
    };

    T &MaxKey()
    {
        return std::get<1>(heap.front());
    };

    void update(T t, S s)
    {
        map[t] = heap.modify(map[t], {t,s});
    }

    void fill(std::vector<T> keys, S fill_value)
    {
        for (T &t : keys)
        {
            this->push(t, fill_value);
        }
    };

    const std::tuple<T, S> &operator[](const T& index)
    {
        return *heap.at(map[index]);
    }

  protected:
    std::map<T, std::size_t> map;
    MaxHeap<std::tuple<T, S>> heap;
};

#endif