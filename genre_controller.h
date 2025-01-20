#ifndef GENRE_CONTROLLER_H
#define GENRE_CONTROLLER_H
#include "models.h"

/**
 * @brief Removes a genre from the list of genres.
 *
 * This function displays a list of genres and prompts the user to enter the ID of the genre to remove.
 * It checks if any books are associated with the specified genre. If there are books associated with the genre,
 * the function will not remove the genre and will notify the user. If no books are associated with the genre,
 * the function will remove the genre by setting its ID to -1 and its name to "0".
 */
void RemoveGenre() {
    int id;
    printf("Genres:\n");
    for (int i = 0; i < MAX_ENTITIES; i++) {
        if (genres[i].id != -1) {
            printf("ID: %d, Genre: %s\n", genres[i].id, genres[i].genre);
        }
    }
    printf("Enter the genre ID to remove: ");
    fillBuffer(20);
    sscanf(buffer, "%d", &id);
    
    // Check if any book has this genre
    for (int i = 0; i < MAX_ENTITIES; i++) {
        if (books[i].genreId == id) {
            printf("Cannot remove genre. There are books associated with this genre.\n");
            printf("Type anything to continue...");
            getch();
            system("clear");
            return;
        }
    }

    for (int i = 0; i < MAX_ENTITIES; i++) {
        if (genres[i].id == id) {
            genres[i].id = -1;
            strcpy(genres[i].genre, "0\0");
            printf("Genre successfully removed!\n");
            printf("Type anything to continue...");
            getch();
            system("clear");
            return;
        }
    }
    printf("Genre not found.\n");
    printf("Type anything to continue...");
    getch();
    system("clear");
}

/**
 * @brief Updates the genre name for a given genre ID.
 *
 * This function prompts the user to enter a genre ID and then searches for the genre
 * with the specified ID in the genres array. If found, it displays the current genre
 * name and prompts the user to enter a new genre name. It then checks if the new genre
 * name already exists in the genres array (excluding the current genre). If the new
 * genre name is unique, it updates the genre name and confirms the update to the user.
 * If the genre ID is not found or the new genre name already exists, appropriate
 * messages are displayed.
 */
void UpdateGenre() {
    int id;
    printf("Enter the genre ID to update: ");
    fillBuffer(20);
    sscanf(buffer, "%d", &id);
    for (int i = 0; i < MAX_ENTITIES; i++) {
        if (genres[i].id == id) {
            printf("%d %s\n", genres[i].id, genres[i].genre);
            printf("Enter the new genre name: ");
            fillBuffer(40);
            
            // Check if the new genre name already exists
            for (int j = 0; j < MAX_ENTITIES; j++) {
                if (!strcmp(genres[j].genre, buffer) && genres[j].id != id) {
                    printf("Genre name already exists. Please try again.\n");
                    printf("Type anything to continue...");
                    getch();
                    system("clear");
                    return;
                }
            }
            
            strcpy(genres[i].genre, buffer);
            printf("%d %s\n", genres[i].id, genres[i].genre);
            printf("Genre successfully updated!\n");
            printf("Type anything to continue...");
            getch();
            system("clear");
            return;
        }
    }
    printf("Genre not found.\n");
    printf("Type anything to continue...");
    getch();
    system("clear");
}

/**
 * @brief Lists all genres stored in the genres array.
 *
 * This function iterates through the genres array and prints the ID and genre
 * name for each genre that has a valid ID (not equal to -1). After listing all
 * genres, it prompts the user to type anything to continue and then clears the
 * console screen.
 *
 */
void ListGenres() {
    printf("Genres:\n");
    for (int i = 0; i < MAX_ENTITIES; i++) {
        if (genres[i].id != -1) {
            printf("ID: %d, Genre: %s\n", genres[i].id, genres[i].genre);
        }
    }
    printf("Type anything to continue...");
    getch();
    system("clear");
}

/**
 * @brief Adds a new genre to the list of genres.
 * 
 * This function prompts the user to enter a new genre name and adds it to the list of genres if an empty slot is available.
 * It also checks if the genre name already exists to avoid duplicates.
 * 
 * @details
 * - If no empty genre slot is available, the function prints an error message and waits for user input before returning.
 * - If the genre name already exists, the function prints an error message and waits for user input before returning.
 * - If the genre name is successfully added, the function prints a success message and waits for user input before clearing the screen.
 */
void AddGenre() {
    Genre* g = getEmptyGenre();
    if (!g) {
        printf("No empty genre slot available.\n");
        printf("Type anything to continue...");
        getch();
        return;
    }
    printf("Enter the new genre name: ");
    fillBuffer(40);

    // Check if the genre name already exists
    for (int i = 0; i < MAX_ENTITIES; i++) {
        if (!strcmp(genres[i].genre, buffer) && genres[i].id != -1) {
            printf("Genre name already exists. Please try again.\n");
            printf("Type anything to continue...");
            getch();
            system("clear");
            return;
        }
    }

    strcpy(g->genre, buffer);
    printf("Genre successfully added!\n");
    printf("Type anything to continue...");
    getch();
    system("clear");
}

/**
 * @brief Displays the Genre Menu and handles user input for various genre-related operations.
 *
 * This function presents a menu to the user with options to list, add, update, or remove genres.
 * The user can also choose to go back to the previous menu. The function loops until the user
 * selects the option to go back.
 *
 * Menu options:
 * 1. List Genres - Calls the ListGenres() function to display all genres.
 * 2. Add Genre - Calls the AddGenre() function to add a new genre.
 * 3. Update Genre - Calls the UpdateGenre() function to update an existing genre.
 * 4. Remove Genre - Calls the RemoveGenre() function to remove an existing genre.
 * 5. Back - Exits the menu and returns to the previous menu.
 *
 * The function uses a buffer to read user input and clears the screen after each operation.
 * If an invalid choice is entered, an error message is displayed and the user is prompted to try again.
 */

void GenreMenu() {
    int choice;
    do {
        printf("Genre Menu\n\n1. List Genres\n2. Add Genre\n3. Update Genre\n4. Remove Genre\n5. Back\nOption: ");
        fillBuffer(1);
        sscanf(buffer, "%d", &choice);
        system("clear");
        switch (choice) {
            case 1:
                ListGenres();
            break;
            case 2:
                AddGenre();
            break;
            case 3:
                UpdateGenre();
            break;
            case 4:
                RemoveGenre();
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