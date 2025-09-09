#include <bits/stdc++.h>
using namespace std;

class DFA
{
    int numStates;                        // Total number of states
    int initialState;                     // Starting state
    vector<int> finalStates;              // Accepting states
    map<pair<int, char>, int> transition; // Transition function

public:
    DFA(int states, int start, vector<int> finals)
    {
        numStates = states;
        initialState = start;
        finalStates = finals;
    }

    void addTransition(int from, char symbol, int to)
    {
        transition[{from, symbol}] = to;
    }

    bool isAccepted(const string &input)
    {
        int currentState = initialState;

        for (char symbol : input)
        {
            if (transition.find({currentState, symbol}) == transition.end())
            {
                return false; // No valid transition → reject
            }
            currentState = transition[{currentState, symbol}];
        }

        // Check if current state is in final states
        return find(finalStates.begin(), finalStates.end(), currentState) != finalStates.end();
    }
};

int main()
{
    // Example DFA: Accepts strings over {a,b} ending with "ab"
    int numStates = 3;
    int startState = 0;
    vector<int> finalStates = {2};

    DFA dfa(numStates, startState, finalStates);

    // Define transitions
    dfa.addTransition(0, 'a', 1);
    dfa.addTransition(0, 'b', 0);
    dfa.addTransition(1, 'a', 1);
    dfa.addTransition(1, 'b', 2);
    dfa.addTransition(2, 'a', 1);
    dfa.addTransition(2, 'b', 0);

    string input;
    cout << "Enter input string (over {a,b}): ";
    cin >> input;

    if (dfa.isAccepted(input))
    {
        cout << "✅ String ACCEPTED by DFA" << endl;
    }
    else
    {
        cout << "❌ String REJECTED by DFA" << endl;
    }

    return 0;
}
