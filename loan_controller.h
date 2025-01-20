#ifndef RESERVATION_CONTROLLER_H_
#define RESERVATION_CONTROLLER_H_
#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <time.h>

#include "models.h"
#include "cstdin.h"
#include "repository.h"

/**
 * @brief Validates if the given date string is in the format YYYY-MM-DD.
 *
 * This function uses regular expressions to check if the input date string
 * matches the format YYYY-MM-DD, where YYYY is a 4-digit year, MM is a 2-digit
 * month, and DD is a 2-digit day.
 *
 * @param date A pointer to a null-terminated string representing the date to be validated.
 * @return Returns 1 if the date is in the valid format, otherwise returns 0.
 */
int isValidDateFormat(char* date) {
    regex_t regex;
    int result;

    result = regcomp(&regex, "^[0-9]{4}-[0-9]{2}-[0-9]{2}$", REG_EXTENDED);
    if (result) {
        fprintf(stderr, "Could not compile regex\n");
        return 0;
    }

    result = regexec(&regex, date, 0, NULL, 0);
    regfree(&regex);

    return !result;
}

/**
 * @brief Creates a loan menu for the user to input loan details.
 * 
 * This function prompts the user to enter the client's name, loan date, and book titles.
 * It performs various checks such as validating the client, ensuring the client does not already have an active loan,
 * and validating the date format. It also updates the stock of the books being loaned.
 * 
 * @note If the client is not found or already has an active loan, the function will terminate early.
 * 
 * @details
 * - Prompts the user to enter the client's name and searches for the client.
 * - Checks if the client already has an active loan.
 * - Prompts the user to enter the loan date and validates the date format.
 * - Prompts the user to enter the titles of the books to be loaned.
 * - Updates the stock of the books being loaned.
 * - Sets the loan deadline to 7 days from the start date.
 * - Displays a success message upon successful loan creation.
 * 
 * @return void
 */
void CreateLoanMenu() {
    Loan* l = getEmptyLoan();
    
    printf("Enter the client's name: ");
    fillBuffer(40);
    Client* c = SearchClientByName(buffer);
    if (c == NULL) {
        printf("Client not found.\n");
        l->id = -1;
        return;
    }
    strcpy(l->userCpf, c->cpf);

    // Check if the client already has an active loan
    Loan* existingLoan = SearchLoanByClient(c->cpf);
    if (existingLoan && existingLoan->id != -1) {
        printf("Client already has an active loan.\n");
        l->id = -1;
        return;
    }

    printf("Enter Loan date (YYYY-MM-DD) [Empty if today]: ");
    fillBuffer(20);
    if(buffer[0] != '\0' && !isValidDateFormat(buffer)) {
        printf("Invalid date format. Please use the format YYYY-MM-DD.\n");
        l->id = -1;
        return;
    }
    if(buffer[0] == '\0') {
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        snprintf(buffer, 20, "%04d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
    }
    strcpy(l->startDate, buffer);

    printf("Enter the first book's name: ");
    fillBuffer(40);
    Book* b = SearchBookByTitle(buffer);
    Book* b2 = NULL;
    l->book1Id = b->id;
    printf("Enter the second book's name (\"Enter\" if none): ");
    fillBuffer(40);
    if(buffer[0] != '\0') {
        b2 = SearchBookByTitle(buffer);
        l->book2Id = b2->id;
    } else {
        l->book2Id = -1;
    }
    struct tm tm = {0};
    sscanf(l->startDate, "%d-%d-%d", &tm.tm_year, &tm.tm_mon, &tm.tm_mday);
    tm.tm_year -= 1900;
    tm.tm_mon -= 1;
    tm.tm_mday += 7;
    mktime(&tm);
    strftime(buffer, 20, "%Y-%m-%d", &tm);
    strcpy(l->deadline, buffer);
    b->stock--;
    if(b2 && b2->id != -1){
        b2->stock--;
    }
    printf("Loan successfully added!\n");
    printf("Type anything to continue...");
    getch();
    system("clear");
}

/**
 * @brief Lists all the loans in the system.
 *
 * This function iterates through all the loan entities and prints the details
 * of each loan that has a valid ID. For each loan, it displays the loan ID,
 * client CPF, details of the first book, and if available, details of the second book.
 * It also prints the start date and deadline of the loan.
 *
 * The function waits for user input before clearing the screen.
 *
 * @note The function assumes that the `loans` array, `MAX_ENTITIES`, `SearchBookById` function,
 *       and `Book` structure are defined elsewhere in the code.
 */
void ListLoans() {
    printf("Loans:\n\n");
    for (int i = 0; i < MAX_ENTITIES;i++){
        if (loans[i].id != -1) {
            Book* b1 = SearchBookById(loans[i].book1Id);
            Book* b2 = SearchBookById(loans[i].book2Id);
            printf("Loan ID: %d\n", loans[i].id);
            printf("Client CPF: %s\n", loans[i].userCpf);
            printf("Book 1 : ID:%d Title:%s\n", b1->id, b1->title);
            if(b2 && b2->id != -1) {
                printf("Book 2 : ID:%d Title:%s\n", b2->id, b2->title);
            }
            printf("Start Date: %s\n", loans[i].startDate);
            printf("Deadline: %s\n", loans[i].deadline);
            printf("\n");
        }
    }
    printf("Type anything to continue...");
    getch();
    system("clear");
}

/**
 * @brief Handles the return of books by a client.
 *
 * This function prompts the user to enter the client's name, searches for the client and their loan,
 * updates the stock of the returned books, calculates any applicable fine based on the return date,
 * and marks the loan as returned.
 *
 * @note The function assumes the existence of several helper functions:
 * - fillBuffer(int size): Fills a buffer with user input.
 * - SearchClientByName(const char* name): Searches for a client by name.
 * - SearchLoanByClient(const char* cpf): Searches for a loan by client CPF.
 * - SearchBookById(int bookId): Searches for a book by its ID.
 *
 * @details
 * - If the client is not found, the function prints an error message and returns.
 * - If the loan is not found or does not belong to the client, the function prints an error message and returns.
 * - The stock of the returned books is incremented.
 * - The function calculates the fine based on the number of days late. The fine is $2.00 plus $0.50 for each day late.
 * - The loan is marked as returned by setting its ID to -1.
 * - The function prints the total fine and a success message.
 * - The function waits for user input before clearing the screen.
 */
void ReturnBookMenu() {
    printf("Enter the client's name to return books: ");
    fillBuffer(40);
    Client* c = SearchClientByName(buffer);
    if (c == NULL) {
        printf("Client not found.\n");
        return;
    }

    Loan* l = SearchLoanByClient(c->cpf);
    if (!l || l->id == -1) {
        printf("Loan not found or does not belong to the client.\n");
        return;
    }

    Book* b1 = SearchBookById(l->book1Id);
    Book* b2 = SearchBookById(l->book2Id);

    b1->stock++;
    if (b2 && b2->id != -1) {
        b2->stock++;
    }

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char currentDate[20];
    snprintf(currentDate, 20, "%04d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);

    char deadlineStr[20];
    strcpy(deadlineStr, l->deadline);
    struct tm deadlineTm = {0};
    int year, month, day;
    sscanf(deadlineStr, "%d-%d-%d", &year, &month, &day);

    deadlineTm.tm_year = year - 1900;
    deadlineTm.tm_mon = month - 1;
    deadlineTm.tm_mday = day;
    time_t deadlineTime = mktime(&deadlineTm);

    double seconds = difftime(t, deadlineTime);
    int daysLate = seconds / (60 * 60 * 24);
    double fine = 2.0 + (daysLate > 0 ? daysLate * 0.50 : 0);

    printf("The total fine is: $%.2f\n", fine);

    l->id = -1; // Mark the loan as returned
    printf("Books successfully returned!\n");
    printf("Type anything to continue...");
    getch();
    system("clear");
}

/**
 * @brief Displays the reservation menu and handles user input for loan operations.
 *
 * This function presents a menu to the user with options to list loans, create a loan,
 * return books, or go back. It processes the user's choice and calls the appropriate
 * function based on the selection. The menu continues to be displayed until the user
 * chooses to go back.
 *
 * @note The function uses a loop to repeatedly display the menu and process user input.
 *       It clears the screen after each input to provide a clean interface.
 *
 * @param void No parameters.
 *
 * @return void No return value.
 */
void ReservationMenu(void) {
    int choice;
    do {
        printf("Loan\n\n1. List Loans\n2. Create Loan\n3. Return Book(s)\n4. Back\n");
        fillBuffer(1);
        sscanf(buffer, "%d", &choice);
        system("clear");
        switch(choice) {
            case 1:
                ListLoans();
                break;
            case 2:
                CreateLoanMenu();
                break;
            case 3:
                ReturnBookMenu();
                break;
            case 4:
                // Handle return
                printf("Return selected.\n");
                // Add return handling code here
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }while(choice != 4);
}
#endif