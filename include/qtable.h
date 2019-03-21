#ifndef _INCLUDE_Q_TABLE_H_
#define _INCLUDE_Q_TABLE_H_

#include <vector>
#include <iostream>
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
    //std::cout << "Updating " << state.Hash() << std::endl;

    MaxHeapMap<Action, int> &map = state_action_reward_map[state];
    
    //std::cout << "Retrieved map" << std::endl;

    int old_est = std::get<0>(map[action]);

    //std::cout << "Previous estimate: " << old_est << std::endl;

    int best_new_state_est = new_state.IsTerminal() ? 0 : GetActionRewardMap(new_state).MaxValue();

    //std::cout << "Best estimate for new state: " << best_new_state_est << std::endl;

    if (!is_players_turn)
    {
      best_new_state_est *= -1;
    }

    int new_value = (1.0-step_size)*old_est + step_size*(reward + gamma * best_new_state_est);

    //std::cout << "New best for old state: " << new_value << std::endl;

    map.update(action, new_value);
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
      //std::cout << "Filling new state" << std::endl;
      action_map.fill(state.AvailableActions(), default_value);
    }

    return action_map;
  }

  Action GetBestAction(State state)
  {
    return GetActionRewardMap(state).MaxKey();
  }

protected:
  std::map<State, MaxHeapMap<Action, int>> state_action_reward_map;
  int default_value;
  double step_size;
  double gamma;
  double epsilon;
};

#endif