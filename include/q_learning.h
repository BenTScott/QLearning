#ifndef _INCLUDE_Q_LEARNING_H_
#define _INCLUDE_Q_LEARNING_H_

#include <map>
#include "game.h"

template <typename State, typename Action>
class QLearning
{
  public:
    QLearning(Game<State, Action> game) : game(game)
    {
    }

  protected:
    Game game;
    std::map<>
};

#endif