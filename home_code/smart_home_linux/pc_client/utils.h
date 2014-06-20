#ifndef UTILS_H
#define UTILS_H
#include <QString>
//本类为项目工具类
//在本类中包含有整个项目会用到的一些命令字符串
//以及一些数据库静态方法
class Utils
{
public:
    //用于udp查找服务器的命令字符串
    const static QString WHO_IS_SERVER;
    const static QString I_AM_SERVER;
    const static QString I_AM_QUIT;
    //用于更新客户端连接状态的字符串
    const static QString HAVE_SERVER;
    const static QString SERVER_CONNECTED;
    //用于设置温度阀值的命令字符串
    const static QString SET_TEMP_MIN;
    const static QString SET_TEMP_MAX;
    //用于设置湿度阀值的命令字符串
    const static QString SET_HUMI_MIN;
    const static QString SET_HUMI_MAX;
    //用于请求温度的命令字符串
    const static QString ASK_TEMP_DAT;
    //用于请求湿度的命令字符串
    const static QString ASK_HUMI_DAT;
    //用于解析服务器发来的数据的命令字符串
    const static QString TEMP_DAT_FROM_SER;
    const static QString HUMI_DAT_FROM_SER;
    //用于控制子节点执行的命令字符串
    //开关灯
    const static QString OPEN_THE_LIGHT;
    const static QString CLOSE_THE_LIGHT;
    //用于控制子节点执行的命令字符串
    //开关电扇
    const static QString OPEN_THE_FAN;
    const static QString CLOSE_THE_FAN;

    const static QString BROADCAST_ADDR;
    //操作返回状态码
    const static int     SUCCESS=0;
    const static int     FAIL=1;
    //服务器TCP监听的端口
    const static int     SER_TCP_PORT=8888;
    //服务器UDP监听端口
    const static int     SER_UDP_RCV_PORT=8904;
    //客户端接收使用的端口
    const static int     CLI_UDP_RCV_PORT=8903;
};

#endif // UTILS_H
