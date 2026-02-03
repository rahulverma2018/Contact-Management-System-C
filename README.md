# Contact Management System (C)

A console-based Contact Management System implemented in C, designed using modular programming principles.  
The application allows users to manage contacts efficiently with persistent storage using CSV files.

---

## Features
- Create new contacts with validation
- Search contacts by name, phone number, or email
- Edit existing contacts
- Delete contacts
- List all contacts
- Sort contacts by:
  - Name
  - Phone number
  - Email
- Prevent duplicate contacts (phone & email)
- Save and load contacts using a CSV file

---

## Project Structure
Contact_Management_System_C/
│
├── include/
│   ├── contact.h
│   ├── file.h
│   └── populate.h
│
├── src/
│   ├── main.c
│   ├── contact.c
│   ├── file.c
│   └── populate.c
│
├── .gitignore
├── build.bat
├── ContactsDatabase.csv
└── README.md

---

## Validation Rules
- Name: Alphabetic characters only (A–Z, a–z)
- Phone Number:
  - Exactly 10 digits
  - Must start with 6, 7, 8, or 9
  - Digits only
- Email:
  - Must follow standard email format  
    `example@domain.com`
- Duplicate Prevention:
  - Phone numbers must be unique
  - Email IDs must be unique

---

## File Storage
- Contacts are stored in a CSV file: `ContactsDatabase.csv`
- The file is automatically created if it does not exist
- Contacts are loaded into memory at program startup
- Contacts are saved back to the file on exit

---

## Technologies Used
- C Programming
- File Handling (CSV)
- Structures & Pointers
- Modular Programming (Header & Source files)
- GCC Compiler

---

## How to Build and Run

### Linux / macOS
```bash
gcc src/*.c -I include -o AddressBook
./AddressBook
```
