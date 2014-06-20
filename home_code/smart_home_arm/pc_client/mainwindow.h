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
    //发送udp数据报的函数
    //输入：Qstring 类型的msg
    //      QHostAddress类型的addr
    //      int类型的port
    void Client_sendDatagram(QString msg, QHostAddress addr,int port);
    //tcp发送命令函数
    //输入：QString 类型的cmd
    //返回：操作状态码
    int Client_sendCmd(QString cmd);
    //命令解析器
    //输入：QString类型的 cmd
    //输出：int    类型的状态码
    int Client_cmd_parser(QString cmd);
private slots:
    //查找服务器按钮按下触发的槽函数
    void on_searchButton_clicked();


private:
    Ui::MainWindow *ui;

    //udp接收套接字对象
    QUdpSocket *udpReceiveSocket;
    //udp发送套接字对象
    QUdpSocket *udpSendSocket;
    //保存服务器地址的变量
    QHostAddress *ser_addr;
    //tcp套接字对象
    QTcpSocket   *clientSocket;
    //用于定时请求的定时器
    QTimer *fresht_cli;
    //一堆槽函数的声明
private slots:
    //当服务端发送消息时触发的槽函数
    void Client_dataReceive();
    //处理服务器端发送的udp数据报的槽函数
    void processPendingDatagrams();
    //当设置温度最小阀值按钮被按下时触发的槽函数
    void on_pushButton_temp_min_clicked();
    //当设置温度最大阀值按钮被按下时触发的槽函数
    void on_pushButton_temp_max_clicked();
    //当设置湿度最大阀值按钮被按下时触发的槽函数
    void on_pushButton_humi_min_clicked();
    //当设置湿度最大阀值按钮被按下时触发的槽函数
    void on_pushButton_humi_max_clicked();
    //当连接服务器按钮被按下时触发的槽函数
    void on_pushButton_conn_clicked();
    //当断开服务器连接按钮被按下时触发的槽函数
    void on_pushButton_discon_clicked();

    //当客户端连接服务器成功时触发的槽函数
    void socketConnected();
    //当客户端断开与服务器的连接时触发的槽函数
    void socketDisConnected();
    //向服务器查询数据的槽函数
    void query_data();

    void on_pushButton_open_light_clicked();
    void on_pushButton_clicked();
};

#endif // MAINWINDOW_H
