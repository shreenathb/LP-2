#include <iostream>
using namespace std;
const int N = 8;

void printSol(int ** board){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cout << board[i][j];
        }cout << endl;
    }cout << endl;
}

bool check(int ** board, int row , int col){
    for(int i=0;i<N;i++){
        if(board[i][col] == 1 || board[row][i] == 1)return false;
    }

    // top left
    int i=row;
    int j = col;

    while(i>=0 && j >= 0){
        if(board[i][j] == 1)return false;
        i--;
        j--;
    }

    i=row;
    j = col;

    // bottom left
    while(i<N && j >= 0){
        if(board[i][j] == 1)return false;
        i++;
        j--;
    }


    i = row;
    j = col;
    // bottom right
    while(i<N && j <N){
        if(board[i][j] == 1)return false;
        i++;
        j++;
    }

    // top right
    i = row;
    j = col;
    while(i>=0 && j <N){
        if(board[i][j] == 1)return false;
        i--;
        j++;
    }
    return true;
}

void solveNQueens(int ** board, int col){
    if(col >= N){
        printSol(board);
        return;
    }

    for(int i=0;i<N;i++){

        if(check(board, i , col)){
            board[i][col] = 1;
            solveNQueens(board, col+1);
            board[i][col] = 0;
        }
    }
}

int main(){
    int ** board = new int*[N];
    for(int i=0;i<N;i++){
        board[i] = new int[N];
    }

    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            board[i][j] = 0;
        }
    }

    solveNQueens(board, 0);
}