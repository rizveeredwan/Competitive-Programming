#include <bits/stdc++.h>
using namespace std;

#define MAX 10000

struct Graph{
    vector<int>edges[MAX+1];
    vector<int>weight[MAX+1];
    int node,edge_count;
    void add_edge_without_weight(int u, int v){
        this->edges[u].push_back(v);
    }
    void add_edge_with_weight(int u, int v, int w){
        this->add_edge_without_weight(u,v);
        this->weight[u].push_back(w);
    }
    void input(){
        cin>>this->node>>this->edge_count;
        int u,v;
        for(int i=0; i<this->edge_count; i++){
            cin>>u>>v;
            this->add_edge_without_weight(u,v);
            this->add_edge_without_weight(v,u);
        }
        //this->print_edges();
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

struct Bfs{
    int dist[MAX+1];
    int color[MAX+1];
    int parent[MAX+1];
    int INF = 100000000;
    void algorithm(Graph g, int s, int d){
        this->init(g);
        this->dist[s] = 0;
        this->color[s] = 1; // grey
        queue<int>q;
        q.push(s);
        int u;
        while(q.empty() != true){
            u = q.front();
            //cout<<"top "<<u<<endl;
            q.pop();
            for(int i=0; i<g.edges[u].size(); i++){
                if(this->color[g.edges[u][i]] == 0) {
                    this->color[g.edges[u][i]] = 1;
                    this->dist[g.edges[u][i]] = this->dist[u] + 1;
                    this->parent[g.edges[u][i]] = u;
                    q.push(g.edges[u][i]);
                    if(g.edges[u][i] == d) break; // already reached destination
                }
            }
            this->color[u] = 2; // black
        }
        this->print(d);
    }
    void init(Graph g){
        for(int i=1; i<=g.node; i++){
            this->dist[i] = this->INF;
            this->color[i] = 0; // white
            this->parent[i] = -1;  // parent tracking
        }
    }
    void print(int d){
        if(this->dist[d] == this->INF) {
            cout<<"INF"<<endl;
        }
        else {
            cout<<this->dist[d]<<endl;
        }
    }
};

int main(void){
    freopen("in1.txt", "r", stdin);
    Graph g;
    g.input();
    int s,d;
    cin>>s>>d;
    Bfs b;
    b.algorithm(g, s, d);
    return 0;
}
