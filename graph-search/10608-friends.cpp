#include <iostream>
#include <bits/stdc++.h>

using namespace std;

struct Node{
    bool visited = false;
    vector<Node*> friends;
};

int BFS(Node ppl[], int length){
    int max = 0;

    for (int i = 0; i < length; i++){
        if (ppl[i].visited == false){
            ppl[i].visited = true;
            queue<Node*> q;
            q.push(&ppl[i]);
            
            int friends = 0;
            while (!q.empty()){
                Node* current = q.front();
                q.pop();
                friends += 1;

                for (int j = 0; j < current->friends.size(); j++){
                    Node* node = current->friends.at(j);

                    if (node->visited == false){
                        node->visited = true;
                        q.push(node);
                    }
                }
            }

            max = max > friends ? max : friends;
        }
    }

    return max;
}

int main(){
    int sets;
    cin >> sets;

    int ppl, pairs;
    for (int i = 0; i < sets; i++){
        cin >> ppl >> pairs;

        Node arr[ppl];

        int f1, f2;
        for (int j = 0; j < pairs; j++){
            cin >> f1 >> f2;
            f1 -= 1;
            f2 -= 1;

            arr[f1].friends.push_back(&arr[f2]);
            arr[f2].friends.push_back(&arr[f1]);
        }

        cout << BFS(arr, ppl) << endl;
    }

    return 0;
}