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
void GoToChoice(int choice);
int InputData();
void DisplayMenu();
struct Node *CreateNode(int dest);
struct Graph *CreateGraph(int numVertices);
int InputVertices();
int InputSource();
int InputDestination();
void addEdge(struct Graph* graph, int src, int dest);
void printGraph(struct Graph* graph, int src, int dest);


int main()
{
	int choice = 0;

	do{
        DisplayMenu();
        choice = InputChoice();
        GoToChoice(choice);
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

void GoToChoice(int choice) {
    struct Graph* graph;
    int source, destination, numVertices;

	switch (choice) {
        case 1:
            numVertices=InputVertices();
            graph = CreateGraph(numVertices);
		break;
        case 2:
            source=InputSource();
        break;
        case 3:
            // destination=InputDestination();
            // addEdge(graph, source, destination);

            addEdge(graph, 0, 1);
            addEdge(graph, 0, 4);
            addEdge(graph, 1, 2);
            addEdge(graph, 1, 3);
            addEdge(graph, 1, 4);
            addEdge(graph, 2, 3);
            addEdge(graph, 3, 4);
        break;
        case 4:
            source=InputSource();
            destination=InputDestination();
            printGraph(graph, source, destination);
        break;
  		case 5:
            printf("Exiting...\n");
    	break;
        default:
            printf("\nChoice Invalid.\n");
        break;
    }
}

int InputVertices() {
	int data;

	printf("Enter number of vertices: ");
 	scanf("%d", &data);

	return data;
}

// Create a graph with a given number of vertices
struct Graph* CreateGraph(int numVertices) {
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

// Create a new node
struct Node* CreateNode(int dest) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// Add an edge to the graph
void addEdge(struct Graph* graph, int src, int dest) {
    // Add an edge from source to destination
    struct Node* newNode = CreateNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    // Uncomment the following lines if the graph is undirected

    // // Add an edge from destination to source
    newNode = CreateNode(src);
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

// Print the graph
void printGraph(struct Graph* graph, int source, int destination) {
    int i, data=source;


    printf("Shortest distance from %d to %d: ", source, destination);
    printf("%d ", source);
    while (data!=destination) {
        struct Node* temp = graph->adjList[data];
        printf("%d ", temp->dest);
        data = temp->dest;
        temp = temp->next;
    }
    printf("\n");
}
