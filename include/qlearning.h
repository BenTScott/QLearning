#ifndef _INCLUDE_Q_LEARNING_H_
#define _INCLUDE_Q_LEARNING_H_

#include <map>
#include <string>
#include <vector>
#include <array>
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
      game->Initialise();
      State s = game->current_state;
      while (!s.IsTerminal())
      {
        Action a = q_table.GetNextAction(s);
        auto current_player = game->current_player;
        int reward = game->ApplyAction(a);
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

protected:
  Game<State, Action> *game;
  QTable<State, Action> q_table;
  double epsilon;
};

#endif