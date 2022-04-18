#include <bits/stdc++.h>
using namespace std;

// optimization of merged loop
// https://stackoverflow.com/questions/12123409/two-operations-in-one-loop-vs-two-loops-performing-the-same-operations-one-per-l

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
    void input(bool undirected, bool unweighted, Graph *g2){
        // updated it to handle multiple graphs: reverse graph
        cin>>this->node>>this->edge_count;
        (*g2).node = this->node;
        (*g2).edge_count = this->edge_count;
        this->init(this->node, unweighted, g2);
        int u,v,w;
        for(int i=0; i<this->edge_count; i++){
            cin>>u>>v;
            if(unweighted == false) { // weighted graph
                cin>>w; // taking weight input
            }
            if(unweighted == true) {
                this->add_edge_without_weight(u,v);
                (*g2).add_edge_without_weight(v,u); // reverse graph
            }
            else { // weighted graph
                this->add_edge_with_weight(u,v,w);
                (*g2).add_edge_with_weight(v,u,w); // reverse graph with weight
            }
            if(undirected == true) {
                if(unweighted==true) {
                    this->add_edge_without_weight(v,u);
                    (*g2).add_edge_without_weight(u,v); // reverse graph
                }
                else {
                    this->add_edge_with_weight(v,u,w);
                    (*g2).add_edge_with_weight(u,v,w);
                }
            }
        //this->print_edges();
        }
    }
    void init(int node, bool unweighted, Graph *g2){
        this->edges.clear();
        this->weight.clear();
        (*g2).edges.clear();
        (*g2).weight.clear();
        vector<int>temp;
        for(int i=0; i<=node;i++){
            this->edges.push_back(temp);
            (*g2).edges.push_back(temp);
            if(unweighted == false) this->weight.push_back(temp), (*g2).weight.push_back(temp);
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


struct SCC{
vector<int>color;
    vector<int>parent;
    vector<int>discovery;
    vector<int>finish;
    vector<int>order;
    vector<int>id;
    vector<vector<int>>scc_components;
    vector<vector<int>>scc_graph;
    int time;
    int INF = 100000000;
    void algorithm(Graph g1, Graph g2){
        this->init(g1);
        this->order.clear();
        for(int i=1; i<=g1.node; i++){
            if(this->color[i] == 0) { // white
                cout<<"start "<<i<<" "<<this->color[i]<<endl;
                this->recursion_dfs(g1,i, false);
            }
        }
        this->init(g2);
        vector<int>temp;
        for(int i=this->order.size()-1; i>=0; i--){
            //cout<<this->order[i]<<" "<<this->color[this->order[i]]<<endl;
            // working on finish time, which node finished late, starting with that node
            if(this->color[this->order[i]] == 0) {
                this->scc_components.push_back(temp);
                this->recursion_dfs(g2,this->order[i], true);
            }
        }
        this->print_scc_componets();
        this->construct_scc_graph(g1);
        this->print_scc_graph();
    }
    void init(Graph g){
        this->oneD_vector_init(g.node, 0, &this->color);
        this->oneD_vector_init(g.node, -1, &this->parent);
        this->oneD_vector_init(g.node, 0, &this->discovery);
        this->oneD_vector_init(g.node, 0, &this->finish);
        this->oneD_vector_init(g.node, -1, &this->id);
        this->time = 0;
        this->scc_components.clear();
        this->scc_graph.clear();
        return;
    }
    void recursion_dfs(Graph g, int u, bool component_finding){
        this->time = this->time + 1;
        this->color[u] = 1; // grey
        this->discovery[u] = this->time;
        for(int i=0; i<g.edges[u].size(); i++){
            if(this->color[g.edges[u][i]] == 0) {
                this->parent[g.edges[u][i]] = u;
                this->recursion_dfs(g,g.edges[u][i], component_finding);
            }
            else if(this->color[g.edges[u][i]] == 1 && this->parent[u] != g.edges[u][i]){
                continue;
                //cout<<"cycle detected "<<u<<" "<<g.edges[u][i]<<endl;
                //return;
            }
        }
        this->time = this->time + 1;
        this->finish[u] = this->time;
        this->color[u] = 2; // black
        this->order.push_back(u);
        if(component_finding == true){
            // inserting components into SCC
            this->scc_components[this->scc_components.size()-1].push_back(u);
            this->id[u] = this->scc_components.size()-1;
        }
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
    }
    void print_scc_componets(){
        for(int i=0; i<this->scc_components.size(); i++){
            cout<<"i = "<<i<<endl;
            for(int j=0; j<this->scc_components[i].size(); j++){
                cout<<this->scc_components[i][j]<<" ";
            }
            cout<<endl;
        }
    }
    void construct_scc_graph(Graph g){
        vector<int>temp;
        for(int i=0; i<this->scc_components.size(); i++){
            this->scc_graph.push_back(temp); // 3 components, 3 nodes
        }
        set<int>S;
        for(int i=0; i<this->scc_components.size(); i++){
            S.clear();
            for(int j=0; j<this->scc_components[i].size(); j++){
                for(int k=0; k<g.edges[this->scc_components[i][j]].size(); k++){
                    if(this->id[this->scc_components[i][j]] != this->id[g.edges[this->scc_components[i][j]][k]]){
                        // in two scc: components
                        S.insert(this->id[g.edges[this->scc_components[i][j]][k]]);
                    }
                }
            }
            for(auto it=S.begin(); it != S.end(); it++){
                this->scc_graph[i].push_back(*it);
            }
        }
    }
    void print_scc_graph(){
        for(int i=0; i<this->scc_components.size();i++){
            for(int j=0; j<this->scc_graph[i].size(); j++){
                cout<<i<<" "<<this->scc_graph[i][j]<<endl;
            }
        }
        return;
    }
};

/*
8 14
1 2
2 3
2 5
2 6
3 4
3 7
4 3
4 8
5 1
5 6
6 7
7 6
7 8
8 8
*/

int main(void){
    freopen("in1.txt", "r", stdin);
    Graph g1,g2;
    g1.input(false, true, &g2);
    g1.print_edges();
    g2.print_edges();
    SCC sc;
    sc.algorithm(g1,g2);
    return 0;
}
