#include "data_base.h"
#include <QSqlQuery>
#include <QCryptographicHash>
#include <QDebug>
#include <QCoreApplication>
#include <QSqlError>
#include <QVector>

Data_Base::Data_Base(QObject *parent)
    : QObject(parent)
{}

void Data_Base::create(const QString &path){
    userdatabase = QSqlDatabase::addDatabase("QSQLITE");
    userdatabase.setDatabaseName(path);
    userdatabase.open();
}
bool Data_Base::open_data_base(){
    if(!userdatabase.open()){
        qDebug() << "Не удалось открыть базу данных.";
        return false;
    }
    return true;
}

bool Data_Base::create_table()
{
    qDebug() << "Попытка открыть БД:" << userdatabase.databaseName();

    QSqlQuery query(userdatabase);
    bool success_us = query.exec(
        "CREATE TABLE IF NOT EXISTS users ("
        "login TEXT PRIMARY KEY, "
        "password TEXT NOT NULL)"
        );
    bool success_arr = query.exec(
        "CREATE TABLE IF NOT EXISTS arrays ("
        "id_array INTEGER PRIMARY KEY AUTOINCREMENT, "
        "login TEXT NOT NULL, "
        "original_data TEXT NOT NULL, "
        "sorted_data TEXT NOT NULL, "
        "FOREIGN KEY(login) REFERENCES users(login) ON DELETE CASCADE)"
        );

    if (!success_us and !success_arr)
    {
        qWarning() << "Ошибка создания таблиц";
        return false;
    }
    else if (!success_us)
    {
        qWarning() << "Ошибка создания таблицы пользователей";
        return false;
    }
    else if (!success_arr)
    {
        qWarning() << "Ошибка создания таблицы массивов";
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
    query.prepare("INSERT INTO users (login, password) VALUES (?, ?)");
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
    QSqlQuery query(userdatabase);
    query.prepare("INSERT INTO arrays (login, original_data, sorted_data) VALUES (?, ?, ?)");
    query.addBindValue(login);
    query.addBindValue(original_data);
    query.addBindValue(sorted_data);
    return query.exec();
}

QVector<QPair<QString, QString>> Data_Base::loading_data(const QString &login)
{
    QVector<QPair<QString, QString>> result;
    QSqlQuery query(userdatabase);
    query.prepare("SELECT original_data, sorted_data FROM arrays WHERE login = ? ORDER BY id_array");
    query.addBindValue(login);
    if (query.exec()) {
        while (query.next()) {
            result.append({
                query.value(0).toString(),
                query.value(1).toString()
            });
        }
    }
    return result;
}

// bool Data_Base::clear_data_base(const QString &login, QString &original_data, QString &sorted_data)
// {
//     QSqlQuery query(userdatabase);
//     query.prepare("DELETE FROM users");
//     if (!query.exec()) {
//         qWarning() << "Ошибка очистки БД:" << query.lastError().text();
//         return false;
//     }
//     return true;
// }
