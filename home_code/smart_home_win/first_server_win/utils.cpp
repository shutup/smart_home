#include "utils.h"
//����UDP���ҷ������������ַ���
const  QString Utils::WHO_IS_SERVER="who_is_server";
const  QString Utils::I_AM_SERVER="i_am_server";
const  QString Utils::I_AM_QUIT="i_am_quit";
//���������¶���С��ֵ�������ַ���
const  QString Utils::SET_TEMP_MIN="set_temp_min_:";
const  QString Utils::SET_TEMP_MAX="set_temp_max_:";
// ���������¶����ֵ�������ַ���
const  QString Utils::SET_HUMI_MIN="set_humi_min_:";
const  QString Utils::SET_HUMI_MAX="set_humi_max_:";
// ���ڿͻ����������ݵ������ַ���
const  QString Utils::ASK_TEMP_DAT="give_me_temp";
const  QString Utils::ASK_HUMI_DAT="give_me_humi";
// ���ڿͻ��˽������ݵ������ַ���
const  QString Utils::TEMP_DAT_TO_CLIENT="temp_data_is:";
const  QString Utils::HUMI_DAT_TO_CLIENT="humi_data_is:";
// ����node�ڵ��ύ���ݵ������ַ���
const QString Utils::TEMP_VALUE_FROM_NODE="the_temp_value_is:";
const QString Utils::HUMI_VALUE_FROM_NODE="the_humi_value_is:";
//���ڿ����ӽڵ�ִ�е������ַ���
//���ص�
const QString Utils::OPEN_THE_LIGHT="open_the_light";
const QString Utils::CLOSE_THE_LIGHT="close_the_light";
//���ڿ����ӽڵ�ִ�е������ַ���
//���ص���
const QString Utils::OPEN_THE_FAN="open_the_fan";
const QString Utils::CLOSE_THE_FAN="close_the_fan";
// ���ݿ�����
const QString Utils::DATABASE_NAME="smart.db";
//�¶ȴ������ڵ�ID
const QString Utils::TEMP_ID="101";
//ʪ�ȴ������ڵ�ID
const QString Utils::HUMI_ID="102";

//�����ݿ�������ݵľ�̬����
int Utils::add_data(QString id, QString name, QString type, QString value, QString value_min, QString value_max)
{
    //�������ݿ�����ִ�� ����
    QSqlQuery query;
    //����ִ��״̬
    bool flag;
    //ִ�����ݿ�������
    flag=query.exec("INSERT INTO  node_data VALUES('"+id+"','"+name+"','"+type+"','"+value+"','"+value_min+"','"+value_max+"')");
    if(flag){
        //����ִ��״̬
        return Utils::SUCCESS;
    }
    else{
        //����ִ��״̬
        return Utils::FAIL;
    }
}
//�������ݿ� value�ֶκ���
//���룺�ڵ�ID ��QString���͵�����
//���������״̬��
int Utils::update_value(QString id, QString value)
{
    //�������ݿ�����ִ�� ����
    QSqlQuery query;
    //����ִ��״̬
    bool flag;
    //ִ�����ݿ���²���
    flag=query.exec("update node_data set node_value = '"+value+"'where node_id='"+id+"'");
    if(flag){
        //����ִ��״̬
        return Utils::SUCCESS;
    }
    else{
        //����ִ��״̬
        return Utils::FAIL;
    }
}
//�������ݿ� value_min�ֶκ���
//���룺�ڵ�ID ��QString���͵�����
//���������״̬��
int Utils::update_value_min(QString id, QString value)
{
    //�������ݿ�����ִ�� ����
    QSqlQuery query;
    bool flag;
    //ִ�����ݿ���²���
    flag=query.exec("update node_data set node_value_min = '"+value+"'where node_id='"+id+"'");
    if(flag){
        //����ִ��״̬
        return Utils::SUCCESS;
    }
    else{
        //����ִ��״̬
        return Utils::FAIL;
    }
}
//�������ݿ� value_max�ֶκ���
//���룺�ڵ�ID ��QString���͵�����
//���������״̬��
int Utils::update_value_max(QString id, QString value)
{
    //�������ݿ�����ִ�� ����
    QSqlQuery query;
    bool flag;
    //ִ�����ݿ���²���
    flag=query.exec("update node_data set node_value_max = '"+value+"'where node_id='"+id+"'");
    if(flag){
        //����ִ��״̬
        return Utils::SUCCESS;
    }
    else{
        //����ִ��״̬
        return Utils::FAIL;
    }
}
//��ȡ���ݿ� value�ֶε�ֵ
//���룺�ڵ�ID
//�����QString���͵�����
QString Utils::get_value(QString id)
{
    //�������ݿ�����ִ�� ����
    QSqlQuery query;
    // ���淵�ؽ������ʱ����
    QString value=NULL;
    //ִ�����ݿ��ѯ����
    query.exec("select node_value from node_data where node_id= '"+id+"'");
    //ʹ�����ָ���һ����¼
    query.next();
    //ȡ�����������Ҫ������
    value=query.value(0).toString();
    //������Ϣ
    qDebug()<<"Ser: i got :"<<value;
    //�����ؽ����Ϊ�գ��򷵻�
    if(value !=NULL){
        return value;
    }
    else{
        return NULL;
    }
}
//��ȡ���ݿ� value_min�ֶε�ֵ
//���룺�ڵ�ID
//�����QString���͵�����
QString Utils::get_value_min(QString id)
{
    //�������ݿ�����ִ�� ����
    QSqlQuery query;
    // ���淵�ؽ������ʱ����
    QString value;
    //ִ�����ݿ��ѯ����
    query.exec("select node_value_min from node_data where node_id= '"+id+"'");
    //ʹ�����ָ���һ����¼
    query.next();
    //ȡ�����������Ҫ������
    value=query.value(0).toString();
    //������Ϣ
    qDebug()<<"Ser: i got :"<<value;
     //�����ؽ����Ϊ�գ��򷵻�
    if(value !=NULL){
        return value;
    }
    else{
        return NULL;
    }
}
//��ȡ���ݿ� value_max�ֶε�ֵ
//���룺�ڵ�ID
//�����QString���͵�����
QString Utils::get_value_max(QString id)
{
    //�������ݿ�����ִ�� ����
    QSqlQuery query;
    // ���淵�ؽ������ʱ����
    QString value;
    //ִ�����ݿ��ѯ����
    query.exec("select node_value_max from node_data where node_id= '"+id+"'");
    //ʹ�����ָ���һ����¼
    query.next();
    //ȡ�����������Ҫ������
    value=query.value(0).toString();
    qDebug()<<"Ser: i got :"<<value;
     //�����ؽ����Ϊ�գ��򷵻�
    if(value !=NULL){
        return value;
    }
    else{
        return NULL;
    }
}
