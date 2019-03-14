#ifndef _INCLUDE_Q_TABLE_H_
#define _INCLUDE_Q_TABLE_H_

#include <vector>

template <typename State, typename Action>
class QTable
{
  public:
    QTable(int default_value = 0) : default_value(default_value) 
    {
    }

    IntialiseState(State state, std::vector<Action> avaiable_actions)
    {
        
    }

  protected:
    default_value;
};

#endif