#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H
#include "data_base.h"
#include <QDialog>

namespace Ui {
class Authorization;
}

class Authorization : public QDialog
{
    Q_OBJECT

public:
    explicit Authorization(QWidget *parent = nullptr);
    ~Authorization();

private slots:

    void on_login_clicked();

private:
    Ui::Authorization *ui;
    Data_Base userbd;

signals:
    void login_success(const QString &username);
};

#endif // AUTHORIZATION_H
