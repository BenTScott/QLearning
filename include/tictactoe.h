#ifndef _INCLUDE_TICTACTOE_H_
#define _INCLUDE_TICTACTOE_H_

#include <array>
#include <tuple>
#include <string>
#include "game.h"
#include "state.h"
#include <sstream>
#include <algorithm>

class TicTacToeState : State<int>
{
  public:
    std::array<int, 9> board;
    bool next_player;

    TicTacToeState()
    {
        board.fill(-1);
    }

    TicTacToeState(bool next_player) : next_player(next_player)
    {
        board.fill(-1);
    }

    TicTacToeState(std::array<int, 9> board, bool next_player) : board(board), next_player(next_player) {}

    virtual std::vector<int> AvailableActions() override
    {
        std::vector<int> actions;
        for (int i = 0; i < 9; i++)
        {
            if (board[i] == -1)
            {
                actions.push_back(i);
            }
        }

        return actions;
    }

    virtual bool IsTerminal() override
    {
        if (std::find(board.begin(), board.end(), -1) == board.end())
        {
            return true;
        }
        return false;
    }

    bool IsWin()
    {
        for (int i = 0; i < 3; i++)
        {
            // Vertical
            if (board[i] != -1 && board[i] == board[i + 3] && board[i + 3] == board[i + 6])
            {
                return true;
            }

            // Horizontal
            if (board[3 * i] != -1 && board[3 * i] == board[3 * i + 1] && board[3 * i + 1] == board[3 * i + 2])
            {
                return true;
            }
        }

        // Diagonals
        if (board[0] != -1 && board[0] == board[4] && board[4] == board[8])
        {
            return true;
        }
        if (board[2] != -1 && board[2] == board[4] && board[4] == board[6])
        {
            return true;
        }

        return false;
    }

    std::string Hash() const
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
                os << ((bool)board[i] ^ next_player);
            }
        }

        return os.str();
    }

    friend bool operator==(const TicTacToeState &lhs, const TicTacToeState &rhs);
    friend bool operator!=(const TicTacToeState &lhs, const TicTacToeState &rhs);
    friend bool operator<(const TicTacToeState &lhs, const TicTacToeState &rhs);
    friend bool operator>(const TicTacToeState &lhs, const TicTacToeState &rhs);
    friend bool operator<=(const TicTacToeState &lhs, const TicTacToeState &rhs);
    friend bool operator>=(const TicTacToeState &lhs, const TicTacToeState &rhs);
};

inline bool operator==(const TicTacToeState &lhs, const TicTacToeState &rhs) { return lhs.Hash() == rhs.Hash(); }
inline bool operator!=(const TicTacToeState &lhs, const TicTacToeState &rhs) { return !operator==(lhs, rhs); }
inline bool operator<(const TicTacToeState &lhs, const TicTacToeState &rhs) { return lhs.Hash() < rhs.Hash(); }
inline bool operator>(const TicTacToeState &lhs, const TicTacToeState &rhs) { return operator<(rhs, lhs); }
inline bool operator<=(const TicTacToeState &lhs, const TicTacToeState &rhs) { return !operator>(lhs, rhs); }
inline bool operator>=(const TicTacToeState &lhs, const TicTacToeState &rhs) { return !operator<(lhs, rhs); }

class TicTacToe : public Game<TicTacToeState, int>
{
  public:
    TicTacToe() : Game(2)
    {
        // RandomPlayer();
        // this->SetState(new TicTacToeState(GetCurrentPlayer()));
    }

    //Do we need to return reward for all players at each action and back apply?
    virtual int ApplyAction(int a) override
    {
        current_state.board[a] = current_player;

        if (current_state.IsWin())
        {
            return 1;
        }

        NextPlayer();

        return 0;
    }

    virtual void Initialise() override
    {
        RandomPlayer();
        this->SetState(TicTacToeState(GetCurrentPlayer()));
    }
};

#endif