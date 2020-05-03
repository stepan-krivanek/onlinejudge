#include <iostream>
#include <bits/stdc++.h>

using namespace std;

struct Node{
    int edges = 0;
    bool visited = false;
    vector<Node*> neighbors;
};

bool BFS(Node nodes[], int length){

    queue<Node> q;
    for (int i = 0; i < length; i++){
        if (nodes[i].edges > 0){
            nodes[i].visited = true;
            q.push(nodes[i]);
            break;
        }
    }
    
    if (q.empty()){
        return false;
    }

    while (!q.empty()){
        Node current = q.front();
        q.pop();

        for (int i = 0; i < current.neighbors.size(); i++){
            Node* node = current.neighbors.at(i);

            if (node->visited == false){
                node->visited = true;
                q.push(*node);
            }
        }
    }

    bool possible = true;
    for (int i = 0; i < length; i++){
        if (nodes[i].edges > 0 && nodes[i].visited == false){
            possible = false;
            break;
        }
    }

    return possible;
}

int main(){

    int nodes, edges;
    while(cin >> nodes >> edges){
        Node arr[nodes];

        for (int i = 0; i < nodes; i++){
            Node node = {0, false};
            arr[i] = node;
        }

        int from, to;
        for (int i = 0; i < edges; i++){
            cin >> from;
            cin >> to;

            arr[from].edges += 1;
            arr[to].edges += 1;

            arr[from].neighbors.push_back(&arr[to]);
            arr[to].neighbors.push_back(&arr[from]);
        }

        bool possible = true;
        for (int i = 0; i < nodes; i++){
            if (arr[i].edges % 2 != 0){
                possible = false;
                break;
            }
        }

        if (possible && BFS(arr, nodes)){
            cout << "Possible" << endl;
        } else {
            cout << "Not Possible" << endl;
        }
    }

    return 0;
}