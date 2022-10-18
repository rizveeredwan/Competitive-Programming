#include <bits/stdc++.h>
using namespace std;

/* Base solution BFS*/

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
    void init(int node){
        this->edges.clear();
        this->weight.clear();
        vector<int>temp;
        for(int i=0; i<=node;i++){
            this->edges.push_back(temp);
        }
        return;
    }
    void input(){
        cin>>this->node>>this->edge_count;
        this->init(this->node);
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
    vector<int>dist;
    vector<int>color;
    vector<int>parent;
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
            //cout<<"top "<<u<<" "<<this->dist[u]<<endl;
            q.pop();
            for(int i=0; i<g.edges[u].size(); i++){
                if(this->color[g.edges[u][i]] == 0) {
                    this->color[g.edges[u][i]] = 1;
                    this->dist[g.edges[u][i]] = this->dist[u] + 1;
                    this->parent[g.edges[u][i]] = u;
                    q.push(g.edges[u][i]);
                    //cout<<g.edges[u][i]<<" "<<this->dist[g.edges[u][i]] << endl;
                    if(g.edges[u][i] == d) break; // already reached destination
                }
            }
            this->color[u] = 2; // black
        }
        this->print(d);
    }
    void init(Graph g){
        this->oneD_vector_init(g.node, this->INF, &this->dist); // not reachable
        this->oneD_vector_init(g.node, 0, &this->color); // white
        this->oneD_vector_init(g.node, -1, &this->parent); // parent tracking
        return;
    }
    void print(int d){
        if(this->dist[d] == this->INF) {
            cout<<"INF"<<endl;
        }
        else {
            cout<<this->dist[d]<<endl;
        }
    }
    void oneD_vector_init(int n, int value, vector<int> *temp){
        (*temp).clear();
         for(int i=0; i<=n; i++){
            (*temp).push_back(value);
         }
         return;
    }
    void print_path_edges(int des, int src){
        // to print the edges
        if(this->dist[des] != this->INF){
            vector<pair<int,int>>save;
            int curr = des;
            while(curr != src){
                save.push_back({this->parent[curr], curr});
                curr = this->parent[curr];
            }
            for(int i=save.size()-1; i>=0; i--){
                cout<<save[i].first<<" "<<save[i].second<<endl;
            }
            return;
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
