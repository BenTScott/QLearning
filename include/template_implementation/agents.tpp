#include "agents.h"
#include <fstream>
#include <vector>
#include "utilities.h"

#pragma region POLICYAGENT

template <typename State, typename Action>
void PolicyAgent<State, Action>::ImportPolicy(std::string filename)
{
    std::ifstream ifs(filename, std::ifstream::in);
    std::string line;

    while (getline(ifs, line))
    {
        if (line != "")
        {
            State state;
            Action action;

            std::istringstream ss(line);
            ss >> state;
            ss >> action;

            map[state] = action;
        }
    }
    ifs.close();
}

template <typename State, typename Action>
void PolicyAgent<State, Action>::ExportPolicy(const std::string &filename)
{
    std::ofstream output_file;
    output_file.open(filename);
    for (auto &pair : this->map)
    {
        output_file << pair.first << " " << pair.second << std::endl;
    }
    output_file.close();
}

template <typename State, typename Action>
Action PolicyAgent<State, Action>::GetAction(const State &state)
{
    if (map.count(state))
    {
        return map[state];
    }

    std::vector<Action> av_actions = state.AvailableActions();
    return *RandomElement(av_actions.begin(), av_actions.end());
}

#pragma endregion POLICYAGENT

#pragma region RANDOMAGENT

template <typename State, typename Action>
Action RandomAgent<State, Action>::GetAction(const State &state)
{
    std::vector<Action> av_actions = state.AvailableActions();
    return *RandomElement(av_actions.begin(), av_actions.end());
}

#pragma endregion RANDOMAGENT

#pragma region QLEARNINGAGENT

template <typename State, typename Action>
Action QLearningAgent<State, Action>::GetAction(const State &state)
{
    this->previous_state = new State(state);

    double r = Random::Uniform(0.0, 1.0);

    if (r <= epsilon)
    {
        std::vector<Action> av_actions = state.AvailableActions();
        this->previous_action = new Action(*RandomElement(av_actions.begin(), av_actions.end()));
    }
    else
    {
        this->previous_action = new Action(q_table.GetBestAction(state));
    }

    return *this->previous_action;
}

template <typename State, typename Action>
void QLearningAgent<State, Action>::ApplyReward(const State &new_state, double reward)
{
    if (this->previous_state && this->previous_action)
    {
        this->q_table.UpdateAction(*previous_state, *previous_action, reward, new_state);
    }
}

template <typename State, typename Action>
PolicyAgent<State, Action> QLearningAgent<State, Action>::CreateTestingAgent()
{
    std::map<State, Action> policy;

    std::transform(
        q_table.state_action_reward_map.begin(),
        q_table.state_action_reward_map.end(),
        std::inserter(policy, policy.end()),
        [](std::pair<State, MaximalMap<Action, double>> a) -> std::pair<State, Action> {
            return std::pair<State, Action>(std::get<0>(a), std::get<1>(a).MaxKey());
        });

    return PolicyAgent<State, Action>(policy);
}

#pragma endregion QLEARNINGAGENT

#pragma region PLAYERAGENT

template <typename State, typename Action>
Action PlayerAgent<State, Action>::GetAction(const State &state)
{
    Action action;
    std::cout << "Enter an action: ";
    std::cin >> action;
    return action;
}

#pragma endregion PLAYERAGENT