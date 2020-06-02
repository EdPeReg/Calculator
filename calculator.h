#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Calculator; }
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

    /* Will set up the calculator's interface. */
    void setUpInterfaceStyle();

    /* Will set up the connections from the buttons 0-9. */
    void setUpConnectionNumBtns();

private:
    Ui::Calculator *ui;

    double currentVal = 0.0;

    // 0-9 buttons.
    const int AMOUNT_NUM_BTN = 10;
    bool  divTrigger = false;
    bool  mulTrigger = false;
    bool  addTrigger = false;
    bool  subTrigger = false;

private slots:
    void numBtnPressed();
    /*void mathBtnPressed();
    void equalBtnPressed();
    void changeNumberSign();*/
};
#endif // CALCULATOR_H
