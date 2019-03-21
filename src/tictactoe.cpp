#include "tictactoe.h"

std::string TicTacToeState::Hash() const
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
};

bool TicTacToeState::IsWin() const
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
};

bool TicTacToeState::IsTerminal()
{
    if (IsWin() || std::find(board.begin(), board.end(), -1) == board.end())
    {
        return true;
    }
    return false;
};

std::vector<int> TicTacToeState::AvailableActions()
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
};

int TicTacToe::ApplyAction(int a)
{
    current_state.board[a] = current_player;

    if (current_state.IsWin())
    {
        return 1000;
    }

    NextPlayer();

    return 0;
};

void TicTacToe::Initialise()
{
    RandomPlayer();
    this->SetState(TicTacToeState(GetCurrentPlayer()));
};