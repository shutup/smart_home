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
    //�������ݽ�������
    //���룺�յ��Ĵ�������
    //����ֵ�������ɹ�Utils::SUCCESS������ʧ��Utils::FAIL

        //�ж��Ƿ�����Ч����
    while(1)
    {
        while(msg==NULL);
        if(msg=="")
        {
            //������Ϣ
            qDebug()<<"Ser:empty serial msg!";
            //��infoPad���״̬��Ϣ
//            ui->infoPad->append("Ser:no serial data");
            //����ֵ
//            return Utils::FAIL;
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
            bool flag=Utils::update_value(Utils::TEMP_ID,QString::number(value));
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
//            return Utils::SUCCESS;
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
            bool flag=Utils::update_value(Utils::HUMI_ID,QString::number(value));
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
//            return Utils::SUCCESS;
        }
        else
        {
            //������
            //������Ϣ��δʶ������
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
