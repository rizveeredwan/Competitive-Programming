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
    vector<int>explore_id;
    int INF = 100000000;
    void algorithm(Graph g, int s, int d){
        for(int i=0; i<g.edges.size(); i++){
            sort(g.edges[i].begin(), g.edges[i].end());
        }
        this->init(g);
        this->dist[s] = 0;
        this->color[s] = 1; // grey
        this->explore_id[s] = 1;
        int cnt = 1;
        queue<int>q;
        q.push(s);
        int u;
        while(q.empty() != true){
            u = q.front();
            if(u == d) break; // goal destination
            q.pop();
            for(int i=0; i<g.edges[u].size(); i++){
                if(this->color[g.edges[u][i]] == 0) {
                    this->color[g.edges[u][i]] = 1;
                    this->dist[g.edges[u][i]] = this->dist[u] + 1;
                    this->parent[g.edges[u][i]] = u;
                    q.push(g.edges[u][i]);
                    cnt += 1;
                    this->explore_id[g.edges[u][i]] = cnt;
                    //cout<<g.edges[u][i]<<" "<<this->dist[g.edges[u][i]] << endl;
                }
            }
            this->color[u] = 2; // black
        }
        this->print(d);
        this->print_path_edges(d,s);
        this->print_explore_id(g);
    }
    void init(Graph g){
        this->oneD_vector_init(g.node, this->INF, &this->dist); // not reachable
        this->oneD_vector_init(g.node, 0, &this->color); // white
        this->oneD_vector_init(g.node, -1, &this->parent); // parent tracking
        this->oneD_vector_init(g.node, -1, &this->explore_id); // exploring the ids
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
    void print_explore_id(Graph g){
        for(int i=1; i<=g.node; i++){
            cout<<this->explore_id[i]<<endl;
        }
        return;
    }
    void oneD_vector_init(int n, int value, vector<int> *temp){
        (*temp).clear();
         for(int i=0; i<=n; i++){
            (*temp).push_back(value);
         }
         return;
    }
};

int main(void){
    //freopen("in5.txt", "r", stdin);
    //freopen("out5.txt", "w", stdout);
    Graph g;
    g.input();
    int s,d;
    cin>>s>>d;
    Bfs b;
    b.algorithm(g, s, d);
    return 0;
}
