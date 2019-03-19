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
  QTable(double step_size, double lamda, int default_value = 0) : default_value(default_value), step_size(step_size), lamda(lamda)
  {
  }

  std::string InitialiseState(State state, std::vector<Action> available_actions)
  {
    std::string state_hash = state.Hash();

    std::vector<ActionReward> values;

    std::transform(available_actions.begin(), available_actions.end(), std::back_inserter(values),
                   [](Action a) { return ActionReward(a, default_value) });

    state_map[state_hash] = values;

    return state_hash;
  }

  void UpdateAction(State state, Action action, int reward, State new_state)
  {
    // Find the reward in the map
    std::map<Action, int> &action_reward_map = state_action_reward_map[state];
    
    int old_est = action_reward_map[action];

    action_reward_map.erase(action);

    action_reward_map

    if (map_iter != state_map.end())
    {
      // Find the action within the action list and update the reward
      auto action_list_iter = std::find(map_iter->second.begin(), map_iter->second.end(), action);
      if (action_list_iter != map_iter->second.end())
      {
        map_iter->push_back(ActionReward(action, (1.0-step_size)*action_list_iter->reward + step_size*(reward + lambda * state_map.find(new_state.Hash())->max );
        map_iter->erase(action_list_iter);
        std::push_heap(map_iter->begin(), map_iter->end(), [](const ActionReward &a, const ActionReward &b) {
          return a.reward < b.reward});
      }
    }
  }

  //Gets the action to take in an epsilon greedy manner.
  Action GetNextAction(State state, double eplison)
  {
    const std::map<Action, int> &map = GetActionRewardMap(state);

    double r = Random::Uniform(0.0, 1.0);

    if (r <= eplison)
    {
      return RandomElement(map.begin(), map.end())->first;
    }

    return map.front().first;
  }

  const std::map<Action, int> &GetActionRewardMap(State state)
  {
    MaxHeapMap<Action, int> &action_map = state_action_reward_map[state];
    if (list.empty())
    {
      action_map.fill(state.AvailableActions(), default_value);
    }
    return list;
  }

  // void InitialiseActionRewardMap(State state, std::map<Action, int> &action_map)
  // {
  //   std::vector<Action> available_actions = state.AvailableActions();

  //   std::transform(available_actions.begin(), available_actions.end(), std::back_inserter(action_map),
  //                  [](Action a) { return std::make_pair(a, default_value) });
  // }

  // Action GetBestReward(State state)
  // {
  //   auto map_iter = state_map.find(state.Hash());

  //   if (map_iter == state_map.end())
  //   {
  //     auto hash = InitialiseState(state, available_actions);
  //     return state_map[hash].front().action;
  //   }

  //   return map_iter->front().action;
  // }

protected:
  // struct ActionReward
  // {
  //   Action action;
  //   int reward;
  //   action_reward(Action a, int r) : action(a), reward(r){};
  // };

  // bool operator==(const ActionReward &lhs, const ActionReward &rhs)
  // {
  //   return lhs.action == rhs.action;
  // }

  // bool operator==(const ActionReward &lhs, const Action &rhs)
  // {
  //   return lhs.action == rhs;
  // }

  std::map<State, MaxHeapMap<Action, int>> state_action_reward_map;

  int default_value;
  double step_size;
  double lambda;
};

#endif