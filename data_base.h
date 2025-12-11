#ifndef DATA_BASE_H
#define DATA_BASE_H

#include <QString>
#include <QObject>
#include <QSqlDatabase>

class Data_Base : public QObject
{
    Q_OBJECT
public:
    explicit Data_Base(QObject *parent = nullptr);

    bool open_data_base();
    bool create_table();

    void close();
    void create(const QString &path);

    bool registration_user(const QString &login, const QString &password);
    bool authorization_user(const QString &login, const QString &password);
    bool user_exists(const QString &login);
    bool save_data(const QString &login, const QString &original_data, const QString &sorted_data);
    QVector<QPair<QString, QString>> loading_data(const QString &login);
    bool clear_data_base(const QString &login, QString &original_data, QString &sorted_data);

signals:

private:
    QSqlDatabase userdatabase;
};

#endif // DATA_BASE_H
