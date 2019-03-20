#ifndef _INCLUDE_STATE_H_
#define _INCLUDE_STATE_H_

#include <vector>

// Interface base class for a Q-Learning state
template <typename Action>
class State
{
  public:
    State(){};
    virtual bool IsTerminal() = 0;
    virtual std::vector<Action> AvailableActions() = 0;
};

#endif