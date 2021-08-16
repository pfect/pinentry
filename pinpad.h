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
    void on_connectButton_1_clicked();
    void on_connectButton_2_clicked();
    void on_connectButton_3_clicked();
    void on_connectButton_4_clicked();
    void on_connectButton_5_clicked();
    void on_connectButton_6_clicked();
    void on_disconnectButton_clicked();
    void resetConActiveColors();
    void startConnection();
    void stopConnection();

private:
    Ui::PinPad *ui;
    void readSettings(int id);
    void writeSettings(int id, QString connectionName);
};

#endif // PINPAD_H
