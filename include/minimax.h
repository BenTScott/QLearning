#ifndef _INCLUDE_MINIMAX_H_
#define _INCLUDE_MINIMAX_H_

template <typename State, typename Action>
class Minimax
{
  public:
    Minimax(int max_depth = -1) : max_depth(max_depth) {}

    int max_depth;
};

#endif