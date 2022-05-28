#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX		10 //10개 vertex

typedef struct G_Node{
	int vertex;
	struct G_Node *link;
}GraphNode;

typedef struct G_Type{
	int n;
	GraphNode *adj_list[MAX_VERTEX];
}GraphType;

void initialize(GraphType*);
void insertVertex(GraphType* Graph);
void insertEdge(GraphType* Graph, int v1, int v2);
void DFS();
void BFS();
void printGraph();
void freeGraph(GraphType* Graph);

/* for queue-탐색에 필요함. */
#define MAX_QUEUE_SIZE		10
int queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

int deQueue();
void enQueue(int aNode);


int main()
{
	char command;
	int v, v1, v2;
    GraphType* Graph = (GraphType*)malloc(sizeof(GraphType));

	printf("-----허정윤 2021041047-----\n");
	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                      Binary Search Tree                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Graph     = z                                       \n");
		printf(" Insert Vertex        = v      Insert Edge                  = e \n");
		printf(" Depth First Search   = d      Breath First Search          = b \n");
		printf(" Print Graph          = p      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(Graph);
			break;
		case 'q': case 'Q':
			freeGraph(Graph);
			break;
		case 'v': case 'V':
			insertVertex(Graph);
			break;
		case 'e': case 'E':
			printf("Input two vertex = ");
			scanf("%d %d", &v1, &v2);
			if(v1==v2){
				printf("Error : Same vertex\n");
				break;
			}
			insertEdge(Graph, v1, v2);
			break;

		case 'd': case 'D':
			DFS();
			break;
		case 'b': case 'B':
			BFS();
			break;

		case 'p': case 'P':
			printGraph();
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

void initialize(GraphType* Graph)
{
	Graph->n =0;
	for(int v=0; v<MAX_VERTEX; v++){
		Graph->adj_list[v] = NULL;
	}
}

void insertVertex(GraphType* Graph)
{
    //Graph를 initialize하지 않았을 경우.
    /*
	if(){
        printf("Error : Please Initialize.\n");
        return 1;
    }
	*/

	//n(갯수)에 1을 더해서 최대 vertex보다 크면 오류.
	if(((Graph->n)+1)>MAX_VERTEX){
		printf("Error : Max Vertex\n");
		return;
	}

	//리턴되지 않았으면 n에 1을 더한다.
	Graph->n++;
}

void insertEdge(GraphType* Graph, int v1, int v2)
{
    //Graph를 initialize하지 않았을 경우.
    /*
	if(){
        printf("Error : Please Initialize.\n");
        return 1;
    }
	*/
	//v1,v2가 현재 vertex 외의 vertex를 지정한 경우
	if(v1>=Graph->n||v2>=Graph->n||v1<=Graph->n||v2<=Graph->n){
		printf("Error : Out of Vertex number\n");
		return;
	}

	//노드들을 만들어줌.
	GraphNode* node = (GraphNode*)malloc(sizeof(GraphNode));
	GraphNode* pre = NULL;
	GraphNode* chan = Graph->adj_list[v1];
	node->vertex = v2;
	node->link = NULL;

	//chan->link가 NULL이 아닌동안 chan을 옮겨가며 비교
	for(;chan->link;chan = chan->link){
		//같은 경우는 이미 있는 경우이므로, 오류메시지 출력 후 리턴.
		if(chan->vertex == node->vertex){
			printf("Error : Exsisted Node\n");
			return;
		}
		//오름차순으로 연결한다고 가정하여
		//chan의 vertex가 큰 경우 노드에 chan을 연결
		if(chan->vertex > node->vertex){
			node->link = chan;
			//chan의 앞노드(pre)가 NULL이면 앞에다가 연결
			//그렇지 않으면 pre에다가 node 연결
			if(pre == NULL) {
				Graph->adj_list[v1] = node;
				return;
			}
			else {
				pre->link = node;
				return;
			}
			
		}
		pre = chan;
	}
	//안들어간 경우, 맨 뒤에 붙이기
	chan->link = node;

	//v1과 v2를 바꾸어서 위와 동일하게 시도.
	chan = Graph->adj_list[v2];
	pre = NULL;
	node->vertex = v1;
	for(;chan->link;chan = chan->link){
		if(chan->vertex > node->vertex){
			node->link = chan;
			if(pre == NULL) {
				Graph->adj_list[v2] = node;
				return;
			}
			else {
				pre->link = node;
				return;
			}
		}
		pre = chan;
	}
	//안들어간 경우, 맨 뒤에 붙이기
	chan->link = node;
}

void DFS()
{

}

void BFS()
{

}

void printGraph()
{

}

void freeGraph(GraphType* Graph)
{

}