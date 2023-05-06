#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 5

typedef struct data {
    int id;
    char name[30];
} INFO;

int AskChoice();
int InputSearch();
void DisplayMenu();
void Enqueue(INFO attendance[], int *front, int *rear);
void Dequeue(INFO attendance[], int *front);
void Peek(INFO attendance[], int front);
void Search(INFO attendance[], int front, int rear);
void DisplayQueue(INFO attendance[], int front, int rear);
void GoToChoice(int choice, INFO attendance[], int *front, int *rear);

int main() {
    int choice = 0;
    INFO attendance[MAX];
    int front = -1, rear = -1;

    while (choice != 6) {
        DisplayMenu();
        choice = AskChoice();
        GoToChoice(choice, attendance, &front, &rear);
    }

    return 0;
}

int AskChoice() {
    int choice;
    printf("Enter your choice: ");
    scanf("%d", &choice);
    return choice;
}

void DisplayMenu() {
    printf("\n---Attendance---\n");
    printf("[1] Record attendance\n");
    printf("[2] Remove attendance\n");
    printf("[3] Search\n");
    printf("[4] Display attendance list\n");
    printf("[5] Peek\n");
    printf("[6] Exit\n");
}

void GoToChoice(int choice, INFO attendance[], int *front, int *rear) {
    switch (choice) {
        case 1:
            Enqueue(attendance, front, rear);
        break;
        case 2:
            Dequeue(attendance, front);
        break;
        case 3:
            Search(attendance, *front, *rear);
        break;
        case 4:
            DisplayQueue(attendance, *front, *rear);
        break;
        case 5:
            Peek(attendance, *front);
        break;
        case 6:
            printf("Exiting...\n");
        break;
        default:
            printf("Invalid choice.\n");
        break;
    }
}

void Enqueue(INFO attendance[], int *front, int *rear) {
    int id;
    char name[30];
    
    if (*rear == MAX - 1) {
        printf("Attendance list is full.\n");
        return;
    }
    printf("Enter student ID:\n");
    scanf("%d", &id);
    printf("Enter student name:\n");
    fflush(stdin);
    gets(name);
    
    attendance[++*rear].id = id;
    strcpy(attendance[*rear].name, name);
    printf("Attendance recorded.\n");
    if (*rear == 0) {
        *front = 0;
    }
}

void Dequeue(INFO attendance[], int *front) {
    if (*front == -1) {
        printf("Attendance list is empty.\n");
        return;
    }
    printf("Removed attendance: %d %s\n", attendance[*front].id, attendance[*front].name);
    if (*front == MAX - 1) {
        *front = -1;
    } else {
        (*front)++;
    }
}

void Peek(INFO attendance[], int front) {
    if (front == -1) {
        printf("Attendance list is empty.\n");
        return;
    }
    printf("First attendance: %d %s\n", attendance[front].id, attendance[front].name);
}

void Search(INFO attendance[], int front, int rear) {
    int id = InputSearch();
    int i;
    
    for (i = front; i <= rear; i++) {
        if (attendance[i].id == id) {
            printf("Attendance found: %d %s\n", attendance[i].id, attendance[i].name);
            return;
        }
    }
    
    printf("Attendance not found.\n");
}

int InputSearch() {
    int id;

    printf("Enter student ID to search: ");
    scanf("%d", &id);
    
    return id;
}

void DisplayQueue(INFO attendance[], int front, int rear) {
    int i;
    
    if (front == -1) {
        printf("Attendance list is empty.\n");
        return;
    }

    printf("Attendance list:\n");
    for (i = front; i <= rear; i++) {
        printf("%d %s\n", attendance[i].id, attendance[i].name);
    }
}
