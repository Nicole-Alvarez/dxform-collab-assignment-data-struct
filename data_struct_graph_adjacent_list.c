#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

struct Node {
	int destination;
	struct Node *next;
};

struct Graph {
	int numVertices;
	char **names;
	struct Node **adjLists;
};

struct Node *CreateNode(int destination);
struct Graph *CreateGraph(int numVertices);
void AddEdge(struct Graph *graph, int src, int dest);
void AssignNames(struct Graph *graph);
void AssignNeighbors(struct Graph *graph, int numVertices);
void ShortestDistance(struct Graph *graph, int start, int dest);
void FreeGraph(struct Graph* graph);
int FindIndex(struct Graph *graph, const char *name);
int GetStartingLocation(struct Graph *graph);
int GetDestination(struct Graph *graph);

int main() {
    int numVertices;
    char choice;
    int start, dest;

    printf("Enter the number of vertices: ");
    scanf("%d", &numVertices);

    struct Graph *graph = CreateGraph(numVertices);

    do {
        printf("\n--- MENU ---\n");
        printf("[ a ] Assign Names\n");
        printf("[ b ] Starting Location\n");
        printf("[ c ] Destination\n");
        printf("[ d ] Shortest Distance\n");
        printf("[ e ] Exit\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);

        switch (choice) {
        	case 'a':
        		AssignNames(graph);
        		AssignNeighbors(graph, numVertices);
        	break;
            case 'b':
                start = GetStartingLocation(graph);
                break;
            case 'c':
                dest = GetDestination(graph);
                break;
            case 'd':
                ShortestDistance(graph, start, dest);
                break;
            case 'e':
            	printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
        printf("\n");
    } while (choice != 'e');

    FreeGraph(graph);

    return 0;
}

struct Node* CreateNode(int destination) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->destination = destination;
    newNode->next = NULL;
    return newNode;
}

struct Graph* CreateGraph(int numVertices) {
	int i;
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = numVertices;
    graph->names = (char**)malloc(numVertices * sizeof(char*));
    graph->adjLists = (struct Node**)malloc(numVertices * sizeof(struct Node*));

    for (i = 0; i < numVertices; i++) {
        graph->names[i] = NULL;
        graph->adjLists[i] = NULL;
    }

    return graph;
}

void AssignNames(struct Graph *graph) {
    int numVertices = graph->numVertices;
    int i, nameLength;
	char name[20];

    for (i = 0; i < numVertices; i++) {
        printf("Enter the name for node %d: ", i);
        scanf("%s", name);
        nameLength = strlen(name);
        graph->names[i] = (char*)malloc((nameLength + 1) * sizeof(char));
        strcpy(graph->names[i], name);
        printf("Assigned name '%s' to node %d.\n", graph->names[i], i);
    }
    printf("\n");
}

void AssignNeighbors(struct Graph *graph, int numVertices){
		int i, j;
		char neighbor[5];
		int numNeighbors;
	    for (i = 0; i < numVertices; i++) {
        printf("Enter the number of neighbors for %s: ", graph->names[i]);
        scanf("%d", &numNeighbors);
        for (j = 0; j < numNeighbors; j++) {
            printf("Enter neighbor %d for %s: ", j + 1, graph->names[i]);
            scanf("%s", neighbor);
            int neighborIndex = FindIndex(graph, neighbor);
            if (neighborIndex == -1) {
                printf("Invalid neighbor name. Please try again.\n");
                j--;
                continue;
            }
            AddEdge(graph, i, neighborIndex);
        }
        printf("\n");
    }
}

void AddEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = CreateNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    newNode = CreateNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

int FindIndex(struct Graph* graph, const char* name) {
	int i;
    for (i = 0; i < graph->numVertices; i++) {
        if (strcmp(graph->names[i], name) == 0) {
            return i;
        }
    }
    return -1;
}

int GetStartingLocation(struct Graph* graph) {
    char name[20];
    printf("Enter the starting location: ");
    scanf("%s", name);
    int index = FindIndex(graph, name);
    if (index == -1) {
        printf("Invalid starting location. Please try again.\n");
        return GetStartingLocation(graph);
    }
    return index;
}

// Function to get the destination from the user
int GetDestination(struct Graph* graph) {
    char name[20];
    printf("Enter the destination: ");
    scanf("%s", name);
    int index = FindIndex(graph, name);
    if (index == -1) {
        printf("Invalid destination. Please try again.\n");
        return GetDestination(graph);
    }
    return index;
}

void ShortestDistance(struct Graph* graph, int start, int dest) {
    int i, data = start;

    printf("Shortest distance from node %s to node %s: ", graph->names[start], graph->names[dest]);
    printf("%s ", graph->names[start]);
    while (data != dest) {
        struct Node* temp = graph->adjLists[data];
        printf("%s ", graph->names[temp->destination]);
        data = temp->destination;
        temp = temp->next;
    }
    printf("\n");
}

void FreeGraph(struct Graph *graph) {
	int i;
    if (graph) {
        if (graph->adjLists) {
            for (i = 0; i < graph->numVertices; i++) {
                struct Node* temp = graph->adjLists[i];
                while (temp) {
                    struct Node* prev = temp;
                    temp = temp->next;
                    free(prev);
                }
            }
            free(graph->adjLists);
        }
        if (graph->names) {
            for (i = 0; i < graph->numVertices; i++) {
                free(graph->names[i]);
            }
            free(graph->names);
        }
        free(graph);
    }
}