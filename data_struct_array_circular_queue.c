#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_SIZE 5

typedef struct data{  
    int id; 
    char name[30]; 
    char gender[10];
    int year;
    char section[30];
    char dateTime[30];  
 }INFO;

int InputChoice();
int InputSearch();
void DisplayMenu(); 
void QueueStatus();
void Enqueue(INFO attendance[], int *front, int *rear); 
void Dequeue(INFO attendance[], int *front, int *rear);
void Peek(INFO attendance[], int front, int rear);
void Search(INFO attendance[], int front, int rear);
void DisplayQueue(INFO attendance[], int front, int rear);
void GoToChoice(int choice, INFO attendance[], int *front, int *rear);

int main()
{
	int choice = 0;
	INFO attendance[MAX_SIZE];
	int front = -1, rear = -1;
	
	do{  
        DisplayMenu();
        choice = InputChoice();
        GoToChoice(choice, attendance, &front, &rear);
    }while(choice!=5);
    
    return 0;
}

int InputChoice() {
    int choice;
    scanf("%d", &choice);
    fflush(stdin);

    return choice;
}

int InputSearch() {
    int id;

    printf("Enter student ID to search: ");
    scanf("%d",&id);
    
    return id;
}

void DisplayMenu()
{
    printf("\n---Lecture Attendance---\n");
    printf("\n[1] Set Attendance"); 
    printf("\n[2] Remove Attendance"); 
    printf("\n[3] Search Attendance"); 
    printf("\n[4] Display Attendance"); 
    printf("\n[5] Exit\n");
    printf("\nChoice: "); 
}

void GoToChoice(int choice, INFO attendance[], int *front, int *rear) {
    int i;
	switch (choice) {
        case 1:
            Enqueue(attendance, front, rear);
            break;
        case 2:
            Dequeue(attendance, front, rear);
            break;
        case 3:
            Search(attendance, *front, *rear);
            break;
        case 4:
            DisplayQueue(attendance, *front, *rear);
            break;
        case 5:
            printf("Exiting...\n");
            break;
        default:
            printf("\nChoice Invalid.\n");
            break;
    }
}

void Enqueue(INFO attendance[], int *front, int *rear) {
	
 	time_t currentTime;
    struct tm *localTime;
    currentTime = time(NULL);
    localTime = localtime(&currentTime);

    int id, year, flag = 1;
    char name[30], gender[10], section[30], dateTime[30];
	
	if ((*rear + 1) % MAX_SIZE == *front) {
        QueueStatus(flag);
        return;
    }

    printf("\nID #: ");
    scanf("%d", &id);
    fflush(stdin);
    
    printf("Name: ");
    gets(name);
    
    printf("Gender: ");
    gets(gender);

    printf("Year Level: ");
    scanf("%d", &year);
    fflush(stdin);

    printf("Section: ");
    gets(section);

    strftime(dateTime, sizeof(dateTime), "%m-%d-%Y %H:%M:%S", localTime);
    
	if (*front == -1 && *rear == -1) {
        *front = *rear = 0;

       	attendance[*rear].id = id;
        strcpy(attendance[*rear].name, name);
        strcpy(attendance[*rear].gender, gender); 
        attendance[*rear].year = year;  
        strcpy(attendance[*rear].section, section);
        strcpy(attendance[*rear].dateTime, dateTime);   

    } else {
        *rear = (*rear + 1) % MAX_SIZE;
        
        attendance[*rear].id = id;
        strcpy(attendance[*rear].name, name);
        strcpy(attendance[*rear].gender, gender);
        attendance[*rear].year = year;  
        strcpy(attendance[*rear].section, section);
        strcpy(attendance[*rear].dateTime, dateTime); 
    }
}

void Dequeue(INFO attendance[], int *front, int *rear)
{
    if (*front == -1 && *rear == -1) {
        printf("Circular Queue is empty\n");
    } else if (*front == *rear) {
  	 	printf("Removed attendance: %d %s\n", attendance[*front].id, attendance[*front].name);
        *front = *rear = -1;
    } else {
  	 	printf("Removed attendance: %d %s\n", attendance[*front].id, attendance[*front].name);
        *front = (*front + 1) % MAX_SIZE;
    }
} 

void Peek(INFO attendance[], int front, int rear) 
{
	int flag =0;
    if (front == -1 && rear == -1) {
		QueueStatus(flag); 
    } else{
        printf("\nID: %d", attendance[front].id);
        printf("\nName: %s", attendance[front].name);
        printf("\nGender: %s", attendance[front].gender);
        printf("\nYear & Section: %d - %s", attendance[front].year, attendance[front].section); 
        printf("\nDatetime: %s", attendance[front].dateTime);
    }
}	

void Search(INFO attendance[], int front, int rear) 
{
	int id = InputSearch();
    int flag = 0;
    
    fflush(stdin);
    if (front == -1 && rear == -1) {
         QueueStatus(flag);
    } else{
        int i = front;
        do {  
            if(attendance[i].id == id){
                printf("Attendee is present:\n");
				printf("ID: %d\n", attendance[i].id);
  				printf("Name: %s\n", attendance[i].name);
    			printf("Gender: %s\n", attendance[i].gender);
     			printf("Year & Section: %d - %s\n", attendance[i].year, attendance[i].section); 
 				printf("Datetime: %s\n\n", attendance[i].dateTime);
 				return;
			 } 
            i = (i + 1) % MAX_SIZE;
        } while (i != (rear + 1) % MAX_SIZE);
        printf("\n"); 
    }
    
    printf("Attendee is absent\n");
}

void DisplayQueue(INFO attendance[], int front, int rear) {
	int flag = 0;
	
    if (front == -1 && rear == -1) {
        QueueStatus(flag);
    } else {
        int i = front;
        printf("----Attendance---\n");
        printf("\n\n+--------------------------------------------------------------------------------+");
        printf("\n| ID   | Name                 | Gender | Year & Section   | Datetime             |");
        printf("\n+--------------------------------------------------------------------------------+\n");
        do {
        	printf("\n| %-4d | %-20s | %-6s | %d - %-12s | %-20s |", attendance[i].id, attendance[i].name, attendance[i].gender, attendance[i].year, attendance[i].section, attendance[i].dateTime);
            i = (i + 1) % MAX_SIZE;
        }while(i != (rear + 1) % MAX_SIZE);
        printf("\n+--------------------------------------------------------------------------------+\n");
    }
}

void QueueStatus(int flag){
	if(flag == 0){
		printf("Attendance is empty!\n");
	}
	else{
		printf("Attendance is full!\n");
	}
}
