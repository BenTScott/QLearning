#ifndef _INCLUDE_Q_TABLE_H_
#define _INCLUDE_Q_TABLE_H_

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
  QTable(double step_size, double gamma, double epsilon, double default_value = 0) : default_value(default_value), step_size(step_size), gamma(gamma), epsilon(epsilon)
  {
  }

  void UpdateAction(State state, Action action, double reward, State new_state, bool is_players_turn)
  {
    MaximalMap<Action, double> &map = GetActionRewardMap(state);

    double old_est = map[action];

    double best_new_state_est = new_state.IsTerminal() ? 0 : GetActionRewardMap(new_state).MaxValue();

    if (!is_players_turn)
    {
      best_new_state_est *= -1;
    }

    double new_value = (1.0-step_size)*old_est + step_size*(reward + gamma * best_new_state_est);

    map.push_update(action, new_value);
  }

  //Gets the action to take in an epsilon greedy manner.
  Action GetNextAction(State state)
  {
    MaximalMap<Action, double> &map = GetActionRewardMap(state);

    double r = Random::Uniform(0.0, 1.0);

    if (r <= epsilon)
    {
      return map.RandomKey();
    }

    return map.MaxKey();
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

  std::map<State, MaximalMap<Action, double>> state_action_reward_map;

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

protected:
  
  int default_value;
  double step_size;
  double gamma;
  double epsilon;
};

#endif