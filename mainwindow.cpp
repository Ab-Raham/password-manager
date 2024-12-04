#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "passworddialog.h"
#include <QMessageBox>
#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/rand.h>
#include "encryption.h"
#include "loginwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , inactivityTimer(new QTimer(this))
{
    ui->setupUi(this);
    connect(ui->btnAdd, &QPushButton::clicked, this, &MainWindow::on_btnAdd_clicked);
    connect(ui->btnEdit, &QPushButton::clicked, this, &MainWindow::on_btnEdit_clicked);
    connect(ui->btnDelete, &QPushButton::clicked, this, &MainWindow::on_btnDelete_clicked);
    connect(ui->btnClose, &QPushButton::clicked, this, &MainWindow::on_btnClose_clicked);

    ui->passwordTable->setColumnCount(4); // Updated to 4 columns
    ui->passwordTable->setHorizontalHeaderLabels({"Website","Username","Password","Actions"});

    // Load existing data
    loadData();

    //Setup inactivity timer
    inactivityTimer->setInterval(30000); //30 secs
    connect(inactivityTimer, &QTimer::timeout, this, &MainWindow::lockApplication);

    //Start nactivity timer
    inactivityTimer->start();
    //Event filter
    qApp->installEventFilter(this);
}

MainWindow::~MainWindow(){
    // Save data upon UI close
    saveData();
    delete ui;
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event){
    if(event->type()==QEvent::MouseMove || event->type()==QEvent::KeyPress){
        //Reset inactivity timer upon user input
        inactivityTimer->start();
    }
    return QMainWindow::eventFilter(obj, event);
}

void MainWindow::lockApplication(){
    inactivityTimer->stop();
    LoginWindow *loginWindow = new LoginWindow();
    connect(loginWindow, &LoginWindow::loginSuccessful, [this, loginWindow](){
        this->show();
        loginWindow->deleteLater();
        inactivityTimer->start(); //Restart the timer
    });
    this->hide();
    loginWindow->show();
}
void MainWindow::on_btnAdd_clicked(){
    PasswordDialog dlg(this);
    if(dlg.exec() == QDialog::Accepted){
        qDebug() << "Accepted";

        QString masterPassword = "TheMasterPassword";
        QString encryptedPassword = encrypt(dlg.password(), masterPassword).toBase64();

        int row = ui->passwordTable->rowCount();
        ui->passwordTable->insertRow(row);
        ui->passwordTable->setItem(row, 0, new QTableWidgetItem(dlg.website()));
        ui->passwordTable->setItem(row, 1, new QTableWidgetItem(dlg.username()));
        ui->passwordTable->setItem(row, 2, new QTableWidgetItem(encryptedPassword));

        // Add copy button to the Actions column
        QPushButton *copyButton = new QPushButton("Copy");
        connect(copyButton, &QPushButton::clicked, [this, row]() { on_copyButton_clicked(row); });
        ui->passwordTable->setCellWidget(row, 3, copyButton);
    }else{
        qDebug()<<"Rejected";
    }
}

void MainWindow::on_btnClose_clicked()
{
    qDebug() << "Close button clicked";
    close(); // Exit the main window
}

void MainWindow::on_btnEdit_clicked()
{
    int row = ui->passwordTable->currentRow();
    if(row < 0){
        QMessageBox::warning(this, "Edit", "Please select an entity to edit.");
        return;
    }

    QString website = ui->passwordTable->item(row, 0)->text();
    QString username = ui->passwordTable->item(row, 1)->text();
    QString password = ui->passwordTable->item(row,2)->text();

    PasswordDialog dlg(this);
    dlg.setWebsite(website);
    dlg.setUsername(username);
    dlg.setPassword(password);

    if(dlg.exec() == QDialog::Accepted){
        ui->passwordTable->item(row, 0)->setText(dlg.website());
        ui->passwordTable->item(row, 1)->setText(dlg.username());
        ui->passwordTable->item(row, 2)->setText(dlg.password());
    }
}

void MainWindow::on_btnDelete_clicked()
{
    int row = ui->passwordTable->currentRow();
    if(row < 0){
        QMessageBox::warning(this, "Delete", "Please select what you'd like to delete.");
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Delete", "Are you sure?", QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes){
        ui->passwordTable->removeRow(row);
    }
}

void MainWindow::on_copyButton_clicked(int row)
{
    QTableWidgetItem *item = ui->passwordTable->item(row, 2); // Assuming column 2 for passwords
    QString encryptedPassword = item->text();

    // Decrypt the password
    QString decryptedPassword = decrypt(QByteArray::fromBase64(encryptedPassword.toUtf8()), "TheMasterPassword");

    // Copy the decrypted password to the clipboard
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(decryptedPassword);

    QMessageBox::information(this, "Password Copied", "Decrypted password copied to clipboard!");
}

void MainWindow::saveData()
{
    QString masterPassword = "YourMasterPassword"; // Replace with your master password logic

    QJsonArray passwordArray;
    for (int row = 0; row < ui->passwordTable->rowCount(); ++row) {
        QJsonObject passwordObject;
        passwordObject["website"] = ui->passwordTable->item(row, 0)->text();
        passwordObject["username"] = ui->passwordTable->item(row, 1)->text();
        QString encryptedPassword = encrypt(ui->passwordTable->item(row, 2)->text(), masterPassword).toBase64();
        passwordObject["password"] = encryptedPassword;
        passwordArray.append(passwordObject);
    }

    QJsonDocument saveDoc(passwordArray);
    QFile saveFile(QStringLiteral("passwords.json"));

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return;
    }

    saveFile.write(saveDoc.toJson());
}

void MainWindow::loadData()
{
    QString masterPassword = "TheMasterPassword"; // Replace with your master password logic

    QFile loadFile(QStringLiteral("passwords.json"));

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open load file.");
        return;
    }

    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    QJsonArray passwordArray = loadDoc.array();
    for (const QJsonValue &value : passwordArray) {
        QJsonObject passwordObject = value.toObject();
        int row = ui->passwordTable->rowCount();
        ui->passwordTable->insertRow(row);
        ui->passwordTable->setItem(row, 0, new QTableWidgetItem(passwordObject["website"].toString()));
        ui->passwordTable->setItem(row, 1, new QTableWidgetItem(passwordObject["username"].toString()));
        QString decryptedPassword = decrypt(QByteArray::fromBase64(passwordObject["password"].toString().toUtf8()), masterPassword);
        ui->passwordTable->setItem(row, 2, new QTableWidgetItem(decryptedPassword));

        // Add copy button to the Actions column
        QPushButton *copyButton = new QPushButton("Copy");
        connect(copyButton, &QPushButton::clicked, [this, row]() { on_copyButton_clicked(row); });
        ui->passwordTable->setCellWidget(row, 3, copyButton);
    }
}
