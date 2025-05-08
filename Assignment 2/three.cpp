#include <iostream>
#include <queue>
#include <algorithm>
#include <unordered_set>

using namespace std;

const int N =3 ;

class PuzzleState{
public:
    int puzzle[3][3];
    int g;
    int h;
    int zeroRow;
    int zeroCol;

    bool operator < (const PuzzleState & other) const{
        return (g+h) > (other.g + other.h);
    }
};

int calcManhattanDist(PuzzleState state){
    int dist = 0;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            int value = state.puzzle[i][j];
            if(value != 0){
                int target_i = (value-1)/N;
                int target_j = (value-1)%N;

                dist += (abs(target_i-i) + abs(target_j-j));
            }
        }
    }

    return dist;
}

bool isValid(int i, int j){
    return (i>=0 && i<3 && j >=0 && j<3);
}

void printPuzzle(PuzzleState cur){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            cout << cur.puzzle[i][j];
        }
        cout << endl;
    }cout << endl;
}

vector<PuzzleState> generateNextStates(PuzzleState currentState){
    vector<PuzzleState> nextStates;

    int moves[4][2] = {{1,0}, {0, 1}, {-1, 0}, {0, -1}};
    

    for(int i=0;i<4;i++){
        int nextRow = currentState.zeroRow + moves[i][0];
        int nextCol = currentState.zeroCol + moves[i][1];

        PuzzleState newState;

        if(isValid(nextRow, nextCol)){
            newState = currentState;
            swap(newState.puzzle[currentState.zeroRow][currentState.zeroCol], 
            newState.puzzle[nextRow][nextCol]);

            newState.zeroRow = nextRow;
            newState.zeroCol = nextCol;

            newState.g = currentState.g + 1;
            newState.h = calcManhattanDist(newState);

        
            nextStates.push_back(newState);
        }
    }

    return nextStates;
}

bool isEqual(PuzzleState current, PuzzleState final){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(current.puzzle[i][j] != final.puzzle[i][j]){
                return false;
            }
        }
    }
    return true;
}

void aStar(PuzzleState initial, PuzzleState final){
    priority_queue<PuzzleState, vector<PuzzleState>>pq;
    unordered_set<string>s;

    pq.push(initial);

    string temp = "";
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            temp += to_string(initial.puzzle[i][j]);
        }
    }

    s.insert(temp);

    while(!pq.empty()){
        PuzzleState currentState = pq.top();
        pq.pop();

        printPuzzle(currentState);

        if(isEqual(currentState, final)){
            cout << "Done\n";
            cout << currentState.g << " " << currentState.h << endl;

            printPuzzle(currentState);
            
            return;
        }

        vector<PuzzleState>nextStates = generateNextStates(currentState);

       

        for(PuzzleState state : nextStates){
            string temp = "";
            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                    temp += to_string(state.puzzle[i][j]);
                }
            }
            if(!s.count(temp)){
                s.insert(temp);
                pq.push(state);
            }
        }

    }
}

PuzzleState getPuzzleState(){
    PuzzleState state;
    cout << "Enter the puzzle\n";
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            cin >> state.puzzle[i][j];
            if(state.puzzle[i][j] == 0){
                state.zeroRow = i;
                state.zeroCol = j;
            }
        }
    }

    state.g = 0;
    state.h = calcManhattanDist(state);

    return state;

}

int main(){
    PuzzleState initial = getPuzzleState();
    PuzzleState final = getPuzzleState();

    aStar(initial, final);
}