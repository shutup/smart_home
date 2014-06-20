#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "utils.h"
#include "mythread.h"
#include <QUdpSocket>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
//#include <QString>
#include <QNetworkInterface>

#include<QSqlQueryModel>
#include<QSqlQuery>
#include<QTimer>
//
#include "win_qextserialport.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //��ȡ�����ľ�������ַ������
    QString getIP();
    //���������
    //���룺QString���͵� cmd
    //�����int    ���͵�״̬��
    int Ser_cmd_parser(QString cmd);
    //udp���ͺ���
    //���룺QString���͵� msg
    //�������
    void Ser_sendDatagram(QString msg);
    //tcp����data����
    //���룺QString ���͵�data
    //���أ�����״̬��
    int Ser_sendDat(QString dat);

    //�������ݽ�������
    //���룺QString���͵� msg
    //����� int���͵�״̬��
    int ser_serial_data_parser(QString msg);
    //
    //int add_data(QString id, QString name, QString type, QString value, QString value_min, QString value_max);
    int del_data(QString id, QString name, QString type, QString value, QString value_min, QString value_max);
//    int update_data(QString id, QString name, QString type, QString value, QString value_min, QString value_max);

    //���ڳ�ʼ��
    //�ú���ʵ����com1-com30�Ĵ����Զ�������
    //����ʼ��
    int ser_serial_port_init();

private:
    Ui::MainWindow *ui;
    //����˽�е�tcpͨ�Ŷ���
    //tcp����������
    QTcpServer *tcpServer;
    //tcp�׽��ֶ���
    QTcpSocket *tcpSocket;
    //udp�����׽��ֶ���
    QUdpSocket *udpReceiveSocket;
    //udp�����׽��ֶ���
    QUdpSocket *udpSendSocket;
    //�ͻ��˵ĵ�ַ����
    QHostAddress *addr;

    //
    QSqlQueryModel *model;
    //���ڶ���
    Win_QextSerialPort *ser_Com;
    //
    //���ڶ�ʱˢ�����ݿ���ʾ�б�Ķ�ʱ��
    QTimer *table_fresh_t;
    //
    //���ڶ�ʱ��ȡ���ڻ��������ݵĶ�ʱ��
    QTimer *serial_read_fresh_t;

    //
    MyThread th;
    // ���Utils������󣬽���������ȫ������
    //
    //����ʹ�õ������������
    //�����¶ȵ��������
    //QString  TEMP ;
    //����ʪ�ȵ��������
    //QString  HUMI ;
    //���������״̬��ʶ������Utils������
    //int const static  SUCCESS=0;
    //int const static  FAIL=1;
 //�������ֲۺ���
public slots:
    //startBtn�������´����Ĳۺ���
    void listenBtnClicked();
    //stopBtn�������´����Ĳۺ���
    void stopBtnClicked();
    //���������ڼ���״̬�����пͻ�������ʱ�����˲ۺ���
    void newConnectionComing();
    //���ͻ��˶Ͽ�����ʱ�����Ĳۺ���
    void clientDisConnected();
    //���ͻ��˷�����Ϣʱ�����Ĳۺ���
    void Ser_dataReceive();
    //����ͻ��˷��͵�udp���ݱ��Ĳۺ���
    void processPendingDatagrams();
    //������������ʱ�����Ĳۺ���
    void readSerCom();
    //
    int sendSerCom(QString cmd);
    //���ڶ�ʱˢ����ʾ���ݿ������б�Ĳۺ���
    int view_data();
    //
signals:
    void send_cmd_to_node(QString );
    void send_data_to_thread(QString);
    //
private slots:
    void on_freshButton_clicked();
    void on_testButton_clicked();

};

#endif // MAINWINDOW_H
