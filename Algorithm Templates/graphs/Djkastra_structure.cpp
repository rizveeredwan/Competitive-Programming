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
            cout<<u<<" "<<v<<" "<<w<<endl;
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

struct DijkstraState{
    int node,cost;
};

// this is an structure which implements the
// operator overloading
// this is an structure which implements the
// operator overloading
struct CompareNodes {
    bool operator()(DijkstraState p1, DijkstraState p2)
    {
        // before "p2", for example:
        return p1.cost > p2.cost;
    }
};

struct Dijkstra{
    vector<int>dist;
    priority_queue<DijkstraState, vector<DijkstraState>, CompareNodes >PQ;
    int inf = 100000000;
    void algorithm(Graph g, int s){
        this->init(g);
        this->dist[s]=0;
        this->insert_in_pq(s,0);
        DijkstraState u;
        while(this->PQ.empty() != true){
            u = this->PQ.top();
            this->PQ.pop();
            if(u.cost>this->dist[u.node]) continue; // I have already worked with lower cost
            for(int i=0; i<g.edges[u.node].size(); i++){
                if(this->dist[g.edges[u.node][i]] > (u.cost + g.weight[u.node][i])){
                    this->dist[g.edges[u.node][i]] = u.cost + g.weight[u.node][i];
                    this->insert_in_pq(g.edges[u.node][i],this->dist[g.edges[u.node][i]]);
                }
            }
        }
    }
    void insert_in_pq(int node, int cost){
        DijkstraState temp;
        temp.node=node;
        temp.cost=cost;
        this->PQ.push(temp);
        return;
    }
    void init(Graph g){
        this->dist.clear();
        for(int i=0; i<=g.node; i++){
            this->dist.push_back(this->inf);
        }
        while(this->PQ.empty() != true){
            this->PQ.pop();
        }
    }
};

/*
5 6
1 2 5
2 5 1
5 3 1
1 3 9
1 4 7
3 4 1
*/

int main(void){
    freopen("in1.txt", "r", stdin);
    Graph g;
    g.input(true, false);
    Dijkstra d;
    d.algorithm(g,1);
    return 0;
}
