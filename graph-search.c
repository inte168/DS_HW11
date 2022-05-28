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
void insertEdge(GraphType* Graph, int v1, int v2);
void DFS(GraphType* Graph);
void BFS();
void printGraph();
void freeGraph(GraphType* Graph);

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
	int v, v1, v2;
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
			if(v1==v2){
				printf("Error : Same vertex\n");
				break;
			}
			insertEdge(Graph, v1, v2);
			break;

		case 'd': case 'D':
			DFS(Graph);
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
}

//Edge�� �ִ� �Լ�.
void insertEdge(GraphType* Graph, int v1, int v2)
{
    //Graph�� initialize���� �ʾ��� ���.
	if(Graph == NULL){
        printf("Error : Please Initialize.\n");
        return;
    }
	//v1,v2�� ���� vertex ���� vertex�� ������ ���(0~n�� �ƴ�, n�� ������ �� vertex�� ����.)
	if(v1>=Graph->n||v2>=Graph->n||v1<=Graph->n||v2<=Graph->n){
		printf("Error : Out of Vertex number\n");
		return;
	}

	//������ �������.(���� ���, ���� ���, �ݺ��񱳸� ���� ���)
	GraphNode* node = (GraphNode*)malloc(sizeof(GraphNode));
	GraphNode* pre = NULL;
	GraphNode* chan = Graph->adj_list[v1];
	node->vertex = v2;
	node->link = NULL;

	//chan->link�� NULL�� �ƴѵ��� chan�� �Űܰ��� ��
	for(;chan->link;chan = chan->link){
		//���� ���� �̹� �ִ� ����̹Ƿ�, �����޽��� ��� �� ����.
		if(chan->vertex == node->vertex){
			printf("Error : Exsisted Node\n");
			return;
		}

		//������������ �����Ѵٰ� �����Ͽ�
		//chan�� vertex�� ū ��� ��忡 chan�� ����
		if(chan->vertex > node->vertex){
			node->link = chan;

			//chan�� �ճ��(pre)�� NULL�̸� �տ��ٰ� ����
			//�׷��� ������ pre���ٰ� node ����
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
	//�ȵ� ���, �� �ڿ� ���̱�
	chan->link = node;

	//v1�� v2�� �ٲپ ���� �����ϰ� �õ�.
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
	//�ȵ� ���, �� �ڿ� ���̱�
	chan->link = node;
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
	push(0);
	path[0] = 1;
	printf("%d ", p);

	GraphNode* node = Graph->adj_list[p];//�̸� node�� ���α�.
	//top�� ������ �ƴ϶�� (==������� �ʴٸ�)
	while (top>=0) {
		//vertex������ŭ �ݺ��Ͽ�- node�� �ְ�, vertex�� �湮���� �ʾ����� push�Ѵ�.
		for (int i = N-1; i >= 0; i--) {
			if ((path[node->vertex] != 1) && (node)) {
				push(node->vertex);				
			}
			node = node->link;
		}

		//pop�Ͽ� �湮���� ���� ��� ���.
		p = pop();	
		if (path[p] != 1) {
			printf("%d ", p);
			path[p] = 1;
		}
	}
	free(path);
	return;
}

void BFS()
{

}

void printGraph()
{

}

void freeGraph(GraphType* Graph)
{	
	for(int i =0; i<=Graph->n;i++){
		GraphNode* node = Graph->adj_list[i];
		GraphNode* pre = NULL;
		for(;node;){
			pre = node;
			node = node->link;
			free(pre);
		}
	}
	free(Graph);
}

int pop()
{
	//top<0�̶� ���� ����ִ� �ǹ�.
	if(top<0) return NULL;
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
		return NULL;
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