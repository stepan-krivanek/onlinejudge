#include <iostream>
#include <bits/stdc++.h>

using namespace std;

#define directions 4

struct Point{
    int row;
    int col;
};

int dir[directions][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}};

int DFS(char* maze, int rows, int cols, Point player){
    bool visited[rows][cols];
    memset(visited, false, sizeof(visited));

    stack<Point> s;
    s.push(player);
    visited[player.row][player.col] = true;

    int golds = 0;
    while (!s.empty()){
        Point current = s.top();
        s.pop();

        bool trap = false;
        for (int i = 0; i < directions; i++){
            int row = current.row + dir[i][0];
            int col = current.col + dir[i][1];
            
            if (*(maze + col + row*cols) == 'T'){
                trap = true;
                break;
            }
        }

        if(trap == true){
            continue;
        }

        for (int i = 0; i < directions; i++){
            int row = current.row + dir[i][0];
            int col = current.col + dir[i][1];
            
            if (visited[row][col] == false){
                if (*(maze + col + row*cols) == '.'){
                    visited[row][col] = true;
                    Point p = {row, col};
                    s.push(p);
                } else if (*(maze + col + row*cols) == 'G'){
                    golds += 1;
                    visited[row][col] = true;
                    Point p = {row, col};
                    s.push(p);
                }
            }
        }
    }

    return golds;
}

int main(){
    int rows, cols;
    while (cin >> cols >> rows){
        char arr[rows][cols];
        Point player;

        char c;
        for (int row = 0; row < rows; row++){
            for (int col = 0; col < cols; col++){
                cin >> c;
                arr[row][col] = c;
                
                if (c == 'P'){
                    player = {row, col};
                }
            }
        }

        cout << DFS((char*)arr, rows, cols, player) << endl;
    }

    return 0;
}