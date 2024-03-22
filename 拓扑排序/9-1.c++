#include <stdio.h>
#include<stdlib.h>
#include <string.h>
//领接表节点
typedef struct Node{
    int id;//序号
    struct Node* next;//下一位
} Node;
//图表
typedef struct Graph{
    int numVertices;//顶点数量
    Node* nodes[100];//顶点领接表
    int* indegree;//前置条件
    int* visit;//是否是第一次访问
} Graph;
//新建领接表节点
Node* creatNode(int id){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->id=id;
    newNode->next=NULL;
    return newNode;
}
//新建图表
Graph* creatGraph(int n){
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices=n;
    graph->indegree=(int*)malloc(sizeof(int)*n);//数组
    graph->visit=(int*)malloc(sizeof(int)*n);
    for(int i=0;i<n;++i){
        graph->nodes[i] = NULL;//开始为空，后面会不断连接上邻居节点
        graph->indegree[i] =graph->visit[i] = 0;
    }
    return graph;
}

void creatEdge(Graph* graph,int ru,int chu){
    Node* newNode=creatNode(chu);
    newNode->next=graph->nodes[ru];
    graph->nodes[ru]=newNode;
    graph->indegree[chu]++;
}

Graph* readFile(const char* filename){
    FILE* fp=fopen(filename,"r");
    if(!fp){printf("无法打开文件 %s\n",filename);return NULL;}

    char buffer[100];
    int numVertices=0;
    while (fgets(buffer,sizeof(buffer),fp)){
        numVertices++;
    }
    
    fseek(fp, 0, SEEK_SET);

    Graph* graph=creatGraph(numVertices);

    while (fgets(buffer,sizeof(buffer),fp)){

        char* token=strtok(buffer,",\n");
        char name=token[0];
        int chu= token[0] - 'A';

        token = strtok(NULL,",\n");
        while(token != NULL && token[0] != '^'){
            int ru=token[0] - 'A';
            creatEdge(graph,ru,chu);
            token = strtok(NULL, ",\n");
        }
    }
    fclose(fp);
    return graph;
}

void printGraph(Graph* graph) {
    printf("\n");
    for (int i = 0; i < graph->numVertices; ++i) {


        Node* currentNode = graph->nodes[i];


        printf("%d %d %c ", i,graph->indegree[i],i + 'A');
        if(!currentNode){
            printf("^");
        }
        while (currentNode) {
            char id=currentNode->id;
            printf("->%d ", id);
            currentNode = currentNode->next;
        }
        printf("\n");
    }
}

int main(){
    char filename[]="p01.txt";//文件名


    Graph* graph=readFile(filename);
    printGraph(graph);


    return 0;
}

