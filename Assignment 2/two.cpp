#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

const int N = 3;


class PuzzleState{
public:
    int puzzle[3][3];
    int zeroRow;
    int zeroCol;
    int g;
    int h;

    bool operator < (const PuzzleState & other)const {
        return g+h > other.g + other.h;
    }


};


void aStarSearch(const PuzzleState &initialState, const PuzzleState &finalState) {
    priority_queue<PuzzleState> pq;
    unordered_set<int> visited;

    pq.push(initialState);

    while (!pq.empty()) {
        PuzzleState current = pq.top();
        pq.pop();

        cout << "Current State:\n";
        printPuzzle(current);
        cout << "Number of moves: " << current.g << endl;
        cout << "Heuristic cost: " << current.h << endl;
        cout << "-------------------\n";

        if (isEqual(current, finalState)) {
            cout << "Goal State Reached!\n";
            cout << "Number of moves: " << current.g << endl;
            cout << "Heuristic cost: " << current.h << endl;
            break;
        }

        vector<PuzzleState> nextStates = generateNextStates(current);

        for (const PuzzleState &nextState : nextStates) {
            int hash = 0;
            for (int i = 0; i < N; i++)
                for (int j = 0; j < N; j++)
                    hash = hash * 10 + nextState.puzzle[i][j];

            if (visited.find(hash) == visited.end()) {
                pq.push(nextState);
                visited.insert(hash);
            }
        }
    }
}


PuzzleState getPuzzleState(const string &prompt) {
    PuzzleState state;

    cout << prompt << " (0 represents the empty tile):\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << "Enter value at position (" << i << ", " << j << "): ";
            cin >> state.puzzle[i][j];

            if (state.puzzle[i][j] == 0)
            {
                state.zeroRow = i;
                state.zeroCol = j;
            }
        }
    }

    state.g = 0;
    state.h = calculateManhattanDistance(state);

    return state;
}

int main(){
    PuzzleState initialState = getPuzzleState("Enter the initial state of the puzzle");
    PuzzleState finalState = getPuzzleState("Enter the final state of the puzzle");

    cout << "Initial State:\n";
    printPuzzle(initialState);

    aStarSearch(initialState, finalState);

    return 0;

}