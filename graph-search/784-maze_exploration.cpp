#include <iostream>
#include <bits/stdc++.h>

using namespace std;

#define NUM_OF_NEIGHBORS 4
#define NUM_OF_COORDS 2

const int ROWS = 31;
const int COLS = 80;

struct Point {
    int row;
    int col;
};

int neighbors[NUM_OF_NEIGHBORS][NUM_OF_COORDS] = {
    {-1, 0}, {1, 0}, {0, -1}, {0, 1}
};

void BFS(char arr[ROWS][COLS]){
    Point src = {-1, -1};
    for (int row = 0; row < ROWS; row++){
        for (int col = 0; col < COLS; col++){
            if (arr[row][col] == '*'){
                src = {row, col};
                arr[row][col] = '#';
                break;
            }
        }

        if (src.row != -1){
            break;
        }
    }

    queue<Point> q;
    q.push(src);

    while(!q.empty()){
        Point current = q.front();
        q.pop();

        for (int i = 0; i < NUM_OF_NEIGHBORS; i++){
            int row = current.row + neighbors[i][0];
            int col = current.col + neighbors[i][1];

            if (row >= 0 && row < (ROWS-1) && col >= 0 && col < COLS){
                if (arr[row][col] == ' '){
                    arr[row][col] = '#';
                    Point p = {row, col};
                    q.push(p);
                }
            }
        }
    }
    
    int i = 0;
    while (1){
        char c;
        for (int j = 0; j < COLS; j++){
            c = arr[i][j];
            
            if (c == '\n'){
                break;
            }

            cout << c;
        }
        cout << endl;

        if (arr[i][0] == '_'){
            break;
        }
        i++;
    }
}

int main(){
    int cases;
    cin >> cases;
    getchar();
    for (int s = 0; s < cases; s++){
        char arr[ROWS][COLS];
        memset(arr, '\n', sizeof(arr));

        int i = 0;
        while (1){
            int j = 0;
            char c;
            while (1){
                c = getchar();
                if(c == '\n'){
                    break;
                }

                arr[i][j] = c;
                j++;
            }

            if (arr[i][0] == '_'){
                break;
            }

            i++;
        }

        BFS(arr);
    }

    return 0;
}