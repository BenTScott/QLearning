#ifndef _INCLUDE_AGENTS_H_
#define _INCLUDE_AGENTS_H_

#include <string>
#include <map>
#include <vector>
#include "qtable.h"

template <typename State, typename Action>
class Agent
{
public:
  Agent(){};
  virtual Action GetAction(const State &state) = 0;
};

template <typename State, typename Action>
class PolicyAgent : public Agent<State, Action>
{
public:
  PolicyAgent(){};
  PolicyAgent(std::map<State, Action> policy) : map(policy) {}

  void ImportPolicy(std::string filename);
  void ExportPolicy(const std::string &filename);
  virtual Action GetAction(const State &state) override;

protected:
  std::map<State, Action> map;
};

template <typename State, typename Action>
class RandomAgent : public Agent<State, Action>
{
public:
  RandomAgent() {}

  virtual Action GetAction(const State &state) override;
};

template <typename State, typename Action>
class ProbalisticAgent : public Agent<State, Action>
{
public:
  ProbalisticAgent(std::map<State, std::vector<ProbabilityPair<Action>>> map) : map(map) {}

  virtual Action GetAction(const State &state) override;

  std::map<State, std::vector<ProbabilityPair<Action>>> map;
};

template <typename State, typename Action>
class QLearningAgent : public Agent<State, Action>
{
public:
  QLearningAgent(double epsilon, double alpha, double gamma) : q_table(alpha, gamma), epsilon(epsilon) {}

  virtual Action GetAction(const State &state) override;
  void ApplyReward(const State &new_state, double reward);
  PolicyAgent<State, Action> CreateTestingAgent();
  ProbalisticAgent<State, Action> CreateProbalisticAgent(double temperature);
  void InitialiseEpisode()
  {
    previous_state = nullptr;
    previous_action = nullptr;
  };

  QTable<State, Action> q_table;

protected:
  double epsilon;
  State *previous_state = nullptr;
  Action *previous_action = nullptr;
};

template <typename State, typename Action>
class PlayerAgent : public Agent<State, Action>
{
public:
  PlayerAgent() {}

  virtual Action GetAction(const State &state) override;
};

#include "template_implementation/agents.tpp"

#endif