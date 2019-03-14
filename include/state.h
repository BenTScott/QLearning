#ifndef _INCLUDE_STATE_H_
#define _INCLUDE_STATE_H_

#include <string>

class State
{
  public:
    State(){}

    // Hash value for uniquely identifying a particular state
    virtual std::string Hash() = 0;

};

#endif