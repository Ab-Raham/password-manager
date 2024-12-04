#include "passworddialog.h"
#include "ui_passworddialog.h"
#include <QDebug>
#include <QRandomGenerator>
#include <QTime>

PasswordDialog::PasswordDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PasswordDialog)
{
    ui->setupUi(this);

    //Place holders to replace labels in UI
    ui->txtWebsite->setPlaceholderText("Website");
    ui->txtUsername->setPlaceholderText("Username");
    ui->txtPassword->setPlaceholderText("Password");

    //Connecting the save button to the accept() slot
    connect(ui->btnSave, &QPushButton::clicked, this, &QDialog::accept);
    //Connecting the close button to the reject() slot
    connect(ui->btnClose, &QPushButton::clicked, this, &QDialog::reject);
    //Connecting the generate button
    connect(ui->generateButton, &QPushButton::clicked, this, &PasswordDialog::on_generateButton_clicked);
}

PasswordDialog::~PasswordDialog(){
    delete ui;
}
QString PasswordDialog::website() const{
    return ui->txtWebsite->text();
}
QString PasswordDialog::username() const{
    return ui->txtUsername->text();
}
QString PasswordDialog::password() const{
    return ui->txtPassword->text();
}
void PasswordDialog::setWebsite(const QString &website){
    ui->txtWebsite->setText(website);
}
void PasswordDialog::setUsername(const QString &username){
    ui->txtUsername->setText(username);
}
void PasswordDialog::setPassword(const QString &password){
    ui->txtPassword->setText(password);
}

void PasswordDialog::on_generateButton_clicked(){
    QString generatedPassword = generateRandomPassword();
    ui->txtPassword->setText(generatedPassword);
}
QString PasswordDialog::generateRandomPassword(int length){
    const QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()_+");
    QString randomPassword;
    for(int i=0; i<length; i++){
        int index = QRandomGenerator::global()->bounded(possibleCharacters.length());
        randomPassword.append(possibleCharacters.at(index));
    }
    return randomPassword;
}

//Debug statements
//void PasswordDialog::accept()
//{
//    qDebug() << "Dialog Accepted";
//    qDebug() << "Website:" << website();
//    qDebug() << "Username:" << username();
//    qDebug() << "Password:" << password();
//    QDialog::accept();
//}
