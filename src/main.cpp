#include <iostream>
#include "qlearning.h"
#include "tictactoe.h"

int main(int argc, const char *argv[])
{
	auto r_learning = QLearning<TicTacToeState, int>(new TicTacToe(), 0.1, 0.9, 0.2);

	auto table = r_learning.Run(500000);

	std::cout << "Done training" << std::endl;

	while (true)
	{

		auto game = TicTacToe();

		game.Initialise();

		while (!game.current_state.IsTerminal())
		{
			int action;
			std::cout << game.current_state << std::endl;
			if (game.current_player == 0)
			{
				std::cout << "Enter an action (0-8): ";
				std::cin >> action;
				game.ApplyAction(action);
			}
			else
			{
				action = table.GetBestAction(game.current_state);
				std::cout << "CPU plays " << action << std::endl;
				game.ApplyAction(action);
			}
		}

		if (game.current_state.IsWin())
		{
			if (game.current_player == 0)
			{
				std::cout << "Player wins" << std::endl;
			}
			else
			{
				std::cout << "CPU wins" << std::endl;
			}
		}
		else
		{
			std::cout << "It's a draw" << std::endl;
		}
	}
}