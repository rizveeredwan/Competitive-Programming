#include <bits/stdc++.h>
using namespace std;
#define MAX 501

void input(int *r, int *c, int arr[MAX][MAX]){
    cin>>*r>>*c;
    for(int i=0; i<*r; i++){
        for(int j=0; j<*c; j++){
            cin>>arr[i][j];
        }
    }
    return;
}

struct DijkstraState{
    int x,y,cost;
    // Another way of writing
    bool operator < (const DijkstraState a) const {
        if(cost < a.cost) return false; // need to be in front
        else return true;
    }
};

struct Dijkstra{
    vector<vector<int>>dist;
    map<pair<int,int>, pair<int,int>>parent;
    int dx[3] = {0, 1, -1};
    priority_queue<DijkstraState>PQ;
    int inf = 100000000;
    int algorithm(int arr[MAX][MAX], int r, int c){
        int explored = 0;
        this->init(r,c);
        //cout<<"came"<<endl;
        for(int i=0; i<c; i++){
            this->dist[r-1][i] = arr[r-1][i];
            this->parent[{r-1,i}] = {-1, -1};
            this->insert_in_pq(r-1,i,arr[r-1][i]);
            //cout<<" i "<<i<< " "<<this->PQ.top().x<<" "<<this->PQ.top().y<<" "<<this->PQ.top().cost<<" "<<arr[r-1][i]<<endl;
        }
        //cout<<"came"<<endl;
        DijkstraState u;
        while(this->PQ.empty() != true){
            u = this->PQ.top();
            //cout<<"what "<<u.x<<" "<<u.y<<" "<<u.cost<<endl;
            this->PQ.pop();
            //if(u.cost>this->dist[u.x][u.y]) continue; // I have already worked with lower cost
            if(u.x == 0) {
                cout<<u.cost<<endl;
                break; // reached destination
            }
            explored++;
            for(int i=0; i<3; i++){
                if(u.x-1 >= 0 && u.y+dx[i] >=0 && u.y+dx[i] < c) {
                    //cout<<"u "<<u.x-1<<" "<<u.y+dx[i]<<endl;
                    if(this->dist[u.x-1][u.y+dx[i]] > (u.cost + arr[u.x-1][u.y+dx[i]])){
                        this->dist[u.x-1][u.y+dx[i]] = u.cost + arr[u.x-1][u.y+dx[i]];
                        this->insert_in_pq(u.x-1,u.y+dx[i],this->dist[u.x-1][u.y+dx[i]]);
                        this->parent[{u.x-1, u.y+dx[i]}] = {u.x,u.y};
                    }
                }
            }
        }
        return explored;
    }
    void insert_in_pq(int x, int y, int cost){
        DijkstraState temp;
        temp.x=x;
        temp.y=y;
        temp.cost=cost;
        this->PQ.push(temp);
        //cout<<"x "<<x<<" y = "<<y<<" "<<cost<<endl;
        return;
    }
    void init(int r, int c){
        //cout<<r<<" "<<c<<endl;
        this->dist.clear();
        this->parent.clear();
        vector<int>temp;
        for(int i=0; i<r; i++){
            this->dist.push_back(temp);
            for(int j=0; j<c;j++){
                this->dist[i].push_back(this->inf);
                //cout<<" i "<<i<<" "<<j<<endl;
            }
        }
        while(this->PQ.empty() != true){
            this->PQ.pop();
        }
    }
    void path_print(int arr[MAX][MAX], int r, int c){
        //cout<<"path printing"<<endl;
        int x,y;
        int res = this->inf;
        for(int i=0; i<c; i++){
            if(this->dist[0][i] < res) {
                res = this->dist[0][i];
                x = 0;
                y = i;
            }
        }
        vector<pair<int,int>>V;
        if(res == inf) {
            cout<<"-1"<<endl;
            return;
        }
        pair<int,int>temp;
        while(x != -1 && y != -1){
            //cout<<"x "<<x<<" "<<y<<endl;
            V.push_back({x,y});
            temp = this->parent[{x,y}];
            x = temp.first;
            y = temp.second;
            //break;
        }
        reverse(V.begin(), V.end());
        cout<<V.size()<<endl;
        for(int i=0; i<V.size(); i++) {
            cout<<V[i].first<<" "<<V[i].second<<endl;
        }
        return;
    }
};

int main(void){
    freopen("large_in2.txt", "r", stdin);
    freopen("large_out2.txt", "w", stdout);
    int r,c;
    int arr[MAX][MAX];
    input(&r,&c,arr);
    //cout<<r<<" "<<c<<" "<<arr[r-1][c-1]<<endl;
    Dijkstra d;
    int explored = d.algorithm(arr, r, c);
    d.path_print(arr,r,c);
    cout<<explored<<endl;
    return 0;
}
