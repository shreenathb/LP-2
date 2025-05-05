#include <iostream>

using namespace std;

bool isSafe(int n,int row, int col, int **board){

    for(int i=0;i<n;i++){
        if(board[row][i] == 1 || board[i][col] == 1)return false;
    }

    // top right diag
    int i = row;
    int j = col;
    while(i>=0 && j < n){
        if(board[i][j] == 1){
            return false;
        }
        i--;
        j++;
    }

    // top left diag
    i = row;
    j = col;
    while(i>=0 && j >=0){
        if(board[i][j] == 1){
            return false;
        }
        i--;
        j--;
    }

    // bottom left diag
    i = row;
    j = col;
    while(i<n && j >=0){
        if(board[i][j] == 1){
            return false;
        }
        i++;
        j--;
    }

    // bottom right diag
    i = row;
    j = col;
    while(i<n && j < n){
        if(board[i][j] == 1){
            return false;
        }
        i++;
        j++;
    }

    return true;
}

bool solve(int n, int ** board, int col){
    if(col >= n)return true;

    for(int i=0;i<n;i++){
        if(isSafe(n, i, col, board)){
            board[i][col] = 1;
            if(solve(n, board, col+1)){
                return true;
            }
            board[i][col] = 0;
        }
    }
    return false;
}

void printSolution(int **board, int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << board[i][j] << " ";
    }
    cout << endl;
  }
}

int main(){
    int n;

    cout << "Enter the value of n: ";
    cin >> n;

    int ** board = new int*[n];

    for(int i=0;i<n;i++){
        board[i] = new int[n];
    }

    if (solve(n, board, 0)) {
        cout << "Solution exists:" << endl;
        printSolution(board, n);
    } else {
        cout << "No solution exists" << endl;
    }
}