#include <stdio.h>
#include <stdlib.h>

// Node structure for each element in the adjacency list
struct Node {
    char dest[30];
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
struct Node *CreateNode(char *dest);
struct Graph *CreateGraph(int numVertices);
int InputVertices();
char InputSource(char *);
char InputDestination(char *);
void addEdge(struct Graph* graph, char src, char dest);
void printGraph(struct Graph* graph, char *src, char *dest);


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
    int numVertices;
    char source[20], destination[20];

	switch (choice) {
        case 1:
            numVertices=InputVertices();
            graph = CreateGraph(numVertices);
		    break;
        case 2:
            InputSource(source);
            break;
        case 3:
            InputDestination(destination);
            // addEdge(graph, source, destination);
            break;
        case 4:
            InputSource(source);
            InputDestination(destination);
            // printGraph(graph, source, destination);

            // addEdge(graph, 0, 1);
            // addEdge(graph, 0, 4);
            // addEdge(graph, 1, 2);
            // addEdge(graph, 1, 3);
            // addEdge(graph, 1, 4);
            // addEdge(graph, 2, 3);
            // addEdge(graph, 3, 4);
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

char InputSource(char* str) {
	printf("Enter the source: ");
 	scanf("%s", str);
}

char InputDestination(char* str) {
	printf("Enter the destination: ");
 	scanf("%s", str);
}

// Create a new node
struct Node* CreateNode(char *dest) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(dest, newNode->dest);
    newNode->next = NULL;
    return newNode;
}

// Add an edge to the graph
void addEdge(struct Graph* graph, char src, char dest) {
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
void printGraph(struct Graph* graph, char *source, char *destination) {
    int i, data=source;


    printf("Shortest distance from %s to %s: ", source, destination);
    printf("%s ", source);
    while (strcmp(data, destination);) {
        struct Node* temp = graph->adjList[data];
        printf("%s ", temp->dest);
        strcpy(data, temp->dest);
        temp = temp->next;
    }
    printf("\n");
}
