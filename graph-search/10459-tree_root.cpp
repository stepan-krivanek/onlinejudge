#include <iostream>
#include <bits/stdc++.h>

using namespace std;

struct Node{
    int kids_num = 0;
    bool visited = false;
    vector<int> kids;
};

struct Tree{
    int depth;
    int num_of_roots;
    int roots[2];
};

vector<int> getWorstRoots(Tree tree, Node nodes[], int length){
    
    for (int i = 0; i < length; i++){
        nodes[i].visited = false;
    }

    queue<Node*> q;

    for (int i = 0; i < tree.num_of_roots; i++){
        Node* node = &nodes[tree.roots[i]];
        node->visited = true;
        q.push(node);
    }

    int depth = 1;
    while (depth < tree.depth){
        depth += 1;

        int size = q.size();
        for (int i = 0; i < size; i++){
            Node* current = q.front();
            q.pop();

            for (int j = 0; j < current->kids.size(); j++){
                Node* node = &nodes[current->kids.at(j)];

                if (node->visited == false){
                    node->visited = true;
                    q.push(node);
                }
            }
        }
    }
    
    vector<int> worst_roots;
    for (int i = 0; i < length; i++){
        if (nodes[i].visited == false){
            worst_roots.push_back(i);
        }
    }

    return worst_roots;
}

Tree getBestRoots(Node nodes[], int length){
    queue<Node*> q;

    for (int i = 0; i < length; i++){
        Node* node = &nodes[i];

        if (node->kids.size() == 1){
            node->visited = true;
            q.push(node);
        }
    }

    int depth = 0;
    while (length > 2){
        depth += 1;

        int size = q.size();
        for (int i = 0; i < size; i++){
            Node* current = q.front();
            q.pop();
            length -= 1;

            int index;
            for (int j = 0; j < current->kids.size(); j++){
                index = current->kids.at(j);
                Node* node = &nodes[index];
                
                if (node->visited == false){
                    node->kids_num += 1;

                    if ((node->kids.size() - node->kids_num) == 1){
                        node->visited = true;
                        q.push(node);
                    }
                }
            }
        }
    }

    Tree tree = {depth, length};

    int root = q.front() - &nodes[0];
    q.pop();
    tree.roots[0] = root;

    if (length == 2){
        root = q.front() - &nodes[0];
        q.pop();
        tree.roots[1] = root;
    }

    return tree;
}

int main(){

    int length;
    while (cin >> length){
        Node nodes[length];

        int neighbors;
        for (int i = 0; i < length; i++){
            cin >> neighbors;

            int neighbor;
            for (int j = 0; j < neighbors; j++){
                cin >> neighbor;
                nodes[i].kids.push_back(neighbor - 1);
            }
        }

        Tree tree = getBestRoots(nodes, length);

        if (tree.num_of_roots == 2){
            if (tree.roots[1] < tree.roots[0]){
                int tmp = tree.roots[1];
                tree.roots[1] = tree.roots[0];
                tree.roots[0] = tmp;
            }
        }
        
        cout << "Best Roots  :";
        for (int i = 0; i < tree.num_of_roots; i++){
            cout << " " << (tree.roots[i] + 1);
        }
        cout << endl;

        vector<int> worst_roots = getWorstRoots(tree, nodes, length);
        
        cout << "Worst Roots :";
        for (int i = 0; i < worst_roots.size(); i++){
            cout << " " << worst_roots.at(i) + 1;
        }
        cout << endl;
    }

    return 0;
}