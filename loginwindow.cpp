#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QMessageBox>
#include <QApplication>

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    //Place holder to replace label in UI
    ui->passwordLineEdit->setPlaceholderText("Enter Master Password");
    connect(ui->exitButton, &QPushButton::clicked, this, &LoginWindow::on_exitButton_clicked);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_loginButton_clicked()
{
    QString enteredPassword = ui->passwordLineEdit->text();

    if (enteredPassword == masterPassword) {
        emit loginSuccessful();
        this->close();
    } else {
        QMessageBox::warning(this, "Login Failed", "Incorrect password. Please try again.");
    }
}

void LoginWindow::on_exitButton_clicked()
{
    QApplication::quit();
}
