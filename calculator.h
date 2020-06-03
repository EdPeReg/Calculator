#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QPushButton>

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

    /* Will set up the connection for the math buttons. */
    void setUpConnectionMathBtns();

    /* The new values pressed from the number buttons will be shown in our display.
       @param btnVal will be the value from the button pressed.
       @param displayVal will be the value from our display.
       @return None. */
    void setDisplayValue(const QString &btnVal, const QString &displayVal);

    /* Will reset all the triggers to their defaul values. */
    void resetTriggers();

    /* Will set the corresponding trigger depending of the button operation was pressed. */
    void setTriggers(const QString& btnValue);

    /* Will get the result of the operation. */
    double getResult() const;

    /* Will get which key from 0-9 was pressed and set up into the display.
       @param event will be the event from the keyboard. */
    void numKeyPressed(QKeyEvent *event);
private:
    Ui::Calculator *ui;

    QVector<QPushButton *> numButtons;

    double currentVal = 0.0;

    // 0-9 buttons.
    const int AMOUNT_NUM_BTN = 10;
    bool  divTrigger = false;
    bool  mulTrigger = false;
    bool  addTrigger = false;
    bool  subTrigger = false;

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    /* Will get which button from 0-9 was pressed and set up into the display. */
    void numBtnPressed();

    /* Will check when an operation button is pressed. */
    void mathBtnPressed();

    /* Will do the final result. */
    void equalBtnPressed();
    void changeNumberSign();
    void clear();
};
#endif // CALCULATOR_H
