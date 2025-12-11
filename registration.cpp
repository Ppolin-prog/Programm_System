#include "registration.h"
#include "ui_registration.h"
#include <QMessageBox>
#include <QSqlQuery>

Registration::Registration(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Registration)
{
    ui->setupUi(this);
    setWindowTitle(" ");
    ui->input_regname->setMaxLength(35);
    ui->input_regpassword->setMaxLength(100);
}

Registration::~Registration()
{
    delete ui;
}

void Registration::on_registration_button_clicked()
{
    QString login = ui->input_regname->text();
    QString password = ui->input_regpassword->text();

    if (login.isEmpty() and password.isEmpty()){
        QMessageBox::warning(this, "Ошибка", "Логин и пароль должны содержать хотя бы один символ");
    }
    else if (login.isEmpty()){
        QMessageBox::warning(this, "Ошибка", "Логин должен содержать хотя бы один символ");
    }
    else if (password.isEmpty()){
        QMessageBox::warning(this, "Ошибка", "Пароль должен содержать хотя бы один символ");
    }
    else {
        QMessageBox::information(this, "Регистрация", "Регистрация прошла успешно");
        QWidget::close();
    }
    if (userbd.user_exists(login)) {
        QMessageBox::warning(this, "Ошибка", "Пользователь с таким логином уже существует");
        return;
    }

    bool success = userbd.registration_user(login, password);

    if (!success) {
        QMessageBox::critical(this, "Ошибка", "Не удалось сохранить данные. Попробуйте снова.");
    }

}
