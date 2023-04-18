#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

const double tol = 1e-5;  // convergence tolerance
const int num_states = 10;  // number of states
const int num_actions = 2;  // number of actions
const double gamma_val = 0.9;  // discount factor

// reward function
vector<double> reward_function = {0, 0, 0, 0, 1000, 0, 0, 0, 0, 0};

// transition model
vector<vector<vector<double>>> transition_model = {
    {{0.7, 0.3}, {0.3, 0.7}},
    {{0.7, 0.3}, {0.3, 0.7}},
    {{0.7, 0.3}, {0.4, 0.6}},
    {{0.8, 0.2}, {0.2, 0.8}},
    {{0, 0}, {0, 0}},
    {{0.8, 0.2}, {0.3, 0.7}},
    {{0.7, 0.3}, {0.1, 0.9}},
    {{0.8, 0.2}, {0.4, 0.6}},
    {{0.5, 0.5}, {0.5, 0.5}},
    {{0, 0}, {0, 0}}
};

// value iteration function
vector<int> value_iteration() {
    vector<double> values(num_states, 0);  // initialize values to zero
    vector<double> temp_values(num_states, 0);
    double delta = 0;

    vector<int> policy(num_states, 0); // initialize policy to 0

    while (true) {
        delta = 0;
        for (int s = 0; s < num_states; s++) {
            double temp = values[s];
            vector<double> v_list(num_actions, 0);
            for (int a = 0; a < num_actions; a++) {
                vector<double> p = transition_model[s][a];
                double v = reward_function[s];
                for (int sp = 0; sp < num_states; sp++) {
                    v += gamma_val * p[sp] * values[sp];
                }
                v_list[a] = v;
            }
            auto best_action = std::max_element(v_list.begin(), v_list.end()); // get the best action for state s
            policy[s] = std::distance(v_list.begin(), best_action); // store the index of the best action
            values[s] = *best_action;  // update values
            delta = max(delta, abs(temp - values[s]));  // compute change in values
        }
        if (delta < tol) {
            break;  // convergence achieved
        }
    }
    return policy;
}

int main() {
    vector<int> policy = value_iteration();
    cout << "Optimal policy: [";
    for (int s = 0; s < num_states; s++) {
        cout << policy[s] << ", ";
    }
    cout << "]" << endl;
    return 0;
}
