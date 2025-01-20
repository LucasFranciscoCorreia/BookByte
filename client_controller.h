#ifndef CLIENT_CONTROLLER_H
#define CLIENT_CONTROLLER_H
#include "models.h"
#include "cstdin.h"
#include "repository.h"


/**
 * @brief Displays a menu to search for a client by name and shows the client's details.
 *
 * This function prompts the user to enter a client's name, searches for the client by name,
 * and displays the client's CPF and address details if found. If the address is not found,
 * it notifies the user. The function waits for user input before clearing the screen.
 *
 * @note This function uses the global buffer to store the client's name input.
 */
void SearchClientByNameMenu() {
    printf("Enter the client's name: ");
    fillBuffer(20);
    Client *c = SearchClientByName(buffer);
    printf("CPF: %s\n", c->cpf);
    Address *add = SearchAddressById(c->addressId);
    if(add && add->id != -1) {
        printf("Street: %s, Number: %s, Complement: %s\n", add->street, add->number, add->complement);
        printf("CEP: %s  \n", add->cep);
        printf("\n");
    } else {
        printf("Address not found.\n");
    }
    printf("Type anything to continue...");
    getch();
    system("clear");
}

/**
 * @brief Displays a menu to search for a client by their CPF (Cadastro de Pessoas Físicas).
 * 
 * This function clears the screen, prompts the user to enter a CPF, and searches for a client
 * with the entered CPF in the clients array. If a matching client is found, their details
 * including name, CPF, and address (if available) are displayed. If no matching client is found,
 * a message indicating that the client was not found is displayed.
 * 
 */
void SearchClientByCPFMenu() {
    int k = 0;
    char cpf[12];
    system("clear");
    printf("Enter the client's CPF: ");
    fillBuffer(12);
    strcpy(cpf, buffer);
    for(int j = 0; j < MAX_ENTITIES; j++) {
        if(!strcmp(clients[j].cpf, cpf) && strcmp(clients[j].cpf, "0")) {
            Address *add = SearchAddressById(clients[j].addressId);
            printf("Name: %s\n", clients[j].name);
            printf("CPF: %s\n", clients[j].cpf);
            if(add && add->id != -1) {
                printf("Street: %s, Number: %s, Complement: %s\n", add->street, add->number, add->complement);
                printf("CEP: %s  ", add->cep);
                printf("\n\n");
            } else {
                printf("Address not found.\n");
            }
            return;
        }
    }
    printf("Client not found.\n");
    printf("type anything to continue...");
    getch();
    system("clear");
}

/**
 * @brief Displays a menu to search for clients by their street address.
 * 
 * This function prompts the user to enter a street name, searches for clients
 * living at that address, and displays the details of the clients found.
 * 
 * @note The function uses global variables `addresses`, `clients`, and `buffer`.
 * 
 * @details
 * - Prompts the user to enter a street name.
 * - Searches the `addresses` array for a matching street name.
 * - If the address is found, it searches the `clients` array for clients living at that address.
 * - Displays the details of the clients found.
 * - If no address is found, it notifies the user and returns.
 * 
 * @return void
 */

void SearchClientByAddressMenu() {
    int j, k = 0;
    char street[40];

    int id = -1;

    printf("Enter the client's street: ");
    fillBuffer(40);
    strcpy(street, buffer);

    for(j = 0; j < MAX_ENTITIES; j++) {
        if(!strcmp(addresses[j].street, street) && strcmp(clients[j].cpf, "0")) {
            id = addresses[j].id;
            break;
        }
    }

    if(id == -1) {
        printf("Address not found.\n");
        printf("Type anything to continue...");
        getch();
        system("clear");
        return;
    }

    Address *add = SearchAddressById(id);

    for(j = 0; j < MAX_ENTITIES; j++) {
        if(strcmp(clients[j].cpf, "0") && clients[j].addressId == add->id) {
            k++;
        }
    }

    system("clear");
    
    printf("\nFound %d clients living at this address: \n", k);
    
    int v = 1;
    for(j = 0; j < MAX_ENTITIES; j++) {
        if (strcmp(clients[j].cpf, "0") && clients[j].addressId == add->id) {
            printf("%d:\nName: %s\n", v++, clients[j].name);
            printf("CPF: %s\n", clients[j].cpf);
            printf("Street: %s, Number: %s, Complement: %s\n", add->street, add->number, add->complement);
            printf("CEP: %s\n", add->cep);
            printf("\n");
        }
    }
    printf("Type anything to continue...");
    getch();
    system("clear");
}


/**
 * @brief Searches for a user based on the given criteria.
 * 
 * @param i The search criteria:
 *          1 - Search by Name
 *          2 - Search by CPF
 *          3 - Search by Address
 *          4 - 
 * If the search criteria is invalid, an error message is displayed.
 * The screen is cleared after the search operation.
 */
void SearchClient(int i) {
    if(i == 1) {
        SearchClientByNameMenu();
    } else if(i == 2) {
        SearchClientByCPFMenu();
    } else if(i == 3) {
        SearchClientByAddressMenu();
    } else if(i==4) {

    }
    else {
        printf("Invalid Option!\n");
        printf("Type anything to continue...");
        getch();
    }
    system("clear");
}

/**
 * @brief Adds a new client to the system.
 *
 * This function prompts the user to enter the new client's details including name, CPF, and address.
 * It checks if a client with the given CPF already exists and aborts the operation if so.
 * If the address already exists in the system, it uses the existing address; otherwise, it registers the new address.
 *
 * @param c Pointer to the Client structure where the new client's details will be stored.
 * @param add Pointer to the Address structure where the new client's address details will be stored.
 */
void AddClient(Client* c, Address *add) {
    printf("Enter the new client's name: ");
    fillBuffer(40);
    strcpy(c->name, buffer);

    printf("Enter the new client's CPF: ");
    fillBuffer(12);
    strcpy(c->cpf, buffer);

    Client *existingClient = SearchClientByCPF(c->cpf);
    if (existingClient) {
        printf("A client with this CPF already exists. Operation aborted.\n");
        printf("Type anything to continue...");
        getch();
        system("clear");
        return;
    }

    printf("Enter the new client's address (Street): ");
    fillBuffer(40);
    strcpy(add->street, buffer);

    printf("Enter the new client's house number: ");
    fillBuffer(5);
    strcpy(add->number, buffer);

    printf("Enter the new client's postal code (CEP): ");
    fillBuffer(10);
    strcpy(add->cep, buffer);

    printf("Enter an additional address information for the new client: ");
    fillBuffer(40);
    strcpy(add->complement, buffer);

    for (int i = 0; i < MAX_ENTITIES; i++) {
        if (!strcmp(addresses[i].street, add->street) &&
            !strcmp(addresses[i].number, add->number) &&
            !strcmp(addresses[i].cep, add->cep) &&
            !strcmp(addresses[i].complement, add->complement)) {
            c->addressId = addresses[i].id;
            add->id = -1;
            printf("Existing address found and used.\n");
            printf("Client successfully registered!!!\n");
            printf("Type anything to continue...");
            getch();
            system("clear");
            return;
        }
    }

    c->addressId = add->id;
    printf("Client successfully registered with new address!!!\n");
    printf("Type anything to continue...");
    getch();
    system("clear");
}


/**
 * @brief Removes a client from the system based on their CPF.
 * 
 * This function prompts the user to enter the CPF of the client they wish to remove.
 * If the client is found, their details are displayed and the user is asked to confirm
 * the removal. If confirmed, the client's CPF is set to "0" to indicate removal.
 * Additionally, if the client's address has no other associated clients, the address
 * is also removed.
 * 
 * @note The user can type "exit" to go back without removing any client.
 * 
 * @warning This function uses system calls to clear the console and may not be portable
 * across different operating systems.
 */
void RemoveClient() {
    do {
        printf("Enter the CPF of the client you want to remove (type \"exit\" to go back): \n");
        fillBuffer(12);
        if(!strcmp("EXIT", buffer)) {
            system("clear");
            return;
        }
        Client* c = SearchClientByCPF(buffer);
        if (c) {
            char x = '\0';
            system("clear");
            printf("Name: %s\n", c->name);
            printf("CPF: %s\n", c->cpf);
            Address *add = SearchAddressById(c->addressId);
            printf("Street: %s, Number: %s, Complement: %s\n", add->street, add->number, add->complement);
            printf("CEP: %s", add->cep);
            printf("\n\n");
            printf("Are you sure you want to remove this client? (Y or N) ");
            fillBuffer(1);
            x = buffer[0];
            if(x == 'Y') {
                strcpy(c->cpf, "0\0");
                printf("Client removed.\n");

                // Check if the address has no other clients
                int hasClients = 0;
                for (int i = 0; i < MAX_ENTITIES; i++) {
                    if (clients[i].addressId == add->id && strcmp(clients[i].cpf, "0") != 0) {
                        hasClients = 1;
                        break;
                    }
                }
                if (!hasClients) {
                    add->id = -1;
                    printf("Address removed as it has no other clients.\n");
                }

                printf("Type anything to continue...");
                getch();
            } else {
                printf("Operation canceled.\n");
                printf("Type anything to continue...");
                getch();
            }
            system("clear");
            return;
        }
        printf("Client not found. Try again...\n");
        printf("Type anything to continue...");
        getch();
        system("clear");
    } while(!strcmp("EXIT", buffer));
}

/**
 * @brief Updates the client's menu with options to edit client details.
 *
 * This function prompts the user to enter a client's CPF and searches for the client.
 * If the client is found, it displays a menu with options to edit the client's name,
 * CPF, or address. The user can also choose to go back to the previous menu.
 *
 * @note The function uses several helper functions such as fillBuffer, SearchClientByCPF,
 *       SearchAddressById, and getch. It also uses the global buffer and addresses array.
 *
 * @details
 * - If the client is not found, a message is displayed and the function returns.
 * - If the client is found, the user is presented with the following options:
 *   1. Edit name: Prompts the user to enter a new name and updates the client's name.
 *   2. Edit CPF: Prompts the user to enter a new CPF and updates the client's CPF if it is unique.
 *   3. Address: Prompts the user to enter new address details and updates the client's address.
 *   4. Back: Returns to the previous menu.
 * - After each successful update, a confirmation message is displayed.
 * - If an invalid choice is entered, an error message is displayed and the menu is cleared.
 */
void UpdateClientMenu() {
    printf("Enter the client's CPF: ");
    fillBuffer(12);
    Client* c = SearchClientByCPF(buffer);
    if (!c) {
        printf("Client not found.\n");
        printf("Type anything to continue...");
        getch();
        system("clear");
        return;
    }
    int choice;
    Address* add = SearchAddressById(c->addressId);
    system("clear");
    printf("Name: %s\nCPF: %s", c->name, c->cpf);
    printf("\n\n1. Edit name\n2. Edit CPF\n3. Address\n4. Back\nOption:");
    fillBuffer(20);
    sscanf(buffer, "%d", &choice);
    system("clear");
    switch (choice) {
        case 1:
            printf("Enter the new name: ");
            fillBuffer(40);
            strcpy(c->name, buffer);
            printf("\n\nClient successfully updated!\n");
            printf("Type anything to continue...");
            getch();
            break;
        case 2:
            printf("Enter the new CPF: ");
            fillBuffer(12);
            Client *existingClient = SearchClientByCPF(buffer);
            if (existingClient) {
                printf("A client with this CPF already exists. Operation aborted.\n");
                printf("Type anything to continue...");
                getch();
                system("clear");
                break;
            }
            strcpy(c->cpf, buffer);
            printf("\n\nClient successfully updated!\n");
            printf("Type anything to continue...");
            getch();
            break;
        case 3:
            printf("Enter the street: ");
            fillBuffer(40);
            strcpy(add->street, buffer);

            printf("Enter the number: ");
            fillBuffer(5);
            strcpy(add->number, buffer);

            printf("Enter the postal code (CEP): ");
            fillBuffer(10);
            strcpy(add->cep, buffer);

            printf("Enter the complement: ");
            fillBuffer(40);
            strcpy(add->complement, buffer);
            int existingAddress = 0;
            // Check if the address already exists
            for (int i = 0; i < MAX_ENTITIES; i++) {
                if (!strcmp(addresses[i].street, add->street) &&
                    !strcmp(addresses[i].number, add->number) &&
                    !strcmp(addresses[i].cep, add->cep) &&
                    !strcmp(addresses[i].complement, add->complement)) {
                    c->addressId = addresses[i].id;
                    add->id = -1;
                    existingAddress = 1;
                    printf("Existing address found and used.\n");
                    printf("\n\nClient successfully updated!\n");
                    printf("Type anything to continue...");
                    getch();
                    break;
                }
            }
            if(existingAddress) {
                break;
            }

            // If address does not exist, use the new one
            c->addressId = add->id;
            printf("\n\nClient successfully updated with new address!\n");
            printf("Type anything to continue...");
            getch();
            break;
        case 4:
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
 * @brief Lists all clients and their respective addresses.
 *
 * This function iterates through the list of clients and prints their names,
 * CPFs, and addresses. If a client's CPF is not "0", it prints the client's
 * name and CPF. It then searches for the client's address using the client's
 * address ID. If the address is found and valid, it prints the address details
 * (street, number, complement, and CEP). If the address is not found, it prints
 * "Address not found." After listing all clients, it prompts the user to type
 * anything to continue and clears the screen.
 *
 * @note This function uses the global array `clients` and the constant `MAX_ENTITIES`.
 *       It also relies on the `SearchAddressById` function to retrieve address details.
 */
void ListClients() {
    printf("Clients:\n");
    for (int i = 0; i < MAX_ENTITIES; i++) {
        if (strcmp(clients[i].cpf, "0") != 0) {
            printf("Name: %s, CPF: %s\n", clients[i].name, clients[i].cpf);
            Address *add = SearchAddressById(clients[i].addressId);
            if (add && add->id != -1) {
                printf("Street: %s, Number: %s, Complement: %s, CEP: %s\n", add->street, add->number, add->complement, add->cep);
            } else {
                printf("Address not found.\n");
            }
            printf("\n");
        }
    }
    printf("Type anything to continue...");
    getch();
    system("clear");
}

/**
 * @brief Adds a new client to the system.
 *
 * This function attempts to add a new client by first retrieving an empty user slot.
 * If no empty user slot is available, it prints an error message and waits for user input to continue.
 * Next, it attempts to retrieve an empty address slot. If no empty address slot is available,
 * it prints an error message and waits for user input to continue.
 * If both an empty user slot and an empty address slot are available, it adds the client using these slots.
 */
void AddClientMenu(void) {
    Client *c = getEmptyUser();
    if(!c){
        printf("No empty user available.\n");
        printf("Type anything to continue...");
        getch();
        return;
    }
    Address *add = getEmptyAddress();
    if (!add) {
        printf("Addresses are full\n");
        printf("Type anything to continue...");
        getch();
        return;
    }
    AddClient(c, add);
}

/**
 * @brief Displays the Edit Client Menu and handles user input for updating or removing a client.
 *
 * This function presents a menu to the user with options to update a client, remove a client, or exit the menu.
 * It uses a loop to repeatedly display the menu until the user chooses to exit.
 * 
 * The menu options are:
 * 1. Update - Calls the UpdateClientMenu function to update client details.
 * 2. Remove - Calls the RemoveClient function to remove a client.
 * 3. Exit - Exits the menu.
 *
 * If an invalid option is selected, an error message is displayed and the user is prompted to try again.
 */
void EditClientMenu() {
    int choice = 0;
    do{
        system("clear");
        printf("1. Update\n2. Remove\n3. Exit\nOption:");
        fillBuffer(1);
        sscanf(buffer,"%d",&choice);
        if(choice == 1) {
            system("clear");
            UpdateClientMenu();
        }else if(choice == 2) {
            system("clear");
            RemoveClient();
        } else if (choice == 3){
            system("clear");
        } else{
            printf("Invalid option!\n Try again\n");
            printf("Type anything to continue...");
            getch();
        }
    }while (choice != 3);
}

/**
 * @brief Displays a menu for searching clients by different criteria and processes the user's choice.
 *
 * This function presents a menu to the user with options to search for clients by name, CPF, or address.
 * The user can also choose to go back to the previous menu. The function reads the user's choice,
 * clears the screen, and calls the SearchClient function with the selected option.
 *
 * @note The function uses a loop to repeatedly display the menu until the user chooses to go back (option 4).
 */
void SearchClientMenu() {
    int op;
    do {
        printf("Search client by:\n1.Name\n2.CPF\n3.Address\n4.Back\nOption: ");
        fillBuffer(20);
        sscanf(buffer, "%d", &op);
        system("clear");
        SearchClient(op);
    } while(op!=4);
}

/**
 * @brief Displays the client menu and handles user input for various client operations.
 *
 * This function presents a menu to the user with options to list clients, search for a client,
 * add a new client, edit an existing client, or go back to the previous menu. The user's choice
 * is read and the corresponding function is called to perform the selected operation.
 *
 * The menu options are:
 * 1. List - Calls the ListClients() function to display a list of clients.
 * 2. Search - Calls the SearchClientMenu() function to search for a client.
 * 3. Add - Calls the AddClientMenu() function to add a new client.
 * 4. Edit - Calls the EditClientMenu() function to edit an existing client.
 * 5. Back - Exits the client menu and returns to the previous menu.
 *
 * The function uses a loop to repeatedly display the menu and process user input until the user
 * chooses the "Back" option.
 */
void ClientMenu() {
    int choice;
    do {
        printf("Client\n\n");
        printf("1. List\n2. Search\n3. Add\n4. Edit\n5. Back\nOption:");
        fillBuffer(1);
        sscanf(buffer, "%d",&choice);
        system("clear");
        switch(choice) {
            case 1:
                ListClients();
            break;
            case 2:
                SearchClientMenu();
            break;
            case 3:
                AddClientMenu();
            break;
            case 4:
                EditClientMenu();
            break;
            default: break;
        }
    } while(choice!=5);
}


#endif