#ifndef MODELS_H
#define MODELS_H
#define MAX_ENTITIES 50

/**
 * @struct Genre
 * @brief Represents a genre with an ID and a name.
 * 
 * @var Genre::id
 * The unique identifier for the genre.
 * 
 * @var Genre::genre
 * The name of the genre, stored as a string with a maximum length of 40 characters.
 */
typedef struct {
    int id;
    char genre[40];
} Genre;

/**
 * @struct Author
 * @brief Represents an author with an ID and a name.
 * 
 * @var Author::id
 * Member 'id' contains the unique identifier for the author.
 * 
 * @var Author::name
 * Member 'name' contains the name of the author, with a maximum length of 40 characters.
 */
typedef struct {
    int id;
    char name[40];
} Author;

/**
 * @struct Book
 * @brief Represents a book in the inventory.
 * 
 * @var Book::id
 * Unique identifier for the book.
 * 
 * @var Book::title
 * Title of the book. Maximum length is 40 characters.
 * 
 * @var Book::authorId
 * Identifier for the author of the book.
 * 
 * @var Book::genreId
 * Identifier for the genre of the book.
 * 
 * @var Book::amount
 * Total amount of the book available.
 * 
 * @var Book::stock
 * Current stock of the book.
 */
typedef struct {
    int id;
    char title[40];
    int authorId;
    int genreId;
    int amount;
    int stock;
} Book;

/**
 * @struct Address
 * @brief Represents an address with various details.
 * 
 * @var Address::id
 * Member 'id' represents the unique identifier for the address.
 * 
 * @var Address::street
 * Member 'street' represents the name of the street. It is a character array with a maximum length of 40 characters.
 * 
 * @var Address::number
 * Member 'number' represents the number of the address. It is a character array with a maximum length of 5 characters.
 * 
 * @var Address::cep
 * Member 'cep' represents the postal code (CEP) of the address. It is a character array with a maximum length of 10 characters.
 * 
 * @var Address::complement
 * Member 'complement' represents additional address information. It is a character array with a maximum length of 40 characters.
 */
typedef struct {
    int id;
    char street[40];
    char number[5];
    char cep[10];
    char complement[40];
} Address;

/**
 * @struct Client
 * @brief Represents a client in the system.
 * 
 * This structure holds information about a client, including their personal details,
 * address, fines, and borrowed books.
 * 
 * @var Client::name
 * Member 'name' stores the name of the client. It is a character array with a maximum length of 40 characters.
 * 
 * @var Client::cpf
 * Member 'cpf' stores the CPF (Cadastro de Pessoas Físicas) of the client. It is a character array with a maximum length of 12 characters.
 * 
 * @var Client::addressId
 * Member 'addressId' stores the identifier for the client's address. It is an integer value.
 * 
 * @var Client::fineAmount
 * Member 'fineAmount' stores the total amount of fines the client has. It is an integer value.
 * 
 * @var Client::bookId1
 * Member 'bookId1' stores the identifier of the first book borrowed by the client. It is an integer value.
 * 
 * @var Client::bookId2
 * Member 'bookId2' stores the identifier of the second book borrowed by the client. It is an integer value.
 * 
 * @var Client::deadline
 * Member 'deadline' stores the deadline for returning the borrowed books. It is a character array with a maximum length of 8 characters.
 */
typedef struct
{
    char name[40];
    char cpf[12];
    int addressId;
    int fineAmount;
    int bookId1;
    int bookId2;
    char deadline[8];
} Client;

/**
 * @struct Loan
 * @brief Represents a loan record in the system.
 * 
 * This structure holds information about a loan, including the loan ID, 
 * the user's CPF (Cadastro de Pessoas Físicas, Brazilian individual taxpayer registry identification), 
 * the IDs of two books associated with the loan, and the start and deadline dates of the loan.
 * 
 * @var Loan::id
 * Member 'id' contains the unique identifier for the loan.
 * 
 * @var Loan::userCpf
 * Member 'userCpf' contains the CPF of the user who took the loan.
 * 
 * @var Loan::book1Id
 * Member 'book1Id' contains the ID of the first book in the loan.
 * 
 * @var Loan::book2Id
 * Member 'book2Id' contains the ID of the second book in the loan.
 * 
 * @var Loan::startDate
 * Member 'startDate' contains the start date of the loan in a string format.
 * 
 * @var Loan::deadline
 * Member 'deadline' contains the deadline date of the loan in a string format.
 */
typedef struct {
    int id;
    char userCpf[12];
    int book1Id;
    int book2Id;
    char startDate[20];
    char deadline[20];
} Loan;
/**
 * @struct Admin
 * @brief Represents an administrator with login credentials.
 * 
 * This structure holds the login credentials for an administrator.
 * 
 * @var Admin::login
 * Member 'login' stores the login name of the administrator. It is a character array with a maximum length of 19 characters plus a null terminator.
 * 
 * @var Admin::password
 * Member 'password' stores the password of the administrator. It is a character array with a maximum length of 9 characters plus a null terminator.
 */

typedef struct
{
    char login[20];
    char password[10];
} Admin;

#endif

