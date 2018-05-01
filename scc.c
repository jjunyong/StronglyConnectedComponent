#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define numOfVertex 8

struct node{
	int index; 
	struct node * link;
};

struct node * linkedArray[numOfVertex];
struct node * linkedArray_trans[numOfVertex];
int time=1;
int d[numOfVertex]={0};
int f[numOfVertex]={0};
int dG[numOfVertex]={0};
int fG[numOfVertex]={0};
char color[numOfVertex];
int order[numOfVertex];
int cnt=0;

void addEdge(int v1, int v2) {

	if(v1>=17 && v2>=17){
		v1 = v1-17;
		v2 = v2-17;

//		printf("v1 : %d, v2: %d\n",v1,v2);
	}

	struct node * newNode = (struct node *)malloc(sizeof(struct node));

	struct node * cur = linkedArray[v1];

	newNode->index = v2;
	newNode->link = NULL;

	if (cur == NULL) {
		linkedArray[v1] = newNode;
		return;
	}
	else {
		while (cur->link != NULL) {
			cur = cur->link;
		}
		cur->link = newNode;
		return;
	}
}
void addTransEdge(int v1, int v2) {

	if(v1>=17 && v2>=17){
		v1 = v1-17;
		v2 = v2-17;
	}

	struct node * newNode = (struct node *)malloc(sizeof(struct node));

	struct node * cur = linkedArray_trans[v1];

	newNode->index = v2;
	newNode->link = NULL;

	if (cur == NULL) {
		linkedArray_trans[v1] = newNode;
		return;
	}
	else {
		while (cur->link != NULL) {
			cur = cur->link;
		}
		cur->link = newNode;
		return;
	}
}
void DFS_Visit(int u){

	color[u] = 'G';
	dG[u] = time++;

	struct node* cur;
	
	cur = linkedArray[u];
	while(cur!=NULL){
		if(color[cur->index]=='W'){
//			printf("visit vertex %d\n",cur->index);
			DFS_Visit(cur->index);
		}
		cur = cur->link;
	}
	color[u] = 'B';
	fG[u] = time++;
}


void DFS_Visit_trans(int u, int SCC){

	color[u] = 'G';
	d[u] = time++;

	struct node* cur;
	
	cur = linkedArray_trans[u];
	while(cur!=NULL){
		if(color[cur->index]=='W'){
			if(SCC)
				printf("vertex%c ",(char)((cur->index)+'0'+17));
			DFS_Visit_trans(cur->index,SCC);
		}
		cur = cur->link;
	}
	color[u] = 'B';
	f[u] = time++;
}

void DFS(){

	time = 1;

	for(int i=0;i<numOfVertex;i++){
		color[i] = 'W';
	}
	for(int i=0;i<numOfVertex;i++){
		if(color[i] == 'W'){
	//		printf("Start DFS from vertex %d\n",i);
			DFS_Visit(i);
		}
	}
}

void DFS_decrease_order(int SCC){

	time = 1;

	for(int i=0;i<numOfVertex;i++){
		color[i] = 'W';
	}
	

	if(SCC==1){
		
		for(int i=0;i<numOfVertex;i++){
			if(color[order[i]] == 'W'){
				printf("\nSCC %d :",cnt++);
				printf("vertex%c ",(char)(order[i]+'0'+17));
				DFS_Visit_trans(order[i],SCC);
			}
		}
	}
	else{
		for(int i=0;i<numOfVertex;i++){
			if(color[i] == 'W'){
//				printf("Start DFS from vertex %d\n",i);
				DFS_Visit_trans(i,SCC);
			}
		}
	}
}

void show(){

	for(int i=0;i<numOfVertex;i++){
		struct node* cur= linkedArray[i];
		printf("%c vertex is linked to :",(char)(i+'0'+17));
		while(cur!=0){
			printf("%c ",(char)(cur->index+'0'+17));
			cur = cur->link;
		}
		printf("\n");
	}
	
}

int main() {

	
	FILE *fp ; //파일 포인터

        fp = fopen("hw4.data","r");

        char storage[numOfVertex+1][numOfVertex+1];
        char ch;


        int i=0;
        while(i<numOfVertex+1){
                int j=0;
                while(j<numOfVertex+1){
                        ch=fgetc(fp);
                        if(i==0 && j==0){
                                storage[i][j]= ' ';
                                j++;
                                continue;
                        }
                        if(ch!='\t' && ch!=' ' && ch!='\n' && ch!='\v' && ch!='\f' && ch!='\r'){
                                storage[i][j] = ch;
                                j++;
                        }

                }
                i++;
        }


        int j;
        for(i=0;i<numOfVertex+1;i++){
                for(j=0;j<numOfVertex+1;j++){
                        printf("%c",storage[i][j]);
                }
                printf("\n");
	}
	printf("-----------------------------------------------------\n");


	for(int i=1;i<numOfVertex+1;i++){
		for(int j=1;j<numOfVertex+1;j++){
			if(storage[i][j]=='1'){
				addEdge(storage[i][0]-'0',storage[0][j]-'0');
				addTransEdge(storage[0][j]-'0',storage[i][0]-'0');
			//	printf("%c - %c\n", storage[i][0],storage[j][0]);
			}
		}
	}


	show();
	DFS();
	printf("-----------------------------------------------------\n");
	printf("discovery time & finish time of input Graph\n");
	for(int i=0;i<numOfVertex;i++)
		printf("discovery time of vertex %c : %d\n",(char)(i+'0'+17),dG[i]);
	for(int i=0;i<numOfVertex;i++)
		printf("finish time of vertex %c: %d\n",(char)(i+'0'+17),fG[i]);
	
	for(int i=0;i<numOfVertex;i++){
		int max=fG[0];	
		int index=0;
	
		for(int j=1;j<numOfVertex;j++){
			if(max<fG[j]){
				max = fG[j];
				index = j;
			}		
		}
		order[i] = index;
		fG[index] = -1;
	}

	DFS_decrease_order(0);
	printf("-----------------------------------------------------\n");
	printf("discovery time & finish time of transposed input Graph\n");
	for(int i=0;i<numOfVertex;i++)
		printf("discovery time of vertex %c : %d\n",(char)(i+'0'+17),d[i]);
	for(int i=0;i<numOfVertex;i++)
		printf("finish time of vertex %c : %d\n",(char)(i+'0'+17),f[i]);
	printf("-----------------------------------------------------\n");
	printf("*****Strongly Connected Components of given graph*****"); 
	DFS_decrease_order(1);
	printf("\n");

	return 0;
}
