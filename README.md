# Library Management System

This project is a simple Library Management System implemented in C. It allows users to perform various operations related to library management, such as searching for books, borrowing books, returning books, and managing user details. The system supports two types of users: Students and Admins, each with different access levels.

## Features

### For Students
- **Login and Registration**: Students can register and log in to the system.
- **Search Books**: Search for books by title, author, or ID.
- **Borrow Books**: Borrow available books.
- **Return Books**: Return borrowed books.
- **View Borrowed Books**: View the list of books they have borrowed.
- **Reserve Books**: Reserve books that are currently unavailable.

### For Admins
- **Login and Registration**: Admins can register and log in to the system.
- **View Borrowed Books**: View the list of books borrowed by any user.
- **Reserve Books**: Reserve books for users.
- **Add/Remove Books**: Add new books to the library or remove existing ones.
- **Update Book Details**: Update the details of existing books.
- **Manage User**: Manage user details, such as updating user information.
- **Issue Books**: Issue books to users.
- **Track Fines**: Track fines for overdue books.

## File Structure

- `main.c`: The main source code file containing the implementation of the Library Management System.
- `books.txt`: A text file used to store book information.
- `users.txt`: A text file used to store user information.

## How to Run

1. **Compile the Code**: Use a C compiler to compile the `main.c` file.
   ```sh
   gcc main.c -o library
   ```

2. **Run the Executable**: Run the compiled executable.
   ```sh
   ./library
   ```

## Usage

1. **Register**: Register as a new user (either student or admin).
2. **Login**: Log in using your registered credentials.
3. **Perform Operations**: Based on your role (student or admin), perform the available operations from the menu.

## Data Storage

- **Books**: Stored in `books.txt` in the format:
  ```
  id,title,author,available,reserved
  ```
- **Users**: Stored in `users.txt` in the format:
  ```
  id,name,password,borrowedBookId,fine,role
  ```

## Example Data

### `books.txt`
```
1,The Great Gatsby,F. Scott Fitzgerald,5,0
2,1984,George Orwell,3,0
3,To Kill a Mockingbird,Harper Lee,4,0
```

### `users.txt`
```
123,Aranya,123,-1,0,admin
124,Rouf,123,-1,0,admin
125,Diba,123,-1,0,student
```

## Contributing

Contributions are welcome! Please fork the repository and submit a pull request for any improvements or bug fixes.

## License

This project is licensed under the MIT License. See the `LICENSE` file for more details.
