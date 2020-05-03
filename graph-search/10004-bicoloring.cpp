#include <iostream>
#include <bits/stdc++.h>

using namespace std;

struct Node {
    bool color = NULL;
    vector<Node*> kids;
};

bool BFS(Node nodes[], int length){
    queue<Node*> q;
    nodes[0].color = true;
    q.push(&nodes[0]);

    bool bicolor = true;
    while(!q.empty()){
        Node* current = q.front();
        q.pop();

        for (int i = 0; i < current->kids.size(); i++){
            Node* node = current->kids.at(i);

            if (node->color == NULL){
                node->color = !current->color;
                q.push(node);
            } else if (node->color != !current->color){
                bicolor = false;
                break;
            }
        }

        if (bicolor == false){
            break;
        }
    }

    return bicolor;
}

int main(){
    int nodes, edges;
    while (1){
        cin >> nodes;
        if (nodes == 0){
            break;
        }
        cin >> edges;
        Node arr[nodes];

        int a, b;
        for (int i = 0; i < edges; i++){
            cin >> a >> b;

            arr[a].kids.push_back(&arr[b]);
            arr[b].kids.push_back(&arr[a]);
        }

        if (BFS(arr, nodes)){
            cout << "BICOLORABLE." << endl;
        } else {
            cout << "NOT BICOLORABLE." << endl;
        }
    }

    return 0;
}