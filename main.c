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
void addPersonnel();
void updatePersonnel();
void deletePersonnel();
void archivePersonnel();
void assignProject();
void addProject();
void updateTask();
void addTask();
void showPersonnelList();
void assignTask();
int findTaskIndex(int taskID);
void clearBuffer();
void runProjectCompletion();
void showDelayedTask();
void showProjectDetails();
char *getCurrentDate();
char* getProjectName(int projectID);
char* getPersonnelName(int personnelID);
void showTodayTasks(int assignID);
void showAssignedTask();
void updateTaskStatus();
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
                    addPersonnel();
                    break;
                case 2:
                    updatePersonnel();
                    break;
                case 3:
                    deletePersonnel();
                    break;
                case 4:
                    archivePersonnel();
                    break;
                case 5:
                    assignProject();
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
                    updateTask();
                    break;
                case 4:
                    showPersonnelList();
                    break;
                case 5:
                    assignTask();
                    break;
                case 6:
                    showProjectDetails();
                    break;
                case 7:
                    showDelayedTask();
                    break;
                case 8:
                    runProjectCompletion();
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
                    addProject();
                    break;
                case 2:
                    addTask();
                    break;
                case 3:
                    updateTask();
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
void updateTask() {
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
    taskIndex = findTaskIndex(taskID);
    
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

void showAssignedTask() {
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

void showTodayTasks(int assignID) {
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
        if (strcmp(taskList[i].startdate, curr_date) <= 0 && strcmp(taskList[i].enddate, curr_date) >= 0 && taskList[i].assignID == assignID) {
            printf("%d\t%-16s\t%-16s\t%s\t%s\n", taskList[i].taskID, taskList[i].name, getProjectName(taskList[i].projectID), taskList[i].startdate, taskList[i].enddate);
            found = 1;
        }
    }

    if (!found) {
        printf("No tasks assigned to you for today (%s).\n", curr_date);
    }
}

// Return the name of the personnel with the given ID
char* getPersonnelName(int personnelID) {
    for (int i = 0; i < numPersonnel; i++) {
        if (personnelList[i].personnelID == personnelID) {
            return personnelList[i].username;
        }
    }
    return NULL;
}

char* getProjectName(int projectID) {
    for (int i = 0; i < numProjects; i++) {
        if (projectList[i].projectID == projectID) {
            return projectList[i].name;
        }
    }
    return "Unknown";
}

char *getCurrentDate() {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    static char date[11];
    strftime(date, sizeof(date), "%m/%d/%Y", t);
    return date;
}
void runProjectCompletion() {
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

void showDelayedTask() {
    int count = 0;
    printf("\nDelayed Tasks:\n");
    for (int i = 0; i < numTasks; i++) {
        if (taskList[i].status == 0 && strcmp(taskList[i].enddate, getCurrentDate()) < 0) {
            printf("%d. %s\n", ++count, taskList[i].name);
            printf("    Project: %s\n", getProjectName(taskList[i].projectID));
            printf("    Assigned to: %s\n", getPersonnelName(taskList[i].assignID));
            printf("    End Date: %s\n", taskList[i].enddate);
        }
    }
    if (count == 0) {
        printf("No delayed tasks found.\n");
    }
}

void showProjectDetails() {
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

void assignTask() {
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

void showPersonnelList() {
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
int findTaskIndex(int taskID) {
    for (int i = 0; i < numTasks; i++) {
        if (taskList[i].taskID == taskID) {
            return i;
        }
    }
    return -1; // if taskID not found
}

void updateTaskStatus() {
    int taskID, index;
    printf("\n---------------------\n");
    printf("     Update Task\n");
    printf("---------------------\n");

    // Ask the user for the task ID to be updated
    printf("Enter the Task ID to be updated: ");
    scanf("%d", &taskID);

    // Find the index of the task in the taskList array
    index = findTaskIndex(taskID);

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

void addTask() {
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
        numTasks++;
        printf("\nTask added successfully.\n");
    } else {
        printf("\nTask not added.\n");
    }
}

void addProject() {
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
    scanf(" %[^\n]s", newProject.description);
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
        numProjects++;
        printf("\nProject added successfully.\n");
    } else {
        printf("\nOperation canceled.\n");
    }
}

// Implement the functions for Personnel management
void addPersonnel() {
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
	FILE *fp = fopen("preloaded.txt", "a");
    personnelList[numPersonnel] = newPersonnel;
    fprintf(fp, "%d,%s,%s,%d,%d\n", &personnelList[numPersonnel].personnelID, personnelList[numPersonnel].username,
           personnelList[numPersonnel].password, 1, 2);
    numPersonnel++;
    printf("New personnel added successfully.\n");
} else {
    printf("New personnel not added.\n");
}
}
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
void deletePersonnel() {
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

int findPersonnelIndex(int personnelID) {
    for (int i = 0; i < numPersonnel; i++) {
        if (personnelList[i].personnelID == personnelID) {
            return i;
        }
    }
    return -1; // Personnel not found
}

void archivePersonnel() {
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
    personnelIndex = findPersonnelIndex(personnelID);

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

void assignProject() {
    printf("\n---------------------\n");
    printf("   Assign Project\n");
    printf("---------------------\n");

    // Display all the active projects
    printf("Active Projects:\n");
    for (int i = 0; i < numProjects; i++) {
        if (projectList[i].status == 1) {
            printf("%d: %s\n", projectList[i].projectID, projectList[i].name);
        }
    }

    // Display all the active personnel with user access of 2 (Manager)
    printf("\nActive Managers:\n");
    for (int i = 0; i < numPersonnel; i++) {
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
void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}
