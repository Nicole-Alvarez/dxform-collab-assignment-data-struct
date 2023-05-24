#include <stdio.h>
#include <stdlib.h>

// Node structure for each element in the adjacency list
struct Node {
    int dest;
    struct Node* next;
};

// Graph structure
struct Graph {
    int numVertices;
    struct Node** adjList;
};

int InputChoice();
int InputData();
void DisplayMenu();
struct Node *CreateNode(int dest);
struct Node *CreateGraph(int numVertices);
int InputSource();
int InputDestination();


int main()
{
	struct Node *root = NULL;
	int choice = 0;

	do{
        DisplayMenu();
        choice = InputChoice();
        GoToChoice(choice, &root);
    }while(choice!=5);

    return 0;
}

int InputChoice() {
    int choice;
    scanf("%d", &choice);
    fflush(stdin);

    return choice;
}

int InputData() {
	int data;

	printf("Enter the value to insert: ");
 	scanf("%d", &data);

	return data;
}

void DisplayMenu()
{
    printf("\n[1] Assign names to Nodes");
    printf("\n[2] Starting Location");
    printf("\n[3] Destination");
    printf("\n[4] Shortest Distance");
    printf("\n[5] Exit\n");
    printf("\nChoice: ");
}

void GoToChoice(int choice, struct Node **root) {
    int source, destination;
    int numVertices = 5;

	switch (choice) {
        case 1:
            struct Graph* graph = createGraph(numVertices);
		break;
        case 2:
            source=InputSource();
        break;
        case 3:
            destination=InputDestination();
        break;
        case 4:
            addEdge(graph, source, destination);
            addEdge(graph, 0, 4);
            addEdge(graph, 1, 2);
            addEdge(graph, 1, 3);
            addEdge(graph, 1, 4);
            addEdge(graph, 2, 3);
            addEdge(graph, 3, 4);

            printGraph(graph);
        break;
  		case 5:
            printf("Exiting...\n");
    	break;
        default:
            printf("\nChoice Invalid.\n");
        break;
    }
}

// Create a new node
struct Node* createNode(int dest) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// Create a graph with a given number of vertices
struct Graph* createGraph(int numVertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = numVertices;

    // Create an array of adjacency lists
    graph->adjList = (struct Node**)malloc(numVertices * sizeof(struct Node*));

    // Initialize each adjacency list as empty
    int i;
    for (i = 0; i < numVertices; i++) {
        graph->adjList[i] = NULL;
    }

    return graph;
}

int InputSource() {
	int data;

	printf("Enter the source: ");
 	scanf("%d", &data);

	return data;
}

int InputDestination() {
	int data;

	printf("Enter the destination: ");
 	scanf("%d", &data);

	return data;
}

// Add an edge to the graph
void addEdge(struct Graph* graph, int src, int dest) {
    // Add an edge from source to destination
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    // Uncomment the following lines if the graph is undirected

    // // Add an edge from destination to source
    // newNode = createNode(src);
    // newNode->next = graph->adjList[dest];
    // graph->adjList[dest] = newNode;
}

// Print the graph
void printGraph(struct Graph* graph) {
    int i;
    for (i = 0; i < graph->numVertices; i++) {
        struct Node* temp = graph->adjList[i];
        printf("Adjacency list of vertex %d: ", i);
        while (temp) {
            printf("%d ", temp->dest);
            temp = temp->next;
        }
        printf("\n");
    }
}
