#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_SIZE 5

typedef struct data{  
    char id[30]; 
    char name[30]; 
    char gender[10];
    int year;
    char section[30];
    char dateTime[30];  
 }INFO;

INFO attendance[MAX_SIZE];
int front = -1;
int rear = -1;

int menuDisplay(); 
void choiceReturn();  
void inputAppointment(); 
void enqueque(char[10], char[30], char[10], int, char[30], char[30]); 
void dequeue(); 
void peek();
void inputSearch();
void search(char[10]);
void displayQueue();

int main()
{
    choiceReturn();
}

int menuDisplay()
{
    int choice;
    printf("\n\nLecture Attendance\n");
    printf("\n[1] Set Attendance"); 
    printf("\n[2] Dequeue Attendance"); 
    printf("\n[3] Search Apointment"); 
    printf("\n[4] Display Apointments"); 
    printf("\n[5] Exit\n");
    printf("\nChoice: "); 
    scanf("%d", &choice);

    return choice;
}

void choiceReturn()
{ 
    int choice;
    do{  
        choice = menuDisplay(); 
  
        switch (choice)
        {
            case 1: 
                inputAppointment();
                break;
            case 2:
                dequeue();
                break; 
            case 3:
                inputSearch();
                break;
            case 4:  
                displayQueue();
                break; 
            case 5:   
                break;     
            default:
                printf("\nChoice Invalid.\n"); 
                break;
        }
    
    }while(choice!=5);
}

void inputAppointment()
{  
    time_t currentTime;
    struct tm *localTime; 
    currentTime = time(NULL); 
    localTime = localtime(&currentTime);

    int year;
    char id[10], name[30], gender[10], section[30], dateTime[30];   
 
    fflush(stdin);
    printf("\nID #: ");
    fgets(id, 10, stdin);
    fflush(stdin);

    printf("Name: ");
    fgets(name, 30, stdin);
    fflush(stdin);

    printf("Gender: ");
    scanf("%c", &gender);  
    fflush(stdin);

    printf("School Year: "); 
    scanf("%d", &year);  
    fflush(stdin);

    printf("Section: "); 
    fgets(section, 30, stdin);
    fflush(stdin);


    strftime(dateTime, sizeof(dateTime), "%m-%d-%Y %H:%M:%S", localTime);

    enqueque(id, name, gender, year, section, dateTime);
}

void enqueque(char id[10], char name[30], char gender[10], int year, char section[30], char dateTime[30] )
{  

    if ((rear + 1) % MAX_SIZE == front) {
        printf("Circular Queue is full\n");
    } else if (front == -1 && rear == -1) {
        front = rear = 0;

        strcpy(attendance[rear].id, id);
        strcpy(attendance[rear].name, name);
        strcpy(attendance[rear].gender, gender); 
        attendance[rear].year = year;  
        strcpy(attendance[rear].section, section);
        strcpy(attendance[rear].dateTime, dateTime);   

    } else {
        rear = (rear + 1) % MAX_SIZE;
        
        strcpy(attendance[rear].id, id);
        strcpy(attendance[rear].name, name);
        strcpy(attendance[rear].gender, gender);
        attendance[rear].year = year;  
        strcpy(attendance[rear].section, section);
        strcpy(attendance[rear].dateTime, dateTime); 
    }
}  

void dequeue()
{
    if (front == -1 && rear == -1) {
        printf("Circular Queue is empty\n");
    } else if (front == rear) {
        peek();
        front = rear = -1;
        printf("Dequeue succesful.\n");
    } else {
        peek();
        front = (front + 1) % MAX_SIZE;
        printf("Dequeue succesful.\n");
    }
} 

void peek() 
{
    fflush(stdin);
    if (front == -1 && rear == -1) {
        printf("Queue is empty\n"); 
    } else{
        printf("\nID: %s", attendance[front].id);
        printf("\nName: %s", attendance[front].name);
        printf("\nGender: %s", attendance[front].gender);
        printf("\nYear & Section: %d - %s", attendance[front].year, attendance[front].section); 
        printf("\nDatetime: %s", attendance[front].dateTime);
    }
}

void inputSearch()
{
    char id[10];

    fflush(stdin);
    printf("\nSearch by ID #: ");
    fgets(id, 10, stdin);
    fflush(stdin);

    search(id);
}

void search(char id[30]) 
{
    int flag = 1;
    
    fflush(stdin);
    if (front == -1 && rear == -1) {
        printf("Queue is empty\n"); 
    } else{
        int i = front;
        do {  
            if(strcmp(attendance[i].id, id) == 0){
                printf("\n\nID: %s", attendance[i].id);
                printf("\nName: %s", attendance[i].name);
                printf("\nGender: %s", attendance[i].gender);
                printf("\nYear & Section: %d - %s", attendance[i].year, attendance[i].section); 
                printf("\nDatetime: %s", attendance[i].dateTime);

                flag = 0;
            } 
            i = (i + 1) % MAX_SIZE;
        } while (i != (rear + 1) % MAX_SIZE);
        printf("\n"); 
    }

    if(flag==1){
        printf("Attendee is absent\n"); 
    }
}

void displayQueue()
{
    fflush(stdin);
    if (front == -1 && rear == -1) {
        printf("\nCircular Queue is empty\n");
    } else {
        printf("\nAttendees are:\n");
        int i = front;
        do {  
            printf("\n------------------\n");
            printf("\nID: %s", attendance[i].id);
            printf("\nName: %s", attendance[i].name);
            printf("\nGender: %s", attendance[i].gender);
            printf("\nYear & Section: %d - %s", attendance[i].year, attendance[i].section); 
            printf("\nDatetime: %s\n", attendance[i].dateTime);

            i = (i + 1) % MAX_SIZE;
        } while (i != (rear + 1) % MAX_SIZE);
        printf("\n");
    }
}
