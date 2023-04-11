/***************************************************************************************
**********
This is to certify that this project is my own work, based on my personal efforts in
studying and applying the concepts learned. I have constructed the functions and their
respective algorithms and corresponding code by myself. The program was run, tested,
and debugged by my own efforts. I further certify that I have not copied in part or
whole or otherwise plagiarized the work of other students and/or persons.

<Bigalbal, Zhienj>, DLSU ID #12206806
<De Guzman, Evan>, DLSU ID #12206180
****************************************************************************************
*********/

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

Personnel personnelList[MAX_PERSONNEL];
Project projectList[MAX_PROJECTS];
Task taskList[MAX_TASKS];
// Declare the functions for Personnel, Project and Task management
void addPersonnel(int numPersonnel);
void updatePersonnel();
void deletePersonnel();
void archivePersonnel();
void assignProject();
void addProject();
void updateTask();
void addTask();
void showPersonnelList();
void assignTask();
int findTaskIndex(int numTasks,int taskID);
void clearBuffer();
void runProjectCompletion();
void showDelayedTask();
void showProjectDetails();
char *getCurrentDate();
char* getProjectName(int numProjects, int projectID);
char* getPersonnelName(int numPersonnel,int personnelID);
void showTodayTasks(int numTasks,int numProjects,int taskAssign);
void showAssignedTask();
void updateTaskStatus();
int main() {
    int choice;
    int numPersonnel = 0;
    int numProjects = 0;
    int numTasks = 0;
    int taskAssign = taskList->assignID;
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
                    addPersonnel(numPersonnel);
                    break;
                case 2:
                    updatePersonnel();
                    break;
                case 3:
                    deletePersonnel(numTasks, numProjects, numProjects);
                    break;
                case 4:
                    archivePersonnel(numPersonnel);
                    break;
                case 5:
                    assignProject(numProjects, numPersonnel);
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
                    addProject();
                    break;
                case 2:
                    addTask();
                    break;
                case 3:
                    updateTask(numTasks);
                    break;
                case 4:
                    showPersonnelList(numPersonnel);
                    break;
                case 5:
                    assignTask(numPersonnel);
                    break;
                case 6:
                    showProjectDetails();
                    break;
                case 7:
                    showDelayedTask(numTasks, numProjects, numPersonnel);
                    break;
                case 8:
                    runProjectCompletion(numTasks, numProjects);
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
                   showTodayTasks(numTasks, numProjects, taskAssign);
                    break;
                case 2:
                    addTask();
                    break;
                case 3:
                    updateTask(numTasks);
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

/*
updateTask prints a certain task status and allows whoever the user is, given they are a registered user,
the choice to change the current status of their assigned task
@param numTasks - how many Tasks are made in file
Precondition: All inputs are of correct corresponding data type
*/

void updateTask(int numTasks) {
    int taskID, choice;
    int personnelID = personnelList[0].personnelID; // get the ID of the logged-in user
    int taskIndex = -1;
    
    // Display all tasks assigned to the login user
    printf("\nAll Tasks Assigned to You:\n");
    printf("ID\tName\t\t\t\tStatus\n");
    for (int i = 0; i < numTasks; i++) {
        if (taskList[i].assignID == personnelID) {
            printf("%d\t%-30s\t", taskList[i].taskID, taskList[i].name);
            switch (taskList[i].status) {
                case 1:
                    printf("Not Started\n");
                    break;
                case 2:
                    printf("In Progress\n");
                    break;
                case 3:
                    printf("Done\n");
                    break;
                default:
                    printf("Unknown\n");
            }
        }
    }
    
    // Ask the user to enter the task ID to be updated
    printf("\nEnter the Task ID to Update: ");
    scanf("%d", &taskID);
    taskIndex = findTaskIndex(numTasks,taskID);
    
    if (taskIndex == -1) {
        printf("\nTask ID %d not found.\n", taskID);
    }
    else if (taskList[taskIndex].assignID != personnelID) {
        printf("\nTask ID %d is not assigned to you.\n", taskID);
    }
    else {
        // Ask the user to select the new status for the task
        printf("\nSelect the New Task Status:\n");
        printf("1 - Not Started\n");
        printf("2 - In Progress\n");
        printf("3 - Done\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        
        // Update the task status based on the user's choice
        switch (choice) {
            case 1:
                taskList[taskIndex].status = 1;
                printf("\nTask status updated to Not Started.\n");
                break;
            case 2:
                taskList[taskIndex].status = 2;
                printf("\nTask status updated to In Progress.\n");
                break;
            case 3:
                taskList[taskIndex].status = 3;
                printf("\nTask status updated to Done.\n");
                break;
            default:
                printf("\nInvalid choice. Task status not updated.\n");
        }
    }
}

/*
void ShowAssignedTask returns lines detailing Task ID, Name, Project ID, Start date and End date
or No Assigned Tasks Found f or a given user ID.
@param numTasks - how many Tasks are made in file
Precondition: assignID input is of an integer data type
*/

void showAssignedTask(numTasks) {
    int assignID;
    printf("Enter your login user ID: ");
    scanf("%d", &assignID);
    printf("Assigned tasks:\n");
    int found = 0;
    for (int i = 0; i < numTasks; i++) {
        if (taskList[i].assignID == assignID) {
            printf("Task ID: %d\n", taskList[i].taskID);
            printf("Name: %s\n", taskList[i].name);
            printf("Project ID: %d\n", taskList[i].projectID);
            printf("Start date: %s\n", taskList[i].startdate);
            printf("End date: %s\n\n", taskList[i].enddate);
            found = 1;
        }
    }
    if (!found) {
        printf("No assigned tasks found.\n");
    }
}
/*
showTodayTasks prints the tasks assigned to a user ID, given that the user ID is registered, and the day
or it can print out no tasks assigned to you for today along with current date
@param numTasks - how many Tasks are made in file
@param numProjects - how many Projects are made in file
@param assignID - the ID of the task
*/
void showTodayTasks(int numTasks, int numProjects, int taskAssign) {
    time_t now;
    struct tm *local;
    char curr_date[MAX_DATE_LEN];
    time(&now);
    local = localtime(&now);
    strftime(curr_date, sizeof(curr_date), "%m/%d/%Y", local);

    int found = 0;
    printf("\nTasks assigned to you for today (%s):\n", curr_date);
    printf("------------------------------------------------------\n");
    printf("ID\tName\t\tProject\t\tStart Date\tEnd Date\n");
    printf("------------------------------------------------------\n");

    for (int i = 0; i < numTasks; i++) {
        if (strcmp(taskList[i].startdate, curr_date) <= 0 && strcmp(taskList[i].enddate, curr_date) >= 0 && taskList[i].assignID == taskAssign) {
            printf("%d\t%-16s\t%-16s\t%s\t%s\n", taskList[i].taskID, taskList[i].name, getProjectName(numProjects,taskList[i].projectID), taskList[i].startdate, taskList[i].enddate);
            found = 1;
        }
    }

    if (!found) {
        printf("No tasks assigned to you for today (%s).\n", curr_date);
    }
}

// Return the name of the personnel with the given ID
/*
getPersonnelName returns either a user name or NULL of a certain personnel. It will be
NULL if the personnelID does not exist.
@param numPersonnel - how many Personnels are made in file
@param personnelID - ID of a certain personnel
Precondition: Prior inputs such as personnelID is of valid data type.
*/
char* getPersonnelName(int numPersonnel,int personnelID) {
    for (int i = 0; i < numPersonnel; i++) {
        if (personnelList[i].personnelID == personnelID) {
            return personnelList[i].username;
        }
    }
    return NULL;
}
/*
getProjectName returns the project name or an unknown project. It will be Unknown if 
projectID does not exist.
@param numProjects - how many Projects are made in file
@param projectID - ID of a certain project
Precondition: Prior inputs such as projectID is of valid data type.
*/
char* getProjectName(int numProjects, int projectID) {
    for (int i = 0; i < numProjects; i++) {
        if (projectList[i].projectID == projectID) {
            return projectList[i].name;
        }
    }
    return "Unknown";
}
/*
getCurrentDate returns the date
*/
char *getCurrentDate() {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    static char date[11];
    strftime(date, sizeof(date), "%m/%d/%Y", t);
    return date;
}
/*
runProjectCompletion calculates how finished a certain project is and returns the calculated
or if a project ID is not found, it will print Project not found.
@param numTasks - how many Tasks are made in file
@param numProjects - how many Projects are made in file
Precondition: projectID input is of integer data type 
*/
void runProjectCompletion(int numTasks, int numProjects) {
    int projectId;
    printf("\nEnter the project ID: ");
    scanf("%d", &projectId);
    
    // Find the project with the provided projectId
    int projectIndex = -1;
    for (int i = 0; i < numProjects; i++) {
        if (projectList[i].projectID == projectId) {
            projectIndex = i;
            break;
        }
    }
    
    // If the project is not found, display an error message
    if (projectIndex == -1) {
        printf("Project not found.\n");
        return;
    }
    
    // Calculate project completion
    float totalDuration = 0.0;
    float completedDuration = 0.0;
    
    for (int i = 0; i < numTasks; i++) {
        if (taskList[i].projectID == projectId) {
            totalDuration += taskList[i].totalDuration;
            if (taskList[i].status == 2) {
                completedDuration += taskList[i].totalDuration;
            }
        }
    }
    
    projectList[projectIndex].completion = (completedDuration / totalDuration) * 100;
    printf("Project completion calculated.\n");
}
/*
showDelayedTask shows any task that is outside of the given end date by the manager
@param numTasks - how many Tasks are made in file
@param numProjects - how many Projects are made in file
@param numPersonnel - how many Personnels are made in file
Precondition: All prior inputs are made of correct corresponding data types.
*/
void showDelayedTask(int numTasks, int numProjects,int numPersonnel) {
    int count = 0;
    printf("\nDelayed Tasks:\n");
    for (int i = 0; i < numTasks; i++) {
        if (taskList[i].status == 0 && strcmp(taskList[i].enddate, getCurrentDate()) < 0) {
            printf("%d. %s\n", ++count, taskList[i].name);
            printf("    Project: %s\n", getProjectName(numProjects,taskList[i].projectID));
            printf("    Assigned to: %s\n", getPersonnelName(numPersonnel,taskList[i].assignID));
            printf("    End Date: %s\n", taskList[i].enddate);
        }
    }
    if (count == 0) {
        printf("No delayed tasks found.\n");
    }
}
/*
showProjecctDetails prints out all the details of the project including a list of all Active Projects, their ID and a drop down of all details of a selected Project
@param numTasks - how many Tasks are made in file
@param numProjects - how many Projects are made in file
Precondition: All prior inputs, such as Project ID, is made of correct corresponding data types.
*/
void showProjectDetails(numTasks,numProjects) {
    // Display the list of active projects
    printf("\nActive Projects:\n");
    printf("ID\tName\n");
    for (int i = 0; i < numProjects; i++) {
        if (projectList[i].status == 1) {
            printf("%d\t%s\n", projectList[i].projectID, projectList[i].name);
        }
    }

    // Ask for the project ID to display details for
    int projectID;
    printf("\nEnter the ID of the project to display details for: ");
    scanf("%d", &projectID);

    // Find the project record with the provided project ID
    int projectIndex = -1;
    for (int i = 0; i < numProjects; i++) {
        if (projectList[i].projectID == projectID) {
            projectIndex = i;
            break;
        }
    }

    // If the project is not found, display an error message and return
    if (projectIndex == -1) {
        printf("\nProject with ID %d not found.\n", projectID);
        return;
    }

    // Display the project details
    printf("\nProject Details:\n");
    printf("Name: %s\n", projectList[projectIndex].name);
    printf("Status: %d\n", projectList[projectIndex].status);
    printf("Completion: %.2f%%\n", projectList[projectIndex].completion);
    printf("Description: %s\n", projectList[projectIndex].description);
    printf("Assigned to Personnel ID: %d\n", projectList[projectIndex].assignID);

    // Display the tasks for the project
    printf("\nTasks:\n");
    printf("ID\tName\tSequence\tStatus\tAssigned to Personnel ID\n");
    for (int i = 0; i < numTasks; i++) {
        if (taskList[i].projectID == projectID) {
            printf("%d\t%s\t%d\t\t%d\t\t%d\n", taskList[i].taskID, taskList[i].name,
                taskList[i].sequence, taskList[i].status, taskList[i].assignID);
        }
    }
}
/*
assignTask assigns a certain task to a user ID, but also checks if the user ID already has a task assigned to them or if the task does not exist.
@param numTasks - how many Tasks are made in file
@param numPersonnel - how many Personnels are made in file
Precondition: All prior inputs, such as taskID, task name and other properties of a task, are made with correct corressponding data types.
*/
void assignTask(numTasks,numPersonnel) {
    int taskID, personnelID, taskIndex, personnelIndex;

    // Ask for the taskID
    printf("Enter taskID to assign: ");
    scanf("%d", &taskID);

    // Find the task record with the provided taskID
    taskIndex = -1;
    for (int i = 0; i < numTasks; i++) {
        if (taskList[i].taskID == taskID) {
            taskIndex = i;
            break;
        }
    }

    // If the task is not found, display an error message and return to the Manager Menu
    if (taskIndex == -1) {
        printf("Task not found. Please try again.\n");
        return;
    }

    // Show the task details
    printf("Task details:\n");
    printf("Name: %s\n", taskList[taskIndex].name);
    printf("Project ID: %d\n", taskList[taskIndex].projectID);
    printf("Start Date: %s\n", taskList[taskIndex].startdate);
    printf("End Date: %s\n", taskList[taskIndex].enddate);
    printf("Status: %d\n", taskList[taskIndex].status);

    // If the task is already assigned, display an error message and return to the Manager Menu
    if (taskList[taskIndex].assignID != -1) {
        printf("Task is already assigned. Please try again.\n");
        return;
    }

    // Ask for the personnelID
    printf("Enter personnelID to assign to this task: ");
    scanf("%d", &personnelID);

    // Find the personnel record with the provided personnelID
    personnelIndex = -1;
    for (int i = 0; i < numPersonnel; i++) {
        if (personnelList[i].personnelID == personnelID) {
            personnelIndex = i;
            break;
        }
    }

    // If the personnel is not found, display an error message and return to the Manager Menu
    if (personnelIndex == -1) {
        printf("Personnel not found. Please try again.\n");
        return;
    }

    // If the personnel is not active, display an error message and return to the Manager Menu
    if (personnelList[personnelIndex].active != 1) {
        printf("Personnel is not active. Please try again.\n");
        return;
    }

    // Assign the task to the personnel
    taskList[taskIndex].assignID = personnelID;
    printf("Task assigned successfully.\n");
}

/*
showPersonnelList shows all registered Personnels in the file
@param numPersonnel - how many Personnels are made in file
Precondition: All prior inputs into the details of a personnel are made with correct
corressponding data types.
*/
void showPersonnelList(int numPersonnel) {
    printf("\n---------------------\n");
    printf(" Active Personnel List\n");
    printf("---------------------\n");

    // Display the header for the personnel list
    printf("%-5s%-20s%-20s\n", "ID", "Username", "Access");

    // Display each personnel record in the list
    for (int i = 0; i < numPersonnel; i++) {
        if (personnelList[i].active == 1) {
            printf("%-5d%-20s%-20s\n", personnelList[i].personnelID, personnelList[i].username,
                   personnelList[i].access == 1 ? "Admin" : "Manager");
        }
    }
}
/*
findTaskIndex returns a certain number i that is incrementing to find the corresponding taskID
from the structure traskList.taskID. It can also return -1 if the taskID is not found
@param numTasks - how many Tasks are made in file
@param taskID - the ID given to a certain task
Precondition: All prior inputs, such as taskID, are made with correct corresponding data types.
*/
int findTaskIndex(int numTasks,int taskID) {
    for (int i = 0; i < numTasks; i++) {
        if (taskList[i].taskID == taskID) {
            return i;
        }
    }
    return -1; // if taskID not found
}
/*
updateTaskStatus prints all the details of a task and allows the user to update any of the details/values
afterwards
@param numTasks - how many Tasks are made in file
Precondition: All inputs that will be made, such as taskID, will have a correct corresponding
data types.
*/
void updateTaskStatus(numTasks) {
    int taskID, index;
    printf("\n---------------------\n");
    printf("     Update Task\n");
    printf("---------------------\n");

    // Ask the user for the task ID to be updated
    printf("Enter the Task ID to be updated: ");
    scanf("%d", &taskID);

    // Find the index of the task in the taskList array
    index = findTaskIndex(numTasks,taskID);

    // If the task is not found, display an error message and return to the Manager Menu
    if (index == -1) {
        printf("\nTask not found. Please try again.\n");
        return;
    }

    // Display the current task information
    printf("\nCurrent Task Information:\n");
    printf("Name: %s\n", taskList[index].name);
    printf("Sequence: %d\n", taskList[index].sequence);
    printf("Description: %s\n", taskList[index].description);
    printf("Project ID: %d\n", taskList[index].projectID);
    printf("Start Date: %s\n", taskList[index].startdate);
    printf("End Date: %s\n", taskList[index].enddate);
    printf("Total Duration: %.2f\n", taskList[index].totalDuration);
    printf("Status: %d\n", taskList[index].status);
    printf("Assigned Personnel ID: %d\n\n", taskList[index].assignID);

    // Ask the user to confirm if they want to update the task
    char confirm;
    printf("Are you sure you want to update this task? (Y/N): ");
    clearBuffer();
    scanf("%c", &confirm);

    if (confirm == 'Y' || confirm == 'y') {
        // Update the task information
        printf("\nEnter the new information for the task:\n");

        printf("Name: ");
        fgets(taskList[index].name, MAX_NAME_LEN, stdin);
        taskList[index].name[strcspn(taskList[index].name, "\n")] = '\0';

        printf("Sequence: ");
        scanf("%d", &taskList[index].sequence);
        clearBuffer();

        printf("Description: ");
        fgets(taskList[index].description, MAX_DESC_LEN, stdin);
        taskList[index].description[strcspn(taskList[index].description, "\n")] = '\0';

        printf("Project ID: ");
        scanf("%d", &taskList[index].projectID);
        clearBuffer();

        printf("Start Date (MM/DD/YYYY): ");
        fgets(taskList[index].startdate, MAX_DATE_LEN, stdin);
        taskList[index].startdate[strcspn(taskList[index].startdate, "\n")] = '\0';

        printf("End Date (MM/DD/YYYY): ");
        fgets(taskList[index].enddate, MAX_DATE_LEN, stdin);
        taskList[index].enddate[strcspn(taskList[index].enddate, "\n")] = '\0';

        printf("Total Duration: ");
        scanf("%f", &taskList[index].totalDuration);
        clearBuffer();

        printf("Status: ");
        scanf("%d", &taskList[index].status);
        clearBuffer();

        printf("Assigned Personnel ID: ");
        scanf("%d", &taskList[index].assignID);
        clearBuffer();

        printf("\nTask updated successfully.\n");
    }
}
/*
addTask allows the registered user to enter a task and generate an ID for the file
@param numTasks - how many Tasks are made in file
Precondition: All inputs of string, integers and float are made with correct corresponding data types
*/
void addTask(numTasks) {
    Task newTask;
    char confirm;

    printf("\n---------------------\n");
    printf("    Add New Task\n");
    printf("---------------------\n");

    // Generate a new task ID
    newTask.taskID = numTasks + 1;

    // Get the required task details from the user
    printf("Name: ");
    scanf("%s", newTask.name);
    printf("Sequence: ");
    scanf("%d", &newTask.sequence);
    printf("Description: ");
    scanf("%s", newTask.description);
    printf("Project ID: ");
    scanf("%d", &newTask.projectID);
    printf("Start Date (MM/DD/YYYY): ");
    scanf("%s", newTask.startdate);
    printf("End Date (MM/DD/YYYY): ");
    scanf("%s", newTask.enddate);
    printf("Total Duration (in days): ");
    scanf("%f", &newTask.totalDuration);
    printf("Status (0: Not Started, 1: In Progress, 2: Completed): ");
    scanf("%d", &newTask.status);
    printf("Assigned Personnel ID: ");
    scanf("%d", &newTask.assignID);

    // Confirm the details with the user
    printf("\nAre these details correct? (Y/N)\n");
    printf("Task ID: %d\n", newTask.taskID);
    printf("Name: %s\n", newTask.name);
    printf("Sequence: %d\n", newTask.sequence);
    printf("Description: %s\n", newTask.description);
    printf("Project ID: %d\n", newTask.projectID);
    printf("Start Date: %s\n", newTask.startdate);
    printf("End Date: %s\n", newTask.enddate);
    printf("Total Duration: %.2f\n", newTask.totalDuration);
    printf("Status: %d\n", newTask.status);
    printf("Assigned Personnel ID: %d\n", newTask.assignID);
    scanf(" %c", &confirm);

    // Add the new task to the taskList if the user confirms
    if (confirm == 'Y' || confirm == 'y') {
    	taskList[numTasks] = newTask;
    FILE *fp = fopen("task.txt", "a");
    
    fprintf(fp, "%d,%d,%s,%d,%s,%s,%d,%d,%d\n", numTasks + 1, taskList[numTasks].sequence, taskList[numTasks].description, taskList[numTasks].projectID,taskList[numTasks].startdate,
           taskList[numTasks].enddate,taskList[numTasks].totalDuration,taskList[numTasks].status, taskList[numTasks].assignID);
    numTasks++;
    fclose(fp);
        
        
        printf("\nTask added successfully.\n");
    } else {
        printf("\nTask not added.\n");
    }
}
/*
addProject - allows the admin or manager to create a project, to be assigned.
@param numProjects - how many Projects are made in file
Precondition: All prior inputs are valid and all inputs of string, integers and float are made
with correct corresponding data types.
*/
void addProject(numProjects) {
    Project newProject;
    char confirm;
    printf("\n---------------------\n");
    printf("    Add New Project\n");
    printf("---------------------\n");

    // Generate a new project ID
    newProject.projectID = numProjects + 1;

    // Prompt the manager to enter the details of the new project
    printf("Enter the name of the project: ");
    scanf("%s", newProject.name);
    printf("Enter the description of the project: ");
    scanf("%s", newProject.description);
    printf("Enter the personnel ID to assign the project: ");
    scanf("%d", &newProject.assignID);

    // Set the status and completion fields to default values
    newProject.status = 0;
    newProject.completion = 0.0;

    // Ask for confirmation before adding the new project
    printf("\nAre you sure you want to add the following project?\n");
    printf("Name: %s\n", newProject.name);
    printf("Description: %s\n", newProject.description);
    printf("Assigned Personnel ID: %d\n", newProject.assignID);
    printf("Status: %d\n", newProject.status);
    printf("Completion: %.2f\n", newProject.completion);
    printf("Enter Y to confirm, any other key to cancel: ");
    scanf(" %c", &confirm);

    // Add the new project to the project list if confirmed
    if (confirm == 'Y' || confirm == 'y') {
        projectList[numProjects] = newProject;
        
        
        FILE *fp = fopen("proj.txt", "a");
    fprintf(fp, "%d,%s,%d,%d,%s\n", projectList[numProjects].projectID, projectList[numProjects].name, 1, 2, projectList[numProjects].description);
    numProjects++;
        fclose(fp);
        printf("\nProject added successfully.\n");
        
        
    } else {
        printf("\nOperation canceled.\n");
    }
}

// Implement the functions for Personnel management
/*
addPersonnel creates a new personnel
@param numPersonnel - how many Personnels are made
Precondition: All prior inputs are made with correct corresponding values and all inputs in the functions are valid.
*/
void addPersonnel(int numPersonnel) {
Personnel newPersonnel;
char confirm;
printf("\n---------------------\n");
printf("   Add New Personnel\n");
printf("---------------------\n");

// Generate a new personnel ID

newPersonnel.personnelID = numPersonnel + 1;

// Get the new personnel information from the administrator
printf("Username: ");
scanf("%s", newPersonnel.username);

printf("Temporary Password: ");
scanf("%s", newPersonnel.password);

newPersonnel.access = 2; // Set the access value to 2 (Manager)

newPersonnel.active = 1; // Set the active status to 1 (Active)

printf("\nConfirm to add new personnel? (Y/N): ");
scanf(" %c", &confirm);

if (confirm == 'Y' || confirm == 'y') {
	FILE *fp = fopen("personel.txt", "a");
    personnelList[numPersonnel] = newPersonnel;
    fprintf(fp, "%d,%s,%s,%d,%d\n", numPersonnel + 1, personnelList[numPersonnel].username,
           personnelList[numPersonnel].password, 1, 2);
    numPersonnel++;
    fclose(fp);
    printf("New personnel added successfully.\n");
} else {
    printf("New personnel not added.\n");
}
}
/*
updatePersonnel prints out an updated version of the details of a user given userID
Precondition: personnelID is made with valid input
*/
void updatePersonnel() {
int personnelID;
printf("\n---------------------\n");
printf(" Update Personnel\n");
printf("---------------------\n");
// Ask for the personnel ID to update
printf("Enter the Personnel ID to update: ");
scanf("%d", &personnelID);


printf("Personnel record updated successfully.\n");
}
/*
deletePersonnel is the function that allows the admin to delete a user from its database
@param numTasks - how many Tasks are made in file
@param numProjects - how many Projects are made in file
@param numPersonnel - how many Personnels are made in file
Precondition: All inputs in the function are made with correct corresponding data types.
*/
void deletePersonnel(int numTasks,int numProjects ,int numPersonnel) {
    int personnelID, index;
    char confirm;

    printf("\n---------------------\n");
    printf("     Delete User\n");
    printf("---------------------\n");

    // Ask for the personnelID of the user to be deleted
    printf("Personnel ID: ");
    scanf("%d", &personnelID);
	
    // Find the index of the user with the provided personnelID
//    index = findPersonnelIndex(personnelID);

    if (index == -1) {
        printf("Personnel with ID %d not found.\n", personnelID);
    }
    else {
        // Confirm the deletion with the administrator
        printf("Are you sure you want to delete the account of %s? (Y/N) ", personnelList[index].username);
//        clearBuffer(); // clear input buffer before using fgets
        fgets(&confirm, sizeof(confirm), stdin);
		getchar();
        if (confirm == 'Y' || confirm == 'y') {
            // If the user account is attached to a record (Task or Project), assign it to the Administrator account
            for (int i = 0; i < numTasks; i++) {
                if (taskList[i].assignID == personnelID) {
                    taskList[i].assignID = personnelList[0].personnelID; // assign to Administrator account
                }
            }
            for (int i = 0; i < numProjects; i++) {
                if (projectList[i].assignID == personnelID) {
                    projectList[i].assignID = personnelList[0].personnelID; // assign to Administrator account
                }
            }

            // Shift the remaining personnel records to fill the gap
            for (int i = index; i < numPersonnel-1; i++) {
                personnelList[i] = personnelList[i+1];
            }
            numPersonnel--;

            printf("Account of %s has been deleted.\n", personnelList[index].username);
        }
        else {
            printf("Account deletion canceled.\n");
        }
    }
}
/*
findPersonnelIndex runs through the number of numPersonnels to find an equal personnelID from the structure personnelList.personnelID
@param numPersonnel - how many Personnels are made in file
@param personnelID - ID of a certain personnel
Precondition: All prior inputs, such as personnelID, are made with correct corresponding data types.
*/
int findPersonnelIndex(int numPersonnel, int personnelID) {
    for (int i = 0; i < numPersonnel; i++) {
        if (personnelList[i].personnelID == personnelID) {
            return i;
        }
    }
    return -1; // Personnel not found
}
/*
archivePersonnel allows admin to archive a certain personnel, making them inactive but not necessarily deleting them
@param numPersonnel - how many Personnels are made in file
Precondition: All inputs such as personnelID and confirmare made with correct corresponding data type.
*/
void archivePersonnel(int numPersonnel) {
    int personnelID;
    int personnelIndex;
    char confirm;

    printf("\n---------------------\n");
    printf("    Archive Personnel\n");
    printf("---------------------\n");

    // Ask for the personnel ID to archive
    printf("Enter the Personnel ID to archive: ");
    scanf("%d", &personnelID);

    // Find the index of the personnel record with the provided ID
    personnelIndex = findPersonnelIndex(numPersonnel, personnelID);

    if (personnelIndex == -1) {
        printf("Personnel with ID %d not found.\n", personnelID);
    } else {
        Personnel personnel = personnelList[personnelIndex];

        // Ask for confirmation before archiving the personnel
        printf("Are you sure you want to archive Personnel %d (Y/N)? ", personnelID);
//        clearBuffer();
        scanf("%c", &confirm);

        if (confirm == 'Y' || confirm == 'y') {
            // Mark the personnel as archived by setting the active status to 2
            personnel.active = 2;
            personnelList[personnelIndex] = personnel;
            printf("Personnel %d has been archived.\n", personnelID);
        } else {
            printf("Personnel %d has not been archived.\n", personnelID);
        }
    }
}
/*
assignProject allows admin to assign a project to a certain manager
@param numProjects - how many Projects are made in file
@param numPersonnel - how many Personnels are made in file
Precondition: All inputs for projectID and personnelID are made with correct corresponding data type.
*/
void assignProject(int numProjects, int numPersonnel) {
    printf("\n---------------------\n");
    printf("   Assign Project\n");
    printf("---------------------\n");
    int i;
    // Display all the active projects
    printf("Active Projects:\n");
    for (i = 0; i < numProjects; i++) {
        if (projectList[i].status == 1) {
            printf("%d: %s\n", projectList[i].projectID, projectList[i].name);
        }
    }

    // Display all the active personnel with user access of 2 (Manager)
    printf("\nActive Managers:\n");
    for (i = 0; i < numPersonnel; i++) {
        if (personnelList[i].active == 1 && personnelList[i].access == 2) {
            printf("%d: %s\n", personnelList[i].personnelID, personnelList[i].username);
        }
    }

    int projectID, personnelID;
    printf("\nEnter the project ID: ");
    scanf("%d", &projectID);
    printf("Enter the personnel ID: ");
    scanf("%d", &personnelID);

}
/*
clearBuffers clears buffer
*/
void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

