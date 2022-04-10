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


int main(void){

}
