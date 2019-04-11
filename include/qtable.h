#ifndef _INCLUDE_QTABLE_H_
#define _INCLUDE_QTABLE_H_

#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <fstream>
#include "utilities.h"
#include "maximalmap.h"

template <typename State, typename Action>
class QTable
{
public:
  QTable(double alpha, double gamma, double default_value = 0) : alpha(alpha), gamma(gamma), default_value(default_value)
  {
  }

  void UpdateAction(State state, Action action, double reward, State new_state)
  {
    MaximalMap<Action, double> &map = GetActionRewardMap(state);

    double old_est = map[action];

    double best_new_state_est = new_state.IsTerminal() ? 0 : GetActionRewardMap(new_state).MaxValue();

    double new_value = (1.0-alpha)*old_est + alpha*(reward + gamma * best_new_state_est);

    map.push_update(action, new_value);
  }

  MaximalMap<Action, double> &GetActionRewardMap(State state)
  {
    MaximalMap<Action, double> &action_map = state_action_reward_map[state];

    if (action_map.empty())
    {
      action_map.fill(state.AvailableActions(), default_value);
    }

    return action_map;
  }

  Action GetBestAction(State state)
  {
    return GetActionRewardMap(state).MaxKey();
  }

  void ExportPolicy(const std::string &filename)
  {
    std::ofstream output_file;
    output_file.open(filename);
    for (auto &pair : state_action_reward_map)
    {
      output_file << pair.first << " " << pair.second.MaxKey() << std::endl;
    }
    output_file.close();
  }

  std::map<State, MaximalMap<Action, double>> state_action_reward_map;

protected:
  
  double alpha;
  double gamma;
  int default_value;
};

#endif