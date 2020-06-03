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
    setUpConnectionMathBtns();

    connect(ui->btnEqual, &QPushButton::released, this, &Calculator::equalBtnPressed);
    connect(ui->btnClear, &QPushButton::released, this, &Calculator::clear);
    connect(ui->btnChangeSign, &QPushButton::released, this, &Calculator::changeNumberSign);

    QKeyEvent *event;
    keyPressEvent(event);
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

    for(int i = 0; i < AMOUNT_NUM_BTN; i++) {
        // btnName should be exactly the object button name.
        QString btnName = "btn" + QString::number(i);

        // Search a button provided by name.
        numButtons.append(Calculator::findChild<QPushButton *>(btnName));

        // Make a connection when a button is released.
        connect(numButtons.at(i), &QPushButton::released, this, &Calculator::numBtnPressed);
    }
}

void Calculator::setUpConnectionMathBtns()
{
    connect(ui->btnAdd, &QPushButton::released, this, &Calculator::mathBtnPressed);
    connect(ui->btnSub, &QPushButton::released, this, &Calculator::mathBtnPressed);
    connect(ui->btnMult, &QPushButton::released, this, &Calculator::mathBtnPressed);
    connect(ui->btnDivision, &QPushButton::released, this, &Calculator::mathBtnPressed);
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

void Calculator::resetTriggers() {
    divTrigger = false;
    mulTrigger = false;
    addTrigger = false;
    subTrigger = false;
}

void Calculator::setTriggers(const QString &btnValue) {
    // If any arithmetic operation is clicked.
    if(QString::compare(btnValue, "*", Qt::CaseInsensitive) == 0) {
        mulTrigger = true;
    } else if(QString::compare(btnValue, "/", Qt::CaseInsensitive) == 0) {
        divTrigger = true;
    } else if(QString::compare(btnValue, "+", Qt::CaseInsensitive) == 0) {
        addTrigger = true;
    } else {
        subTrigger = true;
    }
}

double Calculator::getResult() const
{
    double solution = 0.0;
    QString displayVal = ui->display->text();
    double dblDisplayBal = displayVal.toDouble();

    if(mulTrigger) {
        solution = currentVal * dblDisplayBal;
    } else if(divTrigger) {
        solution = currentVal / dblDisplayBal;
    } else if(addTrigger) {
        solution = currentVal + dblDisplayBal;
    } else {
        solution = currentVal - dblDisplayBal;
    }

    return solution;
}

void Calculator::numKeyPressed(QKeyEvent *event)
{
    QString keyValue = event->text();
    QString displayValue = ui->display->text();

    setDisplayValue(keyValue, displayValue);
}

void Calculator::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()) {
        case Qt::Key_0:
            numKeyPressed(event);
        break;
        case Qt::Key_1:
            numKeyPressed(event);
        break;
        case Qt::Key_2:
            numKeyPressed(event);
        break;
        case Qt::Key_3:
            numKeyPressed(event);
        break;
        case Qt::Key_4:
            numKeyPressed(event);
        break;
        case Qt::Key_5:
            numKeyPressed(event);
        break;
        case Qt::Key_6:
            numKeyPressed(event);
        break;
        case Qt::Key_7:
            numKeyPressed(event);
        break;
        case Qt::Key_8:
            numKeyPressed(event);
        break;
        case Qt::Key_9:
            numKeyPressed(event);
        break;
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

void Calculator::mathBtnPressed() {
    resetTriggers();

    QPushButton *btn = (QPushButton *)sender();
    QString btnValue = btn->text();
    QString displayVal = ui->display->text();
    currentVal = displayVal.toDouble();
    setTriggers(btnValue);

    // We clear the display because we are going to insert a new value to do the operation.
    ui->display->clear();
}

void Calculator::equalBtnPressed() {
    double solution = getResult();
    ui->display->setText(QString::number(solution));
}

void Calculator::changeNumberSign() {
    QString displayVal = ui->display->text();

    /* Math the character - between 0 and 1 times in the range 0-9 between 0 and unlimited times. */
    QRegExp reg("[-]?[0-9]*");

    if(reg.exactMatch(displayVal)) {
        double dblDisplayVal = displayVal.toDouble();
        double dblDisplayValSign = -1 * dblDisplayVal;
        ui->display->setText(QString::number(dblDisplayValSign));
    }
}

void Calculator::clear()
{
    currentVal = 0.0;
    resetTriggers();
    ui->display->setText("0.0");
}



