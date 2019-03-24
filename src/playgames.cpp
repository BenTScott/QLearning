#include "playgames.h"
#include <iostream>

void PlayTicTacToe(Policy<TicTacToeState, int> &policy)
{
	auto game = TicTacToe();

	game.Initialise();

	while (!game.current_state.IsTerminal())
	{
		int action;
		std::cout << game.current_state.PrettyPrint() << std::endl;
		if (game.current_player == 0)
		{
			std::cout << "Enter an action (0-8): ";
			std::cin >> action;
			game.ApplyAction(action);
		}
		else
		{
			action = policy.GetAction(game.current_state); //q_table.GetBestAction(game.current_state);
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