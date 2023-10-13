#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPushButton"
#include "QMessageBox"
#include "QRandomGenerator"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::show_pin_check_window() {

    pin_window = new QWidget(); //Создание виджета как окна для ввода пин кода
    pin_window->setGeometry(683,350,270,120);

    QVBoxLayout *layout_pin = new QVBoxLayout;

    QLabel *pin_code_label = new QLabel("Пин код"); //Лейбл для пинкода
    input_pincode = new QLineEdit(); // Инпут для пинкода
    input_pincode->setEchoMode(QLineEdit::Password);

    QPushButton *check_pin_btn = new QPushButton("Вход"); //Кнопка для проверки
    connect(check_pin_btn, SIGNAL(clicked()), this, SLOT(check_pin_code())); //При нажатии на кнопку отправляемся в функцию проверки

    //Добавляем в окно лейбл кнопку и инпут
    layout_pin->addWidget(pin_code_label);
    layout_pin->addWidget(input_pincode);
    layout_pin->addWidget(check_pin_btn);
    pin_window->setLayout(layout_pin);

    pin_window->show();
}

int MainWindow::check_pin_code() {
    const QString orig_code = "1234";
    QString code = input_pincode->text();

    if (orig_code == code) {
        delete[] pin_window;
        this->show_game_window(); //запускаем основное окно
        this->show();
        return 0;

    }
    else {
        QMessageBox::critical(NULL,QObject::tr("Ошибка"),tr("Ошибка ввода пин-кода"));
        return 0;
    }
}


int MainWindow::show_game_window() {
    //Создание маперов для кнопок
    game_mapper = new QSignalMapper(this);
    QObject::connect(game_mapper,SIGNAL(mappedInt(int)),this,SLOT(on_click_game_btn(int))); //сигнал передачу id кнопки при нажатии на кнопку

    list_of_number[9]; //Массив хранит в себе значения рандомных чисел

    //Создание кнопок
    for (int i = 0; i < 9; i++) {
        QPushButton* game_btn = create_game_btn(i); //Создание кнопки
        game_btn_list.push_back(game_btn); // Добавление в общий лист

        quint32 number = QRandomGenerator::global()->bounded(-1000,1000); //Создание рандомного числа
        list_of_number[i] = (int)number;//Добавление в масив рандомных чисел

    }

    //Добавление кнопок в графическое окно
    for (int i = 0; i < game_btn_list.length();) {
        QHBoxLayout *Hlayout = new QHBoxLayout;
        for (int j = 0; j < 3; j++, i++) {
            Hlayout->addWidget(game_btn_list[i]);//Добавляем в гориз лайаут кнопку из листа
        }
        ui->verticalLayout->addLayout(Hlayout);
    }
    return 0;
}

QPushButton* MainWindow::create_game_btn(int id) {
    QPushButton *current_game_btn = new QPushButton("Click");//Создание кнопки

    game_mapper->setMapping(current_game_btn, id); //Вместе с кнопкой передаем id
    connect(current_game_btn,SIGNAL(clicked()),game_mapper,SLOT(map())); //слот на передачу при нажатии

    return current_game_btn;
}

int MainWindow::on_click_game_btn (int id) {
    count_of_click = count_of_click + 1; //Счет кликов

    sum = ui->label_of_sum->text().toInt();// Получаем переменную суммы

    game_btn_list[id]->setText(QString::number(list_of_number[id]));//Вскрываем число кнопки

    ui->label_of_sum->setText(QString::number(sum + list_of_number[id])); // Обновляем переменную sum

    //Если 3 нажатия на кнопку
    if (count_of_click >= 3) {
        //Вывод суммы в отдельном окне
        QMessageBox::information(this, "Information", "Your sum is " + QString::number(ui->label_of_sum->text().toInt()));

        //Сбрасываем поле
        reset();
        return 0;
    }

    return 0;
}

int MainWindow::reset() {
    return 0;
}

void MainWindow::on_pushButton_clicked()
{
    reset();
}

