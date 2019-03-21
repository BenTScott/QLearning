#include <iostream>
#include "qlearning.h"
#include "tictactoe.h"

int main(int argc, const char *argv[])
{
	auto r_learning = QLearning<TicTacToeState, int>(new TicTacToe(), 0.5, 1, 0.2);

	auto table = r_learning.Run(500000);

	std::cout << "Done training" << std::endl;

	while ((true))
	{

		auto game = TicTacToe();

		game.Initialise();

		while (!game.current_state.IsTerminal())
		{
			int action;
			std::cout << game.current_state.Hash() << std::endl;
			if (game.current_player == 0)
			{
				std::cout << "Enter an action (0-8): ";
				std::cin >> action;
				game.ApplyAction(action);
			}
			else
			{
				auto map = table.state_action_reward_map[game.current_state];
				auto actions = game.current_state.AvailableActions();
				// for (const auto &i : actions)
				// {
				// 	auto pair = map[i];
				// 	std::cout << std::get<0>(pair) << " " << std::get<1>(pair) << std::endl;
				// }
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