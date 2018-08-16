#include "serialport.h"

serialport::serialport(QObject *parent) : QObject(parent){
    m_serialport = nullptr;
    m_portname = "";
    m_baudrate = QSerialPort::UnknownBaud;
    m_databits = QSerialPort::UnknownDataBits;
    m_stopbits = QSerialPort::UnknownStopBits;
    m_parity = QSerialPort::UnknownParity;
    m_flowcontrol = QSerialPort::UnknownFlowControl;
    m_isOpen = false;
}

serialport::~serialport(){
    if(m_serialport){
        if(m_isOpen)
            m_serialport->close();
        delete m_serialport;
    }
}

void serialport::listSerialPort(QList<QSerialPortInfo> &list){
    list.clear();
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
            list.append(info);
    }
}

bool serialport::open(QString portname,
                      QSerialPort::BaudRate baudrate,
                      QSerialPort::DataBits databits,
                      QSerialPort::StopBits stopbits,
                      QSerialPort::Parity parity,
                      QSerialPort::FlowControl flowcontrol,
                      QIODevice::OpenMode mode){
    m_portname = portname;
    m_baudrate = baudrate;
    m_databits = databits;
    m_stopbits = stopbits;
    m_parity = parity;
    m_flowcontrol = flowcontrol;

    m_serialport = new QSerialPort(this);

    if(!m_serialport && !m_isOpen){
        qDebug()<<"serialport error";
        return false;
    }

    /* Set serialport name */
    m_serialport->setPortName(m_portname);

    /* Set serialport baudrate */
    m_serialport->setBaudRate(m_baudrate,QSerialPort::AllDirections);

    /* Set serialport databits */
    m_serialport->setDataBits(m_databits);

    /* Set serialport stopbit */
    m_serialport->setStopBits(m_stopbits);

    /* Set serialport parity */
    m_serialport->setParity(m_parity);

    /* Set serialport flowcontrol */
    m_serialport->setFlowControl(m_flowcontrol);

    if (m_serialport->open(mode))
        qDebug()<<"open serialport success";
    else{
        qDebug()<<"open serialport failed";
        return false;
    }

    connect(m_serialport, SIGNAL(readyRead()), this, SLOT(recv()));

    connect(m_serialport, SIGNAL(error(QSerialPort::SerialPortError)),this, SLOT(errorHandle(QSerialPort::SerialPortError)));

    m_isOpen = true;

    return true;
}

int serialport::send(const char *data, qint64 size){
    int ret = -1;
    if(m_isOpen)
        ret = m_serialport->write(data, size);
    return ret;
}

int serialport::recv(){
    int ret = -1;
    QByteArray bytearray = m_serialport->readAll();
    sigRecvDatas(bytearray);
    ret = bytearray.size();
    return ret;
}

void serialport::errorHandle(QSerialPort::SerialPortError){
    qDebug()<<m_serialport->errorString();
    m_serialport->close();
    m_isOpen = false;
}

void serialport::close(){
    if(m_serialport){
        if(m_isOpen)
            m_serialport->close();
        m_isOpen = false;
    }
}

