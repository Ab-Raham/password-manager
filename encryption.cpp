#include "encryption.h"
#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <QCryptographicHash>

// Helper function to derive a key from a password
QByteArray deriveKey(const QString &password, const QByteArray &salt) {
    QByteArray key(32, 0); // 256-bit key
    QCryptographicHash hash(QCryptographicHash::Sha256);
    hash.addData(salt);
    hash.addData(password.toUtf8());
    key = hash.result();
    return key;
}

QByteArray encrypt(const QString &plaintext, const QString &password) {
    QByteArray salt(16, 0);
    RAND_bytes(reinterpret_cast<unsigned char*>(salt.data()), salt.size());

    QByteArray key = deriveKey(password, salt);
    QByteArray iv(16, 0);
    RAND_bytes(reinterpret_cast<unsigned char*>(iv.data()), iv.size());

    QByteArray ciphertext(plaintext.size() + AES_BLOCK_SIZE, 0);
    int outlen;

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, reinterpret_cast<const unsigned char*>(key.data()), reinterpret_cast<const unsigned char*>(iv.data()));
    EVP_EncryptUpdate(ctx, reinterpret_cast<unsigned char*>(ciphertext.data()), &outlen, reinterpret_cast<const unsigned char*>(plaintext.toUtf8().data()), plaintext.size());
    EVP_EncryptFinal_ex(ctx, reinterpret_cast<unsigned char*>(ciphertext.data()) + outlen, &outlen);
    EVP_CIPHER_CTX_free(ctx);

    return salt + iv + ciphertext;
}

QString decrypt(const QByteArray &ciphertext, const QString &password) {
    QByteArray salt = ciphertext.left(16);
    QByteArray iv = ciphertext.mid(16, 16);
    QByteArray enc = ciphertext.mid(32);

    QByteArray key = deriveKey(password, salt);
    QByteArray plaintext(enc.size(), 0);
    int outlen;

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, reinterpret_cast<const unsigned char*>(key.data()), reinterpret_cast<const unsigned char*>(iv.data()));
    EVP_DecryptUpdate(ctx, reinterpret_cast<unsigned char*>(plaintext.data()), &outlen, reinterpret_cast<const unsigned char*>(enc.data()), enc.size());
    EVP_DecryptFinal_ex(ctx, reinterpret_cast<unsigned char*>(plaintext.data()) + outlen, &outlen);
    EVP_CIPHER_CTX_free(ctx);

    return QString::fromUtf8(plaintext.trimmed());
}
