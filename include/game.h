#ifndef _INCLUDE_GAME_H_
#define _INCLUDE_GAME_H_

#include "utilities.h"
#include "state.h"

template <typename Action>
class Game
{
  public:
    Game(State *init_state, unsigned int number_of_players, unsigned int first_player = 0) : current_state(init_state), number_of_players(number_of_players), current_player(first_player) {}
    Game(unsigned int number_of_players, unsigned int first_player = 0) : number_of_players(number_of_players), current_player(first_player) {}

    virtual int ApplyAction(Action a) = 0;

    virtual std::vector<Action> GetAvailableActions() = 0;

    void NextPlayer()
    {
        current_player++;
        current_player = current_player % number_of_players;
    }

    unsigned int GetCurrentPlayer()
    {
        return current_player;
    }

    void RandomPlayer()
    {
        current_player = random.Uniform<int>(0, number_of_players - 1);
    }

    void SetState(State *new_state)
    {
        current_state = new_state;
    }

  protected:
    State *current_state;
    unsigned int number_of_players;
    unsigned int current_player;
    Random random = Random();
};

#endif