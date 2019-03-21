#ifndef _INCLUDE_GAME_H_
#define _INCLUDE_GAME_H_

#include "utilities.h"

template <typename State, typename Action>
class Game
{
  public:
    Game(State init_state, unsigned int number_of_players, unsigned int first_player = 0) : current_state(init_state), number_of_players(number_of_players), current_player(first_player) {}
    Game(unsigned int number_of_players, unsigned int first_player = 0) : number_of_players(number_of_players), current_player(first_player) {}

    virtual double ApplyAction(Action a) = 0;
    
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
        current_player =  Random::Uniform(0, number_of_players - 1);
    }

    void SetState(State new_state)
    {
        current_state = new_state;
    }

    virtual void Initialise() = 0;

    unsigned int number_of_players;
    unsigned int current_player;
    State current_state;
};

#endif