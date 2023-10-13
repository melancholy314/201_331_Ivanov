#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QSignalMapper"
#include "QListWidgetItem"
#include "QVBoxLayout"
#include "QPushButton"
#include "QMessageBox"
#include "QLabel"
#include "QLineEdit"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    //Переменные для окна ввода пин кода
    QWidget *pin_window;
    QLineEdit *input_pincode;

    //Хранилище
    QList<QPushButton *> game_btn_list; //Хранение кнопок
    int list_of_number[9]; //Хранение рандомных чисел
    int count_of_click = 0; //Количество нажатий
    int sum = 0; // Общая сумма

    //Функции
    QPushButton* create_game_btn(int id);//Функция создание одной кнопки
    QSignalMapper *game_mapper;//отслеживание кнопки копирования логина
    void show_pin_check_window();//Функция показа окна для ввода pincode
    int show_game_window();//Функция показа основного игрового окна
    int reset();//Функция сброса игрового поля

private slots:
    int check_pin_code();
    int on_click_game_btn (int id);
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
