#include <bits/stdc++.h>
using namespace std;

void print(vector<int>temp);

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
        this->init(this->node, unweighted);
        int u,v,w;
        for(int i=0; i<this->edge_count; i++){
            cin>>u>>v;
            if(unweighted == false) { // weighted graph
                cin>>w; // taking weight input
            }
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

struct TopologicalSorting{
    vector<int>color;
    vector<int>parent;
    vector<int>discovery;
    vector<int>finish;
    vector<int>order;
    int time;
    int INF = 100000000;
    void algorithm(Graph g){
        this->init(g);
        for(int i=1; i<=g.node; i++){
            if(this->color[i] == 0) { // white
                cout<<"start "<<i<<" "<<this->color[i]<<endl;
                this->recursion_dfs(g,i);
            }
        }
        reverse(this->order.begin(), this->order.end());
        this->print_topo_order();
        return;
    }
    void init(Graph g){
        this->oneD_vector_init(g.node, 0, &this->color);
        this->oneD_vector_init(g.node, -1, &this->parent);
        this->oneD_vector_init(g.node, 0, &this->discovery);
        this->oneD_vector_init(g.node, 0, &this->finish);
        this->time = 0;
        return;
    }
    void recursion_dfs(Graph g, int u){
        this->time = this->time + 1;
        this->color[u] = 1; // grey
        this->discovery[u] = this->time;
        for(int i=0; i<g.edges[u].size(); i++){
            if(this->color[g.edges[u][i]] == 0) {
                this->parent[g.edges[u][i]] = u;
                this->recursion_dfs(g,g.edges[u][i]);
            }
            else if(this->color[g.edges[u][i]] == 1 && this->parent[u] != g.edges[u][i]){
                cout<<"cycle detected "<<u<<" "<<g.edges[u][i]<<endl;
                //return;
            }
        }
        this->time = this->time + 1;
        this->finish[u] = this->time;
        this->color[u] = 2; // black
        this->order.push_back(u);
        return;
    }
    void oneD_vector_init(int n, int value, vector<int> *temp){
         (*temp).clear();
         for(int i=0; i<=n; i++){
            (*temp).push_back(value);
         }
    }
    void cycle_node_extraction(int u, int cycle_end){
        vector<int>temp;
        temp.push_back(u);
        int v;
        while(true){
            v = this->parent[u];
            if(v == -1) break;
            temp.push_back(v);
            if(v == cycle_end) break; // reached the grey node
        }
        sort(temp.begin(), temp.end());
        print(temp);
    }
    void print_topo_order(){
        for(int i=0;i<this->order.size(); i++){
            cout<<this->order[i]<<endl;
        }
        return;
    }
};

void print(vector<int>temp){
    for(int i=0; i<temp.size(); i++){
        if(i==temp.size()-1) cout<<temp[i]<<endl;
        else cout<<temp[i]<<" ";
    }
}

/*
9 9
1 2
1 3
4 3
2 4
5 4
5 6
6 7
4 7
8 3
*/

int main(void){
    freopen("in1.txt", "r", stdin);
    Graph g;
    g.input(false, true);
    TopologicalSorting d;
    d.algorithm(g);
    return 0;
}
