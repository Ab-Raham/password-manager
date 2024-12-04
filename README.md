[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/kDZuZY56)

# Group 14
# Project: Password Manager

Group Members:
1. Thembo Bernard
2. Patricia Okoboi
3. Ddembe Lincoln
4. Nanyonga Olivia
5. Mukhwana Abraham


## Overview
The Password Manager is a secure and user-friendly application that helps you manage your passwords efficiently. It includes features such as password generation, secure storage, encryption, and automatic locking on inactivity.

## Features
- **Master Login**: Secure access to the application with a master password.
- **Password Generation**: Generate strong, random passwords.
- **Password Management**: Add, edit, delete, and copy passwords.
- **Auto-Lock**: Automatically locks the application after 30 seconds of inactivity.
- **Encrypted Storage**: Ensures all passwords are securely encrypted.

## Prerequisites
- **Operating System**: Debian 12
- **Libraries**: OpenSSL

## Setup Instructions

### Building the Application
1. Clone the repository:
    ```sh
    git clone <repository-url>
    cd <repository-directory>
    ```
2. Install the necessary dependencies:
    ```sh
    sudo apt-get install libssl-dev
    ```
3. Open the project in Qt Creator:
    - Launch Qt Creator.
    - Open the project file (.pro or CMakeLists.txt).

4. Build the project:
    - Click on the "Build" button in Qt Creator to compile the project.

### Running the Application
- Click the "Run" button in Qt Creator to start the application.
- You will be prompted to enter the master password to access the application.

## Usage

### Login
- Enter the master password and click "Login".
- If the password is correct, the main window will open.

### Adding a Password
1. Click the "Add" button.
2. Enter the website, username, and password in the dialog.
3. You can generate a strong password by clicking the "Generate" button.
4. Click "Save" to add the password to the list.

### Editing a Password
1. Select the password entry from the list.
2. Click the "Edit" button.
3. Modify the details in the dialog and click "Save".

### Deleting a Password
1. Select the password entry from the list.
2. Click the "Delete" button and confirm the action.

### Copying a Password
- Click the "Copy" button next to the password entry.
- The password will be copied to your clipboard.

## File Structure
```
|-- encryption.h
|-- encryption.cpp
|-- loginwindow.h
|-- loginwindow.cpp
|-- mainwindow.h
|-- mainwindow.cpp
|-- main.cpp
|-- passworddialog.h
|-- passworddialog.cpp
```

## Security
- **Encryption**: Uses AES-256 encryption to securely store passwords.
- **Auto-Lock**: Automatically locks the application after 30 seconds of inactivity to prevent unauthorized access.

## Additional Notes
- **Code Comments**: Ensure that your code is well-commented to explain the logic and flow, especially in complex sections like encryption and password management.
- **Error Handling**: Implement robust error handling to manage scenarios such as incorrect master password entry, failed encryption, or file read/write errors.
- **Testing**: Include unit tests for critical components like encryption and password management to ensure reliability and security.
- **Documentation**: Provide inline documentation and a separate detailed document if necessary to explain the architecture, design decisions, and any third-party libraries used.

