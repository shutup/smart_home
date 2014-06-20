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
    //设置编码，可用于国际化
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("gb2312"));

    //此定时器为轮询串口缓存数据
    serial_read_fresh_t=new QTimer(this);
    //设置定时器刷新周期
    serial_read_fresh_t->setInterval(400);
    //对串口进行初始化
    if(ser_serial_port_init()==Utils::SUCCESS)
    {
        ui->infoPad->append("Ser : Found Serial Device");
        th.start();
    }
    else
    {
        ui->infoPad->append(("Ser : No Serial Device Found"));
    }
    //初始化tcp服务器端
    tcpServer =new QTcpServer(this);
    //初始化udp发送套接字对象
    udpSendSocket = new QUdpSocket(this);
    //初始化udp接收套接字对象
    udpReceiveSocket = new QUdpSocket(this);
    //绑定本地udp套接字监听//8904
    udpReceiveSocket->bind(Utils::SER_UDP_RCV_PORT, QUdpSocket::ShareAddress);
    //绑定本地udp套接字的readyRead信号到processPendingDatagrams槽函数
    connect(udpReceiveSocket, SIGNAL(readyRead()),this, SLOT(processPendingDatagrams()));
    //初始化客户端默认地址对象
    addr = new QHostAddress("192.168.1.1");

    //设置按钮的初始化状态
    ui->startBtn->setEnabled(true);
    ui->stopBtn->setEnabled(false);
    //绑定tcpServer的newConnection信号到newConnectionComing槽函数
    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(newConnectionComing()));
    //绑定startBtn的clicked信号到listenBtnClicked槽函数
    connect(ui->startBtn,SIGNAL(clicked()),this,SLOT(listenBtnClicked()));
     //绑定stopBtn的clicked信号到listenBtnClicked槽函数
    connect(ui->stopBtn,SIGNAL(clicked()),this,SLOT(stopBtnClicked()));
    //子节点将会发送的命令
    //在下一个迭代版本中将分离出去
    //
    // 将公用数据移入Utils工具类
    //  2014，03，15 已完成

    //温度传感器子节点发送的命令头
    // TEMP ="temp_data_is:";
    //湿度传感器子节点发送的命令头
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
//startBtn按键按下触发的槽函数
void MainWindow::listenBtnClicked()
{
    //调试信息：测试工具类（静态成员类）
    // qDebug()<<"test "<<Utils::SET_TEMP_MAX;
    //调试信息
    //qDebug()<<"listenBtnClicked ok";
    //初始化清空infoPad
    ui->infoPad->clear();
    //向infopad追加状态信息
    ui->infoPad->append("SER:start listen ...");
    //tcpServer开始在本地8888端口监听
    tcpServer->listen(QHostAddress::Any,8888);
    //判断tcpServer是否开始监听
    if(tcpServer->isListening())
    {
        //调试信息
        //qDebug()<<getIP();
        //向infopad追加状态信息
       ui->infoPad->append(getIP()+" listen on 8888");
       //更新按键状态
       ui->startBtn->setEnabled(false);
       ui->stopBtn->setEnabled(true);
    }
}
//stopBtn按键按下触发的槽函数
void MainWindow::stopBtnClicked()
{
//清空infoPad输出数据
    ui->infoPad->clear();
    //关闭tcpServer服务器，此时不再响应连接
    tcpServer->close();
    //判断tcpServer服务器是否监听
    if(!tcpServer->isListening())
    {
        //向infopad追加状态信息
        ui->infoPad->append("SER:close the server");
        //更新按键状态
        ui->startBtn->setEnabled(true);
        ui->stopBtn->setEnabled(false);
    }
    //向infopad追加状态信息
    ui->infoPad->append("SER:stop listen ...");
}
//服务器处于监听状态，当有客户端连接时触发此槽函数
void MainWindow::newConnectionComing()
{
    //向infopad追加状态信息
    ui->infoPad->append("SER:New Connection Coming");
    //获取和客户端通信的套接字
    //如果需要连接多个客户端，需要将获取到的每个客户端套接字保存起来
    //比如将其传送给一个线程
    //get socket from server
    //if you need more client you need to send the socket to another worker thread
    tcpSocket =tcpServer->nextPendingConnection();
    //向infopad追加状态信息
    ui->infoPad->append(tcpSocket->peerAddress().toString() + " connected");
    //将tcpsocket的disconnected信号与clientDisConnected槽函数进行绑定
    connect(tcpSocket,SIGNAL(disconnected()),this,SLOT(clientDisConnected()));
    //将tcpSocket的readyRead信号与dataReceive槽函数进行绑定
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(Ser_dataReceive()));
}
//当客户端断开连接时触发的槽函数
void MainWindow::clientDisConnected()
{
    //向infopad追加状态信息
    ui->infoPad->append("SER:client disconnected!");
}
//当客户端发送消息时触发的槽函数
void MainWindow::Ser_dataReceive()
{
    //用于保存消息的临时对象
    QByteArray message;
    //从tcpSocket获取消息
    message=tcpSocket->readAll();

    //向infopad追加状态信息
    ui->infoPad->append(tcpSocket->peerAddress().toString()+":");
    //向infopad追加状态信息
    ui->infoPad->append("\t"+message);
    //在这里可以完成规则检查或协议解析过程
    //目前并没有考虑协议优化等
    //目前使用的不是一个较好的协议，而是字符串协议
    //以下为命令解析的过程，解析成功返回SUCCESS，失败返回FAIL
    if( Ser_cmd_parser(message.trimmed())==Utils::SUCCESS)
    {
        //调试信息
        qDebug()<<"SER:parser ok";
    }
    else
    {
        //调试信息
        qDebug()<<"SER:parser fail";
    }
    //send back message or something other
    //调试信息
    //tcpSocket->write(message);
    //调试信息
     qDebug()<<"Ser:server receive ok";
}
//（tcp）命令解析器函数
//输入：QString 类型的命令
//输出：int 类型的状态标识
//传入的参数必须经过trim（）处理
int MainWindow::Ser_cmd_parser(QString cmd)
{
    //判断输入命令是否为空
    if(cmd=="")
    {
        //调试信息
        qDebug()<<"SER:empty cmd";
        //返回值
        return Utils::FAIL;
    }
    //判断是否为客户端请求温度数据
    else if(cmd==(Utils::ASK_TEMP_DAT))
    {
        //调试信息
        qDebug()<<"SER:client ask for temp dat";
        //组合响应数据请求指令
        //包括命令头和数据
        QString t=QString(Utils::TEMP_DAT_TO_CLIENT).append(QString(Utils::get_value(Utils::TEMP_ID)));
        //调试信息
        qDebug()<<"Ser:"<<t;
        //发送响应指令
        boolean flag=Ser_sendDat(t);
        //判断操作返回码
        if(flag==Utils::SUCCESS)
        {
            //调试信息
            qDebug()<<"Ser:reply to client ok";
        }
        else
        {
            //调试信息
            qDebug()<<"Ser:reply to client fail";
        }
        //
         //返回解析结果状态
        return Utils::SUCCESS;

    }
    //判断是否为客户端请求湿度数据
    else if(cmd==(Utils::ASK_HUMI_DAT))
    {
        //调试信息
        qDebug()<<"SER:client ask for humi dat";
        ////组合响应 数据请求 指令
        //包括命令头和数据
        QString t=QString(Utils::HUMI_DAT_TO_CLIENT).append(QString(Utils::get_value(Utils::HUMI_ID)));
        //调试信息
        qDebug()<<"Ser:"<<t;
        //发送响应指令
        boolean flag=Ser_sendDat(t);
        //判断操作返回码
        if(flag==Utils::SUCCESS)
        {
            //调试信息
            qDebug()<<"Ser:reply to client ok";
        }
        else
        {
            //调试信息
            qDebug()<<"Ser:reply to client fail";
        }
        //
         //返回解析结果状态
        return Utils::SUCCESS;
    }
    else if(cmd.startsWith(Utils::SET_HUMI_MIN))
    {
        //调试信息：表明信息类型
        //qDebug()<<"set humi min";
        //调试信息：打印信息内容
        //qDebug()<<cmd;
        //调试信息：输出信息长度
        //qDebug()<<cmd.length();
        //调试信息：输出比对命令头长度
        //qDebug()<<Utils::SET_HUMI_MIN.length();

        //另一种获取有效数据索引值的方式
        //获取命令中“：”所在的位置
        //int offset =cmd.indexOf(":");
        //通过整个命令的长度计算出有效数据的长度
        //offset =cmd.length()-offset-1;

         //当前使用的获取有效数据的索引的方式
        int offset =cmd.length()-Utils::SET_HUMI_MIN.length();
        //调试信息：输出有效数据索引值
        // qDebug()<<offset;
        //在此处使用临时变量保存获取到的有效数据
        float value =cmd.right(offset).toFloat();
         //调试信息：输出有效数据的值
        qDebug()<<"SER:the humi set low value is "<<value;
        //
        boolean flag=Utils::update_value_min(Utils::HUMI_ID,QString::number(value));
//        boolean flag=Utils::update_value_min(Utils::HUMI_ID,cmd.right(offset));
        if(flag==Utils::SUCCESS)
        {
            //调试信息
            qDebug()<<"Ser:update humi min ok";
        }
        else
        {
            //调试信息
            qDebug()<<"Ser:update humi min fail";
        }
        //
         //返回解析结果状态
        return Utils::SUCCESS;
    }
    else if(cmd.startsWith(Utils::SET_HUMI_MAX))
    {
        //调试信息：表明信息类型
        //qDebug()<<"set humi max";
        //调试信息：打印信息内容
        //qDebug()<<cmd;
        //调试信息：输出信息长度
        //qDebug()<<cmd.length();
        //调试信息：输出比对命令头长度
        //qDebug()<<Utils::SET_HUMI_MAX.length();

        //另一种获取有效数据索引值的方式
        //获取命令中“：”所在的位置
        //int offset =cmd.indexOf(":");
        //通过整个命令的长度计算出有效数据的长度
        //offset =cmd.length()-offset-1;

         //当前使用的获取有效数据的索引的方式
        int offset =cmd.length()-Utils::SET_HUMI_MAX.length();
        //调试信息：输出有效数据索引值
        // qDebug()<<offset;
        //在此处使用临时变量保存获取到的有效数据
        float value =cmd.right(offset).toFloat();
         //调试信息：输出有效数据的值
        qDebug()<<"SER:the humi set high value is "<<value;
        //

        boolean flag=Utils::update_value_max(Utils::HUMI_ID,QString::number(value));
//        boolean flag=Utils::update_value_max(Utils::HUMI_ID,cmd.right(offset));
        if(flag==Utils::SUCCESS)
        {
            //调试信息
            qDebug()<<"Ser:update humi max ok";
        }
        else
        {
            //调试信息
            qDebug()<<"Ser:update humi max fail";
        }
        //
         //返回解析结果状态
        return Utils::SUCCESS;
    }
    //此处可以添加对其它命令的解析
    else if(cmd.startsWith(Utils::SET_TEMP_MIN))
    {
        //调试信息：表明信息类型
        //qDebug()<<"set temp min ";
        //调试信息：打印信息内容
        //qDebug()<<cmd;
        //调试信息：输出信息长度
        //qDebug()<<cmd.length();
        //调试信息：输出比对命令头长度
        //qDebug()<<Utils::SET_TEMP_MIN.length();

        //另一种获取有效数据索引值的方式
        //获取命令中“：”所在的位置
        //int offset =cmd.indexOf(":");
        //通过整个命令的长度计算出有效数据的长度
        //offset =cmd.length()-offset-1;

         //当前使用的获取有效数据的索引的方式
        int offset =cmd.length()-Utils::SET_TEMP_MIN.length();
        //调试信息：输出有效数据索引值
        // qDebug()<<offset;
        //在此处使用临时变量保存获取到的有效数据
        float value =cmd.right(offset).toFloat();
         //调试信息：输出有效数据的值
        qDebug()<<"SER:the temp set low value is "<<value;
        //
        boolean flag=Utils::update_value_min(Utils::TEMP_ID,QString::number(value));
//        boolean flag=Utils::update_value_min(Utils::TEMP_ID,cmd.right(offset));
        if(flag==Utils::SUCCESS)
        {
            //调试信息
            qDebug()<<"Ser:update temp min ok";
        }
        else
        {
            //调试信息
            qDebug()<<"Ser:update temp min fail";
        }
        //
         //返回解析结果状态
        return Utils::SUCCESS;
    }
    //判断输入命令是否为TEMP相关
    else if(cmd.startsWith(Utils::SET_TEMP_MAX))
    {
        //调试信息：表明信息类型
        //qDebug()<<"set temp max";
        //调试信息：打印信息内容
        //qDebug()<<cmd;
        //调试信息：输出信息长度
        //qDebug()<<cmd.length();
        //调试信息：输出比对命令头长度
        //qDebug()<<Utils::SET_TEMP_MAX.length();

        //另一种获取有效数据索引值的方式
        //获取命令中“：”所在的位置
        //int offset =cmd.indexOf(":");
        //通过整个命令的长度计算出有效数据的长度
        //offset =cmd.length()-offset-1;

        //当前使用的获取有效数据的索引的方式
        int offset =cmd.length()-Utils::SET_TEMP_MAX.length();
        //调试信息：输出有效数据索引值
        // qDebug()<<offset;
        //在此处使用临时变量保存获取到的有效数据
        float value =cmd.right(offset).toFloat();
        //调试信息：输出有效数据的值
        qDebug()<<"SER：the temp set high value is "<<value;
        //
        boolean flag=Utils::update_value_max(Utils::TEMP_ID,QString::number(value));
//        boolean flag=Utils::update_value_max(Utils::TEMP_ID,cmd.right(offset));
        if(flag==Utils::SUCCESS)
        {
            //调试信息
            qDebug()<<"Ser:update temp max ok";
        }
        else
        {
            //调试信息
            qDebug()<<"Ser:update temp max fail";
        }
        //
        //返回解析结果状态
        return Utils::SUCCESS;
    }
    //判断是否为客户端请求打开灯
    else if(cmd==(Utils::OPEN_THE_LIGHT))
    {
        //调试信息
        qDebug()<<"SER:client request open the light";
        //发送响应指令
        emit send_cmd_to_node(Utils::OPEN_THE_LIGHT+"\n");
        //返回解析结果状态
        return Utils::SUCCESS;
    }
    //判断是否为客户端请求关闭灯
    else if(cmd==(Utils::CLOSE_THE_LIGHT))
    {
        //调试信息
        qDebug()<<"SER:client request close the light";
        //发送响应指令
        emit send_cmd_to_node(Utils::CLOSE_THE_LIGHT+"\n");
        //返回解析结果状态
        return Utils::SUCCESS;

    }
    //此处处理对未定义指令进行处理
    else
    {
         //返回解析结果状态
        return Utils::FAIL;
    }
}
//从客户端接收udp数据报的槽函数
void MainWindow::processPendingDatagrams()
{
    while (udpReceiveSocket->hasPendingDatagrams())
    {
        //保存客户端发送的数据报的临时对象
        QByteArray datagram;
        //重新调整接收缓存的大小
        datagram.resize(udpReceiveSocket->pendingDatagramSize());
        //用于存储可能客户端地址的临时变量
        QHostAddress *temp=new QHostAddress("123.123.123.123");
        //接收客户端发送的数据报，同时保存客户端地址
        udpReceiveSocket->readDatagram(datagram.data(), datagram.size(),temp,0);
        //向infopad追加状态信息
        ui->infoPad->append(tr("SER:Received datagram: \"%1\"")
                            .arg(datagram.data()));
        //解析客户端发送的数据报信息
        //判断数据报是否为客户端请求服务器
        if(datagram==Utils::WHO_IS_SERVER)
        {
            //调试信息：输出状态信息
            qDebug()<<"SER:someone need me";
            //如果确实是客户端，则更新客户端地址
            addr=temp;
            //响应客户端的请求
            Ser_sendDatagram(Utils::I_AM_SERVER);
        }
        //调试信息：输出客户端发送的数据
        qDebug()<<"SER:(udp)client msg:"<<datagram.data();
        //调试信息：输出客户端地址
        qDebug()<<"SER:(udp)client addr: "<<addr->toString();
    }
}
//接收串口数据的槽函数
void MainWindow::readSerCom()
{
    //保存串口数据的临时变量
    QByteArray temp;
    char c[30]={0};
    //判断串口缓存数据是否大于20
    //此处是为了保证可以读到至少一条完整的指令或数据
    if(ser_Com->bytesAvailable()>=20)
    {
        //读取串口数据
//        temp=ser_Com->readAll().trimmed();
        ser_Com->readLine(c,30);

        qDebug()<<"i got:"<<c;
        temp=QByteArray(c,30);
        //调试信息：打印收到的数据
        //qDebug()<<"temp:"<<temp;
        //sometimes we need the trim function to make sure we are using the right data
        qDebug()<<QString(temp);
        qDebug()<<QString(temp).trimmed();
        //以下为串口数据解析的过程，解析成功返回SUCCESS，失败返回FAIL
        /*
        if(  ser_serial_data_parser(QString(temp)) == Utils::SUCCESS )
//            if(  ser_serial_data_parser(QString(c)) == Utils::SUCCESS )
        {
            //调试信息
            qDebug()<<"SER:serial parser ok";
        }
        else
        {
            //调试信息
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

//串口数据解析函数
//输入：收到的串口数据
//返回值：解析成功Utils::SUCCESS，解析失败Utils::FAIL
int MainWindow::ser_serial_data_parser(QString msg)
{
    //判断是否传入无效数据
    if(msg=="")
    {
        //调试信息
        qDebug()<<"Ser:empty serial msg!";
        //向infoPad输出状态信息
        ui->infoPad->append("Ser:no serial data");
        //返回值
        return Utils::FAIL;
    }
    //判断数据是否为子节点发来的温度数据
    else if(msg.startsWith(Utils::TEMP_VALUE_FROM_NODE))
    {
        //获取有效数据的索引的方式
        int offset =msg.length()-Utils::TEMP_VALUE_FROM_NODE.length();
        //输出整个数据的长度
        //qDebug()<<"msg length:"<<msg.length();
        //输出比对命令字符串的长度
        //qDebug()<<"len:"<<Utils::TEMP_VALUE_FROM_NODE.length();
        //调试信息：输出有效数据索引值
        //qDebug()<<"off"<<offset;
        //在此处使用临时变量保存获取到的有效数据
        float value =msg.right(offset).toFloat();
        //调试信息：输出有效数据的值
        qDebug()<<"SER:node temp value is "<<value;
        //将数据添加或更新到数据库
        //
        boolean flag=Utils::update_value(Utils::TEMP_ID,QString::number(value));
//        boolean flag=Utils::update_value(Utils::TEMP_ID,msg.right(offset));
        if(flag==Utils::SUCCESS)
        {
            //调试信息
            qDebug()<<"Ser:update temp  ok";
        }
        else
        {
            //调试信息
            qDebug()<<"Ser:update temp  fail";
        }
        //
        return Utils::SUCCESS;
    }
    else if(msg.startsWith(Utils::HUMI_VALUE_FROM_NODE))
//          else if(msg.startsWith("the_humi_value_is:"))
    {
        //当前使用的获取有效数据的索引的方式
        int offset =msg.length()-Utils::HUMI_VALUE_FROM_NODE.length();
        //输出整个数据的长度
//        qDebug()<<"msg length:"<<msg.length();
        //输出比对命令字符串的长度
//        qDebug()<<"len:"<<Utils::HUMI_VALUE_FROM_NODE.length();
        //调试信息：输出有效数据索引值
//        qDebug()<<"off"<<offset;
        //在此处使用临时变量保存获取到的有效数据
        //在此处使用临时变量保存获取到的有效数据
        float value =msg.right(offset).toFloat();
        //调试信息：输出有效数据的值
        qDebug()<<"SER:node humi value is "<<value;
        //将数据添加或更新到数据库
        //
        boolean flag=Utils::update_value(Utils::HUMI_ID,QString::number(value));
//        boolean flag=Utils::update_value(Utils::HUMI_ID,msg.right(offset));
        if(flag==Utils::SUCCESS)
        {
            //调试信息
            qDebug()<<"Ser:update humi ok";
        }
        else
        {
            //调试信息
            qDebug()<<"Ser:update humi fail";
        }
        //
        return Utils::SUCCESS;
    }
    else
    {
        //错误处理
        //调试信息：未识别数据
        qDebug()<<"Ser:undefine serial data";
        qDebug()<<"receive :"<<msg<<" leng:"<<msg.length();
        return Utils::FAIL;
    }
}

    //用于发送udp数据报的函数
    //输入：QString类型的 msg
    //输出：无
void MainWindow::Ser_sendDatagram(QString msg)
{
    //保存消息的临时对象
    QByteArray datagram;
    //判断消息是否为空
    if(msg==NULL)
    {
        //向infopad追加状态信息
        ui->infoPad->append(tr("SER:sorry msg is null"));
    }
    else
    {
        //向infopad追加状态信息
        ui->infoPad->append(tr("SER:Now send datagram "));
        //将消息转储到datagram
        datagram = msg.toAscii();
    }
    //udpSocket->writeDatagram(datagram.data(), datagram.size(),
    //                          QHostAddress::Broadcast, 8903);
    //开始发送数据
    //地址：客户端地址
    //端口：客户端端口
    udpSendSocket->writeDatagram(datagram.data(), datagram.size(),
                             *addr,Utils::CLI_UDP_RCV_PORT );
    //调试信息：输出客户端地址和端口
    qDebug()<<addr->toString()<<":"<<Utils::CLI_UDP_RCV_PORT;

}
//用于发送tcp数据的函数
//输入：QString类型的 msg
//输出： 状态
//为了兼容，输出最好包含一个换行符
int MainWindow::Ser_sendDat(QString dat)
{
    //tcp发送数据，并函数保留返回值
    int ret=tcpSocket->write(QString(dat+"\n").toUtf8());
    //向infoPad追加状态信息
    ui->infoPad->append("Ser:");
    //向infoPad追加状态信息
    ui->infoPad->append("\t"+dat);
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
//代码已经移动到工具类中
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
//用于定时刷新显示数据库数据列表的槽函数
int MainWindow::view_data()
{
    model=new QSqlQueryModel();
    model->setQuery("select * from node_data");
    ui->data_table->resizeColumnsToContents();
    ui->data_table->resizeRowsToContents();
    ui->data_table->setModel(model);
    return Utils::SUCCESS;
}


//自动初始化串口对象
//该处使用了第三方的串口类，因为目前使用的版本（4.8.5）没有官方的串口类
//官方是在5.1版本中才引入了串口类
//该函数实现了串口的自动枚举支持（com1-com30）
/*
微软预定义的标准设备中含有“COM1”-“COM9”。所以，“COM1”-“COM9”作为文件名传递给函数时操作系统会自动地将之解析为相应的设备。
但对于COM10及以上的串口，“COM10”之类的文件名系统只视之为一般意义上的文件，而非串行设备。
为了增加对COM10及以上串行端口的支持，微软规定，如果要访问这样的设备，应使用这样的文件名（以COM10为例）：\\\\.\\COM10
*/
int MainWindow::ser_serial_port_init()
{
    //定义包含串口配置信息的串口配置类对象
    //串口配置信息如下：
    //波特率：9600
    //数据位：8位
    //停止位：1位
    //无校验
    //无流控

    struct  PortSettings  serComSetting  =  {BAUD9600,DATA_8,PAR_NONE,STOP_1,FLOW_OFF,
    500};
    //是否找到串口的标志
    bool flag=false;
    //定义保存串口名称的变量
    QString serial_name;
    //枚举com1-com9，判断是否为目标设备
    for(int i=1;i<10;i++)
    {
        //如果为假，继续判断
        if(flag==false)
        {
            //初始化串口名
            serial_name="com";
            //向串口名追加索引号
            serial_name.append(QString("%1").arg(i));
            //初始化串口对象
            //输入：串口名，串口配置信息，查询模式
//            ser_Com=new Win_QextSerialPort(serial_name,serComSetting,QextSerialBase::EventDriven);
            ser_Com=new Win_QextSerialPort(serial_name,serComSetting,QextSerialBase::Polling);
            //调试信息：输出当前正在测试的串口名
            // qDebug()<<serial_name;
            //尝试打开串口设备
            if(ser_Com->open(QIODevice::ReadWrite))
            {
                //调试信息
                //如果打开设备成功，则打印信息
                qDebug()<<"Ser: find:"<<serial_name;
                //将找到串口设备的标志置true
                flag=true;
                //跳出查找
                break;
            }
        }
    }
    //如果还未找到串口设备，则在更大范围查找
    if(flag==false)
    {
        for(int i=10;i<30;i++)
        {
            //重新初始化串口名
            serial_name="\\\\.\\com";
            //向串口名追加索引号
            serial_name.append(QString("%1").arg(i));
            //初始化串口对象
//            ser_Com=new Win_QextSerialPort(serial_name,serComSetting,QextSerialBase::EventDriven);
             ser_Com=new Win_QextSerialPort(serial_name,serComSetting,QextSerialBase::Polling);
            //调试信息：输出当前正在测试的串口名
            // qDebug()<<serial_name;
            //尝试打开串口对象
            if(ser_Com->open(QIODevice::ReadWrite))
            {
                //调试信息
                //如果打开设备成功，则输出相应信息
                qDebug()<<"Ser: find:"<<serial_name;
                //将找到串口设备的标志置为true
                flag=true;
                //跳出查找
                break;
            }
        }
    }
    //如果打开成功
    if(flag)
    {
        //设置串口超时时间
                //myCom->setTimeout(10);
                /*这里的setTimeout()与定时器的timeout()区别：
                PC机向ARM通过串口发送信息时，会有一个“中间存储器”----即串口缓冲区。
                setTimeout()作用是定时读取数据到缓冲区，而timeout()则是定时读取串口缓冲区内容。
                setTimeout(ms)里面大小参数设置原则：越小越好，不过如果pc机一次性发送的数据比较庞大，应该增大参数大小。
                */
        ser_Com->setTimeout(20);
        //将串口对象的readyRead信号和readSerCom槽函数绑定
        //connect(ser_Com,SIGNAL(readyRead()),this,SLOT(readSerCom()));

        connect(serial_read_fresh_t,SIGNAL(timeout()),this,SLOT(readSerCom()));
        serial_read_fresh_t->start();
        return Utils::SUCCESS;
    }
    //调试代码：
/*
    //初始化串口对象com5
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
    //初始化串口对象com51
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
//获取本机的局域网地址并返回
//输入：无
//返回：IP地址字符串，出错返回空
QString MainWindow::getIP()  //获取ip地址
{
    //获得本机ip地址列表
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    //迭代该列表
    foreach (QHostAddress address, list)
    {
        //调试信息
        //qDebug()<<address.toString();
        //此处使用ip地址是否已“192”开头为判断条件
        //在某些情况下，可能会出错
        if(address.toString().startsWith("192",Qt::CaseInsensitive))
//我们使用IPv4地址
            return address.toString();
    }
    //如果没有符合条件的地址，返回空
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
