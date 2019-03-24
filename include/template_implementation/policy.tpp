#include "policy.h"
#include <fstream>
#include <vector>
#include "utilities.h"

template <typename State, typename Action>
void Policy<State, Action>::ImportPolicy(std::string filename)
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
Action Policy<State, Action>::GetAction(const State &state)
{
    if (map.count(state))
    {
        return map[state];
    }

    std::vector<Action> av_actions = state.AvailableActions();
    return *RandomElement(av_actions.begin(), av_actions.end());
}