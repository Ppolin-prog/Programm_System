#ifndef REGISTRATION_H
#define REGISTRATION_H
#include "data_base.h"
#include <QDialog>

namespace Ui {
class Registration;
}

class Registration : public QDialog
{
    Q_OBJECT

public:
    explicit Registration(QWidget *parent = nullptr);
    ~Registration();

private slots:
    void on_registration_button_clicked();

private:
    Ui::Registration *ui;
    Data_Base userbd;
};

#endif // REGISTRATION_H
