#ifndef _INCLUDE_Q_TABLE_H_
#define _INCLUDE_Q_TABLE_H_

#include <vector>
#include <algorithm>
#include <map>
#include "utilities.h"
#include "maxheapmap.h"

template <typename State, typename Action>
class QTable
{
public:
  QTable(double step_size, double gamma, double epsilon, int default_value = 0) : default_value(default_value), step_size(step_size), gamma(gamma), epsilon(epsilon)
  {
  }

  void UpdateAction(State state, Action action, int reward, State new_state, bool is_players_turn)
  {
    MaxHeapMap<Action, int> &map = state_action_reward_map[state];
    
    int old_est = std::get<0>(map[action]);

    int best_new_state_est = GetActionRewardMap(new_state).MaxValue();

    if (!is_players_turn)
    {
      best_new_state_est *= -1;
    }

    map.update(action, (1.0-step_size)*old_est + step_size*(reward + gamma * best_new_state_est));
  }

  //Gets the action to take in an epsilon greedy manner.
  Action GetNextAction(State state)
  {
    MaxHeapMap<Action, int> &map = GetActionRewardMap(state);

    double r = Random::Uniform(0.0, 1.0);

    if (r <= epsilon)
    {
      return map.RandomKey();
    }

    return map.MaxKey();
  }

  MaxHeapMap<Action, int> &GetActionRewardMap(State state)
  {
    MaxHeapMap<Action, int> &action_map = state_action_reward_map[state];

    if (action_map.empty())
    {
      action_map.fill(state.AvailableActions(), default_value);
    }
    return action_map;
  }

protected:
  std::map<State, MaxHeapMap<Action, int>> state_action_reward_map;
  int default_value;
  double step_size;
  double gamma;
  double epsilon;
};

#endif