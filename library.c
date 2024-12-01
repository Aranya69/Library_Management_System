#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Book {
    int id;
    char title[50];
    char author[50];
    int available;
    int reserved;
};


struct User {
    int id;
    char name[50];
    char password[50];
    int borrowedBookId;
    int fine;
    char role[10];
};

void readBooks(struct Book books[], int *numBooks) {
    FILE *fp = fopen("books.txt", "r");
    if (fp == NULL) {
        printf("Error opening books file.\n");
        return;
    }

    int i = 0;
    while (fscanf(fp, "%d,%[^,],%[^,],%d,%d", &books[i].id, books[i].title, books[i].author, &books[i].available, &books[i].reserved) != EOF) {
        i++;
    }
    *numBooks = i;

    fclose(fp);
}

void writeBooks(struct Book books[], int numBooks) {
    FILE *fp = fopen("books.txt", "w");
    if (fp == NULL) {
        printf("Error opening books file.\n");
        return;
    }

    for (int i = 0; i < numBooks; i++) {
        fprintf(fp, "%d,%s,%s,%d,%d\n", books[i].id, books[i].title, books[i].author, books[i].available, books[i].reserved);
    }

    fclose(fp);
}

void readUsers(struct User users[], int *numUsers) {
    FILE *fp = fopen("users.txt", "r");
    if (fp == NULL) {
        printf("Error opening users file.\n");
        return;
    }

    int i = 0;
    while (fscanf(fp, "%d,%[^,],%[^,],%d,%d,%[^,\n]", &users[i].id, users[i].name, users[i].password, &users[i].borrowedBookId, &users[i].fine, users[i].role) != EOF) {
        i++;
    }
    *numUsers = i;

    fclose(fp);
}

void writeUsers(struct User users[], int numUsers) {
    FILE *fp = fopen("users.txt", "w");
    if (fp == NULL) {
        printf("Error opening users file.\n");
        return;
    }

    for (int i = 0; i < numUsers; i++) {
        fprintf(fp, "%d,%s,%s,%d,%d,%s\n", users[i].id, users[i].name, users[i].password, users[i].borrowedBookId, users[i].fine, users[i].role);
    }

    fclose(fp);
}

void registerUser(struct User users[], int *numUsers) {
    struct User newUser;
    printf("Enter your ID: ");
    scanf("%d", &newUser.id);
    printf("Enter your name: ");
    scanf(" %[^\n]", newUser.name);
    printf("Enter your password: ");
    scanf(" %[^\n]", newUser.password);
    printf("Enter your role (student/admin): ");
    scanf(" %[^\n]", newUser.role);
    newUser.borrowedBookId = -1;
    newUser.fine = 0;

    users[*numUsers] = newUser;
    (*numUsers)++;
    writeUsers(users, *numUsers);
    printf("User registered successfully.\n");
}

int loginUser(struct User users[], int numUsers, struct User *loggedInUser) {
    char name[50], password[50];
    printf("Enter your name: ");
    scanf(" %[^\n]", name);
    printf("Enter your password: ");
    scanf(" %[^\n]", password);

    for (int i = 0; i < numUsers; i++) {
        if (strcmp(users[i].name, name) == 0 && strcmp(users[i].password, password) == 0) {
            *loggedInUser = users[i];
            return 1;
        }
    }

    printf("Invalid name or password.\n");
    return 0;
}

void searchBooks(struct Book books[], int numBooks) {
    char query[50];
    printf("Enter the title, author, or ID of the book to search: ");
    scanf(" %[^\n]", query);

    for (int i = 0; i < numBooks; i++) {
        if (strstr(books[i].title, query) != NULL || strstr(books[i].author, query) != NULL || books[i].id == atoi(query)) {
            printf("Book found:\n");
            printf("ID: %d\n", books[i].id);
            printf("Title: %s\n", books[i].title);
            printf("Author: %s\n", books[i].author);
            printf("Available: %d\n", books[i].available);
            printf("Reserved: %d\n", books[i].reserved);
            return;
        }
    }

    printf("Book not found.\n");
}

void borrowBook(struct Book books[], int numBooks, struct User *user) {
    if (user->borrowedBookId != -1) {
        printf("You have already borrowed a book.\n");
        return;
    }

    int bookId;
    printf("Enter the ID of the book you want to borrow: ");
    scanf("%d", &bookId);

    for (int i = 0; i < numBooks; i++) {
        if (books[i].id == bookId) {
            if (books[i].available > 0) {
                books[i].available--;
                user->borrowedBookId = bookId;
                printf("You have successfully borrowed the book: %s\n", books[i].title);
                writeBooks(books, numBooks);
                return;
            } else {
                printf("The book is not available.\n");
                return;
            }
        }
    }

    printf("Book not found.\n");
}

void returnBook(struct Book books[], int numBooks, struct User *user) {
    if (user->borrowedBookId == -1) {
        printf("You have not borrowed any books.\n");
        return;
    }

    for (int i = 0; i < numBooks; i++) {
        if (books[i].id == user->borrowedBookId) {
            books[i].available++;
            user->borrowedBookId = -1;
            printf("You have successfully returned the book: %s\n", books[i].title);
            writeBooks(books, numBooks);
            return;
        }
    }

    printf("Borrowed book not found.\n");
}

void viewBorrowedBooks(struct Book books[], int numBooks, struct User user) {
    if (user.borrowedBookId == -1) {
        printf("You have not borrowed any books.\n");
        return;
    }

    for (int i = 0; i < numBooks; i++) {
        if (books[i].id == user.borrowedBookId) {
            printf("Borrowed Book:\n");
            printf("ID: %d\n", books[i].id);
            printf("Title: %s\n", books[i].title);
            printf("Author: %s\n", books[i].author);
            return;
        }
    }

    printf("Borrowed book not found.\n");
}

void reserveBook(struct Book books[], int numBooks, struct User *user) {
    int bookId;
    printf("Enter the ID of the book you want to reserve: ");
    scanf("%d", &bookId);

    for (int i = 0; i < numBooks; i++) {
        if (books[i].id == bookId) {
            if (books[i].reserved == 0) {
                books[i].reserved = user->id;
                printf("You have successfully reserved the book: %s\n", books[i].title);
                writeBooks(books, numBooks);
                return;
            } else {
                printf("The book is already reserved.\n");
                return;
            }
        }
    }

    printf("Book not found.\n");
}

void addBook(struct Book books[], int *numBooks) {
    struct Book newBook;
    printf("Enter the ID of the new book: ");
    scanf("%d", &newBook.id);
    printf("Enter the title of the new book: ");
    scanf(" %[^\n]", newBook.title);
    printf("Enter the author of the new book: ");
    scanf(" %[^\n]", newBook.author);
    printf("Enter the number of available copies: ");
    scanf("%d", &newBook.available);
    newBook.reserved = 0;

    books[*numBooks] = newBook;
    (*numBooks)++;
    writeBooks(books, *numBooks);
    printf("Book added successfully.\n");
}

void removeBook(struct Book books[], int *numBooks) {
    int bookId;
    printf("Enter the ID of the book to remove: ");
    scanf("%d", &bookId);

    for (int i = 0; i < *numBooks; i++) {
        if (books[i].id == bookId) {
            for (int j = i; j < *numBooks - 1; j++) {
                books[j] = books[j + 1];
            }
            (*numBooks)--;
            writeBooks(books, *numBooks);
            printf("Book removed successfully.\n");
            return;
        }
    }

    printf("Book not found.\n");
}

void updateBookDetails(struct Book books[], int numBooks) {
    int bookId;
    printf("Enter the ID of the book to update: ");
    scanf("%d", &bookId);

    for (int i = 0; i < numBooks; i++) {
        if (books[i].id == bookId) {
            printf("Enter the new title of the book: ");
            scanf(" %[^\n]", books[i].title);
            printf("Enter the new author of the book: ");
            scanf(" %[^\n]", books[i].author);
            printf("Enter the new number of available copies: ");
            scanf("%d", &books[i].available);
            writeBooks(books, numBooks);
            printf("Book details updated successfully.\n");
            return;
        }
    }

    printf("Book not found.\n");
}

void manageUser(struct User users[], int *numUsers) {
    int userId;
    printf("Enter the ID of the user to manage: ");
    scanf("%d", &userId);

    for (int i = 0; i < *numUsers; i++) {
        if (users[i].id == userId) {
            printf("Enter the new name of the user: ");
            scanf(" %[^\n]", users[i].name);
            printf("Enter the new password of the user: ");
            scanf(" %[^\n]", users[i].password);
            writeUsers(users, *numUsers);
            printf("User details updated successfully.\n");
            return;
        }
    }

    printf("User not found.\n");
}

void issueBook(struct Book books[], int numBooks, struct User *user) {
    if (user->borrowedBookId != -1) {
        printf("You have already borrowed a book.\n");
        return;
    }

    int bookId;
    printf("Enter the ID of the book you want to issue: ");
    scanf("%d", &bookId);

    for (int i = 0; i < numBooks; i++) {
        if (books[i].id == bookId) {
            if (books[i].available > 0) {
                books[i].available--;
                user->borrowedBookId = bookId;
                printf("You have successfully issued the book: %s\n", books[i].title);
                writeBooks(books, numBooks);
                return;
            } else {
                printf("The book is not available.\n");
                return;
            }
        }
    }

    printf("Book not found.\n");
}

void trackFines(struct User users[], int numUsers) {
    for (int i = 0; i < numUsers; i++) {
        if (users[i].fine > 0) {
            printf("User ID: %d\n", users[i].id);
            printf("Name: %s\n", users[i].name);
            printf("Fine: %d\n", users[i].fine);
        }
    }
}

int main() {
    struct Book books[100];
    int numBooks;
    struct User users[100];
    int numUsers;
    struct User loggedInUser;
    int loggedIn = 0;

    readBooks(books, &numBooks);
    readUsers(users, &numUsers);

    int choice;
    while (1) {
        if (!loggedIn) {
            printf("1. Register\n");
            printf("2. Login\n");
            printf("3. Exit\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    registerUser(users, &numUsers);
                    break;
                case 2:
                    loggedIn = loginUser(users, numUsers, &loggedInUser);
                    break;
                case 3:
                    exit(0);
                default:
                    printf("Invalid choice.\n");
            }
        } else {
            if (strcmp(loggedInUser.role, "student") == 0) {
                printf("1. Search Books\n");
                printf("2. Borrow Book\n");
                printf("3. Return Book\n");
                printf("4. View Borrowed Books\n");
                printf("5. Reserve Book\n");
                printf("6. Logout\n");
                printf("Enter your choice: ");
                scanf("%d", &choice);

                switch (choice) {
                    case 1:
                        searchBooks(books, numBooks);
                        break;
                    case 2:
                        borrowBook(books, numBooks, &loggedInUser);
                        break;
                    case 3:
                        returnBook(books, numBooks, &loggedInUser);
                        break;
                    case 4:
                        viewBorrowedBooks(books, numBooks, loggedInUser);
                        break;
                    case 5:
                        reserveBook(books, numBooks, &loggedInUser);
                        break;
                    case 6:
                        loggedIn = 0;
                        break;
                    default:
                        printf("Invalid choice.\n");
                }
            } else if (strcmp(loggedInUser.role, "admin") == 0) {
                printf("1. View Borrowed Books\n");
                printf("2. Reserve Book\n");
                printf("3. Add Book\n");
                printf("4. Remove Book\n");
                printf("5. Update Book Details\n");
                printf("6. Manage User\n");
                printf("7. Issue Book\n");
                printf("8. Track Fines\n");
                printf("9. Logout\n");
                printf("Enter your choice: ");
                scanf("%d", &choice);

                switch (choice) {
                    case 1:
                        viewBorrowedBooks(books, numBooks, loggedInUser);
                        break;
                    case 2:
                        reserveBook(books, numBooks, &loggedInUser);
                        break;
                    case 3:
                        addBook(books, &numBooks);
                        break;
                    case 4:
                        removeBook(books, &numBooks);
                        break;
                    case 5:
                        updateBookDetails(books, numBooks);
                        break;
                    case 6:
                        manageUser(users, &numUsers);
                        break;
                    case 7:
                        issueBook(books, numBooks, &loggedInUser);
                        break;
                    case 8:
                        trackFines(users, numUsers);
                        break;
                    case 9:
                        loggedIn = 0;
                        break;
                    default:
                        printf("Invalid choice.\n");
                }
            }
        }
    }

    return 0;
}
