
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// Define the maximum length of each string field
#define MAX_NAME_LEN 40
#define MAX_DESC_LEN 100
#define MAX_DATE_LEN 11 // MM/DD/YYYY format

// Define the maximum number of records to be stored
#define MAX_PERSONNEL 100
#define MAX_PROJECTS 100
#define MAX_TASKS 100

// Define the structures for Personnel, Project and Task records
typedef struct {
    int personnelID;
    char username[MAX_NAME_LEN];
    char password[MAX_NAME_LEN];
    int active;
    int access;
} Personnel;

typedef struct {
    int projectID;
    char name[MAX_NAME_LEN];
    int status;
    float completion;
    char description[MAX_DESC_LEN];
    int assignID;
} Project;

typedef struct {
    int taskID;
    char name[MAX_NAME_LEN];
    int sequence;
    char description[MAX_DESC_LEN];
    int projectID;
    char startdate[MAX_DATE_LEN];
    char enddate[MAX_DATE_LEN];
    float totalDuration;
    int status;
    int assignID;
} Task;

// Declare the global variables to hold the records
Personnel personnelList[MAX_PERSONNEL];
int numPersonnel = 0;

Project projectList[MAX_PROJECTS];
int numProjects = 0;

Task taskList[MAX_TASKS];
int numTasks = 0;

// Declare the functions for Personnel, Project and Task management
//void addPersonnel();
//void updatePersonnel();
//void deletePersonnel();
//void archivePersonnel();
//void assignProject();
//void addProject();
//void updateTask();
//void addTask();
//void showPersonnelList();
//void assignTask();
//int findTaskIndex(int taskID);
//void clearBuffer();
//void runProjectCompletion();
//void showDelayedTask();
//void showProjectDetails();
//char *getCurrentDate();
//char* getProjectName(int projectID);
//char* getPersonnelName(int personnelID);
//void showTodayTasks(int assignID);
//void showAssignedTask();
//void updateTaskStatus();
int main() {
    int choice;
    char username[MAX_NAME_LEN];
    char password[MAX_NAME_LEN];

    // Load the personnel records from a text file
    FILE *fp = fopen("preloaded.txt", "r");
    if (fp == NULL) {
        printf("Error loading personnel records.\n");
        exit(1);
    }

    fscanf(fp, "%d,%[^,],%[^,],%d,%d\n", &personnelList[numPersonnel].personnelID, personnelList[numPersonnel].username,
           personnelList[numPersonnel].password, &personnelList[numPersonnel].active, &personnelList[numPersonnel].access);
    numPersonnel++;

    fclose(fp);

    // Display the Login Menu
    while (1) {
        printf("\n---------------------\n");
        printf("     Login Menu\n");
        printf("---------------------\n");
        printf("Username: ");
        scanf("%s", username);
        printf("Password: ");
        scanf("%s", password);

        int personnelIndex = -1;
        // Find the personnel record with the provided username and password
        for (int i = 0; i < numPersonnel; i++) {
            if (strcmp(username, personnelList[i].username) == 0 && strcmp(password, personnelList[i].password) == 0) {
                personnelIndex = i;
                
                break;
            }
        }

        // If the personnel is not found or the account is archived, display an error message and show the Login Menu again
        if (personnelIndex == -1 || personnelList[personnelIndex].active == 2) {
            printf("\nInvalid username or password. Please try again.\n");
        }
        // If the personnel has access value of 1 (Admin), display the Admin Menu
        else if(personnelList[personnelIndex].access == 1) {
while (choice != 6) {
printf("\n---------------------\n");
printf(" Admin Menu\n");
printf("---------------------\n");
printf("1. Add New User\n");
printf("2. Update User\n");
printf("3. Delete User\n");
printf("4. Archive User\n");
printf("5. Assign Project\n");
printf("6. Back to Login Menu\n");
printf("Enter choice: ");
scanf("%d", &choice);
            switch (choice) {
                case 1:
                    //addPersonnel();
                    break;
                case 2:
                    //updatePersonnel();
                    break;
                case 3:
                    //deletePersonnel();
                    break;
                case 4:
                    //archivePersonnel();
                    break;
                case 5:
                    //assignProject();
                    break;
                case 6:
                    break;
                default:
                    printf("Invalid choice. Please try again.\n");
            }
        }
    }
    // If the personnel has access value of 2 (Manager), display the Manager Menu
    else if (personnelList[personnelIndex].access == 2) {
        while (choice != 9) {
printf("\n---------------------\n");
printf(" Manager Menu\n");
printf("---------------------\n");
printf("1. Add New Project\n");
printf("2. Add New Task\n");
printf("3. Update Task\n");
printf("4. Show Personnel List\n");
printf("5. Assign Task\n");
printf("6. Show Project Details\n");
printf("7. Show Delayed Task\n");
printf("8. Run Project Completion\n");
printf("9. Back to Login Menu\n");
printf("Enter choice: ");
scanf("%d", &choice);
            switch (choice) {
                case 1:
                    //addProject();
                    break;
                case 2:
                    //addTask();
                    break;
                case 3:
                    //updateTask();
                    break;
                case 4:
                    //showPersonnelList();
                    break;
                case 5:
                    //assignTask();
                    break;
                case 6:
                    //showProjectDetails();
                    break;
                case 7:
                    //showDelayedTask();
                    break;
                case 8:
                    //runProjectCompletion();
                    break;
                case 9:
                    break;
                default:
                    printf("Invalid choice. Please try again.\n");
            }
        }
    }else if (personnelList[personnelIndex].access == 3) {
		while (choice != 9) {
printf("\n---------------------\n");
printf(" User Menu\n");
printf("---------------------\n");
printf("1. Show Today’s Task\n");
printf("2. Show All Assigned Task\n");
printf("3. Update Task Status\n");
printf("4. Back to Main Menu\n");
printf("Enter choice: ");
scanf("%d", &choice);
            switch (choice) {
                case 1:
                    //addProject();
                    break;
                case 2:
                    //addTask();
                    break;
                case 3:
                    //updateTask();
                    break;
                case 4:
                    break;
                default:
                    printf("Invalid choice. Please try again.\n");
            }
        }
	}
}

return 0;
}
Projects.c
Displaying Projects.c.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// Define the maximum length of each string field
#define MAX_NAME_LEN 40
#define MAX_DESC_LEN 100
#define MAX_DATE_LEN 11 // MM/DD/YYYY format

// Define the maximum number of records to be stored
#define MAX_PERSONNEL 100
#define MAX_PROJECTS 100
#define MAX_TASKS 100

// Define the structures for Personnel, Project and Task records
typedef struct {
    int personnelID;
    char username[MAX_NAME_LEN];
    char password[MAX_NAME_LEN];
    int active;
    int access;
} Personnel;

typedef struct {
    int projectID;
    char name[MAX_NAME_LEN];
    int status;
    float completion;
    char description[MAX_DESC_LEN];
    int assignID;
} Project;

typedef struct {
    int taskID;
    char name[MAX_NAME_LEN];
    int sequence;
    char description[MAX_DESC_LEN];
    int projectID;
    char startdate[MAX_DATE_LEN];
    char enddate[MAX_DATE_LEN];
    float totalDuration;
    int status;
    int assignID;
} Task;

// Declare the global variables to hold the records
Personnel personnelList[MAX_PERSONNEL];
int numPersonnel = 0;

Project projectList[MAX_PROJECTS];
int numProjects = 0;

Task taskList[MAX_TASKS];
int numTasks = 0;

// Declare the functions for Personnel, Project and Task management
//void addPersonnel();
//void updatePersonnel();
//void deletePersonnel();
//void archivePersonnel();
//void assignProject();
//void addProject();
//void updateTask();
//void addTask();
//void showPersonnelList();
//void assignTask();
//int findTaskIndex(int taskID);
//void clearBuffer();
//void runProjectCompletion();
//void showDelayedTask();
//void showProjectDetails();
//char *getCurrentDate();
//char* getProjectName(int projectID);
//char* getPersonnelName(int personnelID);
//void showTodayTasks(int assignID);
//void showAssignedTask();
//void updateTaskStatus();
int main() {
    int choice;
    char username[MAX_NAME_LEN];
    char password[MAX_NAME_LEN];

    // Load the personnel records from a text file
    FILE *fp = fopen("preloaded.txt", "r");
    if (fp == NULL) {
        printf("Error loading personnel records.\n");
        exit(1);
    }

    fscanf(fp, "%d,%[^,],%[^,],%d,%d\n", &personnelList[numPersonnel].personnelID, personnelList[numPersonnel].username,
           personnelList[numPersonnel].password, &personnelList[numPersonnel].active, &personnelList[numPersonnel].access);
    numPersonnel++;

    fclose(fp);

    // Display the Login Menu
    while (1) {
        printf("\n---------------------\n");
        printf("     Login Menu\n");
        printf("---------------------\n");
        printf("Username: ");
        scanf("%s", username);
        printf("Password: ");
        scanf("%s", password);

        int personnelIndex = -1;
        // Find the personnel record with the provided username and password
        for (int i = 0; i < numPersonnel; i++) {
            if (strcmp(username, personnelList[i].username) == 0 && strcmp(password, personnelList[i].password) == 0) {
                personnelIndex = i;
                
                break;
            }
        }

        // If the personnel is not found or the account is archived, display an error message and show the Login Menu again
        if (personnelIndex == -1 || personnelList[personnelIndex].active == 2) {
            printf("\nInvalid username or password. Please try again.\n");
        }
        // If the personnel has access value of 1 (Admin), display the Admin Menu
        else if(personnelList[personnelIndex].access == 1) {
while (choice != 6) {
printf("\n---------------------\n");
printf(" Admin Menu\n");
printf("---------------------\n");
printf("1. Add New User\n");
printf("2. Update User\n");
printf("3. Delete User\n");
printf("4. Archive User\n");
printf("5. Assign Project\n");
printf("6. Back to Login Menu\n");
printf("Enter choice: ");
scanf("%d", &choice);
            switch (choice) {
                case 1:
                    //addPersonnel();
                    break;
                case 2:
                    //updatePersonnel();
                    break;
                case 3:
                    //deletePersonnel();
                    break;
                case 4:
                    //archivePersonnel();
                    break;
                case 5:
                    //assignProject();
                    break;
                case 6:
                    break;
                default:
                    printf("Invalid choice. Please try again.\n");
            }
        }
    }
    // If the personnel has access value of 2 (Manager), display the Manager Menu
    else if (personnelList[personnelIndex].access == 2) {
        while (choice != 9) {
printf("\n---------------------\n");
printf(" Manager Menu\n");
printf("---------------------\n");
printf("1. Add New Project\n");
printf("2. Add New Task\n");
printf("3. Update Task\n");
printf("4. Show Personnel List\n");
printf("5. Assign Task\n");
printf("6. Show Project Details\n");
printf("7. Show Delayed Task\n");
printf("8. Run Project Completion\n");
printf("9. Back to Login Menu\n");
printf("Enter choice: ");
scanf("%d", &choice);
            switch (choice) {
                case 1:
                    //addProject();
                    break;
                case 2:
                    //addTask();
                    break;
                case 3:
                    //updateTask();
                    break;
                case 4:
                    //showPersonnelList();
                    break;
                case 5:
                    //assignTask();
                    break;
                case 6:
                    //showProjectDetails();
                    break;
                case 7:
                    //showDelayedTask();
                    break;
                case 8:
                    //runProjectCompletion();
                    break;
                case 9:
                    break;
                default:
                    printf("Invalid choice. Please try again.\n");
            }
        }
    }else if (personnelList[personnelIndex].access == 3) {
		while (choice != 9) {
printf("\n---------------------\n");
printf(" User Menu\n");
printf("---------------------\n");
printf("1. Show Today’s Task\n");
printf("2. Show All Assigned Task\n");
printf("3. Update Task Status\n");
printf("4. Back to Main Menu\n");
printf("Enter choice: ");
scanf("%d", &choice);
            switch (choice) {
                case 1:
                    //addProject();
                    break;
                case 2:
                    //addTask();
                    break;
                case 3:
                    //updateTask();
                    break;
                case 4:
                    break;
                default:
                    printf("Invalid choice. Please try again.\n");
            }
        }
	}
}

return 0;
}
Projects.c
Displaying Projects.c.