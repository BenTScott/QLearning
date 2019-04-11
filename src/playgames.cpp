#include "playgames.h"
#include <iostream>

double PlayTicTacToe(Agent<TicTacToeState, int> &agent_0, Agent<TicTacToeState, int> &agent_1, bool verbose)
{
	auto game = TicTacToe();

	game.Initialise();
	double reward;
	int a;
	while (!game.current_state.IsTerminal())
	{
		if (verbose)
		{
			std::cout << game.current_state.PrettyPrint() << std::endl;
		}
		if (game.current_player == 0)
		{
			a = agent_0.GetAction(game.current_state);
			if (verbose)
			{
				std::cout << "Player 0 plays: " << a << std::endl;
			}
		}
		else
		{
			a = agent_1.GetAction(game.current_state);
			if (verbose)
			{
				std::cout << "Player 1 plays: " << a << std::endl;
			}
		}
		reward = game.ApplyAction(a);
	}

	if (verbose)
	{
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

	return reward;
}