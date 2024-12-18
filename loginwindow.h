#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void on_loginButton_clicked();
    void on_exitButton_clicked();

signals:
    void loginSuccessful();

private:
    Ui::LoginWindow *ui;
    QString masterPassword = "TheMasterPassword"; // Store your master password securely
};

#endif // LOGINWINDOW_H
