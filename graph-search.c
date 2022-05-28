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

void initialize(GraphType*);
void insertVertex(GraphType* Graph);
void insertEdge(GraphType* Graph, int v1, int v2);
void DFS();
void BFS();
void printGraph();
void freeGraph(GraphType* Graph);

/* for queue-Ž���� �ʿ���. */
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
    //Graph�� initialize���� �ʾ��� ���.
    /*
	if(){
        printf("Error : Please Initialize.\n");
        return 1;
    }
	*/

	//n(����)�� 1�� ���ؼ� �ִ� vertex���� ũ�� ����.
	if(((Graph->n)+1)>MAX_VERTEX){
		printf("Error : Max Vertex\n");
		return;
	}

	//���ϵ��� �ʾ����� n�� 1�� ���Ѵ�.
	Graph->n++;
}

void insertEdge(GraphType* Graph, int v1, int v2)
{
    //Graph�� initialize���� �ʾ��� ���.
    /*
	if(){
        printf("Error : Please Initialize.\n");
        return 1;
    }
	*/
	//v1,v2�� ���� vertex ���� vertex�� ������ ���
	if(v1>=Graph->n||v2>=Graph->n||v1<=Graph->n||v2<=Graph->n){
		printf("Error : Out of Vertex number\n");
		return;
	}

	//������ �������.
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