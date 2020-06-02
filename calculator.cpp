#include "calculator.h"
#include "ui_calculator.h"

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);

    setUpInterfaceStyle();
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::setUpInterfaceStyle() {
    QList<QPushButton *> btnOperMem = {ui->btnAdd, ui->btnSub, ui->btnMult, ui->btnDivision,
                                       ui->btnMemAdd, ui->btnMemGet, ui->btnMemClear};

    setStyleSheet("QPushButton { "
                        "background-color: #C0C0C0;"
                        "border: 1px solid gray;"
                        "padding: 3px; }"

                  "QPushButton:pressed {"
                        "background-color: #A9A9A9;"
                        "border: 1px solid gray;"
                        "padding: 3px; }"

                  "QLineEdit {"
                        "background-color: #b6bab7;"
                        "color: white;"
                        "border: 2px solid gray;"
                        "font-family: 'monospace';"
                        "font-size: 30px;"
                        "font-weight: bold; }");


    for(auto btn : btnOperMem) {
        btn->setStyleSheet("QPushButton {"
                               "background-color: yellow; } "

                           "QPushButton:pressed {"
                               "background-color: #bdb326; }");
    }

    ui->btnEqual->setStyleSheet("QPushButton {"
                                    "background-color: yellow; }"

                                "QPushButton:pressed {"
                                    "background-color: #bdb326; }");

    ui->display->setText("0.0");
    ui->display->setAlignment(Qt::AlignRight);
}
