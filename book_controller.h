#ifndef BOOK_CONTROLLER_H
#define BOOK_CONTROLLER_H
#include "repository.h"
#include "genre_controller.h"
#include "author_controller.h"

/**
 * @brief Lists all the books in the system.
 *
 * This function iterates through the list of books and prints the details
 * of each book that has a valid ID. For each book, it displays the ID,
 * title, author name, genre, and stock information. The function waits for
 * user input before clearing the screen.
 */
void ListBooks() {
    printf("Books:\n");
    for (int i = 0; i < MAX_ENTITIES; i++) {
        if (books[i].id != -1) {
            printf("ID: %d, Title: %s\n", books[i].id, books[i].title);
            Author *a = SearchAuthorById(books[i].authorId);
            printf("Author: %s\n", a->name);
            Genre *g = SearchGenreById(books[i].genreId);
            printf("Genre: %s\n", g->genre);
            printf("Stock: %d / %d\n", books[i].stock, books[i].amount);
            printf("\n");
        }
    }
    printf("Type anything to continue...");
    getch();
    system("clear");
}
/**
 * @brief Displays a menu to search for a book by its ID and prints the book details.
 *
 * This function prompts the user to enter a book ID, searches for the book using the provided ID,
 * and displays the book's details including its title, author, genre, and stock information.
 * If the book, author, or genre is not found, appropriate messages are displayed.
 *
 * @note This function assumes the existence of the following functions:
 *       - fillBuffer(int size): Fills a buffer with user input.
 *       - SearchBookById(int id): Searches for a book by its ID and returns a pointer to the Book structure.
 *       - SearchAuthorById(int id): Searches for an author by their ID and returns a pointer to the Author structure.
 *       - SearchGenreById(int id): Searches for a genre by its ID and returns a pointer to the Genre structure.
 *
 * @note This function also assumes the existence of the following global variables:
 *       - buffer: A character array used to store user input.
 *
 * @note The Book, Author, and Genre structures should have the following fields:
 *       - Book: id, title, authorId, genreId, stock, amount
 *       - Author: id, name
 *       - Genre: id, genre
 */

void SearchBookByIdMenu() {
    int id;
    printf("Enter the book ID to search: ");
    fillBuffer(20);
    sscanf(buffer, "%d", &id);
    Book* b = SearchBookById(id);
    if (b == NULL) {
        printf("Book not found.\n");
    } else {
        Author* a = SearchAuthorById(b->authorId);
        Genre* g = SearchGenreById(b->genreId);
        printf("ID: %d\nTitle: %s\n", b->id, b->title);
        if (a && a->id != -1) {
            printf("Author: %s\n", a->name);
        } else {
            printf("Author not found.\n");
        }
        if (g && g->id != -1) {
            printf("Genre: %s\n", g->genre);
        } else {
            printf("Genre not found.\n");
        }
        printf("Stock: %d / %d\n", b->stock, b->amount);
    }
}

/**
 * @brief Displays a menu to search for a book by its title.
 * 
 * This function prompts the user to enter a book title, searches for the book
 * in the database, and displays the book's details if found. If the book is not
 * found, it notifies the user. The details displayed include the book's ID, title,
 * author, genre, and stock information.
 * 
 * @note This function relies on the following external functions:
 * - fillBuffer(size_t size): Fills a buffer with user input.
 * - SearchBookByTitle(const char* title): Searches for a book by its title.
 * - SearchAuthorById(int authorId): Searches for an author by their ID.
 * - SearchGenreById(int genreId): Searches for a genre by its ID.
 * 
 * @note The buffer used for storing the book title input is assumed to be a global
 * or external variable.
 */
void SearchBookByTitleMenu() {
    printf("Enter the book title to search: ");
    fillBuffer(40);
    Book* b = SearchBookByTitle(buffer);
    if (b == NULL) {
        printf("Book not found.\n");
    } else {
        Author* a = SearchAuthorById(b->authorId);
        Genre* g = SearchGenreById(b->genreId);
        printf("ID: %d\nTitle: %s\n", b->id, b->title);
        if (a && a->id != -1) {
            printf("Author: %s\n", a->name);
        } else {
            printf("Author not found.\n");
        }
        if (g && g->id != -1) {
            printf("Genre: %s\n", g->genre);
        } else {
            printf("Genre not found.\n");
        }
        printf("Stock: %d / %d\n", b->stock, b->amount);
    }
}

/**
 * @brief Displays a menu to search for books by author name.
 * 
 * This function prompts the user to enter an author name, searches for the author
 * in the database, and if found, lists all books by that author along with their
 * details such as ID, title, genre, and stock information.
 * 
 * @details
 * - Prompts the user to enter an author name.
 * - Searches for the author using the `SearchAuthorByName` function.
 * - If the author is found, iterates through the list of books and displays
 *   details for each book written by the author.
 * - If the author is not found, displays an appropriate message.
 * - For each book, the genre is retrieved using the `SearchGenreById` function.
 * 
 * @see SearchAuthorByName
 * @see SearchGenreById
 */
void SearchBookByAuthorMenu(void) {
    printf("Enter the author name to search: ");
    fillBuffer(40);
    Author* a = SearchAuthorByName(buffer);
    if (a == NULL) {
        printf("Author not found.\n");
    } else {
        for (int i = 0; i < MAX_ENTITIES; i++) {
            if (books[i].authorId == a->id && books[i].id != -1) {
                Genre* g = SearchGenreById(books[i].genreId);
                printf("ID: %d\nTitle: %s\n", books[i].id, books[i].title);
                printf("Author: %s\n", a->name);
                if (g && g->id != -1) {
                    printf("Genre: %s\n", g->genre);
                } else {
                    printf("Genre not found.\n");
                }
                printf("Stock: %d / %d\n", books[i].stock, books[i].amount);
                printf("\n");
            }
        }
    }
}

/**
 * @brief Displays the search book menu and handles user input for searching books by ID, title, or author.
 *
 * This function presents a menu to the user with options to search for a book by its ID, title, or author.
 * It reads the user's choice, clears the screen, and calls the appropriate function based on the user's selection.
 * If the user enters an invalid choice, an error message is displayed.
 * After the search operation, the user is prompted to type anything to continue, and the screen is cleared again.
 */
void SearchBookMenu() {
    int choice = 0;
    printf("Search by:\n1. ID\n2. Title\n3. Author\n");
    fillBuffer(1);
    sscanf(buffer, "%d", &choice);
    system("clear");

    switch (choice) {
        case 1:
            SearchBookByIdMenu();
            break;
        case 2:
            SearchBookByTitleMenu();
            break;
        case 3: {
            SearchBookByAuthorMenu();
            break;
        }
        default:
            printf("Invalid choice. Please try again.\n");
            break;
    }
    printf("Type anything to continue...");
    getch();
    system("clear");
}

/**
 * @brief Adds a new book to the system.
 * 
 * This function prompts the user to enter the details of a new book, including the title, author ID, genre ID, and the number of copies. 
 * It performs various checks to ensure the validity of the entered data, such as checking for duplicate titles, valid author IDs, and valid genre IDs.
 * If any of the checks fail, the function will notify the user and return without adding the book.
 * 
 * The function follows these steps:
 * 1. Prompts the user to enter the book's title and checks if a book with the same title already exists.
 * 2. Displays the list of available authors and prompts the user to enter the author ID.
 * 3. Checks if the entered author ID is valid.
 * 4. Displays the list of available genres and prompts the user to enter the genre ID.
 * 5. Checks if the entered genre ID is valid.
 * 6. Prompts the user to enter the number of copies and sets the book's stock to this number.
 * 7. If all checks pass, the book is successfully registered.
 * 
 * @note The function uses several helper functions such as `fillBuffer`, `SearchBookByTitle`, `SearchAuthorById`, and `SearchGenreById`.
 * @note The function uses global variables `buffer`, `authors`, `genres`, and constants like `MAX_ENTITIES`.
 * 
 * @return void
 */
void AddBook () {
    int k = 0;
    printf("Enter the new book's title: ");
    fillBuffer(40);
    Book* b = SearchBookByTitle(buffer);
    if(b){
        printf("A book with the same title already exists.\n");
        printf("Type anything to continue...");
        getch();
        system("clear");
        return;
    }
    strcpy(b->title, buffer);

    printf("Available authors:\n");
    for (int i = 0; i < MAX_ENTITIES; i++) {
        if (authors[i].id != -1) {
            k++;
            printf("ID: %d, Name: %s\n", authors[i].id, authors[i].name);
        }
    }
    if(k == 0) {
        b->id = -1;
        printf("No authors available. Please add an author first.\n");
        printf("Type anything to continue...");
        getch();
        system("clear");
        return;
    }

    printf("Enter the new book's author ID: ");
    fillBuffer(20);
    sscanf(buffer, "%d", &(b->authorId));
    Author* a = SearchAuthorById(b->authorId);
    if (!a || a->id == -1) {
        b->id = -1;
        printf("Invalid author ID. Please try again.\n");
        printf("Type anything to continue...");
        getch();
        system("clear");
        return;
    }

    k = 0;
    printf("Available genres:\n");
    for (int i = 0; i < MAX_ENTITIES; i++) {
        if (genres[i].id != -1) {
            k++;
            printf("ID: %d, Genre: %s\n", genres[i].id, genres[i].genre);
        }
    }

    if(k == 0) {
        b->id =  -1;
        printf("No genres available. Please add a genre first.\n");
        printf("Type anything to continue...");
        getch();
        system("clear");
        return;
    }

    printf("Enter the new book's genre ID: ");
    fillBuffer(20);
    sscanf(buffer, "%d", &(b->genreId));
    Genre* g = SearchGenreById(b->genreId);
    if (!g || g->id == -1) {
        b->id = -1;
        printf("Invalid genre ID. Please try again.\n");
        printf("Type anything to continue...");
        getch();
        system("clear");
        return;
    }

    printf("Enter the number of copies: ");
    fillBuffer(20);
    sscanf(buffer, "%d", &(b->amount));

    b->stock = b->amount;

    printf("Book successfully registered!!!\n");
    printf("Type anything to continue...");
    getch();
    system("clear");
}

/**
 * @brief Edits the details of a given book.
 *
 * This function allows the user to edit the title, author, and genre of a specified book.
 * It first clears the screen and displays the current title and author of the book.
 * The user is then prompted to confirm if they want to edit the book.
 * If confirmed, the user is prompted to enter a new title, select a new author from the list of available authors,
 * and select a new genre from the list of available genres.
 * The function performs validation checks to ensure the new title does not already exist (unless it belongs to the same book),
 * and that the selected author and genre IDs are valid.
 * If any validation fails, the function displays an error message and returns.
 * Upon successful update, a confirmation message is displayed.
 *
 * @param b Pointer to the Book structure to be edited.
 * @param a Pointer to the Author structure associated with the book.
 */
void EditBook(Book* b, Author* a) {
    system("clear");
    printf("%s\n%s", b->title, a->name);
    printf("\n\nEdit selected book? y/n");
    char choice = getchar();
    system("clear");

    if (choice == 'y' || choice == 'Y') {
        printf("Title: ");
        fillBuffer(40);
        Book* existingBook = SearchBookByTitle(buffer);
        if (existingBook && existingBook->id != b->id) {
            printf("A book with the same title already exists.\n");
            printf("Type anything to continue...");
            getch();
            system("clear");
            return;
        }
        strcpy(b->title, buffer);

        printf("Available authors:\n");
        for (int i = 0; i < MAX_ENTITIES; i++) {
            if (authors[i].id != -1) {
                printf("ID: %d, Name: %s\n", authors[i].id, authors[i].name);
            }
        }
        printf("Authors Id: ");
        fillBuffer(20);
        int authorId;
        sscanf(buffer, "%d", &authorId);
        Author* newAuthor = SearchAuthorById(authorId);
        if (!newAuthor || newAuthor->id == -1) {
            printf("Invalid author ID. Please try again.\n");
            printf("Type anything to continue...");
            getch();
            system("clear");
            return;
        }
        b->authorId = authorId;

        printf("Available genres:\n");
        for (int i = 0; i < MAX_ENTITIES; i++) {
            if (genres[i].id != -1) {
                printf("ID: %d, Genre: %s\n", genres[i].id, genres[i].genre);
            }
        }
        printf("Genre: ");
        fillBuffer(20);
        int genreId;
        sscanf(buffer, "%d", &genreId);
        Genre* newGenre = SearchGenreById(genreId);
        if (!newGenre || newGenre->id == -1) {
            printf("Invalid genre ID. Please try again.\n");
            printf("Type anything to continue...");
            getch();
            system("clear");
            return;
        }
        b->genreId = genreId;

        printf("Book details updated successfully.\n");
        printf("Type anything to continue...");
        getch();
        system("clear");
    }
}

/**
 * @brief Checks if a book is currently on loan.
 *
 * This function iterates through the list of loans and checks if the given book ID
 * matches either book1Id or book2Id in any of the loan records. If a match is found
 * and the loan record is valid (id is not -1), the function returns 1 indicating
 * that the book is on loan. Otherwise, it returns 0.
 *
 * @param bookId The ID of the book to check.
 * @return int Returns 1 if the book is on loan, otherwise returns 0.
 */
int IsBookOnLoan(int bookId) {
    for (int i = 0; i < MAX_ENTITIES; i++) {
        if ((loans[i].book1Id == bookId || loans[i].book2Id == bookId) && loans[i].id != -1) {
            return 1; 
        }
    }
    return 0;
}


/**
 * @brief Removes a book from the collection.
 *
 * This function prompts the user to enter the ID of the book they wish to remove.
 * If the book is currently on loan, it cannot be removed. The user is then asked
 * to confirm the removal and specify the quantity to remove. If the quantity to
 * remove is greater than or equal to the stock, the book is completely removed
 * from the collection. Otherwise, the specified quantity is deducted from the stock.
 *
 * @note The function uses several helper functions:
 * - fillBuffer(int size): Fills a buffer with user input.
 * - IsBookOnLoan(int id): Checks if the book with the given ID is currently on loan.
 * - SearchAuthorById(int id): Searches for an author by their ID.
 * - SearchGenreById(int id): Searches for a genre by its ID.
 *
 * @warning The function uses system calls like `system("clear")` and `getch()`, which
 * may not be portable across different operating systems.
 */
void RemoveBook() {
    Book v;
    int id = 0;

    strcpy(v.title, "\0");

    do {
        printf("Enter the id of the book you want to remove (type \"exit\" to go back): \n");
        fillBuffer(20);
        if (!strcmp("EXIT", buffer)) {
            system("clear");
            return;
        }
        sscanf(buffer, "%d", &id);

        for(int j = 0; j < MAX_ENTITIES; j++) {
            if(books[j].id == id) {
                if (IsBookOnLoan(id)) {
                    printf("The book is currently on loan and cannot be removed.\n");
                    printf("Type anything to continue...");
                    getch();
                    system("clear");
                    return;
                }
                int n;
                Author* a = SearchAuthorById(books[j].authorId);
                Genre* g = SearchGenreById(books[j].genreId);
                system("clear");
                printf("ID: %d\nTitle: %s\n", books[j].id, books[j].title);
                printf("Author: %s\n", a->name);
                printf("Genre: %s\n", g->genre);
                printf("Stock: %d / %d", books[j].stock, books[j].amount);
                printf("\n\n");
                printf("Enter the quantity of books you want to remove: ");
                fillBuffer(20);
                sscanf(buffer, "%d", &n);
                printf("\n\nAre you sure you want to remove? (Y or N) ");
                char x = getchar();

                if(x == 'Y' || x == 'y') {
                    if(n >= books[j].stock) {
                       books[j].stock = 0;
                       books[j].id = -1;
                       printf("Book removed from the collection.\n");
                       break;
                    }
                    books[j].stock -= n;
                    printf("%d books were removed from the collection.\n", n);
                    printf("Type anything to continue...");
                    getch();
                   break;
                }
                printf("Operation canceled.\n");
                printf("Type anything to continue...");
                getch();
                system("clear");
                break;
            }
        }
        system("clear");
        printf("Book not found. Try again...\n");
        printf("Type anything to continue...");
        getch();
        system("clear");
    } while(!strcmp("EXIT\0", buffer));
}

/**
 * @brief Updates the details of a book.
 *
 * This function prompts the user to enter a book ID to edit. If the user types "EXIT", the function will clear the screen and return. 
 * If a valid book ID is entered, the function searches for the book by its ID. If the book is found, it retrieves the author information 
 * and allows the user to edit the book details. The screen is cleared after the operation.
 *
 * @note The function uses a buffer to read user input and compares it to the string "EXIT" to determine if the user wants to exit.
 *       It also uses the `system("clear")` command to clear the screen.
 */
void UpdateBook() {
    int id;
    do {
        printf("Edit\n\nBook ID (or exit to leave): ");
        fillBuffer(20);
        if (!strcmp(buffer, "EXIT")) {
            system("clear");
            return;
        }
        sscanf(buffer, "%d", &id);

        Book* b = SearchBookById(id);

        if (b == NULL) {
            printf("Book not found!\n");
            printf("Type anything to continue...");
            getch();
            system("clear");
            continue;
        }
        Author* a = SearchAuthorById(b->authorId);
        EditBook(b, a);
        system("clear");
        break;
    } while(!strcmp(buffer, "EXIT"));
}

/**
 * @brief Displays the book edit menu and handles user input for editing options.
 *
 * This function presents a menu to the user with options to remove a book, update a book,
 * or go back to the previous menu. It reads the user's choice, clears the screen, and
 * executes the corresponding action based on the user's input.
 *
 * @note The function uses `getchar` to read user input and `sscanf` to parse the input into an integer.
 *       It also uses `system("clear")` to clear the console screen.
 *
 * @warning The function assumes that `RemoveBook`, `UpdateBook`, and `getch` are defined elsewhere in the codebase.
 *          It also assumes that `buffer` is a valid character array with sufficient size.
 */
void BookEditMenu() {
    int choice;
    printf("Edit\n\n1. Remove\n2. Update\n3. Back\n");
    buffer[0] = getchar();
    buffer[1] = '\0';
    sscanf(buffer, "%d",&choice);
    system("clear");
    switch(choice) {
        case 1:
            RemoveBook();
            break;
        case 2:
            UpdateBook();
            break;
        case 3:
            system("clear");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            printf("Type anything to continue...");
            getch();
            system("clear");
            break;
    }
}

/**
 * @brief Displays the book menu and handles user input for various book-related operations.
 * 
 * The menu provides the following options:
 * 1. List all books
 * 2. Display genres menu
 * 3. Display authors menu
 * 4. Search for a book
 * 5. Add a new book
 * 6. Edit an existing book
 * 7. Go back to the previous menu
 * 
 * The function uses a loop to repeatedly display the menu and process user input until the user chooses to go back.
 * It clears the screen after each operation and prompts the user to continue if an invalid choice is made.
 */
void BookMenu() {
    int choice = 0;
    do {
        printf("Book\n\n1. List\n2. Genres\n3. Authors\n4. Search\n5. Add\n6. Edit\n7. Back\n");
        fillBuffer(1);
        sscanf(buffer, "%d", &choice);
        system("clear");
        switch(choice) {
            case 1:
                ListBooks();
            break;
            case 2:
                GenreMenu();
            break;
            case 3:
                AuthorsMenu();
            break;
            case 4:
                SearchBookMenu();
            break;
            case 5:
                Book* b = getEmptyBook();
                if (!b) {
                    printf("Error creating book.\n");
                    printf("Type anything to continue...");
                    getch();
                    system("clear");
                    break;
                }
                AddBook(b);
                break;
            case 6:
                BookEditMenu();
            break;
            case 7:
                break;
            default:
                printf("Invalid choice. Please try again.\n");
            printf("Type anything to continue...");
            getch();
            system("clear");
            break;
        }
    } while(choice != 7);
}
#endif //BOOK_CONTROLLER_H
