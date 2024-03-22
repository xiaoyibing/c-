//这方法好麻烦
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
    int* indegree;//前置条件的个数
    int* visit;//是否是第一次访问
    int* time;//个人
    int* distance;//总体
    int* shang;
    int* s;//是否确定最小
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
    graph->time=(int*)malloc(sizeof(int)*n);
    graph->distance=(int*)malloc(sizeof(int)*n);
    graph->s=(int*)malloc(sizeof(int)*n);
    graph->shang=(int*)malloc(sizeof(int)*n);
    for(int i=0;i<n;++i){
        graph->nodes[i] = NULL;//开始为空，后面会不断连接上邻居节点
        graph->indegree[i] =graph->visit[i]=graph->time[i]=graph->distance[i]=graph->s[i]= 0;
        graph->shang[i]=-1;
        graph->distance[i]=INT_MAX;
    }
    return graph;
}

void creatEdge(Graph* graph,int ru,int chu){
    Node* newNode=creatNode(chu);
    newNode->next=graph->nodes[ru];
    graph->nodes[ru]=newNode;
    graph->indegree[chu]++;
}

bool Number(char n){
    return  n<='Z' && n>='A';
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
        //printf("%s",buffer);

        char* token=strtok(buffer,",\n");
        char name=token[0];
        int chu= token[0] - 'A';

        token = strtok(NULL,",\n");
        while(token != NULL && token[0] != '^' && Number(token[0])){
            int ru=token[0] - 'A';
            creatEdge(graph,ru,chu);
            token = strtok(NULL, ",\n");
        }
        if(token[0] == '^'){
            token = strtok(NULL,",\n");
        }
            int time=atoi(token);
            //printf("%d\n",time);
            graph->time[chu]=time;
    }
    fclose(fp);
    return graph;
}
int minDistance(Graph* graph) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < graph->numVertices; ++v) {
        if (graph->s[v] == 0 && graph->distance[v] < min) {
            min = graph->distance[v];
            min_index = v;
        }
    }
    graph->s[min_index]=1;
    return min_index;
}

// Dijkstra 算法求最短路径
void dijkstra(Graph* graph, int src) {
    graph->distance[src] = graph->time[src];  // 源点到自身的距离
    for (int count = 0; count < graph->numVertices; ++count) {
        int u = minDistance(graph);
        Node* temp = graph->nodes[u];
        while (temp != NULL) {
            int v = temp->id;
            if (graph->distance[u]+graph->time[v] < graph->distance[v]) {
                graph->distance[v] = graph->distance[u]+graph->time[v];
                graph->shang[v]=u;
            }
            temp = temp->next;
        }
    }
    printf("最短路径是：%d\n",graph->distance[22]);
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
            char id=currentNode->id+'A';
            printf("->%c ", id);
            currentNode = currentNode->next;
        }
        printf("%d ",graph->time[i]);
        printf("\n");
    }
}
void topology(Graph* graph){
    int n=0;
    int* output=(int*)malloc(sizeof(int)*graph->numVertices);

    for (int i = 0; i < graph->numVertices; ++i) {
        if (graph->indegree[i] == 0) {
            graph->visit[i] = 1;
            output[n++] = i;
            Node* temp = graph->nodes[i];
            while (temp) {
                graph->indegree[temp->id]--;
                temp = temp->next;
            }
        }
    }
    int count = 0;
    while (n < graph->numVertices) {
        if (graph->visit[count] == 0 && graph->indegree[count] == 0) {
            graph->visit[count] = 1;
            output[n++] = count;
            Node* temp = graph->nodes[count];
            printf("%d ",count);
            while (temp) {
                graph->indegree[temp->id]--;
                temp = temp->next;
            }
            count = 0;
        }
        else {
            count++;
            if(count > graph->numVertices){
                break;
            }
        }
    }
    n--;
    if(n!=graph->numVertices-1){
        printf("有环:");
        for(int i=0;i<graph->numVertices;++i){
            int tf=0;
            for(int j=0;j<=n;++j){
                if(i == output[j]){
                    tf=1;
                    } 
                }
            if(tf==0)
                printf("%c ", i+'A');
        }
    }else{
        printf("无环\n");
        dijkstra(graph,0);
    }
    free(output);
   
}
int main(){
    char filename[]="p02.txt";//文件名
    Graph* graph=readFile(filename);
    //printGraph(graph);
    topology(graph);
    return 0;
}

