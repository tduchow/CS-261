#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "toDoList.h"


int main (int argc, const char * argv[])
{
    Task *newTask;
    Task *firstTask;
    char desc[TASK_DESC_SIZE], filename[50], *nlptr;
    char cmd = ' ';
    FILE *filePointer;
    DynArr* mainList = createDynArr(10);

    printf("\n\n** TO-DO LIST APPLICATION **\n\n");
    
    do
        {
            printf("Press:\n"
                   "'l' to load to-do list from a file\n"
                   "'s' to save to-do list to a file\n"
                   "'a' to add a new task\n"
                   "'g' to get the first task\n"
                   "'r' to remove the first task\n"
                   "'p' to print the list\n"
                   "'e' to exit the program\n"
                   );
            /* get input command (from the keyboard) */
      cmd = getchar();
      /* clear the trailing newline character */
      while (getchar() != '\n');

      /* Fixme:  Your logic goes here! */
        switch (cmd)
        {
            case 'l': // load the to-do list
                printf("Please enter the filename: ");
                if (fgets(filename, sizeof(filename), stdin) != 0)
                {
                    nlptr = strchr(filename, '\n'); // remove the trailing newline
                    if (nlptr)
                    {
                        *nlptr = '\0';
                    }
                }
                filePointer = fopen(filename, "r"); /// open the file
                if (filePointer == 0)
                {
                    fprintf(stderr, "Cannot open %s\n", filename);
                    break;
                }
                loadList(mainList, filePointer); // load the list from the file
                fclose(filePointer); // close the file
                printf("The list has been successfully loaded from the file.\n\n");
                break;
                
            case 's': // save the to-do list
                printf("Please provide a filename: ");
                if (fgest(filename, sizeof(filename), stdin) != 0)
                {
                    nlptr = strchr(filename, '\n'); // remove the trailing newline
                    if (nlptr)
                    {
                        *nlptr = '\0';
                    }
                }
                filePointer = fopen(filename, "w"); // open the file
                if (filePointer == 0)
                {
                    fprintf(stderr, "Cannot open %s\n", filename);
                    break;
                }
                saveList(mainList, filePointer); // save the list to the file
                fclose(filePointer); // close the file
                printf("The list has been successfully saved to the file.\n\n");
                else
                    printf("Your to-do list is empty!\n\n");
                break;
                
            case 'a': // add a new task
                printf("Please enter the task description: \n");
                if (fgets(desc, sizeof(desc), stdin) != 0)
                {
                    nlptr = strchr(desc, '\n'); // remove the trailing newline
                    if (nlptr)
                    {
                        *nlptr = '\0';
                    }
                }
                do
                {
                    print("Please enter the task priority (0-999): ");
                    scanf("%d", &priority);
                } while (!(priority >= 0 && priority <= 999));
                while (getchar() != '\n'); // remove the trailing newline
                    
                newTask = createTask(priority, desc);
                addHeap(mainList, newTask);
                printf("Task successfully added to your to-do list.\n\n");
                break;
                
            case 'g': // get the first task to be completed
                if (sizeDynArr(mainList) > 0)
                {
                    firstTask = (Task *)getMinHeap(mainList);
                    printf("The first task to be completed is: %s\n\n", firstTask->description);
                }
                else
                    printf("Your to-do list is empty!\n\n");
                break;
                
            case 'r': // remove the first task
                if (sizeDynArr(mainList) > 0)
                {
                    firstTask = (Task *)getMinHeap(mainList);
                    removeMinHeap(mainList);
                    printf("The first task has been removed from the list: %s\n\n", firstTask->description);
                    free(firstTask);
                }
                else
                    printf("Your to-do list is empty!\n\n");
                break;
                
            case 'p': // print the to-do list
                if (sizeDynArr(mainList) > 0)
                {
                    printList(mainList);
                }
                else
                    printf("Your to-do list is empty!\n\n");
                break;
                
            case 'e': // exit the program
                printf("Closing To-Do List Application...\n\n");
                break;
                
            default:
                printf("Command not in the list, please press:\n"
                       "'l' to load to-do list from a file\n"
                       "'s' to save to-do list to a file\n"
                       "'a' to add a new task\n"
                       "'g' to get the first task\n"
                       "'r' to remove the first task\n"
                       "'p' to print the list\n"
                       "'e' to exit the program\n"
                       );
                break;
        }

      /* Note: We have provided functions called printList(), saveList() and loadList() for you
         to use.  They can be found in toDoList.c */
    }
    while(cmd != 'e');
    /* delete the list */
    deleteDynArr(mainList);

    return 0;
}
