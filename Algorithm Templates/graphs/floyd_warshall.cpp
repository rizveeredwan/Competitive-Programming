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

struct FloydWarshall{
    vector<vector<int>>dist;
    vector<vector<int>>path;
    int INF = 100000000;
    void init(Graph g){
        this->dist.clear();
        vector<int>temp;
        for(int i=0; i<=g.node; i++){
            temp.push_back(this->INF);
        }
        for(int i=0; i<=g.node; i++){
            dist.push_back(temp);
            path.push_back(temp);
            dist[i][i] = 0;
            path[i][i] = i;
        }
        for(int i=1; i<=g.node; i++){
            for(int j=0; j<g.edges[i].size(); j++){
                if(dist[i][g.edges[i][j]] > g.weight[i][j]) {
                    dist[i][g.edges[i][j]] = g.weight[i][j];
                    path[i][g.edges[i][j]] = i;
                }
            }
        }
    }
    void algorithm(Graph g){
        this->init(g);
        for(int k=1; k<=g.node; k++){
            for(int i=1; i<=g.node; i++){
                for(int j=1; j<=g.node; j++){
                    if(dist[i][j] > dist[i][k] + dist[k][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        path[i][j] = path[k][j];
                    }
                }
            }
        }
        this->print_table(g);
    }

    void print_table(Graph g){
        for(int i=1; i<=g.node; i++){
            for(int j=1; j<=g.node; j++){
                cout<<this->dist[i][j]<<" ";
            }
            cout<<endl;
        }
        for(int i=1; i<=g.node; i++){
            for(int j=1; j<=g.node; j++){
                cout<<"calculation for "<<i <<" "<<j << endl;
                this->print_path(i,j);
                cout<<endl;
            }
        }
        return;
    }

    void print_path(int sr, int des){
        if(this->dist[sr][des] == this->INF) return;
        else if (this->path[sr][des]==sr) {
            cout<<sr<<endl;
            return;
        }
        else {
            this->print_path(sr, this->path[sr][des]);
            this->print_path(this->path[sr][des], des);
        }

    }
};

/*
5 9
1 2 3
1 3 8
1 5 -4
2 4 1
2 5 7
3 2 4
4 1 2
4 3 -5
5 4 6
*/

/*
6 10
1 2 2
1 5 1
2 3 3
2 6 1
3 4 4
4 2 3
4 5 1
5 3 4
5 6 2
6 1 1
*/

int main(void){
    Graph g;
    g.input(false, false);
    FloydWarshall f;
    f.algorithm(g);
}
