#include <iostream>
#include <bits/stdc++.h>

using namespace std;

#define NUM_OF_NEIGHBORS 6
#define NUM_OF_COORDS 3
#define MAX 30

int ROW = 0;
int COL = 0;
int LAY = 0;

struct Point {
    int x;
    int y;
    int z;
};

struct Node {
    Point point;
    int dist;
};

bool isInRange(int row, int col, int lay){
    return (row < ROW) && (row >= 0) &&
           (col < COL) && (col >= 0) &&
           (lay < LAY) && (lay >= 0); 
}


int neighbors[NUM_OF_NEIGHBORS][NUM_OF_COORDS] = {
    {-1, 0, 0}, {1, 0, 0}, {0, -1, 0}, {0, 1, 0}, {0, 0, -1}, {0, 0, 1}
};

int BFS(int maze[MAX][MAX][MAX], Point src, Point dest){
    if (!maze[src.z][src.x][src.y] || !maze[dest.z][dest.x][dest.y]){
        return -1;
    }

    bool visited[LAY][ROW][COL];
    memset(visited, false, sizeof(visited));
    visited[src.z][src.x][src.y] = true;
    
    Node source = {src, 0};
    queue<Node> q;
    q.push(source);

    while (!q.empty()){
        Node current = q.front();
        Point point = current.point;

        if (point.x == dest.x && point.y == dest.y && point.z == dest.z){
            return current.dist;
        }

        q.pop();

        for (int i = 0; i < NUM_OF_NEIGHBORS; i++){
            int row = point.x + neighbors[i][0];
            int col = point.y + neighbors[i][1];
            int lay = point.z + neighbors[i][2];

            if (isInRange(row, col, lay) && maze[lay][row][col] && !visited[lay][row][col]){
                visited[lay][row][col] = true;

                Point p = {row, col, lay};
                Node neighbor = {p, current.dist + 1};
                q.push(neighbor);
            }
        }
    }

    return -1;
}

int main(){

    int num;
    char c;
    Point src, dest;
    while (1){
        cin >> LAY >> ROW >> COL;

        if (LAY == 0 && ROW == 0 && COL == 0){
            break;
        }

        int maze[MAX][MAX][MAX];
        bool isStart = false;
        bool isEnd = false;

        for (int lay = 0; lay < LAY; lay++){
            for (int row = 0; row < ROW; row++){
                for (int col = 0; col < COL; col++){
                    cin >> c;
                    
                    if (c == '#'){
                        num = 0;
                    } else {
                        num = 1;

                        if (c == 'S'){
                            src = {row, col, lay};
                            isStart = true;
                        } else if (c == 'E'){
                            dest = {row, col, lay};
                            isEnd = true;
                        }
                    }

                    maze[lay][row][col] = num;
                }
            }
        }

        if (!isStart || !isEnd){
            cout << "Trapped!" << endl;
            continue;
        }

        int dist = BFS(maze, src, dest);

        if (dist == -1){
            cout << "Trapped!" << endl;
        } else {
            cout << "Escaped in " << dist << " minute(s)." << endl;
        }
    }

    return 0;
}