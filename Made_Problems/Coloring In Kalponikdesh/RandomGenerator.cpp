#include <bits/stdc++.h>
using namespace std;
#define MAX 1005

bool arr[MAX+1][MAX+1];

void question_case_genrate(){
		freopen("question_case.txt","w",stdout);
		//given case generation
		int test_case=3;
		printf("%d\n",test_case);
		for(int i=1;i<=test_case;i++){
				int row=rand()%5+1;
				int col=rand()%5+1;
	
				int sp_cell=rand()%2+1;
				printf("%d %d %d\n",row,col,sp_cell);
				assert(row>=1&&row<=1000);
				assert(col>=1&&col<=1000);
				assert(sp_cell>=1&&sp_cell <= (row*col));
				
				int cnt=1;
				memset(arr,false,sizeof(false));
				//printf("%d %d %d\n",row,col,sp_cell);
				while(cnt<=sp_cell){
					int x=rand()%row+1;
					int y=rand()%col+1;
				//printf(" randome = %d %d\n",x,y);
			    if(arr[x][y]==false){
					arr[x][y]=true;
					cnt++;
					printf("%d %d\n",x,y);
				}
			}
		}
		return;
}

//all the cells are of 1000 * 1000 
void critical_case_1(){
	freopen("critical_case_1.txt","w",stdout);
	//given case generation
		int test_case=50;
		printf("%d\n",test_case);
		for(int i=1;i<=test_case;i++){
				int row=1000;
				int col=1000;
	
				int sp_cell=rand()%1000+1;
				printf("%d %d %d\n",row,col,sp_cell);
				assert(row>=1&&row<=1000);
				assert(col>=1&&col<=1000);
				assert(sp_cell>=1&&sp_cell <= (row*col));
				
				int cnt=1;
				memset(arr,false,sizeof(false));
				//printf("%d %d %d\n",row,col,sp_cell);
				while(cnt<=sp_cell){
					int x=rand()%row+1;
					int y=rand()%col+1;
				//printf(" randome = %d %d\n",x,y);
			    if(arr[x][y]==false){
					arr[x][y]=true;
					cnt++;
					printf("%d %d\n",x,y);
				}
			}
		}
		return;
}

//all the cells are 1000 1000 plus special cells are 300
void critical_case_2(){
	freopen("critical_case_2.txt","w",stdout);
	//given case generation
		int test_case=50;
		printf("%d\n",test_case);
		for(int i=1;i<=test_case;i++){
				int row=1000;
				int col=1000;
	
				int sp_cell=300;
				printf("%d %d %d\n",row,col,sp_cell);
				assert(row>=1&&row<=1000);
				assert(col>=1&&col<=1000);
				assert(sp_cell>=1&&sp_cell <= (row*col));
				
				int cnt=1;
				memset(arr,false,sizeof(false));
				//printf("%d %d %d\n",row,col,sp_cell);
				while(cnt<=sp_cell){
					int x=rand()%row+1;
					int y=rand()%col+1;
				//printf(" randome = %d %d\n",x,y);
			    if(arr[x][y]==false){
					arr[x][y]=true;
					cnt++;
					printf("%d %d\n",x,y);
				}
			}
		}
		return;
}

//all the cells are 1000 1000 plus special cells are greater than 300
void critical_case_3(){
	freopen("critical_case_3.txt","w",stdout);
	//given case generation
		int test_case=50;
		printf("%d\n",test_case);
		for(int i=1;i<=test_case;i++){
				int row=1000;
				int col=1000;
	
				int sp_cell;
				while(1){
						int v=rand()%1000;
						if(v>=300){
							sp_cell=v;
							break;
					 }
				}
				printf("%d %d %d\n",row,col,sp_cell);
				assert(row>=1&&row<=1000);
				assert(col>=1&&col<=1000);
				assert(sp_cell>=1&&sp_cell <= (row*col));
				
				int cnt=1;
				memset(arr,false,sizeof(false));
				//printf("%d %d %d\n",row,col,sp_cell);
				while(cnt<=sp_cell){
					int x=rand()%row+1;
					int y=rand()%col+1;
				//printf(" randome = %d %d\n",x,y);
			    if(arr[x][y]==false){
					arr[x][y]=true;
					cnt++;
					printf("%d %d\n",x,y);
				}
			}
		}
		return;
}

//totally random case
void critical_case_4(){
	freopen("critical_case_4.txt","w",stdout);
	//given case generation
		int test_case=50;
		printf("%d\n",test_case);
		for(int i=1;i<=test_case;i++){
				int row=rand()%1000+1;
				int col=rand()%1000+1;
	
				int sp_cell=rand()%(row*col)+1;
				printf("%d %d %d\n",row,col,sp_cell);
				assert(row>=1&&row<=1000);
				assert(col>=1&&col<=1000);
				assert(sp_cell>=1&&sp_cell <= (row*col));
				
				int cnt=1;
				memset(arr,false,sizeof(false));
				//printf("%d %d %d\n",row,col,sp_cell);
				while(cnt<=sp_cell){
					int x=rand()%row+1;
					int y=rand()%col+1;
				//printf(" randome = %d %d\n",x,y);
			    if(arr[x][y]==false){
					arr[x][y]=true;
					cnt++;
					printf("%d %d\n",x,y);
				}
			}
		}
		return;
}

int main(void){
	srand(time(NULL));
	//question_case_genrate();
	//critical_case_1();
	//critical_case_2();
	//critical_case_3();
	//critical_case_4();
	
	return 0;		
}
