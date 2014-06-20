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
    //获取本机的局域网地址并返回
    QString getIP();
    //命令解析器
    //输入：QString类型的 cmd
    //输出：int    类型的状态码
    int Ser_cmd_parser(QString cmd);
    //udp发送函数
    //输入：QString类型的 msg
    //输出：无
    void Ser_sendDatagram(QString msg);
    //tcp发送data函数
    //输入：QString 类型的data
    //返回：操作状态码
    int Ser_sendDat(QString dat);

    //串口数据解析函数
    //输入：QString类型的 msg
    //输出： int类型的状态码
    int ser_serial_data_parser(QString msg);
    //
    //int add_data(QString id, QString name, QString type, QString value, QString value_min, QString value_max);
    int del_data(QString id, QString name, QString type, QString value, QString value_min, QString value_max);
//    int update_data(QString id, QString name, QString type, QString value, QString value_min, QString value_max);

    //串口初始化
    //该函数实现了com1-com30的串口自动化查找
    //及初始化
    int ser_serial_port_init();

private:
    Ui::MainWindow *ui;
    //声明私有的tcp通信对象
    //tcp服务器对象
    QTcpServer *tcpServer;
    //tcp套接字对象
    QTcpSocket *tcpSocket;
    //udp接收套接字对象
    QUdpSocket *udpReceiveSocket;
    //udp发送套接字对象
    QUdpSocket *udpSendSocket;
    //客户端的地址对象
    QHostAddress *addr;

    //
    QSqlQueryModel *model;
    //串口对象
    Win_QextSerialPort *ser_Com;
    //
    //用于定时刷新数据库显示列表的定时器
    QTimer *table_fresh_t;
    //
    //用于定时读取串口缓存区数据的定时器
    QTimer *serial_read_fresh_t;

    //
    MyThread th;
    // 添加Utils工具类后，将公用数据全部移走
    //
    //测试使用的两个命令对象
    //测试温度的命令对象
    //QString  TEMP ;
    //测试湿度的命令对象
    //QString  HUMI ;
    //命令解析的状态标识，移入Utils工具类
    //int const static  SUCCESS=0;
    //int const static  FAIL=1;
 //声明各种槽函数
public slots:
    //startBtn按键按下触发的槽函数
    void listenBtnClicked();
    //stopBtn按键按下触发的槽函数
    void stopBtnClicked();
    //服务器处于监听状态，当有客户端连接时触发此槽函数
    void newConnectionComing();
    //当客户端断开连接时触发的槽函数
    void clientDisConnected();
    //当客户端发送消息时触发的槽函数
    void Ser_dataReceive();
    //处理客户端发送的udp数据报的槽函数
    void processPendingDatagrams();
    //当串口有数据时触发的槽函数
    void readSerCom();
    //
    int sendSerCom(QString cmd);
    //用于定时刷新显示数据库数据列表的槽函数
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
