#ifndef PASSWORDDIALOG_H
#define PASSWORDDIALOG_H

#include <QDialog>

namespace Ui {
class PasswordDialog;
}

class PasswordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PasswordDialog(QWidget *parent = nullptr);
    ~PasswordDialog();

    QString website() const;
    QString username() const;
    QString password() const;

    //Setter methods to prefill the dialog with existing data
    void setWebsite(const QString &website);
    void setUsername(const QString &username);
    void setPassword(const QString &password);

private slots:
    void on_generateButton_clicked();

private:
    Ui::PasswordDialog *ui;
    QString generateRandomPassword(int length = 12);
};

#endif // PASSWORDDIALOG_H
