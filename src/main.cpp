#include <iostream>
#include "qlearning.h"
#include "tictactoe.h"
#include "playgames.h"
#include "policy.h"

int main(int argc, const char *argv[])
{
	// auto r_learning = QLearning<TicTacToeState, int>(new TicTacToe(), 0.1, 0.9, 0.1);

	// auto table = r_learning.Run(25000000);

	// table.ExportPolicy("out/tictactoepolicy.dat");

	Policy<TicTacToeState, int> policy;
	policy.ImportPolicy("out/tictactoepolicy-25mill-iter-optimal.dat");

	std::cout << "Done training" << std::endl;
	
	while (true)
	{
		PlayTicTacToe(policy);
	}
}