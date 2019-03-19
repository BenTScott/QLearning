#ifndef _INCLUDE_Q_LEARNING_H_
#define _INCLUDE_Q_LEARNING_H_

#include <map>
#include <string>
#include "game.h"
#include "q_table.h"

template <typename State, typename Action>
class QLearning
{
  public:
    QLearning(Game<State, Action> game, double epsilon, double gamma) : game(game), epsilon(epsilon), gamma(gamma)
    {
    }

    QTable<State, Action> Run()
    {
      State s = game.current_state;
      auto actions = game.GetAvailableActions();
      Action a = q_table.GetAction(s, actions, epsilon);
      int reward = game.ApplyAction(a);
      q_table.UpdateAction(s, a, reward, game.current_state);
    }

  protected:
    Game<State, Action> game;
    QTable<State, Action> q_table;
    double epsilon;
};

#endif