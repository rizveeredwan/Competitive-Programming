
#include<bits/stdc++.h>
using namespace std;
#define MAX 100000
vector<int>graph[MAX];
char color[MAX];
int dist[MAX];
int pre[MAX];
vector<int> store;

bool cycle_detected = false;

/*
This problem's intended solution is DFS. Sort of easier to get into depth and find all the nodes of a circular path
Otherwise from BFS, lets you see that (u->v) is a connection and v is gray
- find the parents of u (all)
- find the parents of v (all)
- make the merged vector: remove repeating elements
Best solution will come using DFS and stack
*/

void lca_bruteforce(int u, int v);

bool bfs(int v,int e,int s)
{
    for(int i=1; i<=v; i++) // i = 1 wasn't there
    {
        color[i]='w';
        dist[i]=NULL;
        pre[i]=MAX;
    }
    queue<int> q;
    color[s]='g';
    dist[s]=0;
    pre[s]=-1;
    q.push(s);
    while(!q.empty())
    {
        int node= q.front();
        //cout<<"node = "<<node<<endl;
        q.pop();

        for(int i=0; i<graph[node].size(); i++)
        {
            int next=graph[node][i];
            //cout<<"next "<<next<<" "<< color[next] << " "<< pre[next] << endl;
            if(color[next] == 'w')
            {
                color[next]='g';
                dist[next]=dist[node]+1;
                pre[next]=node;
                q.push(next);
            }
            else if(color[next]=='g' && pre[next] != node)
            {
                //store.push_back(next);
                cycle_detected = true;
                lca_bruteforce(node, next);
                return true;
            }
        }
        color[node]='b';

    }
    return false;
}

void lca_bruteforce(int u, int v){
  // idea using lowest common ancestor finding
  while(true){
       store.push_back(u);
       store.push_back(v);
       u = pre[u];
       v = pre[v];
       if(u == v) {
            store.push_back(u);
            break;
       }
  }
   sort(store.begin(), store.end());
    for(int i=0; i<store.size(); i++){
        cout<<store[i]<<" ";
    }
    cout<<endl;
    return;
}

void path_print(int st, int en){
    // idea on cycle start and end node connection
    store.clear();
    int curr = en;
    while(true){
        store.push_back(curr);
        curr = pre[curr];
        //cout<<"curr "<<curr<<endl;
        if(curr == st) {
            store.push_back(curr);
            break;
        }
    }
    sort(store.begin(), store.end());
    for(int i=0; i<store.size(); i++){
        cout<<store[i]<<" ";
    }
    cout<<endl;
    return;
}

void dfs_solution(int node){

    for(int i=0; i<graph[node].size(); i++){
        //cout<<graph[node][i]<<endl;
        if(color[graph[node][i]] == 'w') {
            pre[graph[node][i]] = node;
            color[graph[node][i]] = 'g';
            dfs_solution(graph[node][i]);
        }
        else if(color[graph[node][i]] == 'g' && pre[node] != graph[node][i]){
            // cycle detected
            cycle_detected = true;
            path_print(graph[node][i], node);

        }
    }
    color[node] = 'b';
    return;
}

void dfs(int v,int e){
    for(int i=1; i<=v; i++) // i = 1 wasn't there
    {
        color[i]='w';
        pre[i]=-1;
    }
    for(int i=1; i<=v; i++){
        if(color[i] == 'w') {
            color[i] == 'g';
            dfs_solution(i);
        }
    }
}

/*
6 6
1 2
2 3
3 4
3 5
4 5
4 6
*/

int main()
{
    int v,e;
    cin>>v>>e;
    for(int i=1; i<=e; i++)
    {
        int v,u;
        cin>>v>>u;
        graph[v].push_back(u);
        graph[u].push_back(v);
    }
    cout<<"solution from bfs"<<endl;
    bool c=bfs(v,e,1);
    cout<<"solution from dfs"<<endl;
    dfs(v,e);
    if(!cycle_detected) cout<<"NO"<<endl;
    return 0;
}
