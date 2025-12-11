#include "sort_with_range.h"
#include "ui_sort_with_range.h"
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QSpinBox>

Sort_With_Range::Sort_With_Range(QTableWidget *table, QSpinBox *rowcount, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Sort_With_Range)
    , main_table(table)
    , main_rowcount(rowcount)
{
    ui->setupUi(this);
    setWindowTitle(" ");
}

Sort_With_Range::~Sort_With_Range()
{
    delete ui;
}

void Sort_With_Range::on_input_numbers_clicked()
{
    QString start_num = ui->input_start->text();
    QString end_num = ui->input_end->text();
    bool right, good;
    int first_number = start_num.toInt(&right);
    int second_number = end_num.toInt(&good);
    if (!right or !good){
        QMessageBox::warning(this, "Ошибка", "Введите целые числа");
        return;
    }
    else if (first_number >= second_number){
        QMessageBox::warning(this, "Ошибка", "Начало диапазона должно быть меньше конца");
        return;
    }

    int row_count = main_rowcount->value();
    main_table->setRowCount(row_count);

    for (int i = 0; i < row_count; i++){
        int value = (rand() % (second_number - first_number + 1) + first_number);
        main_table->setItem(i, 0, new QTableWidgetItem(QString::number(value)));
    }

    QWidget::close();
}
