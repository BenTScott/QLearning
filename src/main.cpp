#include <iostream>
#include "qlearning.h"
#include "tictactoe.h"
#include "playgames.h"
#include "agents.h"

int main(int argc, const char *argv[])
{
	auto r_learning = QLearning<TicTacToeState, int>(new TicTacToe(), 0.2, 0.9, 0.05);

	r_learning.Run(100000);

	PolicyAgent<TicTacToeState, int> agent_1mil;
	agent_1mil.ImportPolicy("out/tictactoepolicy-1mil-iter.dat");

	PolicyAgent<TicTacToeState, int> agent_25mil;
	agent_25mil.ImportPolicy("out/tictactoepolicy-25mill-iter-optimal.dat");

	r_learning.Run(100000, &agent_1mil);
	auto agent = r_learning.Run(100000, &agent_25mil);

	std::cout << "Done training" << std::endl;

	auto test_agent = agent.CreateTestingAgent();

	double total_reward = 0;
	for (int i = 0; i < 10000; i++)
	{
		total_reward += PlayTicTacToe(test_agent, agent_1mil);
	}
	std::cout << "Reward for new agent vs 1mil " << total_reward << std::endl;

	total_reward = 0;
	for (int i = 0; i < 10000; i++)
	{
		total_reward += PlayTicTacToe(test_agent, agent_25mil);
	}
	std::cout << "Reward for new agent vs 25mil " << total_reward << std::endl;

	RandomAgent<TicTacToeState, int> rand_agent;
	total_reward = 0;
	for (int i = 0; i < 10000; i++)
	{
		total_reward += PlayTicTacToe(test_agent, rand_agent);
	}
	std::cout << "Reward for new agent vs rand " << total_reward << std::endl;

	total_reward = 0;
	for (int i = 0; i < 10000; i++)
	{
		total_reward += PlayTicTacToe(agent_1mil, rand_agent);
	}
	std::cout << "Reward for new 1mil vs rand " << total_reward << std::endl;

	total_reward = 0;
	for (int i = 0; i < 10000; i++)
	{
		total_reward += PlayTicTacToe(agent_1mil, rand_agent);
	}
	std::cout << "Reward for new 25mil vs rand " << total_reward << std::endl;
}