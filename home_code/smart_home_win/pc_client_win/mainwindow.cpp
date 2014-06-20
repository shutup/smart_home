#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextCodec>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    //���ñ��룬�����ڹ��ʻ�
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("gb2312"));

    ui->setupUi(this);

    //��ʼ����ʾʪ�ȿؼ�����ʾ��ʽ
    ui->lcdNum_humi->setSegmentStyle(QLCDNumber::Flat);
    //��ʼ����ʾ�¶ȿؼ�����ʾ��ʽ
    ui->lcdNum_temp->setSegmentStyle(QLCDNumber::Flat);
    //����ʪ����ʾ�ؼ���Ĭ����ʾֵ
    ui->lcdNum_humi->display(50);
    //�����¶���ʾ�ؼ���Ĭ����ʾֵ
    ui->lcdNum_temp->display(22);
    //���� ����ʪ�����ֵ��spinbox��ֵ��Χ
    ui->spinBox_humi_max->setRange(0,100);
    //���� ����ʪ����С��ֵ��spinbox��ֵ��Χ
    ui->spinBox_humi_min->setRange(0,100);
    //������ʾ��׺
    ui->spinBox_humi_max->setSuffix("%");
    //������ʾ��׺
    ui->spinBox_humi_min->setSuffix("%");
    //����Ĭ��ѡ��Ĳ���ֵ
    ui->spinBox_humi_min->setValue(20);
    //����Ĭ��ѡ��Ĳ���ֵ
    ui->spinBox_humi_max->setValue(70);
    //���� �����¶����ֵ��spinbox��ֵ��Χ
    ui->spinBox_temp_max->setRange(-20,60);
    //���� �����¶����ֵ��spinbox��ֵ��Χ
    ui->spinBox_temp_min->setRange(-20,60);
    //������ʾ��׺
    ui->spinBox_temp_max->setSuffix("��");
    // ������ʾ��׺
    ui->spinBox_temp_min->setSuffix("��");
    //����Ĭ��ѡ��Ĳ���ֵ
    ui->spinBox_temp_max->setValue(40);
    //����Ĭ��ѡ��Ĳ���ֵ
    ui->spinBox_temp_min->setValue(20);
    //�������ӷ�������ť�ĳ�ʼ״̬
    ui->pushButton_conn->setEnabled(false);
    //���öϿ����������Ӱ�ť�ĳ�ʼ״̬
    ui->pushButton_discon->setEnabled(false);
    //�Է�������ַ���г�ʼ��
    ser_addr=new QHostAddress("222.222.222.222");
    //��ʼ��udp�����׽��ֶ���
    udpSendSocket = new QUdpSocket(this);
    //��ʼ��udp�����׽��ֶ���
    udpReceiveSocket = new QUdpSocket(this);
    //�󶨱���udp�׽��ּ���
    udpReceiveSocket->bind(Utils::CLI_UDP_RCV_PORT, QUdpSocket::ShareAddress);
    //�󶨱���udp�׽��ֵ�readyRead�źŵ�processPendingDatagrams�ۺ���
    connect(udpReceiveSocket, SIGNAL(readyRead()),this, SLOT(processPendingDatagrams()));
    //��ʼ��tcp�׽���
    clientSocket=new QTcpSocket(this);
    //��clientSocket��connected�ź���socketConnected�ۺ�����
    connect(clientSocket,SIGNAL(connected()),this,SLOT(socketConnected()));
    //��clientSocket�� disconnected �ź���socketDisConnected�ۺ�����
    connect(clientSocket,SIGNAL(disconnected()),this,SLOT(socketDisConnected()));
    //��clientSocket�� readyRead �ź���Client_dataReceive�ۺ�����
    connect(clientSocket,SIGNAL(readyRead()),this,SLOT(Client_dataReceive()));
    //��������ˢ�µĶ�ʱ��
    fresht_cli=new QTimer(this);
    //���ö�ʱ�����ʱ��
    fresht_cli->setInterval(1500);
    //����ʱ����timeout�ź���query_data�ۺ�����
    connect(fresht_cli,SIGNAL(timeout()),this,SLOT(query_data()));

}

MainWindow::~MainWindow()
{
    delete ui;
}
//����udp���ݱ��ĺ���
//���룺Qstring ���͵�msg
//      QHostAddress���͵�addr
//      int���͵�port
void MainWindow::Client_sendDatagram(QString msg,QHostAddress addr,int port)
{
//������Ϣ����ʱ����
QByteArray datagram;
//�ж���Ϣ�Ƿ�Ϊ��
if(msg==NULL)
{
    //��infopad׷��״̬��Ϣ
    ui->infoPad->append(tr("sorry msg is null"));
    return;
}
else
{
    //��infopad׷��״̬��Ϣ
    ui->infoPad->append(tr("Client:Now send datagram "));
    //����Ϣת����datagram
    datagram = msg.toAscii();
}
//udpSocket->writeDatagram(datagram.data(), datagram.size(),
//                          QHostAddress::Broadcast, 8903);
//��ʼ��������
//��ַ����ַ
//�˿ڣ��˿�
udpSendSocket->writeDatagram(datagram.data(), datagram.size(),
                         addr,port );
//������Ϣ�������ַ�Ͷ˿�
qDebug()<<addr.toString()<<":"<<port;
}
//tcp���������
//���룺QString ���͵�cmd
//���أ�����״̬��
int MainWindow::Client_sendCmd(QString cmd)
{
//tcp�������ݣ���������������ֵ
int ret=clientSocket->write(cmd.toUtf8());
//��infoPad׷��״̬��Ϣ
ui->infoPad->append("Me:");
//��infoPad׷��״̬��Ϣ
ui->infoPad->append("\t"+cmd);
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

//������˷�����Ϣʱ�����Ĳۺ���
void MainWindow::Client_dataReceive()
{
//���ڱ�����Ϣ����ʱ����
QByteArray message;
//��clientSocket��ȡ��Ϣ
message=clientSocket->readAll();
//��infopad׷��״̬��Ϣ
ui->infoPad->append(clientSocket->peerAddress().toString()+":");
//��infopad׷��״̬��Ϣ
ui->infoPad->append("\t"+message);
//�����������ɹ������Э���������
//Ŀǰ��û�п���Э���Ż���
//Ŀǰʹ�õĲ���һ���Ϻõ�Э�飬�����ַ���Э��
//����Ϊ��������Ĺ��̣������ɹ�����SUCCESS��ʧ�ܷ���FAIL
if( Client_cmd_parser(message)==Utils::SUCCESS)
{
    //������Ϣ
    qDebug()<<"CLI��parser ok";
}
else
{
    //������Ϣ
    qDebug()<<"CLI��parser fail";
}
//send back message or something other
//������Ϣ
//clientSocket->write(message);
//������Ϣ
 qDebug()<<"client receive ok";
}
////���������
//���룺QString���͵� cmd
//�����int    ���͵�״̬��
int MainWindow::Client_cmd_parser(QString cmd)
{
//�ж����������Ƿ�Ϊ��
if(cmd=="")
{
    //      ������Ϣ
    qDebug()<<"CLI��empty cmd";
    //����ֵ
    return Utils::FAIL;
}
else if(cmd.startsWith(Utils::TEMP_DAT_FROM_SER))
{
    qDebug()<<"CLI��ser reply a temp dat";
    //��ǰʹ�õĻ�ȡ��Ч���ݵ������ķ�ʽ
   int offset =cmd.length()-Utils::TEMP_DAT_FROM_SER.length();
   //������Ϣ�������Ч��������ֵ
   // qDebug()<<offset;
   //�ڴ˴�ʹ����ʱ���������ȡ������Ч����
   float value =cmd.right(offset).toFloat();
    //������Ϣ�������Ч���ݵ�ֵ
   qDebug()<<"CLI��the temp value is "<<value;
   //������ʾ���¶�
   ui->lcdNum_temp->display(value);
     //���ؽ������״̬
    return Utils::SUCCESS;

}
else if(cmd.startsWith(Utils::HUMI_DAT_FROM_SER))
{
    qDebug()<<"CLI��ser reply a temp dat";
    //��ǰʹ�õĻ�ȡ��Ч���ݵ������ķ�ʽ
   int offset =cmd.length()-Utils::HUMI_DAT_FROM_SER.length();
   //������Ϣ�������Ч��������ֵ
   // qDebug()<<offset;
   //�ڴ˴�ʹ����ʱ���������ȡ������Ч����
   float value =cmd.right(offset).toFloat();
    //������Ϣ�������Ч���ݵ�ֵ
   qDebug()<<"CLI��the humi value is "<<value;
   //������ʾ��ʪ��
   ui->lcdNum_humi->display(value);
     //���ؽ������״̬
    return Utils::SUCCESS;
}
else
{
    return Utils::FAIL;
}

}

//�ӷ������˽���udp���ݱ��Ĳۺ���
void MainWindow::processPendingDatagrams()
{
while (udpReceiveSocket->hasPendingDatagrams())
{
    //����������˷��͵����ݱ�����ʱ����
    QByteArray datagram;
    //���µ������ջ���Ĵ�С
    datagram.resize(udpReceiveSocket->pendingDatagramSize());
    QHostAddress *temp=new QHostAddress("123.123.123.123");
    //���շ��������͵����ݱ���ͬʱ�����������ַ
    udpReceiveSocket->readDatagram(datagram.data(), datagram.size(),temp,0);
    //��infopad׷��״̬��Ϣ
    ui->infoPad->append(tr("Client:Received datagram: \"%1\"")
                        .arg(datagram.data()));
    //�������������͵����ݱ���Ϣ
    //�ж����ݱ��Ƿ�Ϊ�������Ӧ����
    if(datagram==Utils::I_AM_SERVER)
    {
        //������Ϣ�����״̬��Ϣ
        qDebug()<<"got server";
        ser_addr=temp;
        //���°�ť״̬
        ui->pushButton_conn->setEnabled(true);
        //����״̬״̬��ʶ
        ui->status_label->setText(tr(Utils::HAVE_SERVER.toUtf8().data()));
    }
    //������Ϣ��������������͵�����
    qDebug()<<"client: (udp)ser msg:"<<datagram.data();
    //������Ϣ�������������ַ
    qDebug()<<"client: (udp)ser addr: "<<ser_addr->toString();

}
}
//��tcp��������ʱ���õĲۺ���
void MainWindow::socketConnected()
{
//���°�ť״̬
ui->pushButton_conn->setEnabled(false);
ui->pushButton_discon->setEnabled(true);
//��infoPad׷��״̬��Ϣ
ui->infoPad->append("connected to server success");
//����״̬
ui->status_label->setText(tr(Utils::SERVER_CONNECTED.toAscii()));
//��ʼ���������ѯ����
fresht_cli->start();
}
//��tcp�Ͽ�����ʱ���õĲۺ���
void MainWindow::socketDisConnected()
{
//���°�ť״̬
ui->pushButton_conn->setEnabled(true);
ui->pushButton_discon->setEnabled(false);
//��infoPad׷��״̬��Ϣ
ui->infoPad->append("now disconnected from server");
}
//�����ݽ�������Ķ�ʱ�ۺ���
void MainWindow::query_data()
{
//Ŀǰ������ͬʱ�������ҵ�������������޷�����
//ԭ������δ���Ƕ���ָ��Ľ���
//Ŀǰ�������Ϊ����������
static int i=1;
if(i==1)
{
    //�����¶�����
    Client_sendCmd(Utils::ASK_TEMP_DAT);
    i=2;
}
else{
    //����ʪ������
    Client_sendCmd(Utils::ASK_HUMI_DAT);
    i=1;
}
}
//�����ҷ�������ť������ʱ���õĲۺ���
void MainWindow::on_searchButton_clicked()
{
//������ʱ���󱣴�㲥��ַ
QHostAddress *temp=new QHostAddress(Utils::BROADCAST_ADDR);
//��������㲥����ָ��
Client_sendDatagram(Utils::WHO_IS_SERVER,*temp,Utils::SER_UDP_RCV_PORT);
//���������Ϣ
qDebug()<<"Clent: search btn clicked";
//��infoPad׷��״̬��Ϣ
ui->infoPad->append("Clent: search btn clicked");

}
//�������¶���С��ֵ��ť������ʱ�����Ĳۺ���
void MainWindow::on_pushButton_temp_min_clicked()
{
//������ʱ��������Ҫ���õ�ֵ
int value =ui->spinBox_temp_min->value();
//�ϳ�����ָ��
QString t=QString(Utils::SET_TEMP_MIN).append(QString::number(value));
//���������Ϣ
qDebug()<<t;
//���������������ָ��
bool flag= Client_sendCmd(t);
//�жϷ���ָ���Ƿ�ɹ�
if(flag==Utils::SUCCESS)
{
    //���������Ϣ
    qDebug()<<"send :"<<Utils::SET_TEMP_MIN<<value<<" ok";
    //��infoPad׷��״̬��Ϣ
    ui->infoPad->append("send SET_TEMP_MIN cmd ok");
}
else
{
    //���������Ϣ
    qDebug()<<"send :"<<Utils::SET_TEMP_MIN<<value<<" fail";
    //��infoPad׷��״̬��Ϣ
    ui->infoPad->append("send SET_TEMP_MIN cmd fail");
}
}
//�������¶����ֵ��ť������ʱ�����Ĳۺ���
void MainWindow::on_pushButton_temp_max_clicked()
{
////������ʱ��������Ҫ���õ�ֵ
int value =ui->spinBox_temp_max->value();
//�ϳ�����ָ��
QString t=QString(Utils::SET_TEMP_MAX).append(QString::number(value));
// ���������Ϣ
qDebug()<<t;
//���������������ָ��
bool flag= Client_sendCmd(t);
//�жϷ���ָ���Ƿ�ɹ�
if(flag==Utils::SUCCESS)
{
    //���������Ϣ
    qDebug()<<"send :"<<Utils::SET_TEMP_MAX<<value<<" ok";
    //��infoPad׷��״̬��Ϣ
    ui->infoPad->append("send SET_TEMP_MAX cmd ok");
}
else
{
    //���������Ϣ
    qDebug()<<"send :"<<Utils::SET_TEMP_MAX<<value<<" fail";
    //��infoPad׷��״̬��Ϣ
    ui->infoPad->append("send SET_TEMP_MAX cmd fail");
}
}
//������ʪ����С��ֵ��ť������ʱ�����Ĳۺ���
void MainWindow::on_pushButton_humi_min_clicked()
{
//������ʱ��������Ҫ���õ�ֵ
int value =ui->spinBox_humi_min->value();
//�ϳ�����ָ��
QString t=QString(Utils::SET_HUMI_MIN).append(QString::number(value));
// ���������Ϣ
qDebug()<<t;
//���������������ָ��
bool flag= Client_sendCmd(t);
//�жϷ���ָ���Ƿ�ɹ�
if(flag==Utils::SUCCESS)
{
    //���������Ϣ
    qDebug()<<"send :"<<Utils::SET_HUMI_MIN<<value<<" ok";
    //��infoPad׷��״̬��Ϣ
    ui->infoPad->append("send SET_HUMI_MIN cmd ok");
}
else
{
    //���������Ϣ
    qDebug()<<"send :"<<Utils::SET_HUMI_MIN<<value<<" fail";
    //��infoPad׷��״̬��Ϣ
    ui->infoPad->append("send SET_HUMI_MIN cmd fail");
}
}
//������ʪ�����ֵ��ť������ʱ�����Ĳۺ���
void MainWindow::on_pushButton_humi_max_clicked()
{
//������ʱ��������Ҫ���õ�ֵ
int value =ui->spinBox_humi_max->value();
// qDebug()<<"current val:"<<value;
//�ϳ�����ָ��
QString t=QString(Utils::SET_HUMI_MAX).append(QString::number(value));
// ���������Ϣ
qDebug()<<t;
//���������������ָ��
bool flag= Client_sendCmd(t);
//�жϷ���ָ���Ƿ�ɹ�
if(flag==Utils::SUCCESS)
{
    //���������Ϣ
    qDebug()<<"send :"<<Utils::SET_HUMI_MAX<<value<<" ok";
    //��infoPad׷��״̬��Ϣ
    ui->infoPad->append("send SET_HUMI_MAX cmd ok");
}
else
{
    //���������Ϣ
    qDebug()<<"send :"<<Utils::SET_HUMI_MAX<<value<<" fail";
    //��infoPad׷��״̬��Ϣ
    ui->infoPad->append("send SET_HUMI_MAX cmd fail");
}
}
//�����ӷ�������ť������ʱ�����Ĳۺ���
void MainWindow::on_pushButton_conn_clicked()
{
//�ͻ������ӷ�����
clientSocket->connectToHost(*ser_addr,Utils::SER_TCP_PORT);
//��infoPad׷��״̬��Ϣ
ui->infoPad->append("trying connect to server");

}
//���ͻ��˶Ͽ��������������ʱ�����Ĳۺ���
void MainWindow::on_pushButton_discon_clicked()
{
//�ͻ��˶Ͽ��������������
clientSocket->disconnectFromHost();
//��infoPad׷��״̬��Ϣ
ui->infoPad->append("trying disconnect from server");
}

void MainWindow::on_pushButton_open_light_clicked()
{
    //���������������ָ��
    bool flag= Client_sendCmd(Utils::OPEN_THE_LIGHT);
    //�жϷ���ָ���Ƿ�ɹ�
    if(flag==Utils::SUCCESS)
    {
        //���������Ϣ
        qDebug()<<"send :"<<Utils::OPEN_THE_LIGHT<<" ok";
        //��infoPad׷��״̬��Ϣ
        ui->infoPad->append("send OPEN_THE_LIGHT  cmd ok");
    }
    else
    {
        //���������Ϣ
        qDebug()<<"send :"<<Utils::OPEN_THE_LIGHT<<" fail";
        //��infoPad׷��״̬��Ϣ
        ui->infoPad->append("send OPEN_THE_LIGHT cmd fail");
    }
}

void MainWindow::on_pushButton_close_light_clicked()
{

    //���������������ָ��
    bool flag= Client_sendCmd(Utils::CLOSE_THE_LIGHT);
    //�жϷ���ָ���Ƿ�ɹ�
    if(flag==Utils::SUCCESS)
    {
        //���������Ϣ
        qDebug()<<"send :"<<Utils::CLOSE_THE_LIGHT<<" ok";
        //��infoPad׷��״̬��Ϣ
        ui->infoPad->append("send CLOSE_THE_LIGHT  cmd ok");
    }
    else
    {
        //���������Ϣ
        qDebug()<<"send :"<<Utils::CLOSE_THE_LIGHT<<" fail";
        //��infoPad׷��״̬��Ϣ
        ui->infoPad->append("send CLOSE_THE_LIGHT cmd fail");
    }
}
