#include <bits/stdc++.h>
using namespace std;
#define MAX 1005


//direction Array
int dx[]={-1,1,0,0};
int dy[]={0,0,1,-1};

bool visit[MAX+1][MAX+1];
int row,col;

struct Point{
	int x,y;
	int lev;
};

queue<struct Point>Q;

void init(){
	memset(visit,false,sizeof(visit));
	while(Q.empty()!=true)Q.pop();
}

bool check(int r,int c){
	if(r>=1&&r<=row && c>=1 && c<=col) return true;
	else return false;
}

int bfs(){
	int level=0;
	while(Q.empty() !=true){
		struct Point p;
		p=Q.front();
		Q.pop();
		for(int i=0;i<=3;i++){
				int x=p.x+dx[i];
				int y=p.y+dy[i];
				
				bool ok=check(x,y);
				if(ok && visit[x][y]==false){
					visit[x][y]=true;
					struct Point temp;
					temp.x=x;
					temp.y=y;
					temp.lev=p.lev+1;
					level=max(level,temp.lev);
					Q.push(temp);
				}
				
				
		} 
	}
	return level;
}

int main(void) {
	
	//freopen("critical_case_3.txt","r",stdin);
	//freopen("critical_case_3_out.txt","w",stdout);
	int T,t;
	scanf("%d",&T);
	assert(T>=1 && T<=50);
	for(t=1;t<=T;t++){
		int sp_cell;
		scanf("%d %d %d",&row,&col,&sp_cell);
		assert(row>=1&&row<=1000);
		assert(col>=1&&col<=1000);
		assert(sp_cell>=1 && sp_cell<=(row*col));
		
		//initialize
		init();
		//special cells
		for(int i=1;i<=sp_cell;i++){
			int r,c;
			scanf("%d %d",&r,&c);
			assert(r>=1&&r<=row);
			assert(c>=1&&c<=col);
			
			struct Point temp;
			visit[r][c]=true;
			temp.x=r;
			temp.y=c;
			temp.lev=0;
			Q.push(temp);
		}
		int ans = bfs();
		printf("%d\n",ans);
	}
	return 0;
}
