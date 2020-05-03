#include <iostream>
#include <bits/stdc++.h>

using namespace std;

struct Plot{
    int x;
    int y;
};

struct Land{
    int* area;
    int rows;
    int cols;
};

int neightbors[8][2] = {
    {-1, -1}, {-1, 0}, {-1, 1}, {0, -1},
    {1, -1}, {1, 0}, {1, 1}, {0, 1}
};

void BFS(Land land, Plot plot){
    queue<Plot> q;
    q.push(plot);

    while (!q.empty()){
        Plot p = q.front();
        q.pop();

        for (int i = 0; i < 8; i++){
            int row = p.x + neightbors[i][0];
            int col = p.y + neightbors[i][1];

            int* index = (land.area + col + (row * land.cols));
            if ((row >= 0) && (row < land.rows) && (col >= 0) &&
                (col < land.cols) && (*index == 1))
            {
                *index = 0;
                Plot tmp = {row, col};
                q.push(tmp);
            }
        }
    }
}

int getPockets(Land land){
    int components = 0;

    int* ptr;
    for (int row = 0; row < land.rows; row++){
        for (int col = 0; col < land.cols; col++){
            ptr = (land.area + col + (row * land.cols));

            if (*ptr == 1){
                components += 1;
                *ptr = 0;

                Plot plot = {row, col};
                BFS(land, plot);
            }
        }
    }

    return components;
}


int main(){

    char c;
    bool num;
    int ROWS, COLS;
    while (1){
        cin >> ROWS >> COLS;
        if(ROWS == 0){
            break;
        }

        int table[ROWS][COLS];

        for (int row = 0; row < ROWS; row++){
            for (int col = 0; col < COLS; col++){
                cin >> c;

                if (c == '*'){
                    num = 0;
                } else {
                    num = 1;
                }

                table[row][col] = num;
            }
        }

        Land land = {(int*)table, ROWS, COLS};
        cout << getPockets(land) << endl;
    }
    
    return 0;
}