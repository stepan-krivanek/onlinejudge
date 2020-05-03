#include <iostream>
#include <bits/stdc++.h>

using namespace std;

#define NUM_OF_NEIGHBORS 4
#define NUM_OF_COORDS 2

struct Point {
    int row;
    int col;
};

int neighbors[NUM_OF_NEIGHBORS][NUM_OF_COORDS] = {
    {-1, 0}, {1, 0}, {0, -1}, {0, 1}
};

int getMoves(char* maze, int rows, int cols, Point joe, vector<Point> fire){
    queue<Point> q;
    q.push(joe);

    queue<Point> f;
    for (int i = 0; i < fire.size(); i++){
        f.push(fire.at(i));
    }

    int dist = 0;
    bool escaped = false;
    while (!q.empty()){
        dist += 1;

        int size = q.size();
        for (int s = 0; s < size; s++){
            Point current = q.front();
            q.pop();

            if (*(maze + current.col + current.row*cols) == 'F'){
                continue;
            }

            for (int i = 0; i < NUM_OF_NEIGHBORS; i++){
                int row = current.row + neighbors[i][0];
                int col = current.col + neighbors[i][1];

                if (row >= rows || row < 0 || col >= cols || col < 0){
                    escaped = true;
                    break;
                }

                char* ptr = (maze + col + row*cols);
                if (*ptr == '.'){
                    *ptr = 'J';
                    Point p = {row, col};
                    q.push(p);
                }
            }

            if (escaped){
                break;
            }
        }

        if (escaped){
            break;
        }

        size = f.size();
        for (int s = 0; s < size; s++){
            Point current = f.front();
            f.pop();

            for (int i = 0; i < NUM_OF_NEIGHBORS; i++){
                int row = current.row + neighbors[i][0];
                int col = current.col + neighbors[i][1];

                if (row < 0 || row >= rows || col < 0 || col >= cols){
                    continue;
                }

                char* ptr = (maze + col + row*cols);
                if (*ptr == '.' || *ptr == 'J'){
                    *ptr = 'F';
                    Point p = {row, col};
                    f.push(p);
                }
            }
        }
    }
    
    if (escaped){
        return dist;
    }

    return -1;
}

int main(){
    int cases;
    cin >> cases;

    for (int i = 0; i < cases; i++){
        int rows, cols;
        cin >> rows >> cols;

        char c;
        char maze[rows][cols];
        Point joe;
        vector<Point> fire;
        for (int row = 0; row < rows; row++){
            for (int col = 0; col < cols; col++){
                cin >> c;
                maze[row][col] = c;

                if (c == 'F'){
                    Point p = {row, col};
                    fire.push_back(p);
                } else if (c == 'J'){
                    joe = {row, col};
                }
            }
        }

        int moves = getMoves((char*)maze, rows, cols, joe, fire);

        if (moves == -1){
            cout << "IMPOSSIBLE" << endl;
        } else {
            cout << moves << endl;
        }
    }
   
    return 0;
}