#include <bits/stdc++.h>
using namespace std;
#define MAX 100
#define INF 1000000

struct BellmanFordEdgeList{
	int u,v,w;
};

struct BellmanFord{
	int n;
	int ed;
	int sr;
	vector<BellmanFordEdgeList>edgeList;
	vector<int>dist;
	void Init(){
		edgeList.clear();
		dist.clear();
	}
	void EdgeConstructionWithOrdering(vector<pair<int,int>>graph[],int src,int n){
        queue<int>Q;
        int visit[MAX+1]={0};
        Q.push(src);
        int u;
        while(Q.empty() != true){
            u=Q.front();
            Q.pop();
            if(visit[u] == 1) {
                continue; //all the edges been taken already
            }
            visit[u]=1;
            for(int i=0;i<graph[u].size();i++){
                edgeList.push_back({u,graph[u][i].first,graph[u][i].second});
                //cout<<"edge creating "<<u<<" "<<graph[u][i].first<<" "<<graph[u][i].second<<endl;
                Q.push(graph[u][i].first);
            }
        }
	}
	void print(){
        for(int i=0;i<=this->n;i++){
            cout<<i<<": "<<dist[i]<<endl;
        }
	}
	void Algorithm(){
        for(int i=0;i<n;i++){
            dist.push_back(INF);
        }
        bool update=false;
        dist[sr]=0;
        //normal bellmanford
        for(int i=1;i<=n-1;i++){
            update=false;
            for(int j=0;j<(int)edgeList.size();j++){
                if(dist[edgeList[j].v]>dist[edgeList[j].u]+edgeList[j].w){
                    dist[edgeList[j].v] = dist[edgeList[j].u]+edgeList[j].w;
                    cout<<"u: "<<edgeList[j].u<<" "<<edgeList[j].v<<endl;
                    update=true;
                }
            }
            if(!update) break;
        }
        //negative cycle detection
        if(update){
            update=false;
            for(int j=0;j<(int)edgeList.size();j++){
                if(dist[edgeList[j].v]>dist[edgeList[j].u]+edgeList[j].w){
                    dist[edgeList[j].v] = dist[edgeList[j].u]+edgeList[j].w;
                    update=true;
                }
            }
            if(update) {
                cout<<"Negative Cycle detected"<<endl;
            }
            else this->print();
        }
        else this->print();
        return;
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


int main(void){
    freopen("in1.txt","r",stdin);
    struct BellmanFord bellmanford;
    cout<<"Give total nodes: ";
    cin>>bellmanford.n;
    cout<<endl;
    cout<<"Number of edges: ";
    cin>>bellmanford.ed;
    cout<<endl;
    cout<<"edges will be 0 index based "<<endl;
    vector<pair<int,int>>graph[MAX+1];
    int u,v,w;
    for(int i=1;i<=bellmanford.ed;i++){
        cin>>u>>v>>w;
        cout<<u<<v<<w<<endl;
        graph[u].push_back({v,w});
        //graph[v].push_back({u,w});
    }
    cout<<"Provide source node(0 based): ";
    cin>>bellmanford.sr;
    cout<<endl;
    cout<<"Node sorting "<<endl;
    bellmanford.EdgeConstructionWithOrdering(graph,bellmanford.sr,bellmanford.n);
    bellmanford.Algorithm();
    return 0;
}
