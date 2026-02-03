#include <stdio.h>
#include <string.h>

#include "file.h"

#define FILE_NAME "ContactsDatabase.csv"

void saveContactsToFile(AddressBook *addressBook) {
    FILE *fptr = fopen(FILE_NAME, "w");
    if(fptr==NULL){
        printf("Error opening file for saving!\n");
        return;
    }

    fprintf(fptr, "NAME,PHONE NO.,EMAIL\n");
    for(int i=0;i<addressBook->contactCount;i++){
        fprintf(fptr, "%s,%s,%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
    fclose(fptr);
}

void loadContactsFromFile(AddressBook *addressBook) {
    FILE *fp = fopen(FILE_NAME, "r");
    if(fp==NULL){
        return;         // File does not exist yet!!
    }

    char line[200];                                     // line is just a temporary string.
    fgets(line, sizeof(line), fp);                      // Read & Skips header line (NAME,PHONE NO.,EMAIL).
    while(fgets(line, sizeof(line), fp)){               // Read each contact line and fgets() only reads text into a temporary buffer, NOT into address book.
        if(addressBook->contactCount>=MAX_CONTACTS){
            break;
        }

        Contact *c = &addressBook->contacts[addressBook->contactCount];  // Contact *c helps to store parsed data permanently inside the address book.
        
        char *token = strtok(line, ",");
        if(token==NULL){
            continue;
        }
        strcpy(c->name, token);

        token = strtok(NULL, ",");
        if(token==NULL){
            continue;
        }
        strcpy(c->phone, token);
        
        token = strtok(NULL, ",\n");
        if(token==NULL){
            continue;
        }
        strcpy(c->email, token);

        addressBook->contactCount++;
    }
    fclose(fp);
}
