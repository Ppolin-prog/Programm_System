#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "data_base.h"
#include <QMainWindow>
#include <QCoreApplication>
#include <QWidget>
#include <QImage>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:

    void on_login_account_clicked();
    void on_registration_account_clicked();
    void on_random_range_clicked();
    void on_count_values_valueChanged(int value);
    void on_information_clicked();
    void on_sort_button_clicked();
    void on_random_clicked();
    void on_data_save_clicked();
    void show_login();
    void display_current_array();
    void on_next_data_clicked();
    void on_back_data_clicked();

private:
    Ui::MainWindow *ui;
    Data_Base userdatabase;
    QVector<QPair<QString, QString>> user_arrays;
    QString current_user;
    int current_index = -1;
    QImage wallpaper;
};
#endif // MAINWINDOW_H
