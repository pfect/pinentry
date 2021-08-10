#ifndef PINPAD_H
#define PINPAD_H

#include <QMainWindow>

namespace Ui {
class PinPad;
}

class PinPad : public QMainWindow
{
    Q_OBJECT

public:
    explicit PinPad(QWidget *parent = nullptr);
    ~PinPad();

public slots:
    QString readStatusFifo();
    void writeStatusFifo();
    void writePinCode(char *pinCode);

private slots:
    void on_pinSubmit_clicked();
    void on_connectButton_clicked();
    void on_disconnectButton_clicked();

private:
    Ui::PinPad *ui;

};

#endif // PINPAD_H
