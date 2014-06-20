#ifndef UTILS_H
#define UTILS_H
#include <QString>
//����Ϊ��Ŀ������
//�ڱ����а�����������Ŀ���õ���һЩ�����ַ���
//�Լ�һЩ���ݿ⾲̬����
class Utils
{
public:
    //����udp���ҷ������������ַ���
    const static QString WHO_IS_SERVER;
    const static QString I_AM_SERVER;
    const static QString I_AM_QUIT;
    //���ڸ��¿ͻ�������״̬���ַ���
    const static QString HAVE_SERVER;
    const static QString SERVER_CONNECTED;
    //���������¶ȷ�ֵ�������ַ���
    const static QString SET_TEMP_MIN;
    const static QString SET_TEMP_MAX;
    //��������ʪ�ȷ�ֵ�������ַ���
    const static QString SET_HUMI_MIN;
    const static QString SET_HUMI_MAX;
    //���������¶ȵ������ַ���
    const static QString ASK_TEMP_DAT;
    //��������ʪ�ȵ������ַ���
    const static QString ASK_HUMI_DAT;
    //���ڽ������������������ݵ������ַ���
    const static QString TEMP_DAT_FROM_SER;
    const static QString HUMI_DAT_FROM_SER;

    //���ڿ����ӽڵ�ִ�е������ַ���
    //���ص�
    const static QString OPEN_THE_LIGHT;
    const static QString CLOSE_THE_LIGHT;
    //���ڿ����ӽڵ�ִ�е������ַ���
    //���ص���
    const static QString OPEN_THE_FAN;
    const static QString CLOSE_THE_FAN;

    const static QString BROADCAST_ADDR;
    //��������״̬��
    const static int     SUCCESS=0;
    const static int     FAIL=1;
    //������TCP�����Ķ˿�
    const static int     SER_TCP_PORT=8888;
    //������UDP�����˿�
    const static int     SER_UDP_RCV_PORT=8904;
    //�ͻ��˽���ʹ�õĶ˿�
    const static int     CLI_UDP_RCV_PORT=8903;
};

#endif // UTILS_H
