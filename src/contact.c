#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

#include <stdbool.h>
#include <ctype.h>

bool isContactNameValid(char name[]);
bool isContactPhoneValid(char phone[]);
bool isContactEmailValid(char email[]);
bool isDuplicatePhone(AddressBook *addressBook, char phone[]);
bool isDuplicateEmail(AddressBook *addressBook, char email[]);

void listContacts(AddressBook *addressBook, int sortCriteria) {
    if(addressBook->contactCount==0){
        printf("No contacts to diplay!\n");
        return;
    }

    // Made a Copy of Contacts so that I don't change original order
    Contact tempContacts[MAX_CONTACTS];
    memcpy(tempContacts, addressBook->contacts, sizeof(Contact) * addressBook->contactCount);
    
    // Used Bubble Sort to sort the Contacts based on the choice
    for(int i=0;i<addressBook->contactCount-1;i++){
        for(int j=0;j<addressBook->contactCount-i-1;j++){
            int cmp = 0;
            if(sortCriteria==1){
                cmp = strcmp(tempContacts[j].name, tempContacts[j+1].name);
            }
            else if(sortCriteria==2){
                cmp = strcmp(tempContacts[j].phone, tempContacts[j+1].phone);
            }
            else if (sortCriteria==3){
                cmp = strcmp(tempContacts[j].email, tempContacts[j+1].email);
            }
            else{
                cmp = 0;
            }
            
            if(cmp>0){
                Contact temporary = tempContacts[j];
                tempContacts[j] = tempContacts[j+1];
                tempContacts[j+1] = temporary;
            }
        }
    }

    printf("\n");
    printf("----------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%-25s\t%-15s\t%-30s\n", "NAME", "PHONE NO.", "EMAIL");
    printf("----------------------------------------------------------------------------------------------------------------------------------------\n");
    
    // Sorted contacts based on the chosen criteria
    for(int i=0;i<addressBook->contactCount;i++){
        printf("%-25s\t%-15s\t%-30s\n", tempContacts[i].name, tempContacts[i].phone, tempContacts[i].email);
    }
    printf("----------------------------------------------------------------------------------------------------------------------------------------\n");

}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    loadContactsFromFile(addressBook);  // Load contacts from file during initialization
    
    /*
    if(addressBook->contactCount==0){
        populateAddressBook(addressBook);
    }  
    */  
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    printf("Saving and Exiting...\n");
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook) {
    int index = addressBook->contactCount;
    if(index >= MAX_CONTACTS){
        printf("Address book is full! Cannot add more contacts.\n");
        return;
    }
    printf("----------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("                                                    CREATE CONTACT                                                                      \n");
    printf("----------------------------------------------------------------------------------------------------------------------------------------\n");

    printf("Enter the name: ");
    scanf(" %[^\n]", addressBook->contacts[index].name);
    if(!isContactNameValid(addressBook->contacts[index].name)){
        printf("\n");
        printf("------------------------------------------------------------------------------------------------------------------------------------\n");
        printf("                                          ******* INVALID INPUT *******                                                             \n");
        printf("                                         ENTERED NAME SHOULD CONTAIN ONLY                                                           \n");
        printf("                                                 { [a-z] [A-Z] }                                                                    \n");
        printf("------------------------------------------------------------------------------------------------------------------------------------\n");
        return;    
    }

    printf("Enter the phone no: ");
    scanf(" %[^\n]", addressBook->contacts[index].phone);
    if(!isContactPhoneValid(addressBook->contacts[index].phone)){
        printf("\n");
        printf("------------------------------------------------------------------------------------------------------------------------------------\n");
        printf("                                          ******* INVALID INPUT *******                                                             \n");
        printf("                           ENTERED PHONE NO. SHOULD BE oF 10 DIGITS AND START WITH 6/7/8/9                                          \n");
        printf("------------------------------------------------------------------------------------------------------------------------------------\n");
        return;    
    }
    if(isDuplicatePhone(addressBook, addressBook->contacts[index].phone)){
        printf("\n");
        printf("------------------------------------------------------------------------------------------------------------------------------------\n");
        printf("                                      ******* DUPLICATE PHONE NUMBER *******                                                        \n");
        printf("                                         THIS PHONE NUMBER ALREADY EXISTS                                                           \n");
        printf("------------------------------------------------------------------------------------------------------------------------------------\n");
        return;    
    }

    printf("Enter the e-mail id: ");
    scanf(" %[^\n]", addressBook->contacts[index].email);
    if(!isContactEmailValid(addressBook->contacts[index].email)){
        printf("\n");
        printf("------------------------------------------------------------------------------------------------------------------------------------\n");
        printf("                                          ******* INVALID INPUT *******                                                             \n");
        printf("                                        ENTERED EMAIL MUST BE IN A FORMAT                                                           \n");
        printf("                                              [ example@domain.com ]                                                                \n");
        printf("------------------------------------------------------------------------------------------------------------------------------------\n");
        return;    
    }
    if(isDuplicateEmail(addressBook, addressBook->contacts[index].email)){
        printf("\n");
        printf("------------------------------------------------------------------------------------------------------------------------------------\n");
        printf("                                        ******* DUPLICATE EMAIL-ID *******                                                          \n");
        printf("                                           THIS EMAIL-ID ALREADY EXISTS                                                             \n");
        printf("------------------------------------------------------------------------------------------------------------------------------------\n");
        return;    
    }
    
    addressBook->contactCount++;
    printf("\n");
    printf("----------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("                                       ******* CONTACT CREATED SUCCESSFULLY *******                                                     \n");
    printf("----------------------------------------------------------------------------------------------------------------------------------------\n");  
}

void searchContact(AddressBook *addressBook) {
    if(addressBook->contactCount==0){
        printf("No contacts available!\n");
        return;
    }

    int choice;
    char searchKey[50];
    int found = 0;

    printf("\n");
    printf("SEARCH CONTACT MENU:\n");
    printf("1. Search by Name\n");
    printf("2. Search by Phone No.\n");
    printf("3. Search by Email\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice){
    case 1:
        printf("Enter name to search: ");
        scanf(" %[^\n]", searchKey);
        for(int i=0;i<addressBook->contactCount;i++){
            if(strcmp(addressBook->contacts[i].name, searchKey)==0){
                printf("\nContact Found:\n");
                printf("------------------------------------------------------------------------------------------------------------------------------------\n");
                printf("%-25s %-15s %-30s\n", "NAME", "PHONE NO.", "EMAIL");
                printf("------------------------------------------------------------------------------------------------------------------------------------\n");
                printf("%-25s %-15s %-30s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                printf("------------------------------------------------------------------------------------------------------------------------------------\n");
                found = 1;
            }
        }
        break;
    case 2:
        printf("Enter phone number to search: ");
        scanf(" %[^\n]", searchKey);
        for(int i=0;i<addressBook->contactCount;i++){
            if(strcmp(addressBook->contacts[i].phone, searchKey)==0){
                printf("\nContact Found:\n");
                printf("------------------------------------------------------------------------------------------------------------------------------------\n");
                printf("%-25s %-15s %-30s\n", "NAME", "PHONE NO.", "EMAIL");
                printf("------------------------------------------------------------------------------------------------------------------------------------\n");
                printf("%-25s %-15s %-30s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                printf("------------------------------------------------------------------------------------------------------------------------------------\n");
                found = 1;
            }
        }
        break;
    case 3:
        printf("Enter email to search: ");
        scanf(" %[^\n]", searchKey);
        for(int i=0;i<addressBook->contactCount;i++){
            if(strcmp(addressBook->contacts[i].email, searchKey)==0){
                printf("\nContact Found:\n");
                printf("------------------------------------------------------------------------------------------------------------------------------------\n");
                printf("%-25s %-15s %-30s\n", "NAME", "PHONE NO.", "EMAIL");
                printf("------------------------------------------------------------------------------------------------------------------------------------\n");
                printf("%-25s %-15s %-30s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                printf("------------------------------------------------------------------------------------------------------------------------------------\n");
                found = 1;
            }
        }
        break;    
    case 4:
        return;
        
    default:
        printf("------------------------------------------------------------------------------------------------------------------------------------\n");
        printf("                                          ******* INVALID CHOICE *******                                                            \n");
        printf("------------------------------------------------------------------------------------------------------------------------------------\n");
        return;
    }
    if(!found){
        printf("\nNo matching contact found!\n");
    }
}

void editContact(AddressBook *addressBook) {
	if(addressBook->contactCount==0){
        printf("No contacts available!\n");
        return;
    }

    int choice;
    char searchKey[50];
    int foundIndices[MAX_CONTACTS];
    int foundCount = 0;

    printf("\n");
    printf("EDIT CONTACT MENU:\n");
    printf("1. Search by Name\n");
    printf("2. Search by Phone No.\n");
    printf("3. Search by Email\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    
    if(choice<1 || choice>4){
        printf("------------------------------------------------------------------------------------------------------------------------------------\n");
        printf("                                          ******* INVALID CHOICE *******                                                            \n");
        printf("------------------------------------------------------------------------------------------------------------------------------------\n");
        return;
    }
    if(choice == 4) return;

    printf("Enter search value: ");
    scanf(" %[^\n]", searchKey);

    /*---------------------------------Searching Phase -----------------------------------*/
    for(int i=0;i<addressBook->contactCount;i++){
        if( (choice==1 && strcmp(addressBook->contacts[i].name, searchKey)==0) ||
            (choice==2 && strcmp(addressBook->contacts[i].phone, searchKey)==0) ||
            (choice==3 && strcmp(addressBook->contacts[i].email, searchKey)==0) ) {

                foundIndices[foundCount] = i;
                foundCount++;
                printf("\nContact Found:\n");
                printf("----------------------------------------------------------------------------------------------------------------------------------------\n");
                printf("%-5s %-25s %-15s %-30s\n", "No.", "NAME", "PHONE NO.", "EMAIL");
                printf("----------------------------------------------------------------------------------------------------------------------------------------\n");
                printf("%-5d %-25s %-15s %-30s\n", foundCount, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                printf("----------------------------------------------------------------------------------------------------------------------------------------\n");
        }   
    }
    if(foundCount==0){
        printf("\nNo matching contact found!\n");
    }

    /*---------------------------------Selecting Contact--------------------------------------*/
    int select;
    printf("\nSelect contact number to edit: ");
    scanf("%d", &select);
    
    if(select<1 || select>foundCount){
        printf("------------------------------------------------------------------------------------------------------------------------------------\n");
        printf("                                        ******* INVALID SELECTION *******                                                           \n");
        printf("------------------------------------------------------------------------------------------------------------------------------------\n");
        return;
    }

    int index = foundIndices[select-1];

    /*---------------------------------Editing Menu--------------------------------------*/
    printf("\nWHAT DO YOU WANT TO EDIT?\n");
    printf("1. Name\n");
    printf("2. Phone No.\n");
    printf("3. Email\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    
    switch (choice){
    case 1:
        printf("Enter new name: ");
        scanf(" %[^\n]", addressBook->contacts[index].name);

        if(!isContactNameValid(addressBook->contacts[index].name)){
            printf("Invalid Name!\n");
            return;
        }
        break;
    case 2:
        printf("Enter new phone number: ");
        scanf(" %[^\n]", addressBook->contacts[index].phone);

        if(!isContactPhoneValid(addressBook->contacts[index].phone)){
            printf("Invalid Phone Number!\n");
            return;
        }
        break;
    case 3:
        printf("Enter new email: ");
        scanf(" %[^\n]", addressBook->contacts[index].email);

        if(!isContactEmailValid(addressBook->contacts[index].email)){
            printf("Invalid Email!\n");
            return;
        }
        break;    
        
    default:
        printf("------------------------------------------------------------------------------------------------------------------------------------\n");
        printf("                                          ******* INVALID CHOICE *******                                                            \n");
        printf("------------------------------------------------------------------------------------------------------------------------------------\n");
        return;
    }
    printf("\n");
    printf("----------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("                                       ******* CONTACT UPDATED SUCCESSFULLY *******                                                     \n");
    printf("----------------------------------------------------------------------------------------------------------------------------------------\n");
}

void deleteContact(AddressBook *addressBook) {
	if(addressBook->contactCount==0){
        printf("No contacts available!\n");
        return;
    }

    int choice;
    char searchKey[50];
    int foundIndices[MAX_CONTACTS];
    int foundCount = 0;

    printf("\n");
    printf("DELETE CONTACT MENU:\n");
    printf("1. Delete by Name\n");
    printf("2. Delete by Phone No.\n");
    printf("3. Delete by Email\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    
    if(choice<1 || choice>4){
        printf("------------------------------------------------------------------------------------------------------------------------------------\n");
        printf("                                          ******* INVALID CHOICE *******                                                            \n");
        printf("------------------------------------------------------------------------------------------------------------------------------------\n");
        return;
    }
    if(choice == 4) return;

    printf("Enter search value: ");
    scanf(" %[^\n]", searchKey);

    /*---------------------------------Searching Phase -----------------------------------*/
    for(int i=0;i<addressBook->contactCount;i++){
        if( (choice==1 && strcmp(addressBook->contacts[i].name, searchKey)==0) ||
            (choice==2 && strcmp(addressBook->contacts[i].phone, searchKey)==0) ||
            (choice==3 && strcmp(addressBook->contacts[i].email, searchKey)==0) ) {

                foundIndices[foundCount] = i;
                foundCount++;
                printf("\nContact Found:\n");
                printf("----------------------------------------------------------------------------------------------------------------------------------------\n");
                printf("%-5s %-25s %-15s %-30s\n", "No.", "NAME", "PHONE NO.", "EMAIL");
                printf("----------------------------------------------------------------------------------------------------------------------------------------\n");
                printf("%-5d %-25s %-15s %-30s\n", foundCount, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                printf("----------------------------------------------------------------------------------------------------------------------------------------\n");
        }   
    }
    if(foundCount==0){
        printf("\nNo matching contact found!\n");
        return;
    }

    /*---------------------------------Selecting Contact--------------------------------------*/
    int select;
    printf("\nSelect contact number to delete: ");
    scanf("%d", &select);
    
    if(select<1 || select>foundCount){
        printf("------------------------------------------------------------------------------------------------------------------------------------\n");
        printf("                                        ******* INVALID SELECTION *******                                                           \n");
        printf("------------------------------------------------------------------------------------------------------------------------------------\n");
        return;
    }

    int index = foundIndices[select-1];

    /*---------------------------------Delete Confirmation--------------------------------------*/
    
    // Clear input buffer!
    int ch;
    while( (ch=getchar())!='\n' && ch != EOF);

    char confirm;
    printf("\nAre you sure you want to delete this contact? (y/n): ");
    scanf("%c", &confirm);

    if(confirm != 'y' && confirm != 'Y'){
        printf("Deletion Cancelled!\n");
        return;
    }

    /*----------------------------------Delete by Shifting----------------------------------------*/
    for(int i=index;i<addressBook->contactCount-1;i++){
        addressBook->contacts[i] = addressBook->contacts[i+1];
    }
    addressBook->contactCount--;

    printf("\n");
    printf("----------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("                                        ******* CONTACT DELETED SUCCESSFULLY *******                                                    \n");
    printf("----------------------------------------------------------------------------------------------------------------------------------------\n");
}


//--------------------------------------------Validation Functions Added :)-------------------------------------------------------
bool isContactNameValid(char name[]) {
    if(name[0]=='\0'){
        return false;
    }
    for(int i=0;name[i]!='\0';i++){
        if(!isalpha((unsigned char)name[i]) && name[i] != ' '){
            return false;
        }
    }
    return true;
}

bool isContactPhoneValid(char phone[]) {
    if(phone[0]=='\0'){
        return false;
    }

    // First digit must be 6,7,8 or 9
    if(phone[0] < '6' || phone[0] > '9'){
        return false;
    }    

    int count = 0;
    for(int i=0;phone[i]!='\0';i++){
        if(!isdigit((unsigned char)phone[i])){
            return false;
        }
        count++;
    }
    if(count!=10) return false;
    
    return true;
}

bool isContactEmailValid(char email[]) {
    if(email[0]=='\0'){
        return false;
    }

    int atIndex = -1;
    int dotIndex = -1;
    int len = strlen(email);

    //--------------------------------------// Count @ and locate it----------------------------------------------
    //--------------------------------------// Allowed characters only--------------------------------------------
    for(int i=0;i<len;i++){
        if(email[i]=='@'){
            if(atIndex!=-1){
                return false;
            }
            atIndex = i;
        }
        if( !(isalnum((unsigned char)email[i]) || email[i] == '@' || email[i]== '.') ){
            return false;
        }
    }

    if(atIndex==-1) return false;                         // no @ present
    if(atIndex==0 || atIndex==len-1) return false;        // @ cannot be first or last

    //---------------------------------------// dot must exist after @--------------------------------------------
    for(int i=atIndex+1;i<len;i++){
        if(email[i]=='.'){
            dotIndex = i;
            break;
        }
    }

    if(dotIndex==-1) return false;                         // no dot after @
    if(dotIndex==len-1) return false;                      // dot cannot be last
    if(len-dotIndex-1<2) return false;                     // atleast 2chars after dot
    
    //-------------------------------------// only one dot after @ is allowed-------------------------------------
    for(int i=dotIndex+1; i<len;i++){
        if(email[i]=='.'){
            return false;
        }
    }
    return true;
}

bool isDuplicatePhone(AddressBook *addressBook, char phone[]){
    for(int i=0;i<addressBook->contactCount;i++){
        if(strcmp(addressBook->contacts[i].phone, phone)==0){
            return true;
        }
    }
    return false;
}

bool isDuplicateEmail(AddressBook *addressBook, char email[]){
    for(int i=0;i<addressBook->contactCount;i++){
        if(strcmp(addressBook->contacts[i].email, email)==0){
            return true;
        }
    }
    return false;
}