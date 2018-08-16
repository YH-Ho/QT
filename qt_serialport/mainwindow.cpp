#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent){
    this->setFixedSize(400,270);

    m_lb_portname.setParent(this);
    m_lb_portname.setGeometry(5,5,100,30);
    m_lb_portname.setText("PortName:");

    m_lb_baudrate.setParent(this);
    m_lb_baudrate.setGeometry(5,40,100,30);
    m_lb_baudrate.setText("Baudrate:");

    m_lb_databits.setParent(this);
    m_lb_databits.setGeometry(5,75,100,30);
    m_lb_databits.setText("DataBits:");

    m_lb_stopbits.setParent(this);
    m_lb_stopbits.setGeometry(5,110,100,30);
    m_lb_stopbits.setText("StopBits");

    m_lb_parity.setParent(this);
    m_lb_parity.setGeometry(5,145,100,30);
    m_lb_parity.setText("Parity:");

    m_lb_flowcontrol.setParent(this);
    m_lb_flowcontrol.setGeometry(5,180,100,30);
    m_lb_flowcontrol.setText("FlowControl:");

    m_lb_recv.setParent(this);
    m_lb_recv.setGeometry(225,5,100,30);
    m_lb_recv.setText("Recv:");

    m_lb_send.setParent(this);
    m_lb_send.setGeometry(225,120,100,30);
    m_lb_send.setText("Send:");

    /* UI of Serial port name */
    m_cmb_portname.setParent(this);
    m_cmb_portname.setGeometry(106,5,100,30);

    /* UI of Serial port baudrate */
    m_cmb_baudrate.setParent(this);
    m_cmb_baudrate.setGeometry(106,40,100,30);
    m_cmb_baudrate.addItem("Unknown");
    m_cmb_baudrate.addItem("1200");
    m_cmb_baudrate.addItem("2400");
    m_cmb_baudrate.addItem("4800");
    m_cmb_baudrate.addItem("9600");
    m_cmb_baudrate.addItem("19200");
    m_cmb_baudrate.addItem("38400");
    m_cmb_baudrate.addItem("57600");
    m_cmb_baudrate.addItem("115200");

    /* UI of Serial port data bits */
    m_cmb_databits.setParent(this);
    m_cmb_databits.setGeometry(106,75,100,30);
    m_cmb_databits.addItem("Unknown");
    m_cmb_databits.addItem("5");
    m_cmb_databits.addItem("6");
    m_cmb_databits.addItem("7");
    m_cmb_databits.addItem("8");

    /* UI of Serial port stop bits */
    m_cmb_stopbits.setParent(this);
    m_cmb_stopbits.setGeometry(106,110,100,30);
    m_cmb_stopbits.addItem("Unknown");
    m_cmb_stopbits.addItem("1");
    m_cmb_stopbits.addItem("1.5");
    m_cmb_stopbits.addItem("2");

    /* UI of Serial port parity */
    m_cmb_parity.setParent(this);
    m_cmb_parity.setGeometry(106,145,100,30);
    m_cmb_parity.addItem("Unknown");
    m_cmb_parity.addItem("No");
    m_cmb_parity.addItem("Even");
    m_cmb_parity.addItem("Odd");
    m_cmb_parity.addItem("Space");
    m_cmb_parity.addItem("Mark");

    /* UI of Serial port flow control */
    m_cmb_flowcontrol.setParent(this);
    m_cmb_flowcontrol.setGeometry(106,180,100,30);
    m_cmb_flowcontrol.addItem("Unknown");
    m_cmb_flowcontrol.addItem("No");
    m_cmb_flowcontrol.addItem("Hardware");
    m_cmb_flowcontrol.addItem("Software");

    m_btn_open.setParent(this);
    m_btn_open.setGeometry(5,220,200,30);
    m_btn_open.setText("Open");
    m_btn_open.setCheckable(true);

    m_btn_rclear.setParent(this);
    m_btn_rclear.setGeometry(225,75,80,30);
    m_btn_rclear.setText("clear");

    m_btn_sclear.setParent(this);
    m_btn_sclear.setGeometry(225,190,80,30);
    m_btn_sclear.setText("clear");

    m_btn_send.setParent(this);
    m_btn_send.setGeometry(315,190,80,30);
    m_btn_send.setText("send");

    m_le_recv.setParent(this);
    m_le_recv.setGeometry(225,40,168,30);

    m_le_send.setParent(this);
    m_le_send.setText("send test msg");
    m_le_send.setGeometry(225,155,168,30);

    init();

    connect(&m_btn_open,SIGNAL(toggled(bool)),this,SLOT(openSerial(bool)));
    connect(&m_btn_send,SIGNAL(clicked(bool)),this,SLOT(sendDatas()));
    connect(&m_btn_rclear,SIGNAL(clicked(bool)),this,SLOT(clearRecvDatas()));
    connect(&m_btn_sclear,SIGNAL(clicked(bool)),this,SLOT(clearSendDatas()));
}

void MainWindow::init(){
    m_serial = new serialport(this);
    connect(m_serial,SIGNAL(sigRecvDatas(QByteArray&)),this,SLOT(recvDatas(QByteArray&)));

    m_serial->listSerialPort(m_list);
    for(int i = 0;i<m_list.length();i++){
        QSerialPortInfo info = m_list[i];
        m_cmb_portname.addItem(info.portName());
    }
}

void MainWindow::openSerial(bool stat){
    if(stat){
        /* Set up serial port name */
        m_portname = m_cmb_portname.currentText();

        /* Set up baudrate of serial port */
        switch (m_cmb_baudrate.currentIndex()) {
        case 1:
            m_baudrate = QSerialPort::Baud1200;
            break;
        case 2:
            m_baudrate = QSerialPort::Baud2400;
            break;
        case 3:
            m_baudrate = QSerialPort::Baud4800;
            break;
        case 4:
            m_baudrate = QSerialPort::Baud9600;
            break;
        case 5:
            m_baudrate = QSerialPort::Baud19200;
            break;
        case 6:
            m_baudrate = QSerialPort::Baud38400;
            break;
        case 7:
            m_baudrate = QSerialPort::Baud57600;
            break;
        case 8:
            m_baudrate = QSerialPort::Baud115200;
            break;
        default:
            m_baudrate = QSerialPort::UnknownBaud;
            break;
        }

        /* Set up data bits of serial port */
        switch (m_cmb_databits.currentIndex()) {
        case 1:
            m_databits = QSerialPort::Data5;
            break;
        case 2:
            m_databits = QSerialPort::Data6;
            break;
        case 3:
            m_databits = QSerialPort::Data7;
            break;
        case 4:
            m_databits = QSerialPort::Data8;
            break;
        default:
            m_databits = QSerialPort::UnknownDataBits;
            break;
        }

        /* Set up stop bits of serial port */
        switch (m_cmb_stopbits.currentIndex()) {
        case 1:
            m_stopbits = QSerialPort::OneStop;
            break;
        case 2:
            m_stopbits = QSerialPort::OneAndHalfStop;
            break;
        case 3:
            m_stopbits = QSerialPort::TwoStop;
            break;
        default:
            m_stopbits = QSerialPort::UnknownStopBits;
            break;
        }

        /* Set up parity of serial port */
        switch (m_cmb_parity.currentIndex()) {
        case 1:
            m_parity = QSerialPort::NoParity;
            break;
        case 2:
            m_parity = QSerialPort::EvenParity;
            break;
        case 3:
            m_parity = QSerialPort::OddParity;
            break;
        case 4:
            m_parity = QSerialPort::SpaceParity;
            break;
        case 5:
            m_parity = QSerialPort::MarkParity;
            break;
        default:
            m_parity = QSerialPort::UnknownParity;
            break;
        }

        /* Set up flow control of serial port */
        switch (m_cmb_flowcontrol.currentIndex()) {
        case 1:
            m_flowcontrol = QSerialPort::NoFlowControl;
            break;
        case 2:
            m_flowcontrol = QSerialPort::HardwareControl;
            break;
        case 3:
            m_flowcontrol = QSerialPort::SoftwareControl;
            break;
        default:
            m_flowcontrol = QSerialPort::UnknownFlowControl;
            break;
        }

        /* open serial port */
        if(!m_serial->open(m_portname,
                       m_baudrate,
                       m_databits,
                       m_stopbits,
                       m_parity,
                       m_flowcontrol)){
            m_btn_open.setChecked(false);
        }else
            m_btn_open.setText("Close");

    }else{
        m_serial->close();
        m_btn_open.setText("Open");
    }
}

void MainWindow::recvDatas(QByteArray &bytearray){
    if(m_btn_open.isChecked())
        m_le_recv.setText(QString(bytearray.data()));
    else
        qDebug()<<"serial not open";
}

void MainWindow::sendDatas(){
    if(m_btn_open.isChecked()){
        QString msg = m_le_send.text();
        m_serial->send(msg.toLatin1().data(),msg.toLocal8Bit().length());
    }
    else
        qDebug()<<"serial not open";
}

void MainWindow::clearRecvDatas(){
    m_le_recv.clear();
}

void MainWindow::clearSendDatas(){
    m_le_send.clear();
}

MainWindow::~MainWindow(){
    delete m_serial;
}
