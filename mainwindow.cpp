#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QLabel>
#include <QTableWidgetItem>
#include "authorization.h"
#include "registration.h"
#include "sort_with_range.h"
#include "sort_functions.h"
#include "data_base.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , userdatabase(nullptr)
{
    ui->setupUi(this);
    userdatabase = new Data_Base(this);
    userdatabase->create("app.sqlite");
    setWindowIcon(QIcon());
    setWindowTitle("MSD Radix Sort");

    ui->values_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->count_values->setValue(5);
    ui->count_values->setMinimum(1);
    ui->count_values->setMaximum(10000);

    if (!userdatabase->openpopen()) {
        QMessageBox::critical(this, "Ошибка",  "Не удалось открыть базу данных.");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_login_account_clicked()
{
    Authorization *authorization = new Authorization(this);
    connect(authorization, &Authorization::login_success, this, [this](const QString &username) {
       current_user = username;
        QString raw, sorted;
        if (userdatabase->loading_data(username, raw, sorted)) {
            ui->raw_data->setPlainText(raw);
            ui->sort_data->setPlainText(sorted);
        }
    });
    authorization->exec();
}


void MainWindow::on_registration_account_clicked()
{
    Registration reg_account;
    reg_account.setModal(true);
    reg_account.exec();
}

void MainWindow::on_random_range_clicked()
{
    Sort_With_Range range_values(ui->values_table, ui->count_values, this);
    range_values.setModal(true);
    range_values.exec();
}

void MainWindow::on_count_values_valueChanged(int value)
{
    ui->values_table->setRowCount(value);
}

void MainWindow::on_information_clicked()
{
    QMessageBox::information(this, "Информация о приложении", "Приложение создано для использоватния MSD сортировки.\n"
                                                              "В нем существует возможно регистрации/входа в аккаунт\n"
                                                              "для сохранения результатов сортировки.\n"
                                                              "Существует самостоятельный ввод значений и генерация случайных чисел.");
}

void MainWindow::on_sort_button_clicked()
{
    int row_count = ui->values_table->rowCount();
    std::vector<int> original;
    original.reserve(row_count);

    for (int i = 0; i < row_count; ++i) {
        QTableWidgetItem *item = ui->values_table->item(i, 0);
        if (!item || item->text().trimmed().isEmpty()) {
            QMessageBox::warning(this, "Ошибка",
                                 QString("Пустая ячейка в строке %1").arg(i + 1));
            return;
        }

        bool rigth;
        int value = item->text().toInt(&rigth);
        if (!rigth) {
            QMessageBox::warning(this, "Ошибка",
                                 QString("Некорректное целое число в строке %1").arg(i + 1));
            return;
        }
        original.push_back(value);
    }

    QString raw_text;
    for (size_t i = 0; i < original.size(); ++i) {
        raw_text += QString::number(original[i]);
        if (i != original.size() - 1) raw_text += " ";
    }
    ui->raw_data->setPlainText(raw_text);

    std::vector<int> sorted;
    Radix_Sort(original, sorted);

    QString sorted_text;
    for (size_t i = 0; i < sorted.size(); ++i) {
        sorted_text += QString::number(sorted[i]);
        if (i != sorted.size() - 1) sorted_text += " ";
    }
    ui->sort_data->setPlainText(sorted_text);

}

void MainWindow::on_random_clicked()
{
    int row_count = ui->values_table->rowCount();
    ui->values_table->setRowCount(row_count);

    for (int i = 0; i < row_count; i++){
        int value = (rand() * (rand() % 2 ? 1: -1));
        ui->values_table->setItem(i, 0, new QTableWidgetItem(QString::number(value)));
    }
}



void MainWindow::on_data_save_clicked()
{
    if (current_user.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Сохранение данных не осуществимо без входа в аккаунт.");
        return;
    }

    if (!userdatabase->user_exists(current_user)) {
        QMessageBox::warning(this, "Ошибка", "Данного пользователя нет в базе данных.");
        return;
    }

    QString rawtext = ui->raw_data->toPlainText().trimmed();
    QString sortedtext = ui->sort_data->toPlainText().trimmed();

    if (rawtext.isEmpty() || sortedtext.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Нет данных для сохранения.");
        return;
    }

    if (userdatabase->save_data(current_user, rawtext, sortedtext)) {
        QMessageBox::information(this, "Сохранение данных", "Данные успешно сохранены");
    } else {
        QMessageBox::critical(this, "Ошибка", "Не удалось сохранить данные.");
    }

}

