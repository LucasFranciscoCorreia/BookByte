#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <sys/stat.h>

#include "models.h"
#include "cstdin.h"

#include "repository.h"

#include "client_controller.h"
#include "book_controller.h"
#include "loan_controller.h"

/**
 * @brief Authenticates a user by comparing input login and password with stored credentials.
 *
 * This function prompts the user to enter a login and password, then checks these credentials
 * against a predefined list of administrator credentials. If a match is found, the function
 * returns 1, indicating successful authentication. Otherwise, it returns 0.
 *
 * @return int Returns 1 if the login and password match an administrator's credentials, otherwise returns 0.
 */
int login() {
    char log[20], pass[10];

    printf("Enter login: ");
    fillBuffer(20);
    sscanf(buffer, "%s", log);
    printf("Enter password: ");
    fillBuffer(10);
    sscanf(buffer, "%s", pass);
    for(int i = 0; i < 10; i++) {
        if (!strcmp(adm[i].login, log) && !strcmp(adm[i].password, pass)) {
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Imports data from binary files into the program's data structures.
 *
 * This function attempts to open several binary files containing data for clients, books, addresses, genres, users, authors, and loans.
 * If a file cannot be opened, it initializes the corresponding data structures with default values.
 * If a file is successfully opened, it reads the data into the corresponding data structures.
 *
 * The function handles the following files:
 * - "data/clients.bin": Contains client data.
 * - "data/books.bin": Contains book data.
 * - "data/addresses.bin": Contains address data.
 * - "data/genres.bin": Contains genre data.
 * - "data/users.bin": Contains user data.
 * - "data/authors.bin": Contains author data.
 * - "data/loans.bin": Contains loan data.
 *
 * The function initializes the following data structures if the files cannot be opened:
 * - clients: Initializes each client's fields to default values.
 * - books: Initializes each book's fields to default values.
 * - addresses: Initializes each address's fields to default values.
 * - genres: Initializes each genre's fields to default values.
 * - adm: Initializes each admin's login and password to default values, with the first admin having a predefined login and password.
 * - authors: Initializes each author's fields to default values.
 * - loans: Initializes each loan's fields to default values.
 *
 * The function reads data from the files into the following data structures if the files are successfully opened:
 * - clients: Reads client data from "data/clients.bin".
 * - books: Reads book data from "data/books.bin".
 * - addresses: Reads address data from "data/addresses.bin".
 * - genres: Reads genre data from "data/genres.bin".
 * - adm: Reads user data from "data/users.bin".
 * - authors: Reads author data from "data/authors.bin".
 * - loans: Reads loan data from "data/loans.bin".
 */
void ImportData(void) {
    int i;

    FILE *fclients = fopen("data/clients.bin", "rb");
    if (fclients == NULL) {
        for(i = 0 ; i < MAX_ENTITIES ; i++){
            strcpy(clients[i].cpf, "0\0");
            strcpy(clients[i].name, "0\0");
            strcpy(clients[i].deadline, "0\0");
            clients[i].addressId = -1;
            clients[i].bookId1 = -1;
            clients[i].bookId2 = -1;
            clients[i].fineAmount = 0;
        }
    }else{
        for(i=0;i<MAX_ENTITIES;i++){
            fread(&clients[i], sizeof(Client), 1, fclients);
        }
        fclose(fclients);
    }

    FILE *fbooks = fopen("data/books.bin", "rb");
    if(fbooks == NULL){
        for(i = 0 ; i < MAX_ENTITIES ; i++){
            strcpy(books[i].title, "0\0");
            books[i].authorId = -1;
            books[i].genreId = -1;
            books[i].stock = 0;
            books[i].id = -1;
            books[i].amount = 0;
            books[i].stock = 0;
        }        
    } else{
        for(i=0;i<MAX_ENTITIES;i++){
            fread(&books[i], sizeof(Book), 1, fbooks);
        }
        fclose(fbooks);
    }

    FILE *faddresses = fopen("data/addresses.bin", "rb");
    if(faddresses == NULL){
        for(i = 0 ; i < MAX_ENTITIES ; i++){
            strcpy(addresses[i].street, "0\0");
            strcpy(addresses[i].number, "0\0");
            strcpy(addresses[i].cep, "0\0");
            strcpy(addresses[i].complement, "0\0");
            addresses[i].id = -1;
        }
    } else{
        for(i=0;i<MAX_ENTITIES;i++){
            fread(&addresses[i], sizeof(Address), 1, faddresses);
        }
        fclose(faddresses);
    }

    FILE *fgenres = fopen("data/genres.bin", "rb");
    if(fgenres == NULL){
        for (i = 0 ; i < MAX_ENTITIES ; i++) {
            strcpy(genres[i].genre, "0\0");
            genres[i].id = -1;
        }
    } else {
        for(i=0;i<MAX_ENTITIES;i++){
            fread(&genres[i], sizeof(Address), 1, fgenres);
        }
        fclose(fgenres);
    }

    FILE* fusers = fopen("data/users.bin", "rb");
    if(fusers == NULL) {
        for (i = 0; i < 10 ; i++) {
            strcpy(adm[i].login, "\0");
            strcpy(adm[i].password, "\0");
        }
        strcpy(adm[0].login, "LUCAS\0");
        strcpy(adm[0].password, "12345\0");
    }else {
        for(i = 0; i < 10; i++) {
            fread(&adm[i], sizeof(Admin), 1, fusers);
        }
        fclose(fusers);
    }

    FILE* fauthors = fopen("data/authors.bin", "rb");
    if(fauthors == NULL) {
        for (i = 0; i < MAX_ENTITIES ; i++) {
            authors[i].id = -1;
            strcpy(authors[i].name, "\0");
        }
    }else {
        for(i = 0; i < MAX_ENTITIES; i++) {
            fread(&authors[i], sizeof(Author), 1, fauthors);
        }
        fclose(fauthors);
    }

    FILE* floans = fopen("data/loans.bin", "rb");
    if(floans == NULL) {
        for (i = 0; i < MAX_ENTITIES ; i++) {
            loans[i].id = -1;
            loans[i].book1Id = -1;
            loans[i].book2Id = -1;
            strcpy(loans[i].userCpf, "0\0");
            strcpy(loans[i].startDate, "0\0");
            strcpy(loans[i].deadline, "0\0");
        }
    }else {
        for(i = 0; i < MAX_ENTITIES; i++) {
            fread(&loans[i], sizeof(Loan), 1, floans);
        }
        fclose(floans);
    }
}

/**
 * @brief SaveData function saves the data of clients, books, addresses, genres, authors, and loans to binary files.
 *
 * This function creates a directory named "data" and then opens or creates binary files for clients, books, addresses, genres, authors, and loans.
 * It writes the data from the respective arrays to these files.
 * 
 * The function performs the following steps:
 * 1. Creates a directory named "data" with permissions 0777.
 * 2. Opens or creates "data/clients.bin" and writes the clients data to it.
 * 3. Opens or creates "data/books.bin" and writes the books data to it.
 * 4. Opens or creates "data/addresses.bin" and writes the addresses data to it.
 * 5. Opens or creates "data/genres.bin" and writes the genres data to it.
 * 6. Opens or creates "data/authors.bin" and writes the authors data to it.
 * 7. Opens or creates "data/loans.bin" and writes the loans data to it.
 *
 * If any file cannot be opened, an error message is printed using perror and the function returns early.
 *
 * @note The function assumes that the arrays clients, books, addresses, genres, authors, and loans are defined and populated elsewhere in the code.
 * @note The function assumes that MAX_ENTITIES is defined and represents the number of entities in each array.
 */
void SaveData(void) {
    int i;
    mkdir("data", 0777);
    FILE *fclients = fopen("data/clients.bin", "wb+");
    if (fclients == NULL) {
        perror("Error opening clients file");
        return;
    }
    fseek(fclients, 0, SEEK_SET);
    for( i = 0 ; i < MAX_ENTITIES ; i++) {
        fwrite(&clients[i], sizeof(Client), 1, fclients);
    }
    fclose(fclients);

    FILE *fbooks = fopen("data/books.bin", "wb+");
    fseek(fbooks, 0, SEEK_SET);
    for(i = 0 ; i < MAX_ENTITIES ; i++) {
        fwrite(&books[i], sizeof(Book), 1, fbooks);
    }
    fclose(fbooks);

    FILE *faddress= fopen("data/addresses.bin", "wb+");
    fseek(faddress, 0, SEEK_SET);
    for( i = 0 ; i < MAX_ENTITIES ; i++) {
        fwrite(&addresses[i], sizeof(Address), 1, faddress);
    }
    fclose(faddress);
    
    FILE *fgenres = fopen("data/genres.bin", "wb+");
    for(i = 0 ; i < MAX_ENTITIES ; i++){
        fwrite(&genres[i], sizeof(Address), 1, fgenres);
    }
    fclose(fgenres);

    FILE *fauthors = fopen("data/authors.bin", "wb+");
    for(i = 0 ; i < MAX_ENTITIES ; i++){
        fwrite(&authors[i], sizeof(Author), 1, fauthors);
    }
    fclose(fauthors);

    FILE *floans = fopen("data/loans.bin", "wb+");
    for(i = 0 ; i < MAX_ENTITIES ; i++){
        fwrite(&loans[i], sizeof(Loan), 1, floans);
    }
    fclose(floans);
}

/**
 * @brief Function to handle the main workflow of the system.
 * 
 * This function clears the console screen, displays a login success message,
 * and waits for user input to continue. It then presents a menu with options
 * for managing clients, books, and loans. The user can navigate through the
 * menu until they choose to exit. Upon exiting, the function saves the data.
 * 
 * @return int Returns 1 upon successful completion.
 */

int WorkSystem() {
    system("clear");
    printf("Login successful\n");
    printf("Type anything to continue...");
    getch();
    system("clear");
    int choice;

    do {
        printf("Menu\n\n1. Client\n2. Book\n3. Loan\n4. Exit\nOption: ");
        fillBuffer(1);
        sscanf(buffer, "%d", &choice);
        system("clear");
        if(choice==1){
            ClientMenu();
        } else if(choice==2) {
            BookMenu();
        } else if(choice==3) {
            ReservationMenu();
        }
    } while(choice!=4);
    SaveData();
    return 1;
}

/**
 * @file Projeto Programação.c
 * @brief Main program file for the Library Management System.
 * 
 * This file contains the main function which initializes the system,
 * handles user login, and manages the main workflow of the application.
 * 
 * @details
 * The program starts by importing necessary data and displaying a welcome message.
 * It then enters a loop where it prompts the user to log in. If the login is successful,
 * the program proceeds to the main system workflow. If the login fails, the user is
 * prompted to try again.
 * 
 * @note
 * Developed by DLRS.
 * 
 * @note
 * This program is intended to be run on a Linux system.
 * 
 * @return Returns 1 upon successful execution.
 */
int main()
{
    ImportData();
    printf("||||||Library||||||\n\n\n\n\n\ndeveloped by  DLRS\n\n\n\n\n");
    printf("Type anything to continue...");
    getch();
    system("clear");
    int exit = 0;
    while(!exit){
        if (login()){
            exit = WorkSystem();
        } else {
            system("clear");
            printf("Incorrect login or password\n");
            printf("Type anything to continue...");
            getch();
            system("clear");
        }
    }
    return 1;
}
