#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE		55 //10�� vertex + 45�� Edge�� �ִ�. 100��..? 101��?

int* initialize();
void insertVertex(int* head, int v);
void insertEdge(int* head, int v1, int v2);
void DFS();
void BFS();
void printGraph();
void freeGraph(int* head);

int main()
{
	char command;
	int v, v1, v2;
    int* Graph = NULL;

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
			Graph= initialize();
			break;
		case 'q': case 'Q':
			freeGraph(Graph);
			break;
		case 'v': case 'V':
			printf("Your vertex = ");
			scanf("%d", &v);
			insertVertex(Graph, v);
			break;
		case 'e': case 'E':
			printf("Input two vertex = ");
			scanf("%d %d", &v1, &v2);
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

int* initialize()
{
    int* array = (int*)calloc(MAX_SIZE, sizeof(int));
    return array;
}

void insertVertex(int* Graph, int v)
{
    //Graph�� initialize���� �ʾ��� ���.
    if(Graph == NULL){
        printf("Error : Please Initialize.\n");
        return 1;
    }

    for(int i =0;i<10;i++){
        if(Graph[i] != 0){
            Graph[i] = v;
            return 1;
        }
    }

    //���� 10ĭ�� ��� ������� ���� ���== Vertex�� 10���̹Ƿ� �ִ��̴�.
    printf("Error : Max number of Vertex\n");
    return 1;
}

void insertEdge(int* Graph, int v1, int v2)
{
    //Graph�� initialize���� �ʾ��� ���.
    if(Graph == NULL){
        printf("Error : Please Initialize.\n");
        return 1;
    }
    //edge�� �̹� �ִ� ����� ���� ó��
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

void freeGraph(int* Graph)
{

}