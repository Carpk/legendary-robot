#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "orderList.h"

void addToList(order** head, char* name, int NumBurgers, int NumSalads, char* type) {
    order *currNode;
    currNode = *head;
    order* newNode;

    newNode = (order*)malloc(sizeof(order));
    newNode->name = name;
    newNode->salads = NumSalads;
    newNode->burgers = NumBurgers;
    strncpy(newNode->status, type, 8);
    newNode->next = NULL;

    if (currNode == NULL) {
        *head = newNode;
        return;
    }

    while(currNode->next != NULL) {
        currNode = (currNode)->next;
    }

    currNode->next = newNode;
}

bool doesNameExist(order* head, char* name){
    order* currNode;
    currNode = head;

    while (currNode != NULL) {
        if (strcmp(currNode->name, name) == 0) {
            return true;
        }
        currNode = currNode->next;
    }
    return false;
}

bool updateStatus(order* head, char* name) {
    order* currNode = head;
    while (currNode != NULL) {
        if (strcmp(currNode->name, name) == 0) {
            if (strcmp(currNode->status, "not in") == 0) {
                strncpy(currNode->status, "in", 8);
                return true;
            } else {
                return false;
            }
        }
        currNode = currNode->next;
    }
    return false;
}

char* retrieveAndRemove(order* head, int burgers, int salads) {
    char* name;
    order* currNode = head;
    order* preNode = NULL;

    while (currNode != NULL) {
        int numB = currNode->burgers;
        int numS = currNode->salads;

        if (numB <= burgers && numS <= salads) {
            if (preNode == NULL) {
                *head = currNode->next;
            } else {
                preNode->next = currNode->next;
            }

            /* Not sure what the prof wants, project description says to
             * return the name, so i guess i will free it after I return it */
            name = currNode->name;
            free(currNode);

            return name;
        }

        preNode = currNode;
        currNode = currNode->next;
    }

    return NULL;
}

int countOrdersAhead(order *head, char* name) {
    order* currNode = head;
    int count = 1;

    while (strcmp(currNode->name, name) != 0) {
        count++;
        currNode = currNode->next;
    }

    return count;
}

int displayWaitingTime(order *head, char* name) {
    order* currNode = head;
    int time = 0;

    while (strcmp(currNode->name, name) != 0) {
        time = time + (currNode->burgers * 5);
        time = time + (currNode->salads * 2);

        currNode = currNode->next;
    }

    return time;
}

void displayOrdersAhead (order* head, char name[30]) {
    order* currNode = head;

    while (strcmp(currNode->name, name) != 0) {
        printf("%s: %d burgers and %d salads\n",
               currNode->name, currNode->burgers, currNode->salads);
        currNode = currNode->next;
    }
}

void displayListInformation(order *head) {
    order* currNode = head;
    while (currNode != NULL) {
        printf("%s: %d burgers and %d salads, currently %s the restaurant.\n",
               currNode->name, currNode->burgers, currNode->salads, currNode->status);
        currNode = currNode->next;
    }
}
