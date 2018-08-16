#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QObject>
#include <QList>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>

class serialport : public QObject{
    Q_OBJECT
public:
    explicit serialport(QObject *parent = 0);

    ~serialport();

signals:
    void sigRecvDatas(QByteArray &bytearray);

public slots:
    void listSerialPort(QList<QSerialPortInfo> &list);

    bool open(QString portname,
              QSerialPort::BaudRate baudrate,
              QSerialPort::DataBits databits,
              QSerialPort::StopBits stopbits,
              QSerialPort::Parity parity,
              QSerialPort::FlowControl flowcontrol,
              QIODevice::OpenMode mode = QIODevice::ReadWrite
              );

    int send(const char *data, qint64 size);

    int recv();

    void errorHandle(QSerialPort::SerialPortError);

    void close();

private:
    QSerialPort *m_serialport;

    QString m_portname;
    QSerialPort::BaudRate m_baudrate;
    QSerialPort::DataBits m_databits;
    QSerialPort::StopBits m_stopbits;
    QSerialPort::Parity m_parity;
    QSerialPort::FlowControl m_flowcontrol;

    bool m_isOpen;
};

#endif // SERIALPORT_H
