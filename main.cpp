#include "mainwindow.h"
#include "loginwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginWindow loginWindow;
    MainWindow mainWindow;

    QObject::connect(&loginWindow, &LoginWindow::loginSuccessful, &mainWindow, &MainWindow::show);

    // Ensure the application quits if the login window is closed
    QObject::connect(&loginWindow, &LoginWindow::destroyed, &a, &QApplication::quit);

    loginWindow.show();

    return a.exec();
}
