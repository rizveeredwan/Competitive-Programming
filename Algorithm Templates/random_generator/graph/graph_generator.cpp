#include <bits/stdc++.h>
using namespace std;

#define MAX 100000



struct ComponentTypes{
    int number_of_nodes;
    string type; // tree/cycle
    int extra_edge_count;
    pair<int,int>weight_range={1,1}; // start to end
    bool negative_cycle = false; // want to make negative cycle or not
};

struct ConstructedComponents{
    vector<vector<int>>graph;
    vector<vector<int>>weight;
    int edge;
    int st,en; // component node indexes [1, 10][11-20], etc
};

int find_set(int u, vector<int> &par){
    if(u == par[u]) return u;
    par[u] = find_set(par[u], par);
    return par[u];
}


struct GraphGenerator{
    vector<vector<int>> generate_directions(int n, vector<vector<int>>graph){
        vector<vector<int>>graph2=this->twoD_vector_init(n);
        queue<int>Q;
        int node = rand()%n+1;
        Q.push(node);
        map<int,bool>visit;
        visit[node] = true;
        int u,v;
        while(!Q.empty()){
            u = Q.front();
            Q.pop();
            for(int i=0; i<graph[u].size(); i++){
                v = graph[u][i];
                if(visit.find(v) == visit.end()){
                    // not yet visited
                    graph2[u].push_back(v);
                    Q.push(v);
                    visit[v] = true;
                }
            }
        }
        return graph2;
    }
    vector<vector<int>> tree_generation_using_dsu(int n, bool undirected, int *edge){
        vector<vector<int>>graph=this->twoD_vector_init(n);
        vector<int>par;
        // setting own parent own
        for(int i=0; i<=n; i++){
            par.push_back(i);
        }
        *edge = 0;
        int cnt=0;
        int u,v, a, b;
        while(cnt != n-1){
             u = rand()%n+1;
             v = rand()%n+1;
             a = find_set(u, par);
             b = find_set(v, par);
             if (a != b){
                par[a] = par[b];
                graph[u].push_back(v); // creating graph edge
                graph[v].push_back(u); // creating reverse edge
                cnt++;
                *edge=*edge+1;
             }
        }
        if(undirected == false) graph = this->generate_directions(n, graph);
        return graph;
    }
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
    void print_normal_graph(int node, int edge, vector<vector<int>>graph, vector<vector<int>>weight, bool undirected, bool unweighted){
        cout<<node<<" "<<edge<<endl;
        for(int i=1; i<=node; i++){
            for(int j=0; j<graph[i].size(); j++){
                if((undirected == true && i<graph[i][j]) || undirected == false)  {
                    if(unweighted == true) cout<<i<< " "<<graph[i][j]<<endl;
                    else cout<<i<< " "<<graph[i][j]<<" "<<weight[i][j]<<endl;
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
    void extra_edge_addition(int n, bool undirected, int edge, ConstructedComponents &temp, bool unweighted, int min_value, int max_value){
        int u,v;
        int w;
        while(edge > 0){
            u = rand()%n+1;
            v = rand()%n+1;
            if(u != v){
                if(undirected == true && this->edge_presence(temp.graph, u, v) == false) {
                    edge = edge - 1;
                    temp.graph[u].push_back(v);
                    temp.graph[v].push_back(u);
                    if(unweighted == false) {
                        // weighted graph
                        w = rand()%(max_value-min_value)+min_value;
                        temp.weight[u].push_back(w);
                        temp.weight[v].push_back(w);
                    }
                }
                else if(undirected == false &&  this->edge_presence(temp.graph, v, u) == false && this->edge_presence(temp.graph, u, v) == false){
                    edge = edge - 1;
                    temp.graph[u].push_back(v);
                    if(unweighted == false) {
                        w = rand()%(max_value-min_value)+min_value;
                        temp.weight[u].push_back(w);
                    }
                }
            }
        }
        return;
    }
    void graph_generation(vector<ComponentTypes>component_types, vector<int>joining_edges, bool undirected, bool unweighted){
        int total_node_count=0;
        int total_edge_count=0;
        int global_min,global_max;
        vector<ConstructedComponents>const_comps; // constructed components
        for(int i=0; i<component_types.size(); i++){
            ConstructedComponents temp;
            temp.edge = 0;
            if(component_types[i].type == "tree") {
                // this->tree_generation
                temp.graph = this->tree_generation_using_dsu(component_types[i].number_of_nodes, undirected, &temp.edge);
                if(unweighted == false) {
                    if(i==0) global_min = component_types[i].weight_range.first, global_max = component_types[i].weight_range.second;
                    else global_min = min(global_min, component_types[i].weight_range.first), global_max = max(global_max, component_types[i].weight_range.second);
                    temp.weight = this->bulk_weight_generation(component_types[i].number_of_nodes, temp.edge, temp.graph, component_types[i].weight_range.first, component_types[i].weight_range.second, component_types[i].negative_cycle, undirected);
                }

            }
            else if(component_types[i].type == "cycle"){
                temp.graph = this->cycle_generation(component_types[i].number_of_nodes, undirected, &temp.edge);
                if(unweighted == false) {
                    if(i==0) global_min = component_types[i].weight_range.first, global_max = component_types[i].weight_range.second;
                    else global_min = min(global_min, component_types[i].weight_range.first), global_max = max(global_max, component_types[i].weight_range.second);
                    temp.weight = this->bulk_weight_generation(component_types[i].number_of_nodes, temp.edge, temp.graph, component_types[i].weight_range.first, component_types[i].weight_range.second, component_types[i].negative_cycle, undirected);
                }
            }
            if(component_types[i].extra_edge_count > 0) {
                this->extra_edge_addition(component_types[i].number_of_nodes, undirected, component_types[i].extra_edge_count, temp, unweighted, component_types[i].weight_range.first, component_types[i].weight_range.second);
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
        vector<vector<int>> final_graph, final_weight;
        int ptr = 0;
        for(int i=0; i<const_comps.size(); i++){
            ptr = this->merger_graph(&final_graph, &final_weight, const_comps[i].graph, const_comps[i].weight, component_types[i].number_of_nodes, ptr, unweighted);
            if(i-1>=0) {
                this->create_edges_between_two_components(&final_graph, &final_weight, undirected, const_comps[i-1].st, const_comps[i-1].en,
                                                                        const_comps[i].st, const_comps[i].en, joining_edges[i-1], unweighted, global_min, global_max);
                total_edge_count = total_edge_count + joining_edges[i-1];
            }
        }
        this->print_normal_graph(total_node_count, total_edge_count, final_graph, final_weight, undirected, unweighted);
    }
    void create_edges_between_two_components(vector<vector<int>> *graph, vector<vector<int>> *weight, int undirected, int st1, int end1, int st2, int end2, int edge_count, bool unweighted, int min_range, int max_range){
        int u,v, gap;
        int w;
        for(int i=1; i<=edge_count; i++){
            while(true){
                gap = end1-st1;
                u = rand()%gap+st1;
                gap = end2-st2;
                v = rand()%gap+st2;
                if(undirected == true && this->edge_presence(*graph, u, v) == false){
                     (*graph)[u].push_back(v);
                     (*graph)[v].push_back(u);
                     if(unweighted == false) {
                        w = rand()%(max_range-min_range)+min_range;
                        (*weight)[u].push_back(w);
                        (*weight)[v].push_back(w);
                     }
                     break;
                }
                else if(undirected == false && this->edge_presence(*graph, u, v) == false && this->edge_presence(*graph, v, u) == false) {
                    (*graph)[u].push_back(v);
                    if(unweighted == false) {
                        w = rand()%(max_range-min_range)+min_range;
                        (*weight)[u].push_back(w);
                    }
                    break;
                }
            }
        }
        return ;
    }
    int merger_graph(vector<vector<int>> *graph, vector<vector<int>> *weight, vector<vector<int>> c, vector<vector<int>> w, int n, int ptr, bool unweighted){
        for(int i=(ptr==0)?0:1;i<=n;i++){ // for first time,insert for zero, else (1-n) with shift
            vector<int>temp;
            (*graph).push_back(temp);
            if(unweighted == false)(*weight).push_back(temp);
        }
        for(int i=1; i<=n;i++){
            for(int j=0; j<c[i].size(); j++){
                (*graph)[i+ptr].push_back(c[i][j]+ptr); // node
                if(unweighted == false)(*weight)[i+ptr].push_back(w[i][j]); // weight
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

    vector<vector<int>> bulk_weight_generation(int n, int edge_count, vector<vector<int>>graph, int min_value, int max_value, bool negative_cycle, bool undirected){
        // a normal graph, not multi edge, undirected and directed both are fine
        vector<int>rand_weights = randomized_weight(min_value, max_value, edge_count, negative_cycle); // generating random weights
        map<int, map<int,int>>calculated; // which are already calculated
        vector<vector<int>>weight = this->twoD_vector_init(n);
        int ptr = -1;
        for(int i=1; i<=n; i++){
            for(int j=0; j<graph[i].size(); j++){
                if(undirected == true) {
                    if(i<graph[i][j]) {
                        ptr++;
                        weight[i].push_back(rand_weights[ptr]);
                        calculated[i][graph[i][j]] = rand_weights[ptr];
                    }
                    else{
                        //auto it = calculated.find({i, graph[i][j]});
                        weight[i].push_back(calculated[i][graph[i][j]]);
                    }
                }
                else {
                    // directed graph
                    ptr++;
                    weight[i].push_back(rand_weights[ptr]);
                    calculated[i][graph[i][j]] = rand_weights[ptr];
                }
            }
        }
        return weight;
    }

    vector<int> randomized_weight(int min_range, int max_range, int n, bool neg_cycle){
        // randomization weight
        vector<int>values;
        int diff = max_range-min_range;
        for(int i=0; i<n; i++){
            values.push_back(rand()%diff + min_range);
            assert(values[i] >= 0);
        }
        sort(values.begin(), values.end());
        if(neg_cycle == true) {
            int choice = rand()%10+1;
            vector<int>sum;
            int t_sum = 0;
            for(int i=0; i<n; i++) {
                t_sum = t_sum + values[i];
                sum.push_back(t_sum);
            }
            int split_idx;
            int l_sum,r_sum;
            int sol_idx = -1;
            int i=0;
            while (i<choice){
                split_idx = rand()%n;
                l_sum = 0;
                if(split_idx >= 0) {
                    l_sum = sum[split_idx];
                }
                r_sum = 0;
                if(split_idx <= (n-1)) {
                    r_sum = sum[n-1]-sum[split_idx];
                }
                if(l_sum != r_sum) {
                    i++; // a valid solution
                    if(sol_idx == -1)sol_idx = split_idx;
                    else rand()%2==1?sol_idx = split_idx:sol_idx;
                }
            }
            if(l_sum > r_sum) {
                for(int i=0; i<split_idx; i++) {
                    values[i] = values[i] * -1;
                }
            }
            else {
                for(int i=split_idx+1; i<n; i++){
                    values[i] = values[i] * -1;
                }
            }
        }
        // using built-in random generator
        random_shuffle(values.begin(), values.end());
        return values;
    }

};



int main(void){
    freopen("IN.txt", "w", stdout);
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

    temp.number_of_nodes = 1000;
    temp.type = "tree"; // tree or cycle
    temp.extra_edge_count = 0;
    temp.weight_range.first = 2;
    temp.weight_range.second = 15;
    temp.negative_cycle = false;
    component_types.push_back(temp);

    /*temp.number_of_nodes = 50;
    temp.type = "tree";
    temp.extra_edge_count = 0;
    temp.weight_range.first = 10;
    temp.weight_range.second = 97;
    temp.negative_cycle = false;
    component_types.push_back(temp);

    /*temp.number_of_nodes = 5000;
    temp.type = "cycle";
    temp.extra_edge_count = 800;
    temp.weight_range.first = 10;
    temp.weight_range.second = 200;
    temp.negative_cycle = false;
    component_types.push_back(temp);*/


    vector<int>joining_edges;
    //joining_edges.push_back(10);
    //joining_edges.push_back(300);
    //joining_edges.push_back(1);
    //
    // graph_generation(vector<ComponentTypes>component_types, vector<int>joining_edges, bool undirected, bool unweighted)
    g.graph_generation(component_types, joining_edges, false, true);
    return 0;
}
