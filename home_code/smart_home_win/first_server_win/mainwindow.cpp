#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextCodec>
#include <QByteArray>
#include <QDebug>
#include <QList>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    setCentralWidget(ui->tabWidget);
    //���ñ��룬�����ڹ��ʻ�
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("gb2312"));

    //�˶�ʱ��Ϊ��ѯ���ڻ�������
    serial_read_fresh_t=new QTimer(this);
    //���ö�ʱ��ˢ������
    serial_read_fresh_t->setInterval(400);
    //�Դ��ڽ��г�ʼ��
    if(ser_serial_port_init()==Utils::SUCCESS)
    {
        ui->infoPad->append("Ser : Found Serial Device");
        th.start();
    }
    else
    {
        ui->infoPad->append(("Ser : No Serial Device Found"));
    }
    //��ʼ��tcp��������
    tcpServer =new QTcpServer(this);
    //��ʼ��udp�����׽��ֶ���
    udpSendSocket = new QUdpSocket(this);
    //��ʼ��udp�����׽��ֶ���
    udpReceiveSocket = new QUdpSocket(this);
    //�󶨱���udp�׽��ּ���//8904
    udpReceiveSocket->bind(Utils::SER_UDP_RCV_PORT, QUdpSocket::ShareAddress);
    //�󶨱���udp�׽��ֵ�readyRead�źŵ�processPendingDatagrams�ۺ���
    connect(udpReceiveSocket, SIGNAL(readyRead()),this, SLOT(processPendingDatagrams()));
    //��ʼ���ͻ���Ĭ�ϵ�ַ����
    addr = new QHostAddress("192.168.1.1");

    //���ð�ť�ĳ�ʼ��״̬
    ui->startBtn->setEnabled(true);
    ui->stopBtn->setEnabled(false);
    //��tcpServer��newConnection�źŵ�newConnectionComing�ۺ���
    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(newConnectionComing()));
    //��startBtn��clicked�źŵ�listenBtnClicked�ۺ���
    connect(ui->startBtn,SIGNAL(clicked()),this,SLOT(listenBtnClicked()));
     //��stopBtn��clicked�źŵ�listenBtnClicked�ۺ���
    connect(ui->stopBtn,SIGNAL(clicked()),this,SLOT(stopBtnClicked()));
    //�ӽڵ㽫�ᷢ�͵�����
    //����һ�������汾�н������ȥ
    //
    // ��������������Utils������
    //  2014��03��15 �����

    //�¶ȴ������ӽڵ㷢�͵�����ͷ
    // TEMP ="temp_data_is:";
    //ʪ�ȴ������ӽڵ㷢�͵�����ͷ
    // HUMI ="humi_data_is:";

    table_fresh_t=new QTimer(this);
    table_fresh_t->setInterval(1500);
    connect(table_fresh_t,SIGNAL(timeout()),this,SLOT(view_data()));
    table_fresh_t->start();

    connect(this,SIGNAL(send_cmd_to_node(QString)),this,SLOT(sendSerCom(QString)));
    connect(this,SIGNAL(send_data_to_thread(QString)),&th,SLOT(setData(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
//startBtn�������´����Ĳۺ���
void MainWindow::listenBtnClicked()
{
    //������Ϣ�����Թ����ࣨ��̬��Ա�ࣩ
    // qDebug()<<"test "<<Utils::SET_TEMP_MAX;
    //������Ϣ
    //qDebug()<<"listenBtnClicked ok";
    //��ʼ�����infoPad
    ui->infoPad->clear();
    //��infopad׷��״̬��Ϣ
    ui->infoPad->append("SER:start listen ...");
    //tcpServer��ʼ�ڱ���8888�˿ڼ���
    tcpServer->listen(QHostAddress::Any,8888);
    //�ж�tcpServer�Ƿ�ʼ����
    if(tcpServer->isListening())
    {
        //������Ϣ
        //qDebug()<<getIP();
        //��infopad׷��״̬��Ϣ
       ui->infoPad->append(getIP()+" listen on 8888");
       //���°���״̬
       ui->startBtn->setEnabled(false);
       ui->stopBtn->setEnabled(true);
    }
}
//stopBtn�������´����Ĳۺ���
void MainWindow::stopBtnClicked()
{
//���infoPad�������
    ui->infoPad->clear();
    //�ر�tcpServer����������ʱ������Ӧ����
    tcpServer->close();
    //�ж�tcpServer�������Ƿ����
    if(!tcpServer->isListening())
    {
        //��infopad׷��״̬��Ϣ
        ui->infoPad->append("SER:close the server");
        //���°���״̬
        ui->startBtn->setEnabled(true);
        ui->stopBtn->setEnabled(false);
    }
    //��infopad׷��״̬��Ϣ
    ui->infoPad->append("SER:stop listen ...");
}
//���������ڼ���״̬�����пͻ�������ʱ�����˲ۺ���
void MainWindow::newConnectionComing()
{
    //��infopad׷��״̬��Ϣ
    ui->infoPad->append("SER:New Connection Coming");
    //��ȡ�Ϳͻ���ͨ�ŵ��׽���
    //�����Ҫ���Ӷ���ͻ��ˣ���Ҫ����ȡ����ÿ���ͻ����׽��ֱ�������
    //���罫�䴫�͸�һ���߳�
    //get socket from server
    //if you need more client you need to send the socket to another worker thread
    tcpSocket =tcpServer->nextPendingConnection();
    //��infopad׷��״̬��Ϣ
    ui->infoPad->append(tcpSocket->peerAddress().toString() + " connected");
    //��tcpsocket��disconnected�ź���clientDisConnected�ۺ������а�
    connect(tcpSocket,SIGNAL(disconnected()),this,SLOT(clientDisConnected()));
    //��tcpSocket��readyRead�ź���dataReceive�ۺ������а�
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(Ser_dataReceive()));
}
//���ͻ��˶Ͽ�����ʱ�����Ĳۺ���
void MainWindow::clientDisConnected()
{
    //��infopad׷��״̬��Ϣ
    ui->infoPad->append("SER:client disconnected!");
}
//���ͻ��˷�����Ϣʱ�����Ĳۺ���
void MainWindow::Ser_dataReceive()
{
    //���ڱ�����Ϣ����ʱ����
    QByteArray message;
    //��tcpSocket��ȡ��Ϣ
    message=tcpSocket->readAll();

    //��infopad׷��״̬��Ϣ
    ui->infoPad->append(tcpSocket->peerAddress().toString()+":");
    //��infopad׷��״̬��Ϣ
    ui->infoPad->append("\t"+message);
    //�����������ɹ������Э���������
    //Ŀǰ��û�п���Э���Ż���
    //Ŀǰʹ�õĲ���һ���Ϻõ�Э�飬�����ַ���Э��
    //����Ϊ��������Ĺ��̣������ɹ�����SUCCESS��ʧ�ܷ���FAIL
    if( Ser_cmd_parser(message.trimmed())==Utils::SUCCESS)
    {
        //������Ϣ
        qDebug()<<"SER:parser ok";
    }
    else
    {
        //������Ϣ
        qDebug()<<"SER:parser fail";
    }
    //send back message or something other
    //������Ϣ
    //tcpSocket->write(message);
    //������Ϣ
     qDebug()<<"Ser:server receive ok";
}
//��tcp���������������
//���룺QString ���͵�����
//�����int ���͵�״̬��ʶ
//����Ĳ������뾭��trim��������
int MainWindow::Ser_cmd_parser(QString cmd)
{
    //�ж����������Ƿ�Ϊ��
    if(cmd=="")
    {
        //������Ϣ
        qDebug()<<"SER:empty cmd";
        //����ֵ
        return Utils::FAIL;
    }
    //�ж��Ƿ�Ϊ�ͻ��������¶�����
    else if(cmd==(Utils::ASK_TEMP_DAT))
    {
        //������Ϣ
        qDebug()<<"SER:client ask for temp dat";
        //�����Ӧ��������ָ��
        //��������ͷ������
        QString t=QString(Utils::TEMP_DAT_TO_CLIENT).append(QString(Utils::get_value(Utils::TEMP_ID)));
        //������Ϣ
        qDebug()<<"Ser:"<<t;
        //������Ӧָ��
        boolean flag=Ser_sendDat(t);
        //�жϲ���������
        if(flag==Utils::SUCCESS)
        {
            //������Ϣ
            qDebug()<<"Ser:reply to client ok";
        }
        else
        {
            //������Ϣ
            qDebug()<<"Ser:reply to client fail";
        }
        //
         //���ؽ������״̬
        return Utils::SUCCESS;

    }
    //�ж��Ƿ�Ϊ�ͻ�������ʪ������
    else if(cmd==(Utils::ASK_HUMI_DAT))
    {
        //������Ϣ
        qDebug()<<"SER:client ask for humi dat";
        ////�����Ӧ �������� ָ��
        //��������ͷ������
        QString t=QString(Utils::HUMI_DAT_TO_CLIENT).append(QString(Utils::get_value(Utils::HUMI_ID)));
        //������Ϣ
        qDebug()<<"Ser:"<<t;
        //������Ӧָ��
        boolean flag=Ser_sendDat(t);
        //�жϲ���������
        if(flag==Utils::SUCCESS)
        {
            //������Ϣ
            qDebug()<<"Ser:reply to client ok";
        }
        else
        {
            //������Ϣ
            qDebug()<<"Ser:reply to client fail";
        }
        //
         //���ؽ������״̬
        return Utils::SUCCESS;
    }
    else if(cmd.startsWith(Utils::SET_HUMI_MIN))
    {
        //������Ϣ��������Ϣ����
        //qDebug()<<"set humi min";
        //������Ϣ����ӡ��Ϣ����
        //qDebug()<<cmd;
        //������Ϣ�������Ϣ����
        //qDebug()<<cmd.length();
        //������Ϣ������ȶ�����ͷ����
        //qDebug()<<Utils::SET_HUMI_MIN.length();

        //��һ�ֻ�ȡ��Ч��������ֵ�ķ�ʽ
        //��ȡ�����С��������ڵ�λ��
        //int offset =cmd.indexOf(":");
        //ͨ����������ĳ��ȼ������Ч���ݵĳ���
        //offset =cmd.length()-offset-1;

         //��ǰʹ�õĻ�ȡ��Ч���ݵ������ķ�ʽ
        int offset =cmd.length()-Utils::SET_HUMI_MIN.length();
        //������Ϣ�������Ч��������ֵ
        // qDebug()<<offset;
        //�ڴ˴�ʹ����ʱ���������ȡ������Ч����
        float value =cmd.right(offset).toFloat();
         //������Ϣ�������Ч���ݵ�ֵ
        qDebug()<<"SER:the humi set low value is "<<value;
        //
        boolean flag=Utils::update_value_min(Utils::HUMI_ID,QString::number(value));
//        boolean flag=Utils::update_value_min(Utils::HUMI_ID,cmd.right(offset));
        if(flag==Utils::SUCCESS)
        {
            //������Ϣ
            qDebug()<<"Ser:update humi min ok";
        }
        else
        {
            //������Ϣ
            qDebug()<<"Ser:update humi min fail";
        }
        //
         //���ؽ������״̬
        return Utils::SUCCESS;
    }
    else if(cmd.startsWith(Utils::SET_HUMI_MAX))
    {
        //������Ϣ��������Ϣ����
        //qDebug()<<"set humi max";
        //������Ϣ����ӡ��Ϣ����
        //qDebug()<<cmd;
        //������Ϣ�������Ϣ����
        //qDebug()<<cmd.length();
        //������Ϣ������ȶ�����ͷ����
        //qDebug()<<Utils::SET_HUMI_MAX.length();

        //��һ�ֻ�ȡ��Ч��������ֵ�ķ�ʽ
        //��ȡ�����С��������ڵ�λ��
        //int offset =cmd.indexOf(":");
        //ͨ����������ĳ��ȼ������Ч���ݵĳ���
        //offset =cmd.length()-offset-1;

         //��ǰʹ�õĻ�ȡ��Ч���ݵ������ķ�ʽ
        int offset =cmd.length()-Utils::SET_HUMI_MAX.length();
        //������Ϣ�������Ч��������ֵ
        // qDebug()<<offset;
        //�ڴ˴�ʹ����ʱ���������ȡ������Ч����
        float value =cmd.right(offset).toFloat();
         //������Ϣ�������Ч���ݵ�ֵ
        qDebug()<<"SER:the humi set high value is "<<value;
        //

        boolean flag=Utils::update_value_max(Utils::HUMI_ID,QString::number(value));
//        boolean flag=Utils::update_value_max(Utils::HUMI_ID,cmd.right(offset));
        if(flag==Utils::SUCCESS)
        {
            //������Ϣ
            qDebug()<<"Ser:update humi max ok";
        }
        else
        {
            //������Ϣ
            qDebug()<<"Ser:update humi max fail";
        }
        //
         //���ؽ������״̬
        return Utils::SUCCESS;
    }
    //�˴�������Ӷ���������Ľ���
    else if(cmd.startsWith(Utils::SET_TEMP_MIN))
    {
        //������Ϣ��������Ϣ����
        //qDebug()<<"set temp min ";
        //������Ϣ����ӡ��Ϣ����
        //qDebug()<<cmd;
        //������Ϣ�������Ϣ����
        //qDebug()<<cmd.length();
        //������Ϣ������ȶ�����ͷ����
        //qDebug()<<Utils::SET_TEMP_MIN.length();

        //��һ�ֻ�ȡ��Ч��������ֵ�ķ�ʽ
        //��ȡ�����С��������ڵ�λ��
        //int offset =cmd.indexOf(":");
        //ͨ����������ĳ��ȼ������Ч���ݵĳ���
        //offset =cmd.length()-offset-1;

         //��ǰʹ�õĻ�ȡ��Ч���ݵ������ķ�ʽ
        int offset =cmd.length()-Utils::SET_TEMP_MIN.length();
        //������Ϣ�������Ч��������ֵ
        // qDebug()<<offset;
        //�ڴ˴�ʹ����ʱ���������ȡ������Ч����
        float value =cmd.right(offset).toFloat();
         //������Ϣ�������Ч���ݵ�ֵ
        qDebug()<<"SER:the temp set low value is "<<value;
        //
        boolean flag=Utils::update_value_min(Utils::TEMP_ID,QString::number(value));
//        boolean flag=Utils::update_value_min(Utils::TEMP_ID,cmd.right(offset));
        if(flag==Utils::SUCCESS)
        {
            //������Ϣ
            qDebug()<<"Ser:update temp min ok";
        }
        else
        {
            //������Ϣ
            qDebug()<<"Ser:update temp min fail";
        }
        //
         //���ؽ������״̬
        return Utils::SUCCESS;
    }
    //�ж����������Ƿ�ΪTEMP���
    else if(cmd.startsWith(Utils::SET_TEMP_MAX))
    {
        //������Ϣ��������Ϣ����
        //qDebug()<<"set temp max";
        //������Ϣ����ӡ��Ϣ����
        //qDebug()<<cmd;
        //������Ϣ�������Ϣ����
        //qDebug()<<cmd.length();
        //������Ϣ������ȶ�����ͷ����
        //qDebug()<<Utils::SET_TEMP_MAX.length();

        //��һ�ֻ�ȡ��Ч��������ֵ�ķ�ʽ
        //��ȡ�����С��������ڵ�λ��
        //int offset =cmd.indexOf(":");
        //ͨ����������ĳ��ȼ������Ч���ݵĳ���
        //offset =cmd.length()-offset-1;

        //��ǰʹ�õĻ�ȡ��Ч���ݵ������ķ�ʽ
        int offset =cmd.length()-Utils::SET_TEMP_MAX.length();
        //������Ϣ�������Ч��������ֵ
        // qDebug()<<offset;
        //�ڴ˴�ʹ����ʱ���������ȡ������Ч����
        float value =cmd.right(offset).toFloat();
        //������Ϣ�������Ч���ݵ�ֵ
        qDebug()<<"SER��the temp set high value is "<<value;
        //
        boolean flag=Utils::update_value_max(Utils::TEMP_ID,QString::number(value));
//        boolean flag=Utils::update_value_max(Utils::TEMP_ID,cmd.right(offset));
        if(flag==Utils::SUCCESS)
        {
            //������Ϣ
            qDebug()<<"Ser:update temp max ok";
        }
        else
        {
            //������Ϣ
            qDebug()<<"Ser:update temp max fail";
        }
        //
        //���ؽ������״̬
        return Utils::SUCCESS;
    }
    //�ж��Ƿ�Ϊ�ͻ�������򿪵�
    else if(cmd==(Utils::OPEN_THE_LIGHT))
    {
        //������Ϣ
        qDebug()<<"SER:client request open the light";
        //������Ӧָ��
        emit send_cmd_to_node(Utils::OPEN_THE_LIGHT+"\n");
        //���ؽ������״̬
        return Utils::SUCCESS;
    }
    //�ж��Ƿ�Ϊ�ͻ�������رյ�
    else if(cmd==(Utils::CLOSE_THE_LIGHT))
    {
        //������Ϣ
        qDebug()<<"SER:client request close the light";
        //������Ӧָ��
        emit send_cmd_to_node(Utils::CLOSE_THE_LIGHT+"\n");
        //���ؽ������״̬
        return Utils::SUCCESS;

    }
    //�˴������δ����ָ����д���
    else
    {
         //���ؽ������״̬
        return Utils::FAIL;
    }
}
//�ӿͻ��˽���udp���ݱ��Ĳۺ���
void MainWindow::processPendingDatagrams()
{
    while (udpReceiveSocket->hasPendingDatagrams())
    {
        //����ͻ��˷��͵����ݱ�����ʱ����
        QByteArray datagram;
        //���µ������ջ���Ĵ�С
        datagram.resize(udpReceiveSocket->pendingDatagramSize());
        //���ڴ洢���ܿͻ��˵�ַ����ʱ����
        QHostAddress *temp=new QHostAddress("123.123.123.123");
        //���տͻ��˷��͵����ݱ���ͬʱ����ͻ��˵�ַ
        udpReceiveSocket->readDatagram(datagram.data(), datagram.size(),temp,0);
        //��infopad׷��״̬��Ϣ
        ui->infoPad->append(tr("SER:Received datagram: \"%1\"")
                            .arg(datagram.data()));
        //�����ͻ��˷��͵����ݱ���Ϣ
        //�ж����ݱ��Ƿ�Ϊ�ͻ������������
        if(datagram==Utils::WHO_IS_SERVER)
        {
            //������Ϣ�����״̬��Ϣ
            qDebug()<<"SER:someone need me";
            //���ȷʵ�ǿͻ��ˣ�����¿ͻ��˵�ַ
            addr=temp;
            //��Ӧ�ͻ��˵�����
            Ser_sendDatagram(Utils::I_AM_SERVER);
        }
        //������Ϣ������ͻ��˷��͵�����
        qDebug()<<"SER:(udp)client msg:"<<datagram.data();
        //������Ϣ������ͻ��˵�ַ
        qDebug()<<"SER:(udp)client addr: "<<addr->toString();
    }
}
//���մ������ݵĲۺ���
void MainWindow::readSerCom()
{
    //���洮�����ݵ���ʱ����
    QByteArray temp;
    char c[30]={0};
    //�жϴ��ڻ��������Ƿ����20
    //�˴���Ϊ�˱�֤���Զ�������һ��������ָ�������
    if(ser_Com->bytesAvailable()>=20)
    {
        //��ȡ��������
//        temp=ser_Com->readAll().trimmed();
        ser_Com->readLine(c,30);

        qDebug()<<"i got:"<<c;
        temp=QByteArray(c,30);
        //������Ϣ����ӡ�յ�������
        //qDebug()<<"temp:"<<temp;
        //sometimes we need the trim function to make sure we are using the right data
        qDebug()<<QString(temp);
        qDebug()<<QString(temp).trimmed();
        //����Ϊ�������ݽ����Ĺ��̣������ɹ�����SUCCESS��ʧ�ܷ���FAIL
        /*
        if(  ser_serial_data_parser(QString(temp)) == Utils::SUCCESS )
//            if(  ser_serial_data_parser(QString(c)) == Utils::SUCCESS )
        {
            //������Ϣ
            qDebug()<<"SER:serial parser ok";
        }
        else
        {
            //������Ϣ
            qDebug()<<"SER:serial parser fail";
        }
        */
//        emit send_data_to_thread(QString(temp).trimmed());
        emit send_data_to_thread(QString(temp));
        qDebug()<<"signal send";

    }

}

int MainWindow::sendSerCom(QString cmd)
{
    if(cmd=="")
    {
        qDebug()<<"Ser:empty serial cmd";
        ui->infoPad->append("Ser:can not send empty serial cmd");
        return Utils::FAIL;
    }
    qDebug()<<"the serial cmd is: "<<cmd<<"length"<<cmd.length();

    int i= ser_Com->write(cmd.toAscii());
    qDebug()<<"real: "<<i;
    return Utils::SUCCESS;
}

//�������ݽ�������
//���룺�յ��Ĵ�������
//����ֵ�������ɹ�Utils::SUCCESS������ʧ��Utils::FAIL
int MainWindow::ser_serial_data_parser(QString msg)
{
    //�ж��Ƿ�����Ч����
    if(msg=="")
    {
        //������Ϣ
        qDebug()<<"Ser:empty serial msg!";
        //��infoPad���״̬��Ϣ
        ui->infoPad->append("Ser:no serial data");
        //����ֵ
        return Utils::FAIL;
    }
    //�ж������Ƿ�Ϊ�ӽڵ㷢�����¶�����
    else if(msg.startsWith(Utils::TEMP_VALUE_FROM_NODE))
    {
        //��ȡ��Ч���ݵ������ķ�ʽ
        int offset =msg.length()-Utils::TEMP_VALUE_FROM_NODE.length();
        //����������ݵĳ���
        //qDebug()<<"msg length:"<<msg.length();
        //����ȶ������ַ����ĳ���
        //qDebug()<<"len:"<<Utils::TEMP_VALUE_FROM_NODE.length();
        //������Ϣ�������Ч��������ֵ
        //qDebug()<<"off"<<offset;
        //�ڴ˴�ʹ����ʱ���������ȡ������Ч����
        float value =msg.right(offset).toFloat();
        //������Ϣ�������Ч���ݵ�ֵ
        qDebug()<<"SER:node temp value is "<<value;
        //��������ӻ���µ����ݿ�
        //
        boolean flag=Utils::update_value(Utils::TEMP_ID,QString::number(value));
//        boolean flag=Utils::update_value(Utils::TEMP_ID,msg.right(offset));
        if(flag==Utils::SUCCESS)
        {
            //������Ϣ
            qDebug()<<"Ser:update temp  ok";
        }
        else
        {
            //������Ϣ
            qDebug()<<"Ser:update temp  fail";
        }
        //
        return Utils::SUCCESS;
    }
    else if(msg.startsWith(Utils::HUMI_VALUE_FROM_NODE))
//          else if(msg.startsWith("the_humi_value_is:"))
    {
        //��ǰʹ�õĻ�ȡ��Ч���ݵ������ķ�ʽ
        int offset =msg.length()-Utils::HUMI_VALUE_FROM_NODE.length();
        //����������ݵĳ���
//        qDebug()<<"msg length:"<<msg.length();
        //����ȶ������ַ����ĳ���
//        qDebug()<<"len:"<<Utils::HUMI_VALUE_FROM_NODE.length();
        //������Ϣ�������Ч��������ֵ
//        qDebug()<<"off"<<offset;
        //�ڴ˴�ʹ����ʱ���������ȡ������Ч����
        //�ڴ˴�ʹ����ʱ���������ȡ������Ч����
        float value =msg.right(offset).toFloat();
        //������Ϣ�������Ч���ݵ�ֵ
        qDebug()<<"SER:node humi value is "<<value;
        //��������ӻ���µ����ݿ�
        //
        boolean flag=Utils::update_value(Utils::HUMI_ID,QString::number(value));
//        boolean flag=Utils::update_value(Utils::HUMI_ID,msg.right(offset));
        if(flag==Utils::SUCCESS)
        {
            //������Ϣ
            qDebug()<<"Ser:update humi ok";
        }
        else
        {
            //������Ϣ
            qDebug()<<"Ser:update humi fail";
        }
        //
        return Utils::SUCCESS;
    }
    else
    {
        //������
        //������Ϣ��δʶ������
        qDebug()<<"Ser:undefine serial data";
        qDebug()<<"receive :"<<msg<<" leng:"<<msg.length();
        return Utils::FAIL;
    }
}

    //���ڷ���udp���ݱ��ĺ���
    //���룺QString���͵� msg
    //�������
void MainWindow::Ser_sendDatagram(QString msg)
{
    //������Ϣ����ʱ����
    QByteArray datagram;
    //�ж���Ϣ�Ƿ�Ϊ��
    if(msg==NULL)
    {
        //��infopad׷��״̬��Ϣ
        ui->infoPad->append(tr("SER:sorry msg is null"));
    }
    else
    {
        //��infopad׷��״̬��Ϣ
        ui->infoPad->append(tr("SER:Now send datagram "));
        //����Ϣת����datagram
        datagram = msg.toAscii();
    }
    //udpSocket->writeDatagram(datagram.data(), datagram.size(),
    //                          QHostAddress::Broadcast, 8903);
    //��ʼ��������
    //��ַ���ͻ��˵�ַ
    //�˿ڣ��ͻ��˶˿�
    udpSendSocket->writeDatagram(datagram.data(), datagram.size(),
                             *addr,Utils::CLI_UDP_RCV_PORT );
    //������Ϣ������ͻ��˵�ַ�Ͷ˿�
    qDebug()<<addr->toString()<<":"<<Utils::CLI_UDP_RCV_PORT;

}
//���ڷ���tcp���ݵĺ���
//���룺QString���͵� msg
//����� ״̬
//Ϊ�˼��ݣ������ð���һ�����з�
int MainWindow::Ser_sendDat(QString dat)
{
    //tcp�������ݣ���������������ֵ
    int ret=tcpSocket->write(QString(dat+"\n").toUtf8());
    //��infoPad׷��״̬��Ϣ
    ui->infoPad->append("Ser:");
    //��infoPad׷��״̬��Ϣ
    ui->infoPad->append("\t"+dat);
    //�жϷ����Ƿ����
    //ret == -1 ��ʾ����ʧ��
    if(ret>0)
    {
        //���ط���״̬
        return Utils::SUCCESS;
    }
    else
    {
        //���ط���״̬
        return Utils::FAIL;
    }
}
//�����Ѿ��ƶ�����������
//int MainWindow::add_data(QString id,QString name,QString type,QString value,QString value_min,QString value_max)
//{
//    QSqlQuery query;
//    bool flag;
//    flag=query.exec("INSERT INTO  node_data VALUES('"+id+"','"+name+"','"+type+"','"+value+"','"+value_min+"','"+value_max+"')");
//    if(flag){
//        ui->infoPad->append("insert data success");
//        return Utils::SUCCESS;
//    }
//    else{
//        ui->infoPad->append("insert data fail");
//        return Utils::FAIL;
//    }
//}

int MainWindow::del_data(QString id, QString name, QString type, QString value, QString value_min, QString value_max)
{
    QSqlQuery query;
    bool flag;
    flag=query.exec("delete from node_data where ID='"+id+"'");
    qDebug()<<"delete from node_data where ID='"+id+"'";
    if(flag)
    {
        ui->infoPad->append("del data success");
        return Utils::SUCCESS;
    }
    else
    {
        ui->infoPad->append("del data fail");
        return Utils::FAIL;
    }
    return Utils::SUCCESS;
}

//int MainWindow::update_data(QString id, QString name, QString type, QString value, QString value_min, QString value_max)
//{
//    return Utils::SUCCESS;
//}
//���ڶ�ʱˢ����ʾ���ݿ������б�Ĳۺ���
int MainWindow::view_data()
{
    model=new QSqlQueryModel();
    model->setQuery("select * from node_data");
    ui->data_table->resizeColumnsToContents();
    ui->data_table->resizeRowsToContents();
    ui->data_table->setModel(model);
    return Utils::SUCCESS;
}


//�Զ���ʼ�����ڶ���
//�ô�ʹ���˵������Ĵ����࣬��ΪĿǰʹ�õİ汾��4.8.5��û�йٷ��Ĵ�����
//�ٷ�����5.1�汾�в������˴�����
//�ú���ʵ���˴��ڵ��Զ�ö��֧�֣�com1-com30��
/*
΢��Ԥ����ı�׼�豸�к��С�COM1��-��COM9�������ԣ���COM1��-��COM9����Ϊ�ļ������ݸ�����ʱ����ϵͳ���Զ��ؽ�֮����Ϊ��Ӧ���豸��
������COM10�����ϵĴ��ڣ���COM10��֮����ļ���ϵͳֻ��֮Ϊһ�������ϵ��ļ������Ǵ����豸��
Ϊ�����Ӷ�COM10�����ϴ��ж˿ڵ�֧�֣�΢��涨�����Ҫ�����������豸��Ӧʹ���������ļ�������COM10Ϊ������\\\\.\\COM10
*/
int MainWindow::ser_serial_port_init()
{
    //�����������������Ϣ�Ĵ������������
    //����������Ϣ���£�
    //�����ʣ�9600
    //����λ��8λ
    //ֹͣλ��1λ
    //��У��
    //������

    struct  PortSettings  serComSetting  =  {BAUD9600,DATA_8,PAR_NONE,STOP_1,FLOW_OFF,
    500};
    //�Ƿ��ҵ����ڵı�־
    bool flag=false;
    //���屣�洮�����Ƶı���
    QString serial_name;
    //ö��com1-com9���ж��Ƿ�ΪĿ���豸
    for(int i=1;i<10;i++)
    {
        //���Ϊ�٣������ж�
        if(flag==false)
        {
            //��ʼ��������
            serial_name="com";
            //�򴮿���׷��������
            serial_name.append(QString("%1").arg(i));
            //��ʼ�����ڶ���
            //���룺������������������Ϣ����ѯģʽ
//            ser_Com=new Win_QextSerialPort(serial_name,serComSetting,QextSerialBase::EventDriven);
            ser_Com=new Win_QextSerialPort(serial_name,serComSetting,QextSerialBase::Polling);
            //������Ϣ�������ǰ���ڲ��ԵĴ�����
            // qDebug()<<serial_name;
            //���Դ򿪴����豸
            if(ser_Com->open(QIODevice::ReadWrite))
            {
                //������Ϣ
                //������豸�ɹ������ӡ��Ϣ
                qDebug()<<"Ser: find:"<<serial_name;
                //���ҵ������豸�ı�־��true
                flag=true;
                //��������
                break;
            }
        }
    }
    //�����δ�ҵ������豸�����ڸ���Χ����
    if(flag==false)
    {
        for(int i=10;i<30;i++)
        {
            //���³�ʼ��������
            serial_name="\\\\.\\com";
            //�򴮿���׷��������
            serial_name.append(QString("%1").arg(i));
            //��ʼ�����ڶ���
//            ser_Com=new Win_QextSerialPort(serial_name,serComSetting,QextSerialBase::EventDriven);
             ser_Com=new Win_QextSerialPort(serial_name,serComSetting,QextSerialBase::Polling);
            //������Ϣ�������ǰ���ڲ��ԵĴ�����
            // qDebug()<<serial_name;
            //���Դ򿪴��ڶ���
            if(ser_Com->open(QIODevice::ReadWrite))
            {
                //������Ϣ
                //������豸�ɹ����������Ӧ��Ϣ
                qDebug()<<"Ser: find:"<<serial_name;
                //���ҵ������豸�ı�־��Ϊtrue
                flag=true;
                //��������
                break;
            }
        }
    }
    //����򿪳ɹ�
    if(flag)
    {
        //���ô��ڳ�ʱʱ��
                //myCom->setTimeout(10);
                /*�����setTimeout()�붨ʱ����timeout()����
                PC����ARMͨ�����ڷ�����Ϣʱ������һ�����м�洢����----�����ڻ�������
                setTimeout()�����Ƕ�ʱ��ȡ���ݵ�����������timeout()���Ƕ�ʱ��ȡ���ڻ��������ݡ�
                setTimeout(ms)�����С��������ԭ��ԽСԽ�ã��������pc��һ���Է��͵����ݱȽ��Ӵ�Ӧ�����������С��
                */
        ser_Com->setTimeout(20);
        //�����ڶ����readyRead�źź�readSerCom�ۺ�����
        //connect(ser_Com,SIGNAL(readyRead()),this,SLOT(readSerCom()));

        connect(serial_read_fresh_t,SIGNAL(timeout()),this,SLOT(readSerCom()));
        serial_read_fresh_t->start();
        return Utils::SUCCESS;
    }
    //���Դ��룺
/*
    //��ʼ�����ڶ���com5
    ser_Com =new Win_QextSerialPort("com5",serComSetting,QextSerialBase::EventDriven);
    bool flag =ser_Com->open(QIODevice::ReadWrite);
    if(!flag)
    {
        qDebug()<<flag<<"hehe";
        ui->infoPad->append("fuck win");
    }
    qDebug()<<flag<<"hehe";
*/
 /*
    //��ʼ�����ڶ���com51
    ser_Com =new Win_QextSerialPort("\\\\.\\COM51",serComSetting,QextSerialBase::EventDriven);
    bool flag =ser_Com->open(QIODevice::ReadWrite);
    if(!flag)
    {
        qDebug()<<flag<<"hehe";
        ui->infoPad->append("fuck win");
    }
    qDebug()<<flag<<"hehe";
    */
    return Utils::FAIL;
}
//��ȡ�����ľ�������ַ������
//���룺��
//���أ�IP��ַ�ַ����������ؿ�
QString MainWindow::getIP()  //��ȡip��ַ
{
    //��ñ���ip��ַ�б�
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    //�������б�
    foreach (QHostAddress address, list)
    {
        //������Ϣ
        //qDebug()<<address.toString();
        //�˴�ʹ��ip��ַ�Ƿ��ѡ�192����ͷΪ�ж�����
        //��ĳЩ����£����ܻ����
        if(address.toString().startsWith("192",Qt::CaseInsensitive))
//����ʹ��IPv4��ַ
            return address.toString();
    }
    //���û�з��������ĵ�ַ�����ؿ�
       return 0;
}


void MainWindow::on_freshButton_clicked()
{
    QString t=Utils::get_value("101");
    qDebug()<<t;
}

void MainWindow::on_testButton_clicked()
{
//   int flag= Utils::add_data("test_id","test_name","test_type","test_value","test_value_min","test_value_max");
//   if(flag==Utils::SUCCESS)
//   {
//       qDebug()<<"add_ok";
//   }
//   else
//   {
//       qDebug()<<"add_failed";
//   }
//    QString cmd="open_the_light";
    emit send_cmd_to_node(Utils::OPEN_THE_LIGHT+"\n");
//    if(Utils::update_value("101","ff"))
    {
        qDebug()<<"ok";
    }
}
