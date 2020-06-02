#include "calculator.h"
#include "ui_calculator.h"

#include <iostream>

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);

    ui->display->setReadOnly(true);
    setUpInterfaceStyle();
    setUpConnectionNumBtns();

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

void Calculator::setUpConnectionNumBtns()
{
    ui->display->setText(QString::number(currentVal));
    QVector<QPushButton *> numButtons;

    for(int i = 0; i < AMOUNT_NUM_BTN; i++) {
        // btnName should be exactly the object button name.
        QString btnName = "btn" + QString::number(i);

        // Search a button provided by name.
        numButtons.append(Calculator::findChild<QPushButton *>(btnName));

        // Make a connection when a button is released.
        connect(numButtons.at(i), &QPushButton::released, this, &Calculator::numBtnPressed);
    }
}

void Calculator::setDisplayValue(const QString &btnValue, const QString &displayVal) {
    // There is not value in our display.
    if(displayVal.toDouble() == 0 or displayVal.toDouble() == 0.0) {
        ui->display->setText(btnValue);
    }
    // If there is already a number in our display.
    else {
        QString newValue = displayVal + btnValue;
        double dlbNewValue = newValue.toDouble();

        // 'g' will use 'e' or 'E' format with 16 digitis precision.
        ui->display->setText(QString::number(dlbNewValue, 'g', 16));
    }
}

/************************* SLOTS ***************************************************/

void Calculator::numBtnPressed()
{
    // Get the button who originated the signal.
    QPushButton *btnPressed = (QPushButton *)sender();
    QString btnValue = btnPressed->text();
    QString displayValue = ui->display->text();

    setDisplayValue(btnValue, displayValue);
}

void Calculator::mathBtnPressed()
{

}

void Calculator::equalBtnPressed() {

}

void Calculator::changeNumberSign() {

}



