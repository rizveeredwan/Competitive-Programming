#include <bits/stdc++.h>
#include "trie.cpp"
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

struct DijkstraState{
    int node,cost, number_of_nodes;
    Trie *trie_node;
    // Another way of writing
    bool operator < (const DijkstraState &a) const {
        if(cost < a.cost) return false; // need to be in front
        else if (cost == a.cost) {
            if(number_of_nodes < a.number_of_nodes) return true; // (3 < 7): True
            else if(number_of_nodes == a.number_of_nodes) {
                if(node < a.node) return false;
                else return true;
            }
            return false;
        }
        else return true;
    }
};

// this is an structure which implements the
// operator overloading
// this is an structure which implements the
// operator overloading
/*struct CompareNodes {
    bool operator()(DijkstraState p1, DijkstraState p2)
    {
        // before "p2", for example:
        return p1.cost > p2.cost;
    }
};
priority_queue<DijkstraState, vector<DijkstraState>, CompareNodes >PQ;
*/

struct Dijkstra{
    vector<int>dist;
    vector<int>parent;
    priority_queue<DijkstraState>PQ;
    int inf = 100000000;
    int explored;
    Trie *root = nullptr, *ans = nullptr;
    void algorithm(Graph g, int s, int des){
        this->explored = 0;
        this->init(g);
        this->dist[s]=0;
        this->root = new Trie();
        root->node = s;
        this->ans = nullptr;
        this->insert_in_pq(s,0,0,root);
        DijkstraState u;
        while(this->PQ.empty() != true){
            u = this->PQ.top();
            this->PQ.pop();
            //cout<<"node "<<u.node<<" "<<u.cost<<" "<<u.number_of_nodes<<endl;
            //if(u.cost>this->dist[u.node]) continue; // I have already worked with lower cost
            if(u.node == des) {
                this->ans = u.trie_node;
                break; // reached destination
            }
            explored++;
            for(int i=0; i<g.edges[u.node].size(); i++){
                if (this->dist[g.edges[u.node][i]] > u.cost + g.weight[u.node][i]) {
                    this->dist[g.edges[u.node][i]] = u.cost + g.weight[u.node][i];
                    Trie *trie_node = this->root->create(g.edges[u.node][i], u.trie_node);
                    this->insert_in_pq(g.edges[u.node][i],u.cost + g.weight[u.node][i], u.number_of_nodes+1, trie_node);
                }
            }
        }
    }
    void insert_in_pq(int node, int cost, int number_of_nodes, Trie *trie_node){
        DijkstraState temp;
        temp.node=node;
        temp.cost=cost;
        temp.number_of_nodes=number_of_nodes;
        temp.trie_node = trie_node;
        this->PQ.push(temp);
        return;
    }
    void init(Graph g){
        this->dist.clear();
        this->parent.clear();
        for(int i=0; i<=g.node; i++){
            this->dist.push_back(this->inf);
            this->parent.push_back(-1); // no parent
        }
        while(this->PQ.empty() != true){
            this->PQ.pop();
        }
    }
    void path_print(int src, int des){
        if(src == des) {
            cout<<des<<endl;
            return;
        }
        if(this->dist[des] == -1) {
            cout<<"-1"<<endl;
            return;
        }
        vector<int>V = this->root->traverse(this->ans);
        cout<<V.size()<<endl;
        for(int i=0; i<V.size(); i++) {
            cout<<V[i]<<endl;
        }
        return;
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
    freopen("large_in2.txt", "r", stdin);
    freopen("large_out2.txt", "w", stdout);
    Graph g;
    g.input(true, false);
    Dijkstra d;
    int src,des;
    cin>>src>>des;
    d.algorithm(g,src,des);
    cout<<d.dist[des]<<endl;
    int explored = d.explored;
    d.path_print(src, des);
    cout<<explored<<endl;
    return 0;
}
