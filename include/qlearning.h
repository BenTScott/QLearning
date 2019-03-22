#ifndef _INCLUDE_Q_LEARNING_H_
#define _INCLUDE_Q_LEARNING_H_

#include <map>
#include <string>
#include <vector>
#include <array>
#include <iostream>
#include "game.h"
#include "qtable.h"

template <typename State, typename Action>
class QLearning
{
public:
  QLearning(Game<State, Action> *game, double epsilon, double gamma, double alpha) : game(game), q_table(alpha, gamma, epsilon)
  {
  }

  QTable<State, Action> Run(std::size_t iterations)
  {
    for (std::size_t i = 0; i < iterations; i++)
    {
      std::cout << "Iteration " << i << std::endl;

      game->Initialise();
      State s = game->current_state;

      while (!s.IsTerminal())
      {

#ifdef _DEBUG
        std::cout << "Game state: " << s.Hash() << std::endl;
#endif

        Action a = q_table.GetNextAction(s);

#ifdef _DEBUG
        std::cout << "Action: " << a << std::endl;
#endif

        auto current_player = game->current_player;
        double reward = game->ApplyAction(a);

#ifdef _DEBUG
        std::cout << "Reward: " << reward << std::endl;
#endif

        if (game->current_player == current_player)
        {
          q_table.UpdateAction(s, a, reward, game->current_state, true);
        }
        {
          q_table.UpdateAction(s, a, reward, game->current_state, false);
        }
        s = game->current_state;
      }
    }
    return q_table;
  }

  QTable<State, Action> RunAgainstRandom(std::size_t iterations)
  {
    for (std::size_t i = 0; i < iterations; i++)
    {
      std::cout << "Iteration " << i << std::endl;

      game->Initialise();
      State s = game->current_state;

      while (!s.IsTerminal())
      {
        if (game->current_player == 0)
        {
          std::cout << "Player 0" << std::endl;
          Action a = q_table.GetNextAction(s);
          std::cout << "Action " << a << std::endl;
          auto current_player = game->current_player;
          double reward = game->ApplyAction(a);
          std::cout << "Reward " << reward << std::endl;
          if (game->current_player == current_player)
          {
            q_table.UpdateAction(s, a, reward, game->current_state, true);
          }
          {
            q_table.UpdateAction(s, a, reward, game->current_state, false);
          }
          std::cout << "Action updated";
          s = game->current_state;
        }
        else
        {
          auto actions = game->current_state.AvailableActions();
          game->ApplyAction(*RandomElement(actions.begin(), actions.end()));
        }
      }
    }
    return q_table;
  }

protected:
  Game<State, Action> *game;
  QTable<State, Action> q_table;
  double epsilon;
};

#endif