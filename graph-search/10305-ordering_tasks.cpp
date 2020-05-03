#include <iostream>
#include <bits/stdc++.h>

using namespace std;

struct Node {
    int parents;
    bool visited;
    vector<int> kids;
};

void BFS(Node nodes[], int length){
    queue<Node*> q;

    for (int i = 0; i < length; i++){
        Node* node = &nodes[i];

        if (node->parents == 0){
            cout << (i + 1) << " ";
            node->visited = true;
            q.push(node);
        }
    }

    while (!q.empty()){
        Node* current = q.front();
        q.pop();
        
        int index;
        Node* node;
        
        for (int i = 0; i < current->kids.size(); i++){
            index = current->kids.at(i);
            node = &nodes[index];
            
            if (!node->visited){
                node->parents -= 1;
                
                if(node->parents == 0){
                    cout << (index + 1) << " ";
                    node->visited = true;
                    q.push(node);
                }
            }
        }
    }

    cout << endl;
}

int main(){
    int from, to;
    int nodes, relations;
    while(1){
        cin >> nodes >> relations;
        if (nodes == 0){
            break;
        }

        Node arr[nodes];
        vector<int> kids;
        Node node = {0, false, kids};
        for(int i = 0; i < nodes; i++){
            arr[i] = node;
        }

        for (int i = 0; i < relations; i++){
            cin >> from >> to;
            from -= 1;
            to -= 1;

            arr[from].kids.push_back(to);
            arr[to].parents += 1;
        }
        
        BFS(arr, nodes);
    }

    return 0;
}