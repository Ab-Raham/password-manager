#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QClipboard>
#include <QTimer>
#include <QEvent>
#include <QApplication>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;


private slots:
    void on_btnAdd_clicked();
    void on_btnEdit_clicked();
    void on_btnDelete_clicked();
    void on_btnClose_clicked();
    void on_copyButton_clicked(int row);
    void lockApplication();

private:
    Ui::MainWindow *ui;
    QTimer *inactivityTimer;

    //Save and Load data declarations
    void saveData();
    void loadData();
    void addPasswordToTable(const QString &website, const QString &username, const QString &encryptedPassword);
    QString decryptPassword(const QString &encryptedPassword);
};
#endif // MAINWINDOW_H
