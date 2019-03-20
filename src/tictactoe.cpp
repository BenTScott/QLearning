#include "tictactoe.h"

inline bool operator==(const TicTacToeState& lhs, const TicTacToeState& rhs){ lhs.Hash() == rhs.Hash(); }
inline bool operator!=(const TicTacToeState& lhs, const TicTacToeState& rhs){return !operator==(lhs,rhs);}
inline bool operator< (const TicTacToeState& lhs, const TicTacToeState& rhs){ lhs.Hash() < rhs.Hash(); }
inline bool operator> (const TicTacToeState& lhs, const TicTacToeState& rhs){return  operator< (rhs,lhs);}
inline bool operator<=(const TicTacToeState& lhs, const TicTacToeState& rhs){return !operator> (lhs,rhs);}
inline bool operator>=(const TicTacToeState& lhs, const TicTacToeState& rhs){return !operator< (lhs,rhs);}