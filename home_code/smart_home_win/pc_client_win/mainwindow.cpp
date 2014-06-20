#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextCodec>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    //设置编码，可用于国际化
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("gb2312"));

    ui->setupUi(this);

    //初始化显示湿度控件的显示样式
    ui->lcdNum_humi->setSegmentStyle(QLCDNumber::Flat);
    //初始化显示温度控件的显示样式
    ui->lcdNum_temp->setSegmentStyle(QLCDNumber::Flat);
    //设置湿度显示控件的默认显示值
    ui->lcdNum_humi->display(50);
    //设置温度显示控件的默认显示值
    ui->lcdNum_temp->display(22);
    //设置 设置湿度最大阀值的spinbox域值范围
    ui->spinBox_humi_max->setRange(0,100);
    //设置 设置湿度最小阀值的spinbox域值范围
    ui->spinBox_humi_min->setRange(0,100);
    //设置显示后缀
    ui->spinBox_humi_max->setSuffix("%");
    //设置显示后缀
    ui->spinBox_humi_min->setSuffix("%");
    //设置默认选择的参数值
    ui->spinBox_humi_min->setValue(20);
    //设置默认选择的参数值
    ui->spinBox_humi_max->setValue(70);
    //设置 设置温度最大阀值的spinbox域值范围
    ui->spinBox_temp_max->setRange(-20,60);
    //设置 设置温度最大阀值的spinbox域值范围
    ui->spinBox_temp_min->setRange(-20,60);
    //设置显示后缀
    ui->spinBox_temp_max->setSuffix("℃");
    // 设置显示后缀
    ui->spinBox_temp_min->setSuffix("℃");
    //设置默认选择的参数值
    ui->spinBox_temp_max->setValue(40);
    //设置默认选择的参数值
    ui->spinBox_temp_min->setValue(20);
    //设置连接服务器按钮的初始状态
    ui->pushButton_conn->setEnabled(false);
    //设置断开服务器连接按钮的初始状态
    ui->pushButton_discon->setEnabled(false);
    //对服务器地址进行初始化
    ser_addr=new QHostAddress("222.222.222.222");
    //初始化udp发送套接字对象
    udpSendSocket = new QUdpSocket(this);
    //初始化udp接收套接字对象
    udpReceiveSocket = new QUdpSocket(this);
    //绑定本地udp套接字监听
    udpReceiveSocket->bind(Utils::CLI_UDP_RCV_PORT, QUdpSocket::ShareAddress);
    //绑定本地udp套接字的readyRead信号到processPendingDatagrams槽函数
    connect(udpReceiveSocket, SIGNAL(readyRead()),this, SLOT(processPendingDatagrams()));
    //初始化tcp套接字
    clientSocket=new QTcpSocket(this);
    //将clientSocket的connected信号与socketConnected槽函数绑定
    connect(clientSocket,SIGNAL(connected()),this,SLOT(socketConnected()));
    //将clientSocket的 disconnected 信号与socketDisConnected槽函数绑定
    connect(clientSocket,SIGNAL(disconnected()),this,SLOT(socketDisConnected()));
    //将clientSocket的 readyRead 信号与Client_dataReceive槽函数绑定
    connect(clientSocket,SIGNAL(readyRead()),this,SLOT(Client_dataReceive()));
    //声明用于刷新的定时器
    fresht_cli=new QTimer(this);
    //设置定时器溢出时间
    fresht_cli->setInterval(1500);
    //将定时器的timeout信号与query_data槽函数绑定
    connect(fresht_cli,SIGNAL(timeout()),this,SLOT(query_data()));

}

MainWindow::~MainWindow()
{
    delete ui;
}
//发送udp数据报的函数
//输入：Qstring 类型的msg
//      QHostAddress类型的addr
//      int类型的port
void MainWindow::Client_sendDatagram(QString msg,QHostAddress addr,int port)
{
//保存消息的临时对象
QByteArray datagram;
//判断消息是否为空
if(msg==NULL)
{
    //向infopad追加状态信息
    ui->infoPad->append(tr("sorry msg is null"));
    return;
}
else
{
    //向infopad追加状态信息
    ui->infoPad->append(tr("Client:Now send datagram "));
    //将消息转储到datagram
    datagram = msg.toAscii();
}
//udpSocket->writeDatagram(datagram.data(), datagram.size(),
//                          QHostAddress::Broadcast, 8903);
//开始发送数据
//地址：地址
//端口：端口
udpSendSocket->writeDatagram(datagram.data(), datagram.size(),
                         addr,port );
//调试信息：输出地址和端口
qDebug()<<addr.toString()<<":"<<port;
}
//tcp发送命令函数
//输入：QString 类型的cmd
//返回：操作状态码
int MainWindow::Client_sendCmd(QString cmd)
{
//tcp发送数据，并函数保留返回值
int ret=clientSocket->write(cmd.toUtf8());
//向infoPad追加状态信息
ui->infoPad->append("Me:");
//向infoPad追加状态信息
ui->infoPad->append("\t"+cmd);
//判断发送是否出错
//ret == -1 表示发送失败
if(ret>0)
{
    //返回发送状态
    return Utils::SUCCESS;
}
else
{
    //返回发送状态
    return Utils::FAIL;
}
}

//当服务端发送消息时触发的槽函数
void MainWindow::Client_dataReceive()
{
//用于保存消息的临时对象
QByteArray message;
//从clientSocket获取消息
message=clientSocket->readAll();
//向infopad追加状态信息
ui->infoPad->append(clientSocket->peerAddress().toString()+":");
//向infopad追加状态信息
ui->infoPad->append("\t"+message);
//在这里可以完成规则检查或协议解析过程
//目前并没有考虑协议优化等
//目前使用的不是一个较好的协议，而是字符串协议
//以下为命令解析的过程，解析成功返回SUCCESS，失败返回FAIL
if( Client_cmd_parser(message)==Utils::SUCCESS)
{
    //调试信息
    qDebug()<<"CLI：parser ok";
}
else
{
    //调试信息
    qDebug()<<"CLI：parser fail";
}
//send back message or something other
//调试信息
//clientSocket->write(message);
//调试信息
 qDebug()<<"client receive ok";
}
////命令解析器
//输入：QString类型的 cmd
//输出：int    类型的状态码
int MainWindow::Client_cmd_parser(QString cmd)
{
//判断输入命令是否为空
if(cmd=="")
{
    //      调试信息
    qDebug()<<"CLI：empty cmd";
    //返回值
    return Utils::FAIL;
}
else if(cmd.startsWith(Utils::TEMP_DAT_FROM_SER))
{
    qDebug()<<"CLI：ser reply a temp dat";
    //当前使用的获取有效数据的索引的方式
   int offset =cmd.length()-Utils::TEMP_DAT_FROM_SER.length();
   //调试信息：输出有效数据索引值
   // qDebug()<<offset;
   //在此处使用临时变量保存获取到的有效数据
   float value =cmd.right(offset).toFloat();
    //调试信息：输出有效数据的值
   qDebug()<<"CLI：the temp value is "<<value;
   //更新显示的温度
   ui->lcdNum_temp->display(value);
     //返回解析结果状态
    return Utils::SUCCESS;

}
else if(cmd.startsWith(Utils::HUMI_DAT_FROM_SER))
{
    qDebug()<<"CLI：ser reply a temp dat";
    //当前使用的获取有效数据的索引的方式
   int offset =cmd.length()-Utils::HUMI_DAT_FROM_SER.length();
   //调试信息：输出有效数据索引值
   // qDebug()<<offset;
   //在此处使用临时变量保存获取到的有效数据
   float value =cmd.right(offset).toFloat();
    //调试信息：输出有效数据的值
   qDebug()<<"CLI：the humi value is "<<value;
   //更新显示的湿度
   ui->lcdNum_humi->display(value);
     //返回解析结果状态
    return Utils::SUCCESS;
}
else
{
    return Utils::FAIL;
}

}

//从服务器端接收udp数据报的槽函数
void MainWindow::processPendingDatagrams()
{
while (udpReceiveSocket->hasPendingDatagrams())
{
    //保存服务器端发送的数据报的临时对象
    QByteArray datagram;
    //重新调整接收缓存的大小
    datagram.resize(udpReceiveSocket->pendingDatagramSize());
    QHostAddress *temp=new QHostAddress("123.123.123.123");
    //接收服务器发送的数据报，同时保存服务器地址
    udpReceiveSocket->readDatagram(datagram.data(), datagram.size(),temp,0);
    //向infopad追加状态信息
    ui->infoPad->append(tr("Client:Received datagram: \"%1\"")
                        .arg(datagram.data()));
    //解析服务器发送的数据报信息
    //判断数据报是否为服务端响应请求
    if(datagram==Utils::I_AM_SERVER)
    {
        //调试信息：输出状态信息
        qDebug()<<"got server";
        ser_addr=temp;
        //更新按钮状态
        ui->pushButton_conn->setEnabled(true);
        //更新状态状态标识
        ui->status_label->setText(tr(Utils::HAVE_SERVER.toUtf8().data()));
    }
    //调试信息：输出服务器发送的数据
    qDebug()<<"client: (udp)ser msg:"<<datagram.data();
    //调试信息：输出服务器地址
    qDebug()<<"client: (udp)ser addr: "<<ser_addr->toString();

}
}
//当tcp建立连接时调用的槽函数
void MainWindow::socketConnected()
{
//更新按钮状态
ui->pushButton_conn->setEnabled(false);
ui->pushButton_discon->setEnabled(true);
//向infoPad追加状态信息
ui->infoPad->append("connected to server success");
//更新状态
ui->status_label->setText(tr(Utils::SERVER_CONNECTED.toAscii()));
//开始向服务器查询数据
fresht_cli->start();
}
//当tcp断开连接时调用的槽函数
void MainWindow::socketDisConnected()
{
//更新按钮状态
ui->pushButton_conn->setEnabled(true);
ui->pushButton_discon->setEnabled(false);
//向infoPad追加状态信息
ui->infoPad->append("now disconnected from server");
}
//对数据进行请求的定时槽函数
void MainWindow::query_data()
{
//目前发现若同时请求，则我的命令解析器会无法解析
//原因是我未考虑多条指令的解析
//目前解决方案为分两次请求。
static int i=1;
if(i==1)
{
    //请求温度数据
    Client_sendCmd(Utils::ASK_TEMP_DAT);
    i=2;
}
else{
    //请求湿度数据
    Client_sendCmd(Utils::ASK_HUMI_DAT);
    i=1;
}
}
//当查找服务器按钮被按下时调用的槽函数
void MainWindow::on_searchButton_clicked()
{
//创建临时对象保存广播地址
QHostAddress *temp=new QHostAddress(Utils::BROADCAST_ADDR);
//向局域网广播查找指令
Client_sendDatagram(Utils::WHO_IS_SERVER,*temp,Utils::SER_UDP_RCV_PORT);
//输出调试信息
qDebug()<<"Clent: search btn clicked";
//向infoPad追加状态信息
ui->infoPad->append("Clent: search btn clicked");

}
//当设置温度最小阀值按钮被按下时触发的槽函数
void MainWindow::on_pushButton_temp_min_clicked()
{
//创建临时变量保存要设置的值
int value =ui->spinBox_temp_min->value();
//合成设置指令
QString t=QString(Utils::SET_TEMP_MIN).append(QString::number(value));
//输出调试信息
qDebug()<<t;
//向服务器发送设置指令
bool flag= Client_sendCmd(t);
//判断发送指令是否成功
if(flag==Utils::SUCCESS)
{
    //输出调试信息
    qDebug()<<"send :"<<Utils::SET_TEMP_MIN<<value<<" ok";
    //向infoPad追加状态信息
    ui->infoPad->append("send SET_TEMP_MIN cmd ok");
}
else
{
    //输出调试信息
    qDebug()<<"send :"<<Utils::SET_TEMP_MIN<<value<<" fail";
    //向infoPad追加状态信息
    ui->infoPad->append("send SET_TEMP_MIN cmd fail");
}
}
//当设置温度最大阀值按钮被按下时触发的槽函数
void MainWindow::on_pushButton_temp_max_clicked()
{
////创建临时变量保存要设置的值
int value =ui->spinBox_temp_max->value();
//合成设置指令
QString t=QString(Utils::SET_TEMP_MAX).append(QString::number(value));
// 输出调试信息
qDebug()<<t;
//向服务器发送设置指令
bool flag= Client_sendCmd(t);
//判断发送指令是否成功
if(flag==Utils::SUCCESS)
{
    //输出调试信息
    qDebug()<<"send :"<<Utils::SET_TEMP_MAX<<value<<" ok";
    //向infoPad追加状态信息
    ui->infoPad->append("send SET_TEMP_MAX cmd ok");
}
else
{
    //输出调试信息
    qDebug()<<"send :"<<Utils::SET_TEMP_MAX<<value<<" fail";
    //向infoPad追加状态信息
    ui->infoPad->append("send SET_TEMP_MAX cmd fail");
}
}
//当设置湿度最小阀值按钮被按下时触发的槽函数
void MainWindow::on_pushButton_humi_min_clicked()
{
//创建临时变量保存要设置的值
int value =ui->spinBox_humi_min->value();
//合成设置指令
QString t=QString(Utils::SET_HUMI_MIN).append(QString::number(value));
// 输出调试信息
qDebug()<<t;
//向服务器发送设置指令
bool flag= Client_sendCmd(t);
//判断发送指令是否成功
if(flag==Utils::SUCCESS)
{
    //输出调试信息
    qDebug()<<"send :"<<Utils::SET_HUMI_MIN<<value<<" ok";
    //向infoPad追加状态信息
    ui->infoPad->append("send SET_HUMI_MIN cmd ok");
}
else
{
    //输出调试信息
    qDebug()<<"send :"<<Utils::SET_HUMI_MIN<<value<<" fail";
    //向infoPad追加状态信息
    ui->infoPad->append("send SET_HUMI_MIN cmd fail");
}
}
//当设置湿度最大阀值按钮被按下时触发的槽函数
void MainWindow::on_pushButton_humi_max_clicked()
{
//创建临时变量保存要设置的值
int value =ui->spinBox_humi_max->value();
// qDebug()<<"current val:"<<value;
//合成设置指令
QString t=QString(Utils::SET_HUMI_MAX).append(QString::number(value));
// 输出调试信息
qDebug()<<t;
//向服务器发送设置指令
bool flag= Client_sendCmd(t);
//判断发送指令是否成功
if(flag==Utils::SUCCESS)
{
    //输出调试信息
    qDebug()<<"send :"<<Utils::SET_HUMI_MAX<<value<<" ok";
    //向infoPad追加状态信息
    ui->infoPad->append("send SET_HUMI_MAX cmd ok");
}
else
{
    //输出调试信息
    qDebug()<<"send :"<<Utils::SET_HUMI_MAX<<value<<" fail";
    //向infoPad追加状态信息
    ui->infoPad->append("send SET_HUMI_MAX cmd fail");
}
}
//当连接服务器按钮被按下时触发的槽函数
void MainWindow::on_pushButton_conn_clicked()
{
//客户端连接服务器
clientSocket->connectToHost(*ser_addr,Utils::SER_TCP_PORT);
//向infoPad追加状态信息
ui->infoPad->append("trying connect to server");

}
//当客户端断开与服务器的连接时触发的槽函数
void MainWindow::on_pushButton_discon_clicked()
{
//客户端断开与服务器的连接
clientSocket->disconnectFromHost();
//向infoPad追加状态信息
ui->infoPad->append("trying disconnect from server");
}

void MainWindow::on_pushButton_open_light_clicked()
{
    //向服务器发送设置指令
    bool flag= Client_sendCmd(Utils::OPEN_THE_LIGHT);
    //判断发送指令是否成功
    if(flag==Utils::SUCCESS)
    {
        //输出调试信息
        qDebug()<<"send :"<<Utils::OPEN_THE_LIGHT<<" ok";
        //向infoPad追加状态信息
        ui->infoPad->append("send OPEN_THE_LIGHT  cmd ok");
    }
    else
    {
        //输出调试信息
        qDebug()<<"send :"<<Utils::OPEN_THE_LIGHT<<" fail";
        //向infoPad追加状态信息
        ui->infoPad->append("send OPEN_THE_LIGHT cmd fail");
    }
}

void MainWindow::on_pushButton_close_light_clicked()
{

    //向服务器发送设置指令
    bool flag= Client_sendCmd(Utils::CLOSE_THE_LIGHT);
    //判断发送指令是否成功
    if(flag==Utils::SUCCESS)
    {
        //输出调试信息
        qDebug()<<"send :"<<Utils::CLOSE_THE_LIGHT<<" ok";
        //向infoPad追加状态信息
        ui->infoPad->append("send CLOSE_THE_LIGHT  cmd ok");
    }
    else
    {
        //输出调试信息
        qDebug()<<"send :"<<Utils::CLOSE_THE_LIGHT<<" fail";
        //向infoPad追加状态信息
        ui->infoPad->append("send CLOSE_THE_LIGHT cmd fail");
    }
}
