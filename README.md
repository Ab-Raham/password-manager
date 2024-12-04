# Project: Password Manager

## Overview
The Password Manager is a secure and user-friendly widget application that helps you manage your passwords locally and efficiently. It includes features such as password generation, secure storage, encryption, and automatic locking on inactivity.

## Features
- **Master Login**: Secure access to the application with a master password.
- **Password Generation**: Generate strong, random passwords.
- **Password Management**: Add, edit, delete, and copy passwords.
- **Auto-Lock**: Automatically locks the application after 30 seconds of inactivity.
- **Encrypted Storage**: Ensures all passwords are securely encrypted.

## Prerequisites
- **Operating System**: Developed on Debian 12
- **Libraries**: OpenSSL


## Development instructions
Contributions to development are highly welcome. A proper documentation is still being prepared.
The app is still in active development and is still buggy.

## Setup and usage Instructions

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

Developer contact: