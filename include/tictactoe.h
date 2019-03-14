#ifndef _INCLUDE_TICTACTOE_H_
#define _INCLUDE_TICTACTOE_H_

#include <array>
#include <tuple>
#include <string>
#include "game.h"
#include <sstream>

//typedef Game<std::tuple<std::array<int, 9>, int>, int>;

class TicTacToeState : public State
{
    public:
        TicTacToeState()
        {
            board.fill(-1);
        }

        TicTacToeState(bool next_player) : next_player(next_player)
        {
            board.fill(-1);
        }

        TicTacToeState(std::array<int,9> board, bool next_player) : board(board), next_player(next_player) {}

        virtual std::string Hash()
        {
            std::ostringstream os;
            for (int i = 0; i < 9; i++)
            {
                if (board[i] == -1)
                {
                    os << board[i];
                }
                else
                {
                    os << ((bool) board[i] ^ next_player);
                }
            }

            return os.str();
        }

        std::array<int, 9> board;
        bool next_player;
};

// class TicTacToe : public Game<int>
// {
//   public:
//     TicTacToe() : Game(2) 
//     {
//         RandomPlayer();
//         this->SetState(new TicTacToeState(GetCurrentPlayer()));
//     }

//     //Do we need to return reward for all players at each action and back apply?
//     virtual int ApplyAction(int a) override
//     {
//         current_state[a] = current_player;
        
//         if (false /*Player wins*/)
//         {
//             return 1;
//         }

//         NextPlayer();

//         return 0;
//     }

//     virtual std::vector<int> GetAvailableActions()
//     {
//         auto actions = std::vector<int>();
//         for (int i = 0; i < 9; i++)
//         {
//             if (current_state[i] == -1)
//             {
//                 actions.push_back(i);
//             }
//         }

//         return actions;
//     }
// };

#endif