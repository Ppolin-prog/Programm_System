#include <QCoreApplication>
#include <QtTest>
#include <QSql>
#include <QSqlQuery>
#include <QElapsedTimer>
#include <QTimer>
#include <QApplication>
#include <QWidget>
#include <QDialog>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "data_base.h"
#include "sort_functions.h"

class labatest : public QObject
{
    Q_OBJECT

public:
    labatest();
    ~labatest();

private slots:
    void test_100_arrays();
    void test_1000_arrays();
    void test_10000_arrays();

private:
    void test_loadrandom_arrays(int db_value);
};

labatest::labatest()
{}

labatest::~labatest()
{}

void labatest::test_100_arrays()
{
    srand(time(0));

    if (QSqlDatabase::contains(QSqlDatabase::defaultConnection))
        QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);

    Data_Base db;
    db.create("100arrays.sqlite");

    if (!db.create_table()) {
        QFAIL("Не удалось создать таблицы");
    }

    QSqlQuery userQuery(db.fortest_database());
    userQuery.prepare("INSERT OR IGNORE INTO users (login, password) VALUES (?, ?)");
    userQuery.addBindValue("test_user");
    userQuery.addBindValue("testpass");
    if (!userQuery.exec()) {
        QFAIL("Не удалось создать тестового пользователя");
    }

    QElapsedTimer timer;
    timer.start();

    int add_count = 0;
    for (int i = 0; i < 100; ++i) {
        int len = 2 + rand() % 98;
        std::vector<int> original(len);
        for (int &x : original) {
            x = (rand() % 2 ? 1 : -1) * (1 + rand() % 10000);
        }

        QString original_text;
        for (size_t j = 0; j < original.size(); ++j) {
            if (j > 0) original_text += " ";
            original_text += QString::number(original[j]);
        }

        std::vector<int> sorted = original;
        Radix_Sort(original, sorted);

        QString sorted_text;
        for (size_t j = 0; j < sorted.size(); ++j) {
            if (j > 0) sorted_text += " ";
            sorted_text += QString::number(sorted[j]);
        }

        if (db.save_data_with_login("test_user", original_text, sorted_text)) {
            ++add_count;
        }
    }

    qint64 add_time = timer.elapsed();
    qInfo() << "Добавлено 100 массивов за" << add_time << "мс.";
    if (add_count == 100) {
        qInfo() << "Успешное добавление";
    } else {
        qInfo() << "Неуспешное добавление (" << add_count << "/100)";
    }

    test_loadrandom_arrays(100);

    QElapsedTimer cleartimer;
    cleartimer.start();
    QSqlQuery clearQuery(db.fortest_database());
    bool cleared = clearQuery.exec("DELETE FROM arrays;");
    qint64 cleartime = cleartimer.elapsed();

    qInfo() << "Очистка 100 записей:" << cleartime << "мс.";
    if (cleared) {
        qInfo() << "Очистка выполнена успешно";
    } else {
        qInfo() << "Очистка не выполнена";
    }
}

void labatest::test_1000_arrays()
{
    srand(time(0));

    if (QSqlDatabase::contains(QSqlDatabase::defaultConnection))
        QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);

    Data_Base db;
    db.create("1000arrays.sqlite");

    if (!db.create_table()) {
        QFAIL("Не удалось создать таблицы");
    }

    QSqlQuery userQuery(db.fortest_database());
    userQuery.prepare("INSERT OR IGNORE INTO users (login, password) VALUES (?, ?)");
    userQuery.addBindValue("test_user");
    userQuery.addBindValue("testpass");
    if (!userQuery.exec()) {
        QFAIL("Не удалось создать тестового пользователя");
    }

    QElapsedTimer timer;
    timer.start();

    int add_count = 0;
    for (int i = 0; i < 1000; ++i) {
        int len = 2 + rand() % 98;
        std::vector<int> original(len);
        for (int &x : original) {
            x = (rand() % 2 ? 1 : -1) * (1 + rand() % 10000);
        }

        QString original_text;
        for (size_t j = 0; j < original.size(); ++j) {
            if (j > 0) original_text += " ";
            original_text += QString::number(original[j]);
        }

        std::vector<int> sorted = original;
        Radix_Sort(original, sorted);

        QString sorted_text;
        for (size_t j = 0; j < sorted.size(); ++j) {
            if (j > 0) sorted_text += " ";
            sorted_text += QString::number(sorted[j]);
        }

        if (db.save_data_with_login("test_user", original_text, sorted_text)) {
            ++add_count;
        }
    }

    qint64 add_time = timer.elapsed();
    qInfo() << "Добавлено 1000 массивов за" << add_time << "мс.";
    if (add_count == 1000) {
        qInfo() << "Успешное добавление";
    } else {
        qInfo() << "Неуспешное добавление (" << add_count << "/1000)";
    }

    test_loadrandom_arrays(1000);

    QElapsedTimer cleartimer;
    cleartimer.start();
    QSqlQuery clearQuery(db.fortest_database());
    bool cleared = clearQuery.exec("DELETE FROM arrays;");
    qint64 cleartime = cleartimer.elapsed();

    qInfo() << "Очистка 1000 записей:" << cleartime << "мс.";
    if (cleared) {
        qInfo() << "Очистка выполнена успешно";
    } else {
        qInfo() << "Очистка не выполнена";
    }
}

void labatest::test_10000_arrays()
{
    srand(time(0));

    if (QSqlDatabase::contains(QSqlDatabase::defaultConnection))
        QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);

    Data_Base db;
    db.create("10000arrays.sqlite");

    if (!db.create_table()) {
        QFAIL("Не удалось создать таблицы");
    }

    QSqlQuery userQuery(db.fortest_database());
    userQuery.prepare("INSERT OR IGNORE INTO users (login, password) VALUES (?, ?)");
    userQuery.addBindValue("test_user");
    userQuery.addBindValue("testpass");
    if (!userQuery.exec()) {
        QFAIL("Не удалось создать тестового пользователя");
    }

    QElapsedTimer timer;
    timer.start();

    int add_count = 0;
    for (int i = 0; i < 10000; ++i) {
        int len = 2 + rand() % 98;
        std::vector<int> original(len);
        for (int &x : original) {
            x = (rand() % 2 ? 1 : -1) * (1 + rand() % 10000);
        }

        QString original_text;
        for (size_t j = 0; j < original.size(); ++j) {
            if (j > 0) original_text += " ";
            original_text += QString::number(original[j]);
        }

        std::vector<int> sorted = original;
        Radix_Sort(original, sorted);

        QString sorted_text;
        for (size_t j = 0; j < sorted.size(); ++j) {
            if (j > 0) sorted_text += " ";
            sorted_text += QString::number(sorted[j]);
        }

        if (db.save_data_with_login("test_user", original_text, sorted_text)) {
            ++add_count;
        }
    }

    qint64 add_time = timer.elapsed();
    qInfo() << "Добавлено 10000 массивов за" << add_time << "мс.";
    if (add_count == 10000) {
        qInfo() << "Успешное добавление";
    } else {
        qInfo() << "Неуспешное добавление (" << add_count << "/10000)";
    }

    test_loadrandom_arrays(10000);

    QElapsedTimer cleartimer;
    cleartimer.start();
    QSqlQuery clearQuery(db.fortest_database());
    bool cleared = clearQuery.exec("DELETE FROM arrays;");
    qint64 cleartime = cleartimer.elapsed();

    qInfo() << "Очистка 10000 записей:" << cleartime << "мс.";
    if (cleared) {
        qInfo() << "Очистка выполнена успешно";
    } else {
        qInfo() << "Очистка не выполнена";
    }
}

void labatest::test_loadrandom_arrays(int db_value)
{
    QElapsedTimer timer;
    timer.start();

    std::vector<int> indices;
    for (int i = 0; i < 100; ++i) {
        indices.push_back(rand() % db_value);
    }

    int success = 0;
    for (int idx : indices) {
        QSqlQuery query;
        query.prepare("SELECT original_data FROM arrays "
                      "WHERE login = 'test_user' "
                      "LIMIT 1 OFFSET ?");
        query.addBindValue(idx);

        if (query.exec() && query.next()) {
            success++;
        }
    }

    double avg_time = static_cast<double>(timer.elapsed()) / 100.0;
    qInfo() << "Среднее время загрузки одного массива (" << db_value << " записей):" << avg_time << "мс";

    if (success == 100) {
        qInfo() << "Успешная выгрузка";
    } else {
        qInfo() << "Неуспешная выгрузка (" << success << "/100)";
    }
}

QTEST_MAIN(labatest)

#include "tst_labatest.moc"
