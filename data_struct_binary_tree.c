#include <stdio.h>
#include <stdlib.h>

int InputChoice(); 
void DisplayMenu(); 
void GoToChoice();

int main()
{
	int choice = 0;
	
	do{  
        DisplayMenu();
        choice = InputChoice();
        GoToChoice(choice);
    }while(choice!=6);
    
    return 0;
}

int InputChoice() {
    int choice;
    scanf("%d", &choice);
    fflush(stdin);

    return choice;
} 

void DisplayMenu()
{
    printf("\n[1] Insert Node"); 
    printf("\n[2] Determine Heigh"); 
    printf("\n[3] Determine if Full Binary Tre"); 
    printf("\n[4] Determine if Complete Binary Tree");  
    printf("\n[5] Print Nodes");
    printf("\n[6] Exit\n");
    printf("\nChoice: "); 
}

void GoToChoice(int choice) {
    int i;
	switch (choice) {
        case 1:
            
            break;
        case 2:
            
            break;
        case 3:
            
            break;
        case 4:
            
            break;
         case 5:
            
            break;
        case 6:
            printf("Exiting...\n");
            break;
        default:
            printf("\nChoice Invalid.\n");
            break;
    }
}