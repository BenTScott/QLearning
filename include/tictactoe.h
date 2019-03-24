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

  virtual std::vector<int> AvailableActions() const override;

  virtual bool IsTerminal() override;

  // Returns true if is a winning state
  bool IsWin() const;

  // Returns a hash value for comparing states
  std::string Hash() const;

  std::string PrettyPrint() const;

  friend bool operator==(const TicTacToeState &lhs, const TicTacToeState &rhs);
  friend bool operator!=(const TicTacToeState &lhs, const TicTacToeState &rhs);
  friend bool operator<(const TicTacToeState &lhs, const TicTacToeState &rhs);
  friend bool operator>(const TicTacToeState &lhs, const TicTacToeState &rhs);
  friend bool operator<=(const TicTacToeState &lhs, const TicTacToeState &rhs);
  friend bool operator>=(const TicTacToeState &lhs, const TicTacToeState &rhs);
  friend std::ostream &operator<<(std::ostream &os, const TicTacToeState &obj);
  friend std::istream& operator>>(std::istream& is, TicTacToeState& obj);
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
  TicTacToe() : Game(2) {}

  virtual double ApplyAction(int a) override;

  virtual void Initialise() override;
};

#endif