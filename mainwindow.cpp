#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QLabel>
#include <QTableWidgetItem>
#include <QCoreApplication>
#include <QPainter>
#include "authorization.h"
#include "registration.h"
#include "sort_with_range.h"
#include "sort_functions.h"
#include "data_base.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("MSD Radix Sort");

    QString dbPath = QCoreApplication::applicationDirPath() + "/app.sqlite";
    userdatabase.create(dbPath);
    if (!userdatabase.open_data_base()) {
        QMessageBox::critical(this, "Ошибка", "Не удалось открыть базу данных.");
    } else if (!userdatabase.create_table()) {
        QMessageBox::critical(this, "Ошибка", "Не удалось создать таблицу.");
    }

    ui->values_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->count_values->setValue(5);
    ui->count_values->setMinimum(1);
    ui->count_values->setMaximum(10000);
    qApp->setStyleSheet("QMessageBox QLabel { color: white; }" "QMessageBox QPushButton { color: white; }");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::display_current_array()
{
    if (current_index >= 0 && current_index < user_arrays.size()) {
        ui->original_data->setPlainText(user_arrays[current_index].first);
        ui->sort_data->setPlainText(user_arrays[current_index].second);
    }
}

void MainWindow::show_login()
{
    if (current_user.isEmpty()) {
        ui->show_name->setText("");
    } else {
        ui->show_name->setText(current_user);
    }
}

void MainWindow::on_login_account_clicked()
{
    Authorization *authorization = new Authorization(this);
    connect(authorization, &Authorization::login_success, this, [this](const QString &username) {
        current_user = username;
        user_arrays = userdatabase.loading_data(current_user);
        if (!user_arrays.isEmpty()) {
            current_index = 0;
            display_current_array();
        } else {
            current_index = -1;
            ui->original_data->clear();
            ui->sort_data->clear();
        }
        show_login();
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
    int original_count = ui->values_table->rowCount();
    std::vector<int> original;
    original.reserve(original_count);

    for (int i = 0; i < original_count; ++i) {
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

    QString original_text;
    for (size_t i = 0; i < original.size(); ++i) {
        original_text += QString::number(original[i]);
        if (i != original.size() - 1) original_text += " ";
    }
    ui->original_data->setPlainText(original_text);

    std::vector<int> sorted;
    Radix_Sort(original, sorted);

    QString sorted_text;
    for (size_t i = 0; i < sorted.size(); ++i) {
        sorted_text += QString::number(sorted[i]);
        if (i != sorted.size() - 1) sorted_text += " ";
    }
    ui->sort_data->setPlainText(sorted_text);

    if (!current_user.isEmpty()) {
        userdatabase.save_data(current_user, original_text, sorted_text);
        user_arrays = userdatabase.loading_data(current_user);
        if (!user_arrays.isEmpty()) {
            current_index = user_arrays.size() - 1;
            display_current_array();
        }
    }
}

void MainWindow::on_random_clicked()
{
    int original_count = ui->values_table->rowCount();
    ui->values_table->setRowCount(original_count);

    for (int i = 0; i < original_count; i++){
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
    if (!userdatabase.user_exists(current_user)) {
        QMessageBox::warning(this, "Ошибка", "Данного пользователя нет в базе данных.");
        return;
    }

    QString original_text = ui->original_data->toPlainText().trimmed();
    QString sorted_text = ui->sort_data->toPlainText().trimmed();

    if (original_text.isEmpty() || sorted_text.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Нет данных для сохранения.");
        return;
    }
    if (userdatabase.save_data(current_user, original_text, sorted_text)) {
        QMessageBox::information(this, "Сохранение данных", "Данные успешно сохранены");
    } else {
        QMessageBox::critical(this, "Ошибка", "Не удалось сохранить данные.");
    }
}

void MainWindow::on_next_data_clicked()
{
    if (current_index < static_cast<int>(user_arrays.size()) - 1) {
        current_index++;
        display_current_array();
    }
}

void MainWindow::on_back_data_clicked()
{
    if (current_index > 0) {
        current_index--;
        display_current_array();
    }
}
