#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX		10 //10�� vertex

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

/* for stack -Ž���� �ʿ���*/
#define MAX_SIZE		10
int stack[MAX_SIZE];
int top = -1;

int pop();
void push(int aNode);

/* for queue-Ž���� �ʿ���. */
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

	printf("-----������ 2021041047-----\n");
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

//�׷��� ����
void initialize(GraphType** Graph)
{
	//�׷����� �����Ҵ��ϰ� ������ �������ش�.
	*Graph = (GraphType*)malloc(sizeof(GraphType));
	(*Graph)->n =0;
	for(int v=0; v<MAX_VERTEX; v++){
		(*Graph)->adj_list[v] = NULL;
	}
}

//vertex�� ���� �ø��� �Լ�.
void insertVertex(GraphType* Graph)
{
    //Graph�� initialize���� �ʾ��� ���.
	if(Graph == NULL){
        printf("Error : Please Initialize.\n");
        return;
    }
	
	//n(����)�� 1�� ���ؼ� �ִ� vertex���� ũ�� ����.
	if(((Graph->n)+1)>MAX_VERTEX){
		printf("Error : Max Vertex\n");
		return;
	}

	//���ϵ��� �ʾ����� n�� 1�� ���Ѵ�.
	Graph->n++;
	printf("The number of vertex is %d", Graph->n);
}

//Edge�� �ִ� �Լ�.
int insertEdge(GraphType* Graph, int v1, int v2)
{
    //Graph�� initialize���� �ʾ��� ���.
	if(Graph == NULL){
        printf("Error : Please Initialize.\n");
        return 1;
    }
	//v1,v2�� ���� vertex ���� vertex�� ������ ���(0~n�� �ƴ�, n�� ������ �� vertex�� ����.)
	if(v1>Graph->n||v2>Graph->n||v1<0||v2<0){
		printf("Error : Out of Vertex number\n");
		return 1;
	}

	//������ �������.(���� ���, ���� ���, �ݺ��񱳸� ���� ���)
	GraphNode* node = (GraphNode*)malloc(sizeof(GraphNode));
	GraphNode* pre = NULL;
	GraphNode* chan = Graph->adj_list[v1];
	node->vertex = v2;
	node->link = NULL;

	//ó���� �ؼ� chan�� ���� ���. adj_list�� ����.
	if(chan == NULL){
		Graph->adj_list[v1] = node;
		return 1;
	}
	//chan�� NULL�� �ƴѵ��� chan�� �Űܰ��� ��
	for(;chan;chan = chan->link){
		//���� ���� �̹� �ִ� ����̹Ƿ�, �����޽��� ��� �� ����.
		if(chan->vertex == node->vertex){
			printf("Error : Exsisted Node\n");
			return 1;
		}

		//������������ �����Ѵٰ� �����Ͽ�
		//chan�� vertex�� ū ��� ��忡 chan�� ����
		if(chan->vertex > node->vertex){
			node->link = chan;

			//chan�� �ճ��(pre)�� NULL�̸� �տ��ٰ� ����
			//�׷��� ������ pre���ٰ� node ����
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
	//�ȵ� ���, �� �ڿ� ���̱�
	pre->link = node;
	return 1;
}

void BFS(GraphType* Graph)
{
	//p�� ������. N�� vertex ����, path�� �湮 ����
	int p = 0;
	int N = Graph->n;
	int* path = (int*)malloc(N*sizeof(int));
	for (int i = 0; i < N; i++) {
		//�� 0���� ������ش�. (0�̸� �̹湮, 1�̸� �湮)
		path[i] = 0;
	}

	//�������� 0�� �ְ�, path�� ���, ���
	enQueue(p);
	path[p] = 1;
	printf("%d ", p);

	
	//front == rear�� ��찡 queue�� �� ���.
	while(front != rear) {
		//node�� NULL�� ������. ����� node�� ���� Ž���Ѵ�.
		for(GraphNode* node = Graph->adj_list[p]; node; node = node->link) {
			//�湮���� ���� node�� ������ enqueue
			if (path[node->vertex] != 1) {
				enQueue(node->vertex);				
			}
		}
		//dequeue�Ͽ� �ϳ��� �湮���� Ȯ�� �� ���
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
	//p�� ������. N�� vertex ����, path�� �湮 ����
	int p = 0;
	int N = Graph->n;
	int* path = (int*)malloc(N*sizeof(int));
	for (int i = 0; i < N; i++) {
		//�� 0���� ������ش�. (0�̸� �̹湮, 1�̸� �湮)
		path[i] = 0;
	}

	//�������� 0�� �ְ�, path�� ���, ���
	push(p);
	path[p] = 1;
	printf("%d ", p);

	//�̸� h�� �̿��ؼ� invert �����ش�.
	GraphNode* h;
	for(int i=0;i<N;i++){
		h->link = Graph->adj_list[i];
		invert(h);
		Graph->adj_list[i] = h->link;
	}
	//top�� ������ �ƴ϶�� (==������� �ʴٸ�)
	while (top>=0) {
		//vertex������ŭ �ݺ��Ͽ�- node�� �ְ�, vertex�� �湮���� �ʾ����� push�Ѵ�.
		for (GraphNode* node =  Graph->adj_list[p]; node; node = node->link) {
			if (path[node->vertex] != 1) {
				push(node->vertex);				
			}
		}

		//pop�Ͽ� �湮���� ���� ��쿡�� ���.
		p = pop();	
		if (path[p] != 1) {
			printf("%d ", p);
			path[p] = 1;
		}
	}
	//���� ����� ���ؼ� �ٽ� invert �����ش�.
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
	//adj_list�� index�� ����
	for(int i =0;i<Graph->n;i++){
		GraphNode* node = Graph->adj_list[i];
		printf("vertex %d : ", i);
		//node�� �Ѱܰ��鼭 vertex ���.
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
			//pre�� node�� ��ĭ�� �ű�� pre�� ����.
			pre = node;
			node = node->link;
			free(pre); 
		}
	}
	//Graph���� ����
	free(Graph);
}

int invert(GraphNode* node) {
	//���⼭�� h->first�� ��带 �������⿡ n���� ���� ���ش�.
	//trail�� �������� �����ϱ� ����, middle�� ���� �����ϱ� ���� ���
	GraphNode* middle = NULL;
	GraphNode* trail = NULL;
	GraphNode* n = node->link;

	while(n){
		//middle�� n�� �� ������ ���ư��Եǰ�, trail�� middle�� ���� �޾Ƽ� middle->link�� �����Ѵ�.
		trail = middle;
		middle = n;
		n = n->link;
		middle->link = trail;
	}
	//���� ����� middle�� node�� �־��ش�.(������ �Է��� ������ node)
	node->link = middle;

	return 0;
}

int pop()
{
	//top<0�̶� ���� ����ִ� �ǹ�.
	if(top<0){
		printf("Error : stack is Empty\n");
		return -1;
	}
	//������� ������ stack�� top���� �����ϰ�, top ������ 1�� ����.
	return stack[top--];
}

void push(int aNode)
{
	//top�� 1�� �ְ� top�� �ε����� �� stack�� ���� aNode�� �ִ´�.
	stack[++top] = aNode;
}



int deQueue()
{
	//front�� rear�� ������ �� queue
	if(front == rear) {
		// printf("\nError : Queue is Empty\n");
		return 1;
	}
	//front�� �ִ� size�� ������ �ٽ� 1����
	//�ȳ����� ������ �����̴� �״��.
	front = (front+1) % MAX_SIZE;
	return queue[front];
}

void enQueue(int aNode)
{
	//size�� ������ 1����, �ƴϸ� �״��.
	rear = (rear+1) % MAX_SIZE;

	//'���� ������ ���ļ�' front==rear�� �̹� full�̾��� queue
	//�̹� front==rear�̸� �� queue
	if(front==rear){
		//printf("\nError : Queue is full\n");
		return;
	}
	queue[rear] = aNode;
}