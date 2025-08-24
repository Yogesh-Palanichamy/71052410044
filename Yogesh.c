#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Attendance {
    int studentID;
    char date[15];
    char status[10];   // "Present" or "Absent"
    struct Attendance *next;
} Attendance;

Attendance *head = NULL;

// Function to create new node
Attendance* createNode(int id, char date[], char status[]) {
    Attendance *newNode = (Attendance*)malloc(sizeof(Attendance));
    newNode->studentID = id;
    strcpy(newNode->date, date);
    strcpy(newNode->status, status);
    newNode->next = NULL;
    return newNode;
}

// Insert at end
void addRecord(int id, char date[], char status[]) {
    Attendance *newNode = createNode(id, date, status);
    if (head == NULL) {
        head = newNode;
    } else {
        Attendance *temp = head;
        while (temp->next != NULL) temp = temp->next;
        temp->next = newNode;
    }
    printf("Record added successfully!\n");
}

// Delete by (studentID + date)
void deleteRecord(int id, char date[]) {
    Attendance *temp = head, *prev = NULL;
    while (temp != NULL) {
        if (temp->studentID == id && strcmp(temp->date, date) == 0) {
            if (prev == NULL) head = temp->next;
            else prev->next = temp->next;
            free(temp);
            printf("Record deleted successfully!\n");
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("Record not found!\n");
}

// Search attendance
void searchRecord(int id, char date[]) {
    Attendance *temp = head;
    while (temp != NULL) {
        if (temp->studentID == id && strcmp(temp->date, date) == 0) {
            printf("Found -> ID: %d Date: %s Status: %s\n",
                   temp->studentID, temp->date, temp->status);
            return;
        }
        temp = temp->next;
    }
    printf("Record not found!\n");
}

// Display by date
void displayByDate(char date[]) {
    Attendance *temp = head;
    int found = 0;
    printf("Attendance for %s:\n", date);
    while (temp != NULL) {
        if (strcmp(temp->date, date) == 0) {
            printf("ID: %d | Status: %s\n", temp->studentID, temp->status);
            found = 1;
        }
        temp = temp->next;
    }
    if (!found) printf("No records for this date.\n");
}

// Recursive reverse display
void reverseDisplay(Attendance *node) {
    if (node == NULL) return;
    reverseDisplay(node->next);
    printf("ID: %d | Date: %s | Status: %s\n",
           node->studentID, node->date, node->status);
}

// Clone list
Attendance* cloneList(Attendance *head) {
    if (head == NULL) return NULL;
    Attendance *cloneHead = createNode(head->studentID, head->date, head->status);
    Attendance *currentClone = cloneHead;
    Attendance *currentOrig = head->next;

    while (currentOrig != NULL) {
        currentClone->next = createNode(currentOrig->studentID, currentOrig->date, currentOrig->status);
        currentClone = currentClone->next;
        currentOrig = currentOrig->next;
    }
    return cloneHead;
}

// Display full list
void displayAll(Attendance *node) {
    if (node == NULL) {
        printf("No records.\n");
        return;
    }
    while (node != NULL) {
        printf("ID: %d | Date: %s | Status: %s\n",
               node->studentID, node->date, node->status);
        node = node->next;
    }
}

int main() {
    int choice, id;
    char date[15], status[10];
    Attendance *clonedList = NULL;

    do {
        printf("\n--- Student Attendance Monitoring System ---\n");
        printf("1. Add Record\n2. Delete Record\n3. Search Record\n");
        printf("4. Display by Date\n5. Display in Reverse\n");
        printf("6. Clone Records\n7. Display All Records\n0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter Student ID: ");
            scanf("%d", &id);
            printf("Enter Date (dd-mm-yyyy): ");
            scanf("%s", date);
            printf("Enter Status (Present/Absent): ");
            scanf("%s", status);
            addRecord(id, date, status);
            break;
        case 2:
            printf("Enter Student ID: ");
            scanf("%d", &id);
            printf("Enter Date: ");
            scanf("%s", date);
            deleteRecord(id, date);
            break;
        case 3:
            printf("Enter Student ID: ");
            scanf("%d", &id);
            printf("Enter Date: ");
            scanf("%s", date);
            searchRecord(id, date);
            break;
        case 4:
            printf("Enter Date: ");
            scanf("%s", date);
            displayByDate(date);
            break;
        case 5:
            printf("Attendance Records in Reverse:\n");
            reverseDisplay(head);
            break;
        case 6:
            clonedList = cloneList(head);
            printf("Cloned Records:\n");
            displayAll(clonedList);
            break;
        case 7:
            printf("All Attendance Records:\n");
            displayAll(head);
            break;
        case 0:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice!\n");
        }
    } while (choice != 0);

    return 0;
}
