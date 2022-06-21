#include <bits/stdc++.h>
using namespace std;
#define MAX 501

void input(int *r, int *c, int arr[MAX][MAX], int *src_x, int *src_y, int *des_x, int *des_y){
    int block;
    cin>>*r>>*c>>block;
    int x,y;
    for(int i=0; i<*r; i++){
        for(int j=0; j<*c; j++){
            arr[i][j] = 0;
        }
    }
    for(int i=0; i<block; i++){
        cin>>x>>y;
        arr[x][y] = 1; // block
    }
    cin>>*src_x>>*src_y>>*des_x>>*des_y;
    return;
}

struct DijkstraState{
    int x,y,g,h;
    // Another way of writing
    bool operator < (const DijkstraState a) const {
        if((g+h) < (a.g+a.h)) return false; // need to be in front
        else return true;
    }
};

int return_h_value(int src_x, int src_y, int des_x, int des_y){
    return abs(des_x-src_x)+abs(src_y-des_y);
}

struct Dijkstra{
    vector<vector<int>>dist;
    map<pair<int,int>, pair<int,int>>parent;
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, 1, -1};
    priority_queue<DijkstraState>PQ;
    int inf = 100000000;
    int algorithm(int arr[MAX][MAX], int r, int c, int src_x, int src_y, int des_x, int des_y){
        int explored = 0;
        this->init(r,c);
        //cout<<"came"<<endl;
        this->dist[src_x][src_y] = 0;
        this->insert_in_pq(src_x,src_y,0,return_h_value(src_x, src_y, des_x, des_y));
        this->parent[{src_x,src_y}] = {-1, -1};

        //cout<<"came"<<endl;
        DijkstraState u;
        int solution = -1;
        int nx,ny;
        while(this->PQ.empty() != true){
            u = this->PQ.top();
            //cout<<"what "<<u.x<<" "<<u.y<<" "<<u.g<<" "<<u.h<<endl;
            this->PQ.pop();
            //if(u.cost>this->dist[u.x][u.y]) continue; // I have already worked with lower cost
            if(u.x == des_x && u.y == des_y) {
                solution = u.g;
                break; // reached destination
            }
            cout<<"what "<<u.x<<" "<<u.y<<" "<<u.g<<" "<<u.h<<endl;
            explored++;
            for(int i=0; i<4; i++){
                nx = u.x + dx[i], ny = u.y + dy[i];
                if(nx >= 0 && nx < r && ny >=0 && ny < c && arr[nx][ny] == 0) {
                    //cout<<"u "<<u.x-1<<" "<<u.y+dx[i]<<endl;
                    if(this->dist[nx][ny] > (u.g + 1)){
                        this->dist[nx][ny] = u.g+1;
                        this->insert_in_pq(nx,ny,this->dist[nx][ny], return_h_value(nx, ny, des_x, des_y));
                        this->parent[{nx, ny}] = {u.x,u.y};
                    }
                }
            }
        }
        cout<<solution<<endl;
        return explored;
    }
    void insert_in_pq(int x, int y, int g, int h){
        DijkstraState temp;
        temp.x=x;
        temp.y=y;
        temp.g=g;
        temp.h=h;
        this->PQ.push(temp);
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
    void path_print(int arr[MAX][MAX], int r, int c, int srcx, int srcy, int desx, int desy){
        //cout<<"path printing"<<endl;
        vector<pair<int,int>>V;
        if(this->dist[desx][desy] == inf) {
            cout<<"-1"<<endl;
            return;
        }
        pair<int,int>temp;
        int x=desx, y = desy;
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
    freopen("in1.txt", "r", stdin);
    int r,c, arr[MAX][MAX], src_x, src_y, des_x, des_y;
    input(&r, &c, arr, &src_x, &src_y, &des_x, &des_y);
    Dijkstra d;
    int explored = d.algorithm(arr, r, c, src_x, src_y, des_x, des_y);
    d.path_print(arr, r, c, src_x, src_y, des_x, des_y);
    cout<<explored<<endl;
    return 0;
}
