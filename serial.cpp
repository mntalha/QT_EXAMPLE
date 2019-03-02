#include "serial.h"
#include <QtDebug>

serialport::serialport(int portnumber)
{
    serial = new QSerialPort(this);
    this->PortNumber = portnumber;
    serial_init();

}
void serialport::serial_init()
{

     if(PortNumber==1)
     {
         serial->setPortName("ttyUSB0");
         serial->open(QIODevice::ReadWrite);
         serial->setBaudRate(9600);
         serial->setFlowControl(QSerialPort::NoFlowControl);
         serial->setParity(QSerialPort::NoParity);
         serial->setStopBits(QSerialPort::OneStop);
         qDebug()<<"1. port secildi";
     }


     if(PortNumber==2)
     {
     serial->setBaudRate(9600);
     serial->setPortName("ttyAMA1");
     serial->setFlowControl(QSerialPort::NoFlowControl);
     serial->setParity(QSerialPort::NoParity);
     serial->setStopBits(QSerialPort::OneStop);
     serial->open(QIODevice::ReadWrite);
     }
}

void serialport::writeData(QByteArray &data)
{
    serial->write(data);
}

void serialport::readData(QByteArray &RxData)
{

    RxData = serial->readAll();
    while (serial->bytesAvailable()|| serial->waitForReadyRead(50))
            RxData.append(serial->readAll());
}

