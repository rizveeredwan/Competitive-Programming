#include <bits/stdc++.h>
using namespace std;
#define MAX 100
#define INF 1000000

vector<pair<int,int>>graph[MAX+1];

struct BellmanFordEdgeList
{
    int u,v,w;
};

struct BellmanFord
{
    int n;
    int ed;
    int sr;
    int dest;
    vector<BellmanFordEdgeList>edgeList;
    vector<int>dist;
    void Init()
    {
        edgeList.clear();
        dist.clear();
    }
    void EdgeConstructionWithOrdering(vector<pair<int,int>>graph[],int src,int n)
    {
        queue<int>Q;
        int visit[MAX+1];
        memset(visit, 0, sizeof(visit));
        Q.push(src);
        int u;
        while(Q.empty() != true)
        {
            u=Q.front();
            Q.pop();
            if(visit[u] == 1)
            {
                continue; //all the edges been taken already
            }
            visit[u]=1;
            for(int i=0; i<graph[u].size(); i++)
            {
                edgeList.push_back({u,graph[u][i].first,graph[u][i].second});
                //cout<<"edge creating "<<u<<" "<<graph[u][i].first<<" "<<graph[u][i].second<<endl;
                Q.push(graph[u][i].first);
            }
        }
    }
    void print()
    {
        for(int i=0; i<=this->n; i++)
        {
            cout<<i<<": "<<dist[i]<<endl;
        }
    }
    void Algorithm()
    {
        for(int i=0; i<=n; i++)
        {
            dist.push_back(INF);
        }
        bool update=false;
        dist[sr]=0;
        //normal bellmanford
        for(int i=1; i<=n-1; i++)
        {
            update=false;
            for(int j=0; j<(int)edgeList.size(); j++)
            {
                if(dist[edgeList[j].v]>dist[edgeList[j].u]+edgeList[j].w)
                {
                    dist[edgeList[j].v] = dist[edgeList[j].u]+edgeList[j].w;
                    //cout<<"u: "<<edgeList[j].u<<" "<<edgeList[j].v<<" "<<dist[edgeList[j].v]<<endl;
                    update=true;
                }
            }
            if(!update)
                break;
        }
        //negative cycle detection
        if(update)
        {
            update = false; // lets assume no update occurs
            vector<int>problem_nodes;
            for(int j=0; j<(int)edgeList.size(); j++)
            {
                if(dist[edgeList[j].v]>dist[edgeList[j].u]+edgeList[j].w)
                {
                    dist[edgeList[j].v] = dist[edgeList[j].u]+edgeList[j].w;
                    update=true;
                    problem_nodes.push_back(edgeList[j].v);
                    //cout<<"v "<<edgeList[j].v<<endl;
                }
            }
            if(update) // update occurred
            {
                this->dest_reached_using_dfs(problem_nodes);
            }
            else {
                if(this->dist[dest] == INF) cout<<"INF"<<endl;
                else cout<<this->dist[dest]<<endl; // no negative cycle
            }
        }
        else {
            if(this->dist[dest] == INF) cout<<"INF"<<endl;
            else cout<<this->dist[dest]<<endl; // no negative cycle
        }
        return;
    }
    void dest_reached_using_dfs(vector<int>problems){
        vector<int>color1,color2;
        for(int i=0; i<=n; i++){
            color1.push_back(-1);
            color2.push_back(-1);
        }
        stack<int>s1,s2;
        s1.push(sr);
        color1[sr] = 0;
        int u,v;
        while(!s1.empty()){
            u = s1.top();
            s1.pop();
            for(int i=0; i<graph[u].size(); i++){
                v=graph[u][i].first;
                if(color1[v] == -1) {
                    s1.push(v);
                    color1[v] = 0;
                }
            }
        }
        for(int i=0; i<problems.size(); i++){
              if(color1[problems[i]] == 0 && color1[dest] == 0) {
                    if(color2[problems[i]] == -1) {
                        s2.push(problems[i]);
                        color2[problems[i]]=0;
                    }
              }
        }
        bool neg_cycle_in_path = false;
        while(!s2.empty()){
            u = s2.top();
            s2.pop();
            if(u == dest) {
                neg_cycle_in_path = true;
                break;
            }
            for(int i=0; i<graph[u].size(); i++){
                v=graph[u][i].first;
                if(color2[v] == -1) {
                    s2.push(v);
                    if(v == dest) {
                        neg_cycle_in_path = true;
                        break;
                    }
                }
                color2[v] = 0;
            }
        }
        if(neg_cycle_in_path == false) cout<<dist[this->dest]<<endl;
        else cout<<"INF"<<endl; // negative cycle in path
    }
};

/*
13 17
1 2 3
1 7 2
2 3 -1
2 7 6
3 4 7
4 5 1
5 2 -2
5 6 4
6 12 2
7 8 1
8 5 2
8 6 1
8 9 5
9 10 -3
9 11 3
10 7 -3
11 12 3
1
*/


int main(void)
{
    freopen("in6.txt","r",stdin);
    freopen("out6.txt","w",stdout);
    struct BellmanFord bellmanford;
    //cout<<"Give total nodes: ";
    cin>>bellmanford.n;
    //cout<<endl;
    //cout<<"Number of edges: ";
    cin>>bellmanford.ed;
    //cout<<endl;
    //cout<<"edges will be 0 index based "<<endl;
    int u,v,w;
    for(int i=1; i<=bellmanford.ed; i++)
    {
        cin>>u>>v>>w;
        //cout<<u<<v<<w<<endl;
        graph[u].push_back({v,w});
        //graph[v].push_back({u,w});
    }
    //cout<<"Provide source node(0 based): ";
    cin>>bellmanford.sr;
    cin>>bellmanford.dest;
    //cout<<endl;
    //cout<<"Node sorting "<<endl;
    bellmanford.EdgeConstructionWithOrdering(graph,bellmanford.sr,bellmanford.n);
    bellmanford.Algorithm();
    return 0;
}
