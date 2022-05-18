#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE		55 //10개 vertex + 45개 Edge가 최대. 100개..? 101개?

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
    //Graph를 initialize하지 않았을 경우.
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

    //앞의 10칸이 모두 비어있지 않은 경우== Vertex가 10개이므로 최대이다.
    printf("Error : Max number of Vertex\n");
    return 1;
}

void insertEdge(int* Graph, int v1, int v2)
{
    //Graph를 initialize하지 않았을 경우.
    if(Graph == NULL){
        printf("Error : Please Initialize.\n");
        return 1;
    }
    //edge가 이미 있는 경우의 예외 처리
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