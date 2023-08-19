#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define MAX 25

int start_time[MAX+1],end_time[MAX+1],time_count,visit[MAX+1];
vector<int>graph[MAX+1];

bool cmp(pair<int,int>a, pair<int,int>b){
    if(a.second<b.second) return false;
    if(a.second>b.second) return true;
    return false;
}

void init(){
    memset(start_time,0,sizeof(start_time));
    memset(end_time,0,sizeof(end_time));
    memset(visit,0,sizeof(visit));
    time_count = 0;
}

void dfs(int node){
  visit[node]=1;
  time_count++;
  start_time[node]=time_count;
  for(int i=0;i<graph[node].size();i++){
    if(visit[graph[node][i]]==0){
       dfs(graph[node][i]);
    }
  }
  time_count++;
  end_time[node]=time_count;
}

void TopologicalSorting(int tot_node){
    init();
    vector<int>temp;
    for(int i=0; i<tot_node; i++) temp.push_back(i);
    random_shuffle(temp.begin(), temp.end());
    for(int i=0;i<tot_node;i++){
        if(visit[temp[i]] == 0){
            dfs(temp[i]);
        }
    }
    vector<pair<int,int>>ti;
    for(int i=0;i<tot_node;i++){
        ti.push_back({i,end_time[i]});
    }
    sort(ti.begin(),ti.end(),cmp);
    for(int i=0;i<ti.size();i++){
        cout<<ti[i].first+1<<endl;
    }
    return;
}

int main(void){
    srand(time(nullptr));
    freopen("in1.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int node,edge,a,b;
    cin>>node>>edge;
    for(int i=0;i<edge;i++){
        cin>>a>>b;
        graph[b-1].push_back(a-1); //you can do a after doing b
    }
    for(int i=0; i<node; i++){
        random_shuffle(graph[i].begin(), graph[i].end());
    }
    TopologicalSorting(node);
    return 0;
}
