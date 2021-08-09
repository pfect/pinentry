/*
 * Nitrokey enchanced glorytun key loader user interface
 *
 * Copyright (C) 2021 Pasi Patama
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 */
#include "pinpad.h"
#include "ui_pinpad.h"
#include <QFile>
#include <QTimer>
#include <QDebug>
#include <QTime>
#include <QProcess>
#include <QNetworkInterface>
#include <QObject>
#include <usb.h>


#define NK_STATUS_FIFO_FILE       "/tmp/nk_status"
#define PIN_CODE_FIFO_FIFLE       "/tmp/pincode"

PinPad::PinPad(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PinPad)
{
    ui->setupUi(this);

}

void PinPad:: writePinCode(char *pinCode)
{
    FILE *fp;
    if((fp = fopen(PIN_CODE_FIFO_FIFLE, "w")) == NULL) {
         perror("fopen");
         exit(1);
    }
    fputs(pinCode, fp);
    fclose(fp);
}

void PinPad::writeStatusFifo()
{
    FILE *fp;
    if((fp = fopen(NK_STATUS_FIFO_FILE, "w")) == NULL) {
         perror("fopen");
         exit(1);
    }
    fputs("", fp);
    fclose(fp);
}

QString PinPad::readStatusFifo()
{
    QString statusFifo;
    QFile file(NK_STATUS_FIFO_FILE);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return "";
    if(file.bytesAvailable()){
        statusFifo = file.readLine();
        ui->statusLabel->setText(statusFifo);
        qDebug() <<  QTime::currentTime().toString() << " " << statusFifo;
        writeStatusFifo();
        if ( statusFifo.contains("waiting for pin") )
        {
            ui->pinCode->setFocus();
            ui->pinNotify->setStyleSheet("background-color: rgb(239, 41, 41);");
        }
        if ( statusFifo.contains("Got pin") )
        {
            ui->pinCode->setFocus();
            ui->pinNotify->setStyleSheet("background-color: rgb(239, 239, 41);");
        }
        if ( statusFifo.contains("NK key loaded!") )
        {
            ui->pinNotify->setStyleSheet("background-color: rgb(41, 239, 41);");
        }
    }

    // Get interface names & ip
    QList<QNetworkInterface> ifaces = QNetworkInterface::allInterfaces();
    if ( !ifaces.isEmpty() )
    {
      for(int i=0; i < ifaces.size(); i++)
      {
        QList<QNetworkAddressEntry> addresses = ifaces[i].addressEntries();
        QString interfaceName = ifaces[i].humanReadableName();
        for(int a=0; a < addresses.size(); a++)
        {
          QString ip = addresses[a].ip().toString();
          // qDebug() << "possible address: " << interfaceName << "->" << ip;

          if ( interfaceName.contains("tun0") ) {
              ui->interface_1_status->setStyleSheet("background-color: rgb(41, 239, 41);");
              ui->interface_1_status->setText("🔑");
              ui->interface_1_status->setToolTip(interfaceName + ":" +ip);
              ui->key_1->setVisible(false);
          }
          if ( interfaceName.contains("tun1") ) {
              ui->interface_2_status->setStyleSheet("background-color: rgb(41, 239, 41);");
              ui->interface_2_status->setText("🔑");
              ui->interface_2_status->setToolTip(interfaceName + ":" +ip);
              ui->key_2->setVisible(false);
          }
          if ( interfaceName.contains("tun2") ) {
              ui->interface_3_status->setStyleSheet("background-color: rgb(41, 239, 41);");
              ui->interface_3_status->setText("🔑");
              ui->interface_3_status->setToolTip(interfaceName + ":" +ip);
              ui->key_2->setVisible(false);
          }

        }
      }
    }
    return statusFifo;
}

void PinPad::on_pinSubmit_clicked()
{
    QString pinCode=ui->pinCode->text();
    QByteArray ba = pinCode.toLocal8Bit();
    char *c_pinCode = ba.data();
    writePinCode(c_pinCode);

}

PinPad::~PinPad()
{
    delete ui;
}

void PinPad::on_connectButton_clicked()
{
    QProcess *p = new QProcess(this);
    QString program="/opt/glorytun/start.sh";
    QString arguments = "";
    p->start(program,QStringList() << arguments);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(readStatusFifo()));
    timer->start(500);

    ui->pinSubmit->setEnabled(true);
}

void PinPad::on_disconnectButton_clicked()
{
    QProcess *p = new QProcess(this);
    QString program="/opt/glorytun/stop.sh";
    QString arguments = "";
    p->start(program,QStringList() << arguments);
    ui->statusLabel->setText("Disconnected");
    ui->pinCode->setText("");
    ui->pinNotify->setStyleSheet("");

    ui->interface_1_status->setStyleSheet("");
    ui->interface_2_status->setStyleSheet("");
    ui->interface_3_status->setStyleSheet("");
    ui->interface_1_status->setText("");
    ui->interface_2_status->setText("");
    ui->interface_3_status->setText("");
    ui->interface_1_status->setToolTip("");
    ui->interface_1_status->setToolTip("");
    ui->interface_1_status->setToolTip("");
    ui->pinSubmit->setEnabled(false);
    ui->key_1->setVisible(true);
    ui->key_2->setVisible(true);

}
