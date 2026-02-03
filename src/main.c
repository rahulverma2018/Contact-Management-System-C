#include <stdio.h>
#include "contact.h"

int main() {
    int choice;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    do {
        printf("\nADDRESS BOOK MENU:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
        printf("6. Save and Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:
                printf("Select sort criteria:\n");
                printf("1. Sort by name\n");
                printf("2. Sort by phone\n");
                printf("3. Sort by email\n");
                printf("Enter your choice: ");
                int sortChoice;
                scanf("%d", &sortChoice);
                if(sortChoice<1 || sortChoice>3){
                    printf("------------------------------------------------------------------------------------------------------------------------------------\n");
                    printf("                                          ******* INVALID CHOICE *******                                                            \n");
                    printf("------------------------------------------------------------------------------------------------------------------------------------\n");
                    break;
                }
                listContacts(&addressBook, sortChoice);
                break;
            case 6:
                saveAndExit(&addressBook);
                break;
            default:
                printf("------------------------------------------------------------------------------------------------------------------------------------\n");
                printf("                                          ******* INVALID INPUT *******                                                             \n");
                printf("                                         ENTERED CHOICE MUST BE IN RANGE                                                            \n");
                printf("                                                   { [1-6] }                                                                        \n");
                printf("                                               PLEASE TRY AGAIN :)                                                                  \n");
                printf("------------------------------------------------------------------------------------------------------------------------------------\n");
                      
        }
    } while (choice != 6);
    
       return 0;
}
