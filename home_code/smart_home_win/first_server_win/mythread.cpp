#include "mythread.h"

//MyThread::MyThread(QObject *parent) :
//    QThread(parent)
//{
//}
MyThread::MyThread()
{
    msg="";
}

void MyThread::run()
{
//    while(1)
//    {
//        qDebug()<<currentThreadId();
//        sleep(1);
//    }
    //串口数据解析函数
    //输入：收到的串口数据
    //返回值：解析成功Utils::SUCCESS，解析失败Utils::FAIL

        //判断是否传入无效数据
    while(1)
    {
        while(msg==NULL);
        if(msg=="")
        {
            //调试信息
            qDebug()<<"Ser:empty serial msg!";
            //向infoPad输出状态信息
//            ui->infoPad->append("Ser:no serial data");
            //返回值
//            return Utils::FAIL;
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
            bool flag=Utils::update_value(Utils::TEMP_ID,QString::number(value));
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
//            return Utils::SUCCESS;
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
            bool flag=Utils::update_value(Utils::HUMI_ID,QString::number(value));
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
//            return Utils::SUCCESS;
        }
        else
        {
            //错误处理
            //调试信息：未识别数据
            qDebug()<<"Ser:undefine serial data";
            qDebug()<<"receive :"<<msg<<" leng:"<<msg.length();
//            return Utils::FAIL;
        }
        msg="";
    }
}

void MyThread::setData(QString msg)
{
    this->msg="";
    this->msg=msg;
}
