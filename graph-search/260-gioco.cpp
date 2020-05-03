#include <iostream>
#include <bits/stdc++.h>

using namespace std;
#define NEIGHBORS 6

struct Point {
    int row;
    int col;
};

int neighbors[NEIGHBORS][2] = {
    {-1, -1}, {-1, 0}, {0, -1}, {1, 0}, {1, 1}, {0, 1}
};

char BFS(char arr[200][200], int size){
    int length = size*size;
    bool visited[size][size];
    memset(visited, false, length);

    queue<Point> q;

    for (int row = 0; row < size; row++){
        for (int col = 0; col < size; col++){
            if (visited[row][col]){
                continue;
            }

            Point point = {row, col};
            visited[row][col] = true;
            q.push(point);

            bool top = false;
            bool bot = false;
            while (!q.empty()){
                Point current = q.front();
                q.pop();

                char ch = arr[current.row][current.col];
                if ((ch == 'b' && current.row == 0) || (ch == 'w' && current.col == 0)){
                    top = true;
                }

                if ((ch == 'b' && current.row == (size-1)) || (ch == 'w' && current.col == (size-1))){
                    bot = true;
                }

                for (int i = 0; i < NEIGHBORS; i++){
                    int r = current.row + neighbors[i][0];
                    int c = current.col + neighbors[i][1];

                    if (r >= 0 && r < size && c >= 0 && c < size &&
                        !visited[r][c] && ch == arr[r][c])
                    {
                        visited[r][c] = true;
                        Point p = {r,c};
                        q.push(p);
                    }
                }
            }

            if (top && bot){
                char c = arr[row][col];
                if (c == 'w'){
                    return 'W';
                } else {
                    return 'B';
                }
            }
        }
    }

    return 'e';
}

int main(){

    int size;
    int round = 0;
    while(1){
        round += 1;
        cin >> size;
        if (size == 0){
            break;
        }

        char arr[200][200];

        char c;
        for (int row = 0; row < size; row++){
            for (int col = 0; col < size; col++){
                cin >> c;
                arr[row][col] = c;
            }
        }

        char winner = BFS(arr, size);

        cout << round << " " << winner << endl;
    }

    return 0;
}