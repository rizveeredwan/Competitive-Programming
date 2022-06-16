#include <bits/stdc++.h>
using namespace std;

struct Graph{
    vector<vector<int>>edges;
    vector<vector<int>>weight;
    int node,edge_count;
    void add_edge_without_weight(int u, int v){
        this->edges[u].push_back(v);
    }
    void add_edge_with_weight(int u, int v, int w){
        this->add_edge_without_weight(u,v);
        this->weight[u].push_back(w);
    }
    void input(bool undirected, bool unweighted){
        cin>>this->node>>this->edge_count;
        cout<<this->node<<" "<<this->edge_count<<endl;
        this->init(this->node, unweighted);
        int u,v,w;
        for(int i=0; i<this->edge_count; i++){
            cin>>u>>v;
            if(unweighted == false) { // weighted graph
                cin>>w; // taking weight input
            }
            //cout<<u<<" "<<v<<" "<<w<<endl;
            if(unweighted == true) {
                this->add_edge_without_weight(u,v);
            }
            else { // weighted graph
                this->add_edge_with_weight(u,v,w);
            }
            if(undirected == true) {
                if(unweighted==true) this->add_edge_without_weight(v,u);
                else this->add_edge_with_weight(v,u,w);
            }
        }
        //this->print_edges();
    }
    void init(int node, bool unweighted){
        this->edges.clear();
        this->weight.clear();
        vector<int>temp;
        for(int i=0; i<=node;i++){
            this->edges.push_back(temp);
            if(unweighted == false) this->weight.push_back(temp);
        }
        return;
    }
    void print_edges(){
        cout<<this->node<< " " << this->edge_count<<endl;
        for(int i=1; i<=this->node; i++){
            for(int j=0; j<this->edges[i].size(); j++){
                cout<<this->edges[i][j]<<" ";
            }
            cout<<endl;
        }
    }
};


struct Node {
    int cost;
    int node;
};

struct CMP {
    bool operator () (Node n1, Node n2){
        if(n1.cost > n2.cost) return true;
        return false;
    }
};

struct MSTPrim {
    vector<int>dist;
    vector<bool>flag;
    priority_queue<Node, vector<Node>, CMP> pq;
    //priority_queue<Node> PQ;
    int INF = 100000000;
    void init(Graph g){
        this->dist.clear();
        this->flag.clear();
        for(int i=0; i<=g.node; i++){
            this->dist.push_back(this->INF);
            this->flag.push_back(false);
        }
    }
    void _insert(int node, int cost){
        Node n;
        n.node = node;
        n.cost = cost;
        pq.push(n);
    }
    int algorithm(Graph g){
        this->init(g);
        this->dist[1] = 0;
        int cost = 0;
        this->_insert(1, this->dist[1]);
        Node u;
        int v;
        int final_cost=0;
        while(this->pq.empty() != true){
            u = this->pq.top();
            if(this->flag[u.node] == false){
                this->flag[u.node] = true;
                final_cost += u.cost;
            }
            this->pq.pop();
            for(int i=0; i<g.edges[u.node].size(); i++){
                v = g.edges[u.node][i];
                if(this->dist[v] > g.weight[u.node][i] && this->flag[v] == false){
                    this->dist[v] = g.weight[u.node][i];
                    this->_insert(v, this->dist[v]);
                    cout<<u.node<<" v "<<v<<" "<<this->dist[v]<<endl;
                }
            }
        }
        return final_cost;
    }
};

/*
8 15
1 6 54
1 5 80
1 3 47
2 3 55
2 4 31
2 5 32
2 7 74
2 8 79
3 4 88
3 5 23
3 6 75
3 7 66
4 6 74
4 8 29
7 8 68
*/

/*

7 11
1 2 10
1 3 18
1 4 9
2 3 12
2 6 7
2 7 9
3 4 6
3 6 5
4 5 25
5 6 20
6 7 15
*/

int main(void){
    Graph g;
    g.input(true, false);
    MSTPrim m;
    cout<< m.algorithm(g)<<endl;
    return 0;
}
