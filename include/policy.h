#ifndef _INCLUDE_POLICY_H_
#define _INCLUDE_POLICY_H_

#include <string>
#include <map>

template <typename State, typename Action>
class Policy
{
  public:
    Policy(){}

    void ImportPolicy(std::string filename);
    Action GetAction(const State &state);

  protected:
    std::map<State, Action> map;
};

#include "template_implementation/policy.tpp"

#endif