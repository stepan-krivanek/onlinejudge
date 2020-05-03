#include <iostream>
#include <bits/stdc++.h>

using namespace std;

struct Edge;
struct Node;

struct Edge{
    Node* from;
    Node* to;
    int cost;
    bool visited;
};

struct Node{
    int max_ppl = 0;
    bool visited = false;
    vector<Edge*> edges;
};

class pq {
    private:

    struct n {
        int priority;
        Node* node_ptr;
        struct n *next;
    };

    n* node = NULL;

    public:

    void push(Node* node_ptr){
        int priority = node_ptr->max_ppl;

        n *t, *q;
        t = new n;
        t->node_ptr = node_ptr;
        t->priority = priority;

        if (node == NULL || priority > node->priority){
            t->next = node;
            node = t;
        } else {
            
            q = node;
            while (q->next != NULL && q->next->priority >= priority){
                q = q->next;
            }

            t->next = q->next;
            q->next = t;
        }
    }

    Node* top(){
        n *t;
        if (node != NULL){
            t = node;
            Node* ret = t->node_ptr;
            node = node->next;
            free(t);
            return ret;
        }
    }

    bool empty(){
        if (node == NULL){
            return true;
        } else {
            return false;
        }
    }
};

int BFS(Node nodes[], int length, int src, int dest, int tourists){
    pq q;
    nodes[src].max_ppl = tourists + 1;
    q.push(&nodes[src]);
    
    while (!q.empty()){
        Node* current = q.top();

        if (!current->visited){
            current->visited = true;
        } else {
            continue;
        }

        for (int i = 0; i < current->edges.size(); i++){
            Edge* e = current->edges.at(i);
            if (e->visited){
                continue;
            } else {
                e->visited = true;
            }

            Node* node;
            if (e->from == current){
                node = e->to;
            } else {
                node = e->from;
            }

            int ppl = current->max_ppl < e->cost ? current->max_ppl : e->cost;
            node->max_ppl = ppl > node->max_ppl ? ppl : node->max_ppl;
            q.push(node);
        }
    }

    return (int)ceil((double)tourists / (double)(nodes[dest].max_ppl - 1));
}

int main(){
    int scenario = 0;
    int n, r;
    int src, dest, t;
    while(cin >> n >> r){
        if (n == 0){
            break;
        }

        scenario += 1;
        Node nodes[n];
        Edge edges[r];

        int n1, n2, cost;
        for (int i = 0; i < r; i++){
            cin >> n1 >> n2 >> cost;
            n1 -= 1;
            n2 -= 1;

            edges[i] = {&nodes[n1], &nodes[n2], cost, false};
            nodes[n1].edges.push_back(&edges[i]);
            nodes[n2].edges.push_back(&edges[i]);
        }
        cin >> src >> dest >> t;

        cout << "Scenario #" << scenario << endl;
        cout << "Minimum Number of Trips = " << BFS(nodes, n, src-1, dest-1, t) << endl;
        cout << endl;
    }

    return 0;
}