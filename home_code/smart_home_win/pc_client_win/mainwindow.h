#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "utils.h"

#include <QUdpSocket>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>
#include <QHostAddress>
#include <QDebug>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //����udp���ݱ��ĺ���
    //���룺Qstring ���͵�msg
    //      QHostAddress���͵�addr
    //      int���͵�port
    void Client_sendDatagram(QString msg, QHostAddress addr,int port);
    //tcp���������
    //���룺QString ���͵�cmd
    //���أ�����״̬��
    int Client_sendCmd(QString cmd);
    //���������
    //���룺QString���͵� cmd
    //�����int    ���͵�״̬��
    int Client_cmd_parser(QString cmd);
private slots:
    //���ҷ�������ť���´����Ĳۺ���
    void on_searchButton_clicked();


private:
    Ui::MainWindow *ui;

    //udp�����׽��ֶ���
    QUdpSocket *udpReceiveSocket;
    //udp�����׽��ֶ���
    QUdpSocket *udpSendSocket;
    //�����������ַ�ı���
    QHostAddress *ser_addr;
    //tcp�׽��ֶ���
    QTcpSocket   *clientSocket;
    //���ڶ�ʱ����Ķ�ʱ��
    QTimer *fresht_cli;
    //һ�Ѳۺ���������
private slots:
    //������˷�����Ϣʱ�����Ĳۺ���
    void Client_dataReceive();
    //����������˷��͵�udp���ݱ��Ĳۺ���
    void processPendingDatagrams();
    //�������¶���С��ֵ��ť������ʱ�����Ĳۺ���
    void on_pushButton_temp_min_clicked();
    //�������¶����ֵ��ť������ʱ�����Ĳۺ���
    void on_pushButton_temp_max_clicked();
    //������ʪ�����ֵ��ť������ʱ�����Ĳۺ���
    void on_pushButton_humi_min_clicked();
    //������ʪ�����ֵ��ť������ʱ�����Ĳۺ���
    void on_pushButton_humi_max_clicked();
    //�����ӷ�������ť������ʱ�����Ĳۺ���
    void on_pushButton_conn_clicked();
    //���Ͽ����������Ӱ�ť������ʱ�����Ĳۺ���
    void on_pushButton_discon_clicked();

    //���ͻ������ӷ������ɹ�ʱ�����Ĳۺ���
    void socketConnected();
    //���ͻ��˶Ͽ��������������ʱ�����Ĳۺ���
    void socketDisConnected();
    //���������ѯ���ݵĲۺ���
    void query_data();

    void on_pushButton_open_light_clicked();
    void on_pushButton_close_light_clicked();
};

#endif // MAINWINDOW_H
