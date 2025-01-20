#ifndef REPOSITORY_H
#define REPOSITORY_H

#include "models.h"
#include <string.h> 

Client clients[MAX_ENTITIES];
Book books[MAX_ENTITIES];
Address addresses[MAX_ENTITIES];
Genre genres[MAX_ENTITIES];
Author authors[MAX_ENTITIES];
Loan loans[MAX_ENTITIES];
Admin adm[10];


/**
 * @brief Retrieves the first empty user from the clients array.
 *
 * This function iterates through the clients array and returns a pointer
 * to the first Client structure where the cpf field is equal to "0".
 *
 * @return Client* Pointer to the first empty Client structure, or NULL if no empty user is found.
 */
Client* getEmptyUser(){
    for(int i = 0 ; i < MAX_ENTITIES ; i++){
        if(!strcmp(clients[i].cpf, "0")){
            return &clients[i];
        }
    }
    return NULL;
}

/**
 * @brief Retrieves an empty book from the books array.
 *
 * This function iterates through the books array to find a book with an id of -1,
 * indicating that it is empty. Once found, it assigns the current index as the id
 * and returns a pointer to the empty book.
 *
 * @return Book* Pointer to the empty book if found, otherwise NULL.
 */
Book* getEmptyBook(){
    for(int i = 0 ; i < MAX_ENTITIES ; i++){
        if(books[i].id == -1){
            books[i].id = i;
            return &books[i];
        }
    }
    return NULL;
}

/**
 * @brief Retrieves an empty address from the addresses array.
 *
 * This function iterates through the addresses array to find an address
 * with an id of -1, indicating that it is empty. Once found, it assigns
 * the index value to the id field of the address and returns a pointer
 * to the address.
 *
 * @return Address* Pointer to the empty address if found, otherwise NULL.
 */
Address* getEmptyAddress(){
    for(int i = 0 ; i < MAX_ENTITIES ; i++){
        if(addresses[i].id == -1){
            addresses[i].id = i;
            return &addresses[i];
        }
    }
    return NULL;
}

/**
 * @brief Retrieves an empty Genre object from the genres array.
 *
 * This function iterates through the genres array to find an element with an id of -1,
 * indicating that it is empty. Once found, it assigns the current index as the id and
 * returns a pointer to the empty Genre object.
 *
 * @return Genre* Pointer to the empty Genre object if found, otherwise NULL.
 */
Genre* getEmptyGenre(){
    for(int i = 0 ; i < MAX_ENTITIES ; i++){
        if(genres[i].id == -1){
            genres[i].id = i;
            return &genres[i];
        }
    }
    return NULL;
}


/**
 * @brief Retrieves an empty Author object from the authors array.
 *
 * This function iterates through the authors array to find an Author object
 * with an id of -1, indicating that it is empty. Once found, it assigns the
 * current index as the id of the Author and returns a pointer to it.
 *
 * @return A pointer to an empty Author object if found, otherwise NULL.
 */
Author* getEmptyAuthor(){
    for(int i = 0 ; i < MAX_ENTITIES ; i++){
        if(authors[i].id == -1){
            authors[i].id = i;
            return &authors[i];
        }
    }
    return NULL;
}

/**
 * @brief Retrieves an empty loan from the list of loans.
 *
 * This function iterates through the array of loans and returns a pointer to the first loan
 * that has an id of -1, indicating it is empty. It also assigns the index value to the id of
 * the loan to mark it as occupied.
 *
 * @return Loan* Pointer to the empty loan if found, otherwise NULL.
 */
Loan* getEmptyLoan(){
    for(int i = 0 ; i < MAX_ENTITIES ; i++){
        if(loans[i].id == -1){
            loans[i].id = i;
            return &loans[i];
        }
    }
    return NULL;
}

/**
 * @brief Searches for an Address by its ID.
 *
 * This function iterates through a list of addresses and returns a pointer
 * to the Address structure that matches the given ID. If no matching address
 * is found, the function returns NULL.
 *
 * @param id The ID of the address to search for.
 * @return Address* Pointer to the Address structure if found, otherwise NULL.
 */
Address* SearchAddressById(int id) {
    for(int i = 0; i < MAX_ENTITIES; i++){
        if (addresses[i].id == id) {
            return &addresses[i];
        }
    }
    return NULL;
}

/**
 * @brief Searches for a client by their CPF (Cadastro de Pessoas Físicas).
 *
 * This function iterates through the list of clients and compares each client's CPF
 * with the provided CPF. If a match is found, a pointer to the corresponding client
 * is returned. If no match is found, the function returns NULL.
 *
 * @param cpf A string representing the CPF of the client to search for.
 * @return A pointer to the Client structure if a match is found, otherwise NULL.
 */
Client* SearchClientByCPF(char* cpf) {
    for(int i = 0; i < MAX_ENTITIES; i++){
        if (!strcmp(clients[i].cpf, cpf)) {
            return &clients[i];
        }
    }
    return NULL;
}

/**
 * @brief Searches for a client by name.
 *
 * This function iterates through the list of clients and compares each client's name
 * with the provided name. If a match is found, a pointer to the corresponding client
 * is returned.
 *
 * @param name The name of the client to search for.
 * @return A pointer to the client if found, otherwise NULL.
 */
Client* SearchClientByName(char* name) {
    for(int i = 0; i < MAX_ENTITIES; i++){
        if (!strcmp(clients[i].name, name)) {
            return &clients[i];
        }
    }
    return NULL;
}

/**
 * @brief Searches for a loan by its ID.
 *
 * This function iterates through the list of loans and returns a pointer to the loan
 * that matches the given ID. If no loan with the specified ID is found, the function
 * returns NULL.
 *
 * @param id The ID of the loan to search for.
 * @return A pointer to the loan with the specified ID, or NULL if no such loan is found.
 */
Loan* SearchLoanById(int id) {
    for(int i = 0; i < MAX_ENTITIES; i++){
        if (loans[i].id == id) {
            return &loans[i];
        }
    }
    return NULL;
}

/**
 * @brief Searches for a loan associated with a given client ID.
 *
 * This function iterates through an array of loans and checks if the 
 * userCpf of each loan matches the provided clientId. If a match is 
 * found and the loan's id is not -1, a pointer to the loan is returned.
 *
 * @param clientId A string representing the client's ID (CPF).
 * @return A pointer to the Loan structure if a matching loan is found, 
 *         otherwise NULL.
 */
Loan* SearchLoanByClient(char* clientId) {
    for(int i = 0; i < MAX_ENTITIES; i++){
        if (!strcmp(loans[i].userCpf, clientId) && loans[i].id != -1) {
            return &loans[i];
        }
    }
    return NULL;
}

/**
 * @brief Searches for a genre by its ID.
 *
 * This function iterates through an array of genres and returns a pointer to the genre
 * that matches the given ID. If no genre with the specified ID is found, the function
 * returns NULL.
 *
 * @param id The ID of the genre to search for.
 * @return A pointer to the genre with the specified ID, or NULL if no such genre is found.
 */
Genre* SearchGenreById(int id) {
    for(int i = 0; i < MAX_ENTITIES; i++){
        if (genres[i].id == id) {
            return &genres[i];
        }
    }
    return NULL;
}

/**
 * @brief Searches for an author by their ID.
 *
 * This function iterates through a list of authors and returns a pointer
 * to the author with the specified ID. If no author with the given ID is found,
 * the function returns NULL.
 *
 * @param id The ID of the author to search for.
 * @return A pointer to the Author with the specified ID, or NULL if no such author is found.
 */
Author* SearchAuthorById(int id) {
    for(int i = 0; i < MAX_ENTITIES; i++) {
        if (authors[i].id == id) {
            return &authors[i];
        }
    }
    return NULL;
}

/**
 * @brief Searches for an author by name.
 *
 * This function iterates through a list of authors and compares each author's name
 * with the provided name. If a match is found, a pointer to the corresponding Author
 * structure is returned. If no match is found, NULL is returned.
 *
 * @param name The name of the author to search for.
 * @return A pointer to the Author structure if a match is found, otherwise NULL.
 */
Author* SearchAuthorByName(char* name) {
    for(int i = 0; i < MAX_ENTITIES; i++) {
        if (!strcmp(authors[i].name, name)) {
            return &authors[i];
        }
    }
    return NULL;
}

/**
 * @brief Searches for a book by its ID.
 *
 * This function iterates through the list of books and returns a pointer to the book
 * that matches the given ID. If no book with the specified ID is found, the function
 * returns NULL.
 *
 * @param id The ID of the book to search for.
 * @return A pointer to the book with the specified ID, or NULL if no such book is found.
 */
Book* SearchBookById(int id) {
    for(int i = 0; i < MAX_ENTITIES; i++) {
        if (books[i].id == id) {
            return &books[i];
        }
    }
    return NULL;
}

/**
 * @brief Searches for a book by its title.
 *
 * This function iterates through the list of books and compares each book's title
 * with the provided title. If a match is found, it returns a pointer to the book.
 * If no match is found, it returns NULL.
 *
 * @param title The title of the book to search for.
 * @return A pointer to the book if found, otherwise NULL.
 */
Book* SearchBookByTitle(char* title) {
    for(int i = 0; i < MAX_ENTITIES; i++) {
        if (!strcmp(books[i].title, title)) {
            return &books[i];
        }
    }
    return NULL;
}

#endif