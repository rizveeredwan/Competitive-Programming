#include <bits/stdc++.h>
using namespace std;

// g++ -std=c++11 .\max_flow.cpp

struct Graph{
    vector<vector<int>>edges;
    vector<vector<int>>weight;
    vector<vector<int>>residual_edge;
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
        //cout<<"node "<<node<<" "<<edge_count<<endl;
        this->init(this->node, unweighted);
        int u,v,w;
        for(int i=0; i<this->edge_count; i++){
            cin>>u>>v>>w;
            this->add_edge_with_weight(u,v,w);
            this->add_edge_with_weight(v,u,0); // change for flow
            this->residual_edge[u].push_back(this->edges[v].size()-1);
            this->residual_edge[v].push_back(this->edges[u].size()-1);
            //cout<<"u = "<<u<<" "<<this->residual_edge[u][this->residual_edge[u].size()-1]<<endl;
        }
        //this->print_edges();
    }
    void init(int node, bool unweighted){
        this->edges.clear();
        this->weight.clear();
        this->residual_edge.clear();
        vector<int>temp;
        for(int i=0; i<=node;i++){
            this->edges.push_back(temp);
            this->weight.push_back(temp);
            this->residual_edge.push_back(temp); // storing the residual edge
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

struct MaxFlow{
    vector<pair<int,int>>visit;
    vector<pair<int,int>>parent;
    int INF = 100000000;
    int algorithm(Graph *g, int source, int sink){
        int max_flow = 0;
        int res;
        cout<<"ase"<<endl;
        int ct = 0;
        while(true){
            res = edmond_karp_algorithm(g, source, sink);
            if(res == 0) break;
            max_flow += res;
        }
        return max_flow;
    }
    void init(Graph *g){
        this->visit.clear();
        this->parent.clear();
        for(int i=0; i<=(*g).node; i++){
            this->visit.push_back({this->INF, this->INF}); // distance, min capacity
            this->parent.push_back({-1,-1});
        }
    }
    int edmond_karp_algorithm(Graph *g, int source, int sink){
        this->init(g);
        this->visit[source].first = 0;
        this->visit[source].second = this->INF;
        queue<int>Q;
        Q.push(source);
        int u,v;
        while(Q.empty() != true){
            u = Q.front();
            //cout<<"u = "<<u<<endl;
            Q.pop();
            for(int i=0; i<(*g).edges[u].size(); i++){
                 v = (*g).edges[u][i];
                 //cout<<"u = "<<u<<" v "<<v<<" "<< this->visit[v].first << " "<< (*g).weight[u][i] << endl;
                 if(this->visit[v].first == this->INF && (*g).weight[u][i] > 0){
                    this->visit[v].first = this->visit[u].first + 1;
                    this->visit[v].second = min(this->visit[u].second, (*g).weight[u][i]);
                    this->parent[v].first = u; // node
                    this->parent[v].second = i; // edge no
                    Q.push(v);
                 }
                 if(this->visit[sink].first != this->INF) break;
            }
            if(this->visit[sink].first != this->INF) break;
        }
        if(this->visit[sink].first != this->INF) {
            //cout<<"flow "<<this->visit[sink].second << endl;
            this->edge_update(g, this->visit[sink].second, sink);
            return this->visit[sink].second; // flow
        }
        else return 0;
    }
    void edge_update(Graph *g, int flow, int sink){
        int v = sink;
        int u,ec,new_node;
        while(v != -1) {
            u = this->parent[v].first;
            //cout<<"v "<<v<<" "<<u<<endl;
            if(u == -1) break; // reached source (v is source)
            ec = this->parent[v].second;
            //this->print(g,u);
            //this->print(g,v);
            (*g).weight[u][ec] -= flow; // reducing capacity
            ec = (*g).residual_edge[u][ec]; // reverse edge info
            (*g).weight[v][ec] += flow; // increasing revere flow
            //this->print(g,u);
            //this->print(g,v);
            v = u;
        }
        //cout<<"baire ashe"<<endl;
        return;
    }

    void print(Graph *g, int u){
        cout<<"node "<<u<<endl;
        for(int i=0; i<(*g).edges[u].size();i++){
            cout<<"( "<< (*g).edges[u][i]<<" "<< (*g).weight[u][i]<<" ) "<< endl;
        }
        cout<<endl<<endl;;
        for(int i=0; i<(*g).residual_edge[u].size(); i++){
            cout<<(*g).residual_edge[u][i]<<endl;
        }
    }
};

int main(void){
    freopen("in2.txt", "r", stdin);
    Graph g;
    g.input(false,false);
    int source,sink;
    cin>>source>>sink;
    MaxFlow m;
    cout<<m.algorithm(&g,source,sink);
    return 0;

}
