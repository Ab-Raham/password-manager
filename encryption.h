#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <QString>
#include <QByteArray>

// Function declarations
QByteArray encrypt(const QString &plaintext, const QString &password);
QString decrypt(const QByteArray &ciphertext, const QString &password);

#endif // ENCRYPTION_H
