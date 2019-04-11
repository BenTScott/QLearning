#ifndef _INCLUDE_Q_LEARNING_H_
#define _INCLUDE_Q_LEARNING_H_

#include <map>
#include <string>
#include <vector>
#include <array>
#include <iostream>
#include "game.h"
#include "agents.h"

template <typename State, typename Action>
class QLearning
{
public:
  QLearning(Game<State, Action> *game, double epsilon, double gamma, double alpha) : game(game), epsilon(epsilon), gamma(gamma), alpha(alpha) //, q_table(alpha, gamma, epsilon)
  {
  }

  QLearningAgent<State, Action> Run(std::size_t iterations)
  {
    auto learning_agent = QLearningAgent<State, Action>(epsilon, alpha, gamma);
    auto random_agent = RandomAgent<State, Action>();

    for (std::size_t i = 0; i < iterations; i++)
    {
      std::cout << "Iteration " << i << std::endl;

      game->Initialise();
      learning_agent.InitialiseEpisode();
      State s = game->current_state;
      double reward = 0;
      while (!s.IsTerminal())
      {
        Action a;
        
        if (game->current_player == 0)
        {
          learning_agent.ApplyReward(s, reward);
          a = learning_agent.GetAction(s);
        }
        else
        {
          a = random_agent.GetAction(s);
        }
        reward = game->ApplyAction(a);
        s = game->current_state;
      }
      
      learning_agent.ApplyReward(s, reward);
    }
    return learning_agent;
  }

protected:
  Game<State, Action> *game;
  double epsilon;
  double gamma;
  double alpha;
};

#endif