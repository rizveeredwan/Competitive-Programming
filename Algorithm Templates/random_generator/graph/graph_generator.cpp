#include <bits/stdc++.h>
using namespace std;

#define MAX 100000

struct ComponentTypes{
    int number_of_nodes;
    string type; // tree/cycle
    int extra_edge_count;
    pair<int,int>weight_range; // start to end
    bool negative_cycle = false; // want to make negative cycle or not
};

struct ConstructedComponents{
    vector<vector<int>>graph;
    vector<vector<int>>weight;
    int edge;
    int st,en; // component node indexes [1, 10][11-20], etc
};

struct GraphGenerator{
    vector<vector<int>> tree_generation(int n, bool undirected, int *edge) {
        vector<vector<int>>graph=this->twoD_vector_init(n);
        vector<bool>flag = this->oneD_vector_init(n);
        int u,v;
        int child=0;
        int rem; // the number of remaining children
        bool new_node_generated; // new node generated flag
        int root = rand()%n+1;
        child++;
        flag[root] = 1;
        queue<int>q;
        q.push(root);
        *edge = 0;
        while(q.empty() != true) {
            u = q.front();
            q.pop();
            rem = n-child;
            new_node_generated=false;
            for(int i=1; i<=rem; i++){
                v=rand()%n+1;
                if(flag[v] == false) {
                    flag[v] = true; // this node first time generated
                    q.push(v); // for next iteration
                    graph[u].push_back(v); // creating graph edge
                    if(undirected == true) graph[v].push_back(u); // creating reverse edge
                    child++; // another new node found
                    new_node_generated = true;
                    *edge=*edge+1;
                }
            }
            if(new_node_generated == false && child != n) {
                for(; ; ){
                    v = rand()%n+1; // random selection node
                    if(flag[v] == false) {
                        flag[v] = true; // this node first time generated
                        q.push(v); // for next iteration
                        graph[u].push_back(v); // creating graph edge
                        if(undirected == true) graph[v].push_back(u); // creating reverse edge
                        child++; // another new node found
                        new_node_generated = true;
                        *edge=*edge+1;
                        break;
                    }
                }
            }
        }
        return graph;
    }
    bool edge_presence(vector<vector<int>>graph, int u, int v){
        for(int i=0; i<graph[u].size(); i++){
            if(graph[u][i] == v) return true; //edge is already there
        }
        return false;
    }
    void print_normal_graph(int node, int edge, vector<vector<int>>graph, bool undirected){
        cout<<node<<" "<<edge<<endl;
        for(int i=1; i<=node; i++){
            for(int j=0; j<graph[i].size(); j++){
                if((undirected == true && i<graph[i][j]) || undirected == false)  {
                    cout<<i<< " "<<graph[i][j]<<endl;
                }
            }
        }
    }
    vector<vector<int>> cycle_generation(int n, bool undirected, int *edge){
        vector<vector<int>>graph = this->twoD_vector_init(n);
        vector<bool>flag = this->oneD_vector_init(n);
        int u = rand()%n+1;
        int ct = 1;
        int v;
        flag[u] = true;
        int start = u;
        *edge = 0;
        while(ct != n){
            v = rand()%n+1;
            if(flag[v] == false) {
                flag[v] = true; // found
                ct++; // increasing node count
                graph[u].push_back(v);
                if(undirected == true) graph[v].push_back(u);
                *edge = *edge + 1;
                u = v;
            }
        }
        graph[v].push_back(start);
        if(undirected == true) graph[start].push_back(v);
        *edge = *edge + 1;
        return graph;
    }
    vector<bool> oneD_vector_init(int n){
         vector<bool>flag;
         for(int i=0;i<=n;i++){
            flag.push_back(false);
         }
         return flag;
    }
    vector<vector<int>> extra_edge_addition(int n, bool undirected, int edge, vector<vector<int>>graph){
        int u,v;
        while(edge > 0){
            u = rand()%n+1;
            v = rand()%n+1;
            if(u != v){
                if(undirected == true && this->edge_presence(graph, u, v) == false) {
                    edge = edge - 1;
                    graph[u].push_back(v);
                    graph[v].push_back(u);
                }
                else if(undirected == false &&  this->edge_presence(graph, v, u) == false && this->edge_presence(graph, u, v) == false){
                    edge = edge - 1;
                    graph[u].push_back(v);
                }
            }
        }
        return graph;
    }
    void graph_generation(vector<ComponentTypes>component_types, vector<int>joining_edges, bool undirected, bool unweighted){
        int total_node_count=0;
        int total_edge_count=0;
        vector<ConstructedComponents>const_comps; // constructed components
        for(int i=0; i<component_types.size(); i++){
            ConstructedComponents temp;
            temp.edge = 0;
            if(component_types[i].type == "tree") {
                temp.graph = this->tree_generation(component_types[i].number_of_nodes, undirected, &temp.edge);
            }
            else if(component_types[i].type == "cycle"){
                temp.graph = this->cycle_generation(component_types[i].number_of_nodes, undirected, &temp.edge);
            }
            if(component_types[i].extra_edge_count > 0) {
                temp.graph = this->extra_edge_addition(component_types[i].number_of_nodes, undirected, component_types[i].extra_edge_count, temp.graph);
                temp.edge = temp.edge + component_types[i].extra_edge_count;
            }
            temp.st = total_node_count+1;
            temp.en = total_node_count+component_types[i].number_of_nodes;
            total_node_count = total_node_count + component_types[i].number_of_nodes;
            total_edge_count = total_edge_count + temp.edge;
            const_comps.push_back(temp);
            //cout<<"edge "<<temp.edge<<endl;
            //this->print_normal_graph(component_types[i].number_of_nodes, temp.edge, const_comps[i].graph, undirected);
        }
        vector<vector<int>> final_graph;
        int ptr = 0;
        for(int i=0; i<const_comps.size(); i++){
            ptr = this->merger_graph(&final_graph, const_comps[i].graph, component_types[i].number_of_nodes, ptr);
            if(i-1>=0) {
                final_graph = this->create_edges_between_two_components(final_graph, undirected, const_comps[i-1].st, const_comps[i-1].en,
                                                                        const_comps[i].st, const_comps[i].en, joining_edges[i-1]);
                total_edge_count = total_edge_count + joining_edges[i-1];
            }
        }
        this->print_normal_graph(total_node_count, total_edge_count, final_graph, undirected);
    }
    vector<vector<int>> create_edges_between_two_components(vector<vector<int>> graph, int undirected, int st1, int end1, int st2, int end2, int edge_count){
        int u,v, gap;
        for(int i=1; i<=edge_count; i++){
            while(true){
                gap = end1-st1;
                u = rand()%gap+st1;
                gap = end2-st2;
                v = rand()%gap+st2;
                if(undirected == true && this->edge_presence(graph, u, v) == false){
                     graph[u].push_back(v);
                     graph[v].push_back(u);
                     break;
                }
                else if(undirected == false && this->edge_presence(graph, u, v) == false && this->edge_presence(graph, v, u) == false) {
                    graph[u].push_back(v);
                    break;
                }
            }
        }
        return graph;
    }
    int merger_graph(vector<vector<int>> *graph, vector<vector<int>> c, int n, int ptr){
        for(int i=(ptr==0)?0:1;i<=n;i++){ // for first time,insert for zero, else (1-n) with shift
            vector<int>temp;
            (*graph).push_back(temp);
        }
        for(int i=1; i<=n;i++){
            for(int j=0; j<c[i].size(); j++){
                (*graph)[i+ptr].push_back(c[i][j]+ptr);
            }
        }
        return ptr+n;
    }
    vector<vector<int>> twoD_vector_init(int n){
        vector<vector<int>>graph;
        for(int i=0; i<=n;i++){
            vector<int>temp;
            graph.push_back(temp);
        }
        return graph;
    }
};



int main(void){
    freopen("in6.txt", "w", stdout);
    srand(time(nullptr));
    GraphGenerator g;
    vector<ComponentTypes>component_types;
    ComponentTypes temp;

    /*temp.number_of_nodes = 100;
    temp.type = "tree";
    temp.extra_edge_count = 5;
    component_types.push_back(temp);*/

    /*temp.number_of_nodes = 12;
    temp.type = "cycle";
    temp.extra_edge_count = 4;
    component_types.push_back(temp);*/

    temp.number_of_nodes = 6;
    temp.type = "cycle";
    temp.extra_edge_count = 4;
    temp.weight_range.first = 1;
    temp.weight_range.second = 10;
    component_types.push_back(temp);


    vector<int>joining_edges;
    //joining_edges.push_back(1);
    //joining_edges.push_back(1);

    g.graph_generation(component_types, joining_edges, true, false);
    return 0;
}
