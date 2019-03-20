#include <iostream>
#include "qlearning.h"
#include "tictactoe.h"

int main( int argc, const char* argv[] )
{
	std::cout <<  "\nHello World\n\n";

	auto r_learning = QLearning<TicTacToeState, int>(new TicTacToe(), 0.1, 1, 0.5);

	r_learning.Run(100);

	
}