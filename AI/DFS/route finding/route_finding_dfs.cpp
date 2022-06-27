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
        //cout<<this->node<<" "<<this->edge_count<<endl;
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

struct Dfs{
    vector<int>color;
    vector<int>parent;
    vector<int>discovery;
    vector<int>finish;
    int time;
    int INF = 100000000;
    bool goal_reached = false;
    int cost = -1;
    int explored = 0;
    void algorithm(Graph g, int start, int goal){
        this->init(g);
        int cost = this->recursion_dfs(g,start, goal);
        this->print(cost, start, goal);
    }
    vector<int> find_path(int goal){
        int curr = goal;
        vector<int>V;
        while(curr != -1){
            V.push_back(curr);
            curr = this->parent[curr];
        }
        reverse(V.begin(), V.end());
        return V;
    }
    void print(int cost, int start, int goal){
        if(this->goal_reached == false) {
            cout<<-1<<endl;
            cout<<-1<<endl;
            cout<<this->explored<<endl;
            return;
        }
        cout<<cost<<endl;
        vector<int>V = find_path(goal);
        cout<<V.size()<<endl;
        for(int i=0; i<V.size(); i++) {
            cout<<V[i]<<endl;
        }
        cout<<this->explored<<endl;
        return;
    }
    void init(Graph g){
        this->oneD_vector_init(g.node, 0, &this->color);
        this->oneD_vector_init(g.node, -1, &this->parent);
        this->oneD_vector_init(g.node, 0, &this->discovery);
        this->oneD_vector_init(g.node, 0, &this->finish);
        this->time = 0;
        this->goal_reached = false;
        this->cost = -1;
        return;
    }
    int recursion_dfs(Graph g, int u, int goal){
        if (u == goal) {
            this->goal_reached = true;
            return 0;
        }
        this->time = this->time + 1;
        this->color[u] = 1; // grey
        this->discovery[u] = this->time;
        int local_cost;
        this->explored++;
        cout<<this->explored<<endl;
        for(int i=0; i<g.edges[u].size(); i++){
            if(this->color[g.edges[u][i]] == 0) {
                this->parent[g.edges[u][i]] = u;
                local_cost = g.weight[u][i] + this->recursion_dfs(g,g.edges[u][i], goal);
                if (goal_reached == true) return local_cost;
            }
        }
        this->time = this->time + 1;
        this->finish[u] = this->time;
        this->color[u] = 2; // black
        return 0;
    }
    void oneD_vector_init(int n, int value, vector<int> *temp){
         (*temp).clear();
         for(int i=0; i<=n; i++){
            (*temp).push_back(value);
         }
    }
};

int main(void){
    freopen("large_in2.txt", "r", stdin);
    //freopen("large_out2.txt", "w", stdout);
    Graph g;
    Dfs dfs;
    g.input(true, false);
    int src,des;
    cin>>src>>des;
    dfs.algorithm(g,src,des);
    return 0;
}
