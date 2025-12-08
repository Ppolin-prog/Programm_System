#ifndef SORT_WITH_RANGE_H
#define SORT_WITH_RANGE_H
#include <QDialog>
#include <QTableWidget>
#include <QSpinBox>

class MainWindow;

namespace Ui {
class Sort_With_Range;
}

class Sort_With_Range : public QDialog
{
    Q_OBJECT

public:
    explicit Sort_With_Range(QTableWidget *table, QSpinBox *rowcount, QWidget *parent = nullptr);
    ~Sort_With_Range();

private slots:
    void on_input_numbers_clicked();

private:
    Ui::Sort_With_Range *ui;
    QTableWidget *main_table;
    QSpinBox *main_rowcount;
};

#endif // SORT_WITH_RANGE_H
