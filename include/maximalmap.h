#ifndef _INCLUDE_MAXHEAPMAP_H_
#define _INCLUDE_MAXHEAPMAP_H_

#include <map>
#include <algorithm>
#include <vector>
#include <tuple>
#include "maxheap.h"
#include "utilities.h"

template <typename T, typename S>
class MaximalMap
{
  public:
    MaximalMap(){};

    void push_update(T t, S s)
    {
        map[t] = s;
        // Why is this needed???
        if (!max_pair)
        {
            max_pair = new MaximalPair(t, s);
        }
        else if (s > max_pair->s)
        {
            max_pair->t = t;
            max_pair->s = s;
        }
        else if (max_pair->t == t && max_pair->s > s)
        {
            max_pair->s = s;
            // We need to find the next max
            for(const auto &pair: map)
            {
                if (pair.second > max_pair->s)
                {
                    max_pair->t = pair.first;
                    max_pair->s = pair.second;
                }
            }
        }
    };

    std::tuple<T, S> MaxPair()
    {
        return {max_pair->t, max_pair->s};
    };

    const T &MaxKey()
    {
        return max_pair-> t;
    };

    const S &MaxValue()
    {
        return max_pair->s;
    };

    void fill(std::vector<T> keys, S fill_value)
    {
        for (T &t : keys)
        {
            map[t] = fill_value;
        };

        if (!max_pair)
        {
            max_pair = new MaximalPair(keys.front(), fill_value);
        }
        else if (max_pair->s < fill_value)
        {
            max_pair->t = keys.front();
            max_pair->s = fill_value;
        }
    };

    bool empty()
    {
        return map.empty();
    }

    const S &operator[](const T &index)
    {
        return map[index];
    };

    T RandomKey() const
    {
        return std::get<0>(*RandomElement(map.begin(), map.end()));
    }
    
    std::map<T, S> map;
  protected:
    struct MaximalPair
    {
        T t;
        S s;
        MaximalPair(T t, S s) : t(t), s(s){};
    };

    MaximalPair *max_pair = nullptr;
};

#endif