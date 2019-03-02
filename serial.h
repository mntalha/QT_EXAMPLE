#ifndef SERIAL_H
#define SERIAL_H

#include <QCoreApplication>
#include<QtSerialPort/QtSerialPort>

class serialport : public QObject
{
   Q_OBJECT
public:
     serialport (int portnumber);
     int PortNumber;
     QSerialPort *serial;


signals:

public slots:
    void serial_init();
    void writeData(QByteArray &data);
    void readData(QByteArray &RxData);
    
private:



};
#endif // SERIAL_H
