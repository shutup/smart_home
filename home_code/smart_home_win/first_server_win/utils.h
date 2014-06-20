#ifndef UTILS_H
#define UTILS_H
#include <QString>
#include<QSqlQueryModel>
#include<QSqlQuery>
#include<QDebug>
//����Ϊ��Ŀ������
//�ڱ����а�����������Ŀ���õ���һЩ�����ַ���
//�Լ�һЩ���ݿ⾲̬����
class Utils
{
public:
    //����UDP���ҷ������������ַ���
    const static QString WHO_IS_SERVER;
    const static QString I_AM_SERVER;
    const static QString I_AM_QUIT;
    //���������¶���С��ֵ�������ַ���
    const static QString SET_TEMP_MIN;
    const static QString SET_TEMP_MAX;
    //���������¶����ֵ�������ַ���
    const static QString SET_HUMI_MIN;
    const static QString SET_HUMI_MAX;
    //���ڿͻ����������ݵ������ַ���
    const static QString ASK_TEMP_DAT;
    const static QString ASK_HUMI_DAT;
    //���ڿͻ��˽������ݵ������ַ���
    const static QString TEMP_DAT_TO_CLIENT;
    const static QString HUMI_DAT_TO_CLIENT;
    //����node�ڵ��ύ���ݵ������ַ���
    const static QString TEMP_VALUE_FROM_NODE;
    const static QString HUMI_VALUE_FROM_NODE;
    //���ڿ����ӽڵ�ִ�е������ַ���
    //���ص�
    const static QString OPEN_THE_LIGHT;
    const static QString CLOSE_THE_LIGHT;
    //���ڿ����ӽڵ�ִ�е������ַ���
    //���ص���
    const static QString OPEN_THE_FAN;
    const static QString CLOSE_THE_FAN;
    //��������ִ��״̬������
    const static int     SUCCESS=0;
    const static int     FAIL=1;
    //������UDP�����˿�
    const static int     SER_UDP_RCV_PORT=8904;
    //�ͻ��˽���ʹ�õĶ˿�
    const static int     CLI_UDP_RCV_PORT=8903;
    //���ݿ�����
    const static QString DATABASE_NAME;
    //�������ڵ�ID
    const static QString TEMP_ID;
    const static QString HUMI_ID;
    //�����ݿ�������ݵľ�̬����
    static int add_data(QString id, QString name, QString type, QString value, QString value_min, QString value_max);
    //�����ݿ�������ݵľ�̬����
    //�������ݿ� value�ֶκ���
    //���룺�ڵ�ID ��QString���͵�����
    //���������״̬��
    static int update_value(QString id,QString value);
    //�����ݿ�������ݵľ�̬����
    //�������ݿ� value_min�ֶκ���
    //���룺�ڵ�ID ��QString���͵�����
    //���������״̬��
    static int update_value_min(QString id,QString value);
    //�����ݿ�������ݵľ�̬����
    //�������ݿ� value_max�ֶκ���
    //���룺�ڵ�ID ��QString���͵�����
    //���������״̬��
    static int update_value_max(QString id,QString value);

    //��ȡ���ݿ� value�ֶε�ֵ
    //���룺�ڵ�ID
    //�����QString���͵�����
    static QString get_value(QString id);
    //��ȡ���ݿ� value_min�ֶε�ֵ
    //���룺�ڵ�ID
    //�����QString���͵�����
    static QString get_value_min(QString id);
    //��ȡ���ݿ� value_max�ֶε�ֵ
    //���룺�ڵ�ID
    //�����QString���͵�����
    static QString get_value_max(QString id);


};

#endif // UTILS_H
