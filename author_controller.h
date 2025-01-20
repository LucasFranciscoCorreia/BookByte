#ifndef AUTHOR_CONTROLLER_H
#define AUTHOR_CONTROLLER_H
#include "models.h"

/**
 * @brief Lists all authors stored in the authors array.
 * 
 * This function iterates through the authors array and prints the ID and name
 * of each author whose ID is not -1. After listing all authors, it prompts the
 * user to type anything to continue and then clears the console screen.
 * 
 * @note The function assumes that the authors array and MAX_ENTITIES are defined
 *       elsewhere in the code. It also uses the getch() function to wait for
 *       user input and the system("clear") command to clear the console.
 */
void ListAuthors() {
    printf("Authors:\n");
    for (int i = 0; i < MAX_ENTITIES; i++) {
        if (authors[i].id != -1) {
            printf("ID: %d, Name: %s\n", authors[i].id, authors[i].name);
        }
    }
    printf("Type anything to continue...");
    getch();
    system("clear");
}

/**
 * @brief Adds a new author to the system.
 *
 * This function prompts the user to enter a new author's name, checks if an author
 * with the same name already exists, and if not, adds the new author to the system.
 * If an author with the same name exists, it notifies the user and exits. If there
 * are no empty slots available for a new author, it notifies the user and exits.
 *
 * The function uses the following helper functions:
 * - fillBuffer(int size): Fills a buffer with user input.
 * - SearchAuthorByName(const char* name): Searches for an author by name.
 * - getEmptyAuthor(): Retrieves an empty author slot.
 *
 * The function also uses the following global variables:
 * - buffer: A buffer to store the author's name.
 *
 * @note The function clears the console screen after each user interaction.
 */
void AddAuthor() {
    printf("Enter the new author's name: ");
    fillBuffer(40);
    Author* a = SearchAuthorByName(buffer);
    if(a){
        printf("An author with the same name already exists.\n");
        printf("Type anything to continue...");
        getch();
        system("clear");
        return;
    }

    a = getEmptyAuthor();
    if (!a) {
        printf("No empty author slot available.\n");
        printf("Type anything to continue...");
        getch();
        system("clear");
        return;
    }

    strcpy(a->name, buffer);
    printf("Author successfully added!\n");
    printf("Type anything to continue...");
    getch();
    system("clear");
}

/**
 * @brief Updates the name of an existing author based on the provided author ID.
 * 
 * This function prompts the user to enter an author ID and searches for the author
 * in the authors array. If the author is found, it displays the current author details
 * and prompts the user to enter a new name. If an author with the new name already exists,
 * it notifies the user and exits. Otherwise, it updates the author's name and confirms
 * the update.
 * 
 * @note The function uses `fillBuffer` to read user input and `SearchAuthorByName` to check
 * for duplicate author names.
 * 
 * @warning The function assumes that `fillBuffer`, `SearchAuthorByName`, `authors`, `MAX_ENTITIES`,
 * and `buffer` are defined and properly initialized elsewhere in the code.
 */
void UpdateAuthor() {
    int id;
    printf("Enter the author ID to update: ");
    fillBuffer(20);
    sscanf(buffer, "%d", &id);
    for (int i = 0; i < MAX_ENTITIES; i++) {
        if (authors[i].id == id) {
            printf("%d %s\n", authors[i].id, authors[i].name);
            printf("Enter the new author name: ");
            fillBuffer(40);
            Author* existingAuthor = SearchAuthorByName(buffer);
            if (existingAuthor) {
                printf("An author with the same name already exists.\n");
                printf("Type anything to continue...");
                getch();
                system("clear");
                return;
            }
            strcpy(authors[i].name, buffer);
            printf("%d %s\n", authors[i].id, authors[i].name);
            printf("Author successfully updated!\n");
            printf("Type anything to continue...");
            getch();
            system("clear");
            return;
        }
    }
    printf("Author not found.\n");
    printf("Type anything to continue...");
    getch();
    system("clear");
}

/**
 * @brief Removes an author from the list of authors.
 *
 * This function displays a list of authors and prompts the user to enter the ID of the author to remove.
 * If the author has any associated books, the removal is aborted and a message is displayed.
 * Otherwise, the author is removed from the list.
 *
 * @note The function uses `fillBuffer` to read user input and `sscanf` to parse the author ID.
 *       It also uses `getch` to wait for user input before clearing the screen with `system("clear")`.
 *
 * @warning The function assumes that `authors` and `books` arrays, `MAX_ENTITIES`, and `buffer` are defined globally.
 *          The function also assumes that `fillBuffer` and `getch` are defined elsewhere in the code.
 */
void RemoveAuthor() {
    int id;
    printf("Authors:\n");
    for (int i = 0; i < MAX_ENTITIES; i++) {
        if (authors[i].id != -1) {
            printf("ID: %d, Name: %s\n", authors[i].id, authors[i].name);
        }
    }
    printf("Enter the author ID to remove: ");
    fillBuffer(20);
    sscanf(buffer, "%d", &id);
    for (int i = 0; i < MAX_ENTITIES; i++) {
        if (authors[i].id == id) {
            // Check if there are books from the author
            for (int j = 0; j < MAX_ENTITIES; j++) {
                if (books[j].authorId == id) {
                    printf("Cannot remove author. There are books from this author.\n");
                    printf("Type anything to continue...");
                    getch();
                    system("clear");
                    return;
                }
            }
            authors[i].id = -1;
            strcpy(authors[i].name, "0\0");
            printf("Author successfully removed!\n");
            printf("Type anything to continue...");
            getch();
            system("clear");
            return;
        }
    }
    printf("Author not found.\n");
    printf("Type anything to continue...");
    getch();
    system("clear");
}


/**
 * @brief Displays the Authors Menu and handles user input for various author-related operations.
 *
 * This function presents a menu to the user with options to list authors, add a new author,
 * update an existing author, remove an author, or go back to the previous menu. The user input
 * is read and the corresponding function is called based on the user's choice.
 *
 * @note The function uses a loop to repeatedly display the menu until the user chooses to go back.
 *
 * @param None
 * @return None
 */
void AuthorsMenu() {
    int choice;
    do {
        printf("Authors Menu\n\n1. List Authors\n2. Add Author\n3. Update Author\n4. Remove Author\n5. Back\nOption: ");
        fillBuffer(1);
        sscanf(buffer, "%d", &choice);
        system("clear");
        switch (choice) {
            case 1:
                ListAuthors();
            break;
            case 2:
                AddAuthor();
            break;
            case 3:
                UpdateAuthor();
            break;
            case 4:
                RemoveAuthor();
            break;
            case 5:
                break;
            default:
                printf("Invalid choice. Please try again.\n");
            printf("Type anything to continue...");
            getch();
            system("clear");
            break;
        }
    } while (choice != 5);
}

#endif