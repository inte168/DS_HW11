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

void initialize(GraphType**);
void insertVertex(GraphType* Graph);
int insertEdge(GraphType* Graph, int v1, int v2);
void DFS(GraphType* Graph);
void BFS(GraphType* Graph);
void printGraph();
void freeGraph(GraphType* Graph);
int invert(GraphNode* node);

/* for stack -탐색에 필요함*/
#define MAX_SIZE		10
int stack[MAX_SIZE];
int top = -1;

int pop();
void push(int aNode);

/* for queue-탐색에 필요함. */
int queue[MAX_SIZE];
int front = -1;
int rear = -1;

int deQueue();
void enQueue(int aNode);


int main()
{
	char command;
	int v1, v2;
    GraphType* Graph = NULL;

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
			initialize(&Graph);
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
			insertEdge(Graph, v1, v2);
			insertEdge(Graph, v2, v1);
			break;

		case 'd': case 'D':
			DFS(Graph);
			break;
		case 'b': case 'B':
			BFS(Graph);
			break;

		case 'p': case 'P':
			printGraph(Graph);
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

//그래프 생성
void initialize(GraphType** Graph)
{
	//그래프를 동적할당하고 값들을 설정해준다.
	*Graph = (GraphType*)malloc(sizeof(GraphType));
	(*Graph)->n =0;
	for(int v=0; v<MAX_VERTEX; v++){
		(*Graph)->adj_list[v] = NULL;
	}
}

//vertex의 수를 늘리는 함수.
void insertVertex(GraphType* Graph)
{
    //Graph를 initialize하지 않았을 경우.
	if(Graph == NULL){
        printf("Error : Please Initialize.\n");
        return;
    }
	
	//n(갯수)에 1을 더해서 최대 vertex보다 크면 오류.
	if(((Graph->n)+1)>MAX_VERTEX){
		printf("Error : Max Vertex\n");
		return;
	}

	//리턴되지 않았으면 n에 1을 더한다.
	Graph->n++;
	printf("The number of vertex is %d", Graph->n);
}

//Edge를 넣는 함수.
int insertEdge(GraphType* Graph, int v1, int v2)
{
    //Graph를 initialize하지 않았을 경우.
	if(Graph == NULL){
        printf("Error : Please Initialize.\n");
        return 1;
    }
	//v1,v2가 현재 vertex 외의 vertex를 지정한 경우(0~n이 아닌, n을 넘으면 그 vertex가 없음.)
	if(v1>Graph->n||v2>Graph->n||v1<0||v2<0){
		printf("Error : Out of Vertex number\n");
		return 1;
	}

	//노드들을 만들어줌.(넣을 노드, 앞의 노드, 반복비교를 위한 노드)
	GraphNode* node = (GraphNode*)malloc(sizeof(GraphNode));
	GraphNode* pre = NULL;
	GraphNode* chan = Graph->adj_list[v1];
	node->vertex = v2;
	node->link = NULL;

	//처음에 해서 chan이 없는 경우. adj_list에 넣음.
	if(chan == NULL){
		Graph->adj_list[v1] = node;
		return 1;
	}
	//chan가 NULL이 아닌동안 chan을 옮겨가며 비교
	for(;chan;chan = chan->link){
		//같은 경우는 이미 있는 경우이므로, 오류메시지 출력 후 리턴.
		if(chan->vertex == node->vertex){
			printf("Error : Exsisted Node\n");
			return 1;
		}

		//오름차순으로 연결한다고 가정하여
		//chan의 vertex가 큰 경우 노드에 chan을 연결
		if(chan->vertex > node->vertex){
			node->link = chan;

			//chan의 앞노드(pre)가 NULL이면 앞에다가 연결
			//그렇지 않으면 pre에다가 node 연결
			if(pre == NULL) {
				Graph->adj_list[v1] = node;
				return 1;
			}
			else {
				pre->link = node;
				return 1;
			}
			
		}
		pre = chan;
	}
	//안들어간 경우, 맨 뒤에 붙이기
	pre->link = node;
	return 1;
}

void BFS(GraphType* Graph)
{
	//p는 시작점. N은 vertex 갯수, path는 방문 여부
	int p = 0;
	int N = Graph->n;
	int* path = (int*)malloc(N*sizeof(int));
	for (int i = 0; i < N; i++) {
		//다 0으로 만들어준다. (0이면 미방문, 1이면 방문)
		path[i] = 0;
	}

	//시작점인 0을 넣고, path에 기록, 출력
	enQueue(p);
	path[p] = 1;
	printf("%d ", p);

	
	//front == rear인 경우가 queue가 빌 경우.
	while(front != rear) {
		//node가 NULL일 때까지. 연결된 node를 전부 탐색한다.
		for(GraphNode* node = Graph->adj_list[p]; node; node = node->link) {
			//방문하지 않은 node가 있으면 enqueue
			if (path[node->vertex] != 1) {
				enQueue(node->vertex);				
			}
		}
		//dequeue하여 하나씩 방문여부 확인 및 출력
		p = deQueue();
		if(path[p] != 1) {
			printf("%d ", p);
			path[p] = 1;
		}
	}
	free(path);
	return;
}

void DFS(GraphType* Graph)
{
	//p는 시작점. N은 vertex 갯수, path는 방문 여부
	int p = 0;
	int N = Graph->n;
	int* path = (int*)malloc(N*sizeof(int));
	for (int i = 0; i < N; i++) {
		//다 0으로 만들어준다. (0이면 미방문, 1이면 방문)
		path[i] = 0;
	}

	//시작점인 0을 넣고, path에 기록, 출력
	push(p);
	path[p] = 1;
	printf("%d ", p);

	//미리 h를 이용해서 invert 시켜준다.
	GraphNode* h;
	for(int i=0;i<N;i++){
		h->link = Graph->adj_list[i];
		invert(h);
		Graph->adj_list[i] = h->link;
	}
	//top이 음수가 아니라면 (==비어있지 않다면)
	while (top>=0) {
		//vertex갯수만큼 반복하여- node가 있고, vertex를 방문하지 않았으면 push한다.
		for (GraphNode* node =  Graph->adj_list[p]; node; node = node->link) {
			if (path[node->vertex] != 1) {
				push(node->vertex);				
			}
		}

		//pop하여 방문하지 않은 경우에는 출력.
		p = pop();	
		if (path[p] != 1) {
			printf("%d ", p);
			path[p] = 1;
		}
	}
	//이후 사용을 위해서 다시 invert 시켜준다.
	for(int i=0;i<N;i++){
		h->link = Graph->adj_list[i];
		invert(h);
		Graph->adj_list[i] = h->link;
	}
	free(path);
	return;
}


void printGraph(GraphType* Graph)
{
	//adj_list의 index를 돌림
	for(int i =0;i<Graph->n;i++){
		GraphNode* node = Graph->adj_list[i];
		printf("vertex %d : ", i);
		//node를 넘겨가면서 vertex 출력.
		for(;node;node = node->link){
			printf("%d ", node->vertex);
		}
		printf("\n");
	}
}

void freeGraph(GraphType* Graph)
{	
	for(int i =0; i<=Graph->n;i++){
		GraphNode* node = Graph->adj_list[i];
		GraphNode* pre = NULL;
		for(;node;){
			//pre와 node를 한칸씩 옮기고 pre는 해제.
			pre = node;
			node = node->link;
			free(pre); 
		}
	}
	//Graph까지 해제
	free(Graph);
}

int invert(GraphNode* node) {
	//여기서는 h->first로 노드를 가져오기에 n으로 따로 빼준다.
	//trail은 이전값을 연결하기 위해, middle은 새로 연결하기 위해 사용
	GraphNode* middle = NULL;
	GraphNode* trail = NULL;
	GraphNode* n = node->link;

	while(n){
		//middle과 n은 앞 노드부터 나아가게되고, trail은 middle의 값을 받아서 middle->link로 연결한다.
		trail = middle;
		middle = n;
		n = n->link;
		middle->link = trail;
	}
	//새로 연결된 middle을 node로 넣어준다.(어차피 입력은 복제된 node)
	node->link = middle;

	return 0;
}

int pop()
{
	//top<0이란 것은 비어있단 의미.
	if(top<0){
		printf("Error : stack is Empty\n");
		return -1;
	}
	//비어있지 않으면 stack의 top값을 리턴하고, top 값에서 1을 뺀다.
	return stack[top--];
}

void push(int aNode)
{
	//top을 1을 넣고 top을 인덱스로 한 stack의 값에 aNode를 넣는다.
	stack[++top] = aNode;
}



int deQueue()
{
	//front와 rear가 같으면 빈 queue
	if(front == rear) {
		// printf("\nError : Queue is Empty\n");
		return 1;
	}
	//front가 최대 size를 넘으면 다시 1부터
	//안넘으면 나머지 연산이니 그대로.
	front = (front+1) % MAX_SIZE;
	return queue[front];
}

void enQueue(int aNode)
{
	//size를 넘으면 1부터, 아니면 그대로.
	rear = (rear+1) % MAX_SIZE;

	//'위의 연산을 거쳐서' front==rear면 이미 full이었던 queue
	//이미 front==rear이면 빈 queue
	if(front==rear){
		//printf("\nError : Queue is full\n");
		return;
	}
	queue[rear] = aNode;
}