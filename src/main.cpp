#include <iostream>
#include "tictactoe.h"

int main( int argc, const char* argv[] )
{
	std::cout <<  "\nHello World\n\n";

	auto s = TicTacToeState({1,0,-1,0,-1,-1,-1,-1,1},1);

	std::cout << s.Hash() << std::endl;

	s = TicTacToeState({0,1,-1,1,-1,-1,-1,-1,0},0);

	std::cout << s.Hash() << std::endl;

}