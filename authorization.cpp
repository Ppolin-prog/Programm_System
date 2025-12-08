#include "authorization.h"
#include "ui_authorization.h"
#include <QMessageBox>
#include <QSqlQuery>

Authorization::Authorization(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Authorization)
{
    ui->setupUi(this);
    setWindowIcon(QIcon());
    setWindowTitle(" ");

}

Authorization::~Authorization()
{
    delete ui;
}

void Authorization::on_login_clicked()
{
    QString login = ui->input_logname->text();
    QString password = ui->input_logpassword->text();

    if (userbd.authorization_user(login, password)) {
        emit login_success(login);
        QMessageBox::information(this, "Авторизация", "Авторизация прошла успешно");
        accept();
    } else {
        QMessageBox::warning(this, "Ошибка", "Неверный логин или пароль.");
    }

}

