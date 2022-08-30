#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Student {
    int id;
    char Name[15];
    char Gr1,Gr2;
};


int ReadDataFromFile(struct Student S[])
{
	//Opening file in Write mode.
    FILE *filePointer ;
    filePointer = fopen("data.txt", "r") ;
    if(!filePointer)
    {
        printf("Unable to read File\n");
        return 0;
    }
    char line[500];
    int count = 0;
    while(fgets(line, sizeof(line), filePointer)){
        sscanf( line, "%d %s %c %c",&S[count].id, S[count].Name, &S[count].Gr1, &S[count].Gr2);
        count++;
    }
    fclose(filePointer);
    return count;
}

void LoadToFile(struct Student S[], int counter){
    FILE *filePointer;
    //Opening file in Write mode.
    filePointer = fopen("data.txt","w");
    if(filePointer){
    	int i;
       for(i=0; i< counter; i++){
       		fprintf(filePointer,"%d %s %c %c\n", S[i].id, S[i].Name, S[i].Gr1, S[i].Gr2);
	   }
       fclose(filePointer);
    }
}

int sortById(const void* p, const void* q)
{
    return (((struct Student*)p)->id - ((struct Student*)q)->id);
}

int main() {
    struct Student S[100];
    int count = 0, a;
    count = ReadDataFromFile(S);
    char b;
    while (1) {
        printf("\n0. Exit\n1. Melihat data murid\n2. Memasukan murid baru\n3. Sorting data murid\n4. Edit data murid\nMasukan data : ");
        scanf("%d", &a);
        if(a == 0)
        {
            printf("Thanks you \n");
            break;
        }
        if(a == 1)
        {
        	printf("Id    Name		Course1 Grade 	Course2 Grade\n");
        	int i;
            for(i = 0; i< count; i++){
                printf("%-5d %-20s %-15c %-15c \n", S[i].id, S[i].Name, S[i].Gr1, S[i].Gr2);
            }
        }
        if(a == 2){
        	int exist = 0;
        	char userInput[100];
        	scanf("%c",&b);
        	printf("Enter Id  Name  Course1 Grade Course2 Grade (seperated by space): ");
        	fgets(userInput, 100, stdin);
        	sscanf( userInput, "%d %s %c %c", &S[count].id, S[count].Name,  &S[count].Gr1, &S[count].Gr2);
        	int i;
        	for(i = 0; i< count; i++){
                if( S[count].id ==  S[i].id){
                	printf("This ID already exist unable to add new student\n");
                	exist = 1;
                }
            }
            if(exist == 0){
            	count++;
			}
        }
        if(a == 3){
            //sort by ID
            qsort(S, count, sizeof(struct Student), sortById);
            printf("Id    Name		Course1 Grade 	Course2 Grade\n");
            int i;
            for(i = 0; i< count; i++){
                printf("%-5d %-20s %-15c %-15c \n", S[i].id, S[i].Name, S[i].Gr1, S[i].Gr2);
            }
        }
        
        if(a == 4){
			printf("Id    Name		Course1 Grade 	Course2 Grade\n");
			int i;
            for(i = 0; i< count; i++){
                printf("%-5d %-20s %-15c %-15c \n", S[i].id, S[i].Name, S[i].Gr1, S[i].Gr2);
            }
            printf("Please enter the Id of Student you want to change Grades: ");
            int id, updated = 0;
            scanf("%d", &id);
            for(i = 0; i< count; i++){
                if( id ==  S[i].id){
                	printf("Enter Grades of Course 1: ");
                	scanf(" %c", &S[i].Gr1);
                	printf("Enter Grades of Course 2: ");
                	scanf(" %c", &S[i].Gr2);
                	updated = 1;
                	break;
				}
            }
            if(updated == 0){
            	printf("No Student Found with this Id\n");
			}
			else{
				printf("Student Grade Updated Successfully\n");
			}
		}
    }
    LoadToFile(S, count);
    return 0;
}
