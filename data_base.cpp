#include "data_base.h"
#include <QSqlQuery>
#include <QCryptographicHash>
#include <QDebug>
#include <QCoreApplication>
#include <QSqlError>

Data_Base::Data_Base(QObject *parent)
    : QObject(parent)
{
}

void Data_Base::create(const QString &path){
    userdatabase = QSqlDatabase::addDatabase("QSQLITE");
    userdatabase.setDatabaseName(path);
    userdatabase.open();
}
bool Data_Base::openpopen()
{
    if (!userdatabase.open()) {
        qWarning() << "<Ошибка. БД не открылась.>:" << userdatabase.lastError().text();
        return false;
    }

    qDebug() << "Попытка открыть БД:" << userdatabase.databaseName();

    QSqlQuery query(userdatabase);
    bool success = query.exec(
        "CREATE TABLE IF NOT EXISTS users ("
        "login TEXT PRIMARY KEY, "
        "password TEXT NOT NULL, "
        "raw_data TEXT, "
        "sorted_data TEXT)"
        );

    if (!success) {
        qWarning() << "Ошибка создания таблицы:";
        return false;
    }

    return true;
}

void Data_Base::close()
{
    userdatabase.close();
}

bool Data_Base::registration_user(const QString &login, const QString &password)
{
    QSqlQuery query(userdatabase);
    query.prepare("INSERT INTO users (login, password, original_data, sorted_data) VALUES (?, ?, '', '')");
    query.addBindValue(login);
    query.addBindValue(password);
    return query.exec();
}

bool Data_Base::authorization_user(const QString &login, const QString &password)
{
    QSqlQuery query(userdatabase);
    query.prepare("SELECT password FROM users WHERE login = ?");
    query.addBindValue(login);
    if (query.exec() && query.next()) {
        QString user_password = query.value(0).toString();
        return user_password == password;
    }
    return false;
}

bool Data_Base::user_exists(const QString &login)
{
    QSqlQuery query(userdatabase);
    query.prepare("SELECT 1 FROM users WHERE login = ?");
    query.addBindValue(login);
    return query.exec() && query.next();
}

bool Data_Base::save_data(const QString &login, const QString &original_data, const QString &sorted_data)
{
    if (!userdatabase.isOpen()) {
        if (!userdatabase.open()) {
            qWarning() << "Не удалось открыть БД для сохранения:" << userdatabase.lastError().text();
            return false;
        }
    }
    QSqlQuery query(userdatabase);
    query.prepare("UPDATE users SET raw_data = ?, sorted_data = ? WHERE login = ?");
    query.addBindValue(original_data);
    query.addBindValue(sorted_data);
    query.addBindValue(login);
    return query.exec();
}

bool Data_Base::loading_data(const QString &login, QString &original_data, QString &sorted_data)
{
    QSqlQuery query(userdatabase);
    query.prepare("SELECT raw_data, sorted_data FROM users WHERE login = ?");
    query.addBindValue(login);
    if (query.exec() && query.next()) {
        original_data = query.value(0).toString();
        sorted_data = query.value(1).toString();
        return true;
    }
    return false;
}
