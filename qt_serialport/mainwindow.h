#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPortInfo>
#include <QList>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QLineEdit>

#include <QDebug>

#include "serialport.h"

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void recvDatas(QByteArray &bytearray);

    void sendDatas();

    void clearRecvDatas();

    void clearSendDatas();

    void init();

    void openSerial(bool stat);

private:
    QComboBox m_cmb_portname;
    QComboBox m_cmb_baudrate;
    QComboBox m_cmb_databits;
    QComboBox m_cmb_stopbits;
    QComboBox m_cmb_parity;
    QComboBox m_cmb_flowcontrol;

    QLabel m_lb_portname;
    QLabel m_lb_baudrate;
    QLabel m_lb_databits;
    QLabel m_lb_stopbits;
    QLabel m_lb_parity;
    QLabel m_lb_flowcontrol;
    QLabel m_lb_send;
    QLabel m_lb_recv;

    QPushButton m_btn_open;
    QPushButton m_btn_send;
    QPushButton m_btn_sclear;
    QPushButton m_btn_rclear;

    QLineEdit m_le_recv;
    QLineEdit m_le_send;

    QString m_portname;
    QSerialPort::BaudRate m_baudrate;
    QSerialPort::DataBits m_databits;
    QSerialPort::StopBits m_stopbits;
    QSerialPort::Parity m_parity;
    QSerialPort::FlowControl m_flowcontrol;

    QList<QSerialPortInfo> m_list;

    serialport *m_serial;
};

#endif // MAINWINDOW_H
