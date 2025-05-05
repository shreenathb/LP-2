#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <queue>
#include <unordered_set>

using namespace std;

const int N = 3;

class PuzzleState{
public:
    int puzzleState[N][N];
    int zeroRow;
    int zeroCol;
    int g;
    int h;

    bool operator < (const PuzzleState &other) const{
        return (g+h) > (other.g + other.h);
    }
};

void printPuzzle(const PuzzleState &state){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            cout << state.puzzleState[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

bool isEqual(const PuzzleState &state1, const PuzzleState &state2){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(state1.puzzleState[i][j] != state2.puzzleState[i][j] ){
                return false;
            }
        }
    }
    return true;
}

int calcManhattanDistance(const PuzzleState &currentState){
    int dist = 0;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            int value = currentState.puzzleState[i][j];

            if(value != 0){
                int target_i = (value-1)/N;
                int target_j = (value-1)%N;

                dist += abs(i-target_i) + abs(j-target_j);  
            }
        }
    }
    return dist;
}

bool isValid(int row, int col){
    return (row >=0 && row < N && col >= 0 && col < N);
}

vector<PuzzleState> generateNextStates(const PuzzleState &currentState){
    vector<PuzzleState>nextStates;

    int moves[4][2] = {
        {1, 0},
        {-1, 0},
        {0, -1},
        {0, 1}
    };

    for(int k=0;k<4;k++){
        

        int nextZeroRow = currentState.zeroRow + moves[k][0];
        int nextZeroCol = currentState.zeroCol + moves[k][1];

        if(isValid(nextZeroRow, nextZeroCol)){
            PuzzleState nextState = currentState;

            swap(nextState.puzzleState[nextZeroRow][nextZeroCol], 
            nextState.puzzleState[currentState.zeroRow][currentState.zeroCol]);

            nextState.zeroCol = nextZeroCol;
            nextState.zeroRow = nextZeroRow;

            int next_g = currentState.g + 1;
            int next_h = calcManhattanDistance(currentState);

            nextState.g = next_g;
            nextState.h = next_h;

            nextStates.push_back(nextState);

        }
    }

    return nextStates;
}

void aStarSearch(const PuzzleState &initialState, const PuzzleState &finalState){
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
                    hash = hash * 10 + nextState.puzzleState[i][j];

            if (visited.find(hash) == visited.end()) {
                pq.push(nextState);
                visited.insert(hash);
            }
        }
    }
}

PuzzleState getPuzzleState(const string &prompt) {
    PuzzleState state;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << "Enter value at position (" << i << ", " << j << "): ";
            cin >> state.puzzleState[i][j];

            if (state.puzzleState[i][j] == 0)
            {
                state.zeroRow = i;
                state.zeroCol = j;
            }
        }
    }

    state.g = 0;
    state.h = calcManhattanDistance(state);

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