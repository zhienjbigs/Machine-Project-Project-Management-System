
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