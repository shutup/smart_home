#ifndef UTILS_H
#define UTILS_H
#include <QString>
#include<QSqlQueryModel>
#include<QSqlQuery>
#include<QDebug>
//本类为项目工具类
//在本类中包含有整个项目会用到的一些命令字符串
//以及一些数据库静态方法
class Utils
{
public:
    //用于UDP查找服务器的命令字符串
    const static QString WHO_IS_SERVER;
    const static QString I_AM_SERVER;
    const static QString I_AM_QUIT;
    //用于设置温度最小阀值的命令字符串
    const static QString SET_TEMP_MIN;
    const static QString SET_TEMP_MAX;
    //用于设置温度最大阀值的命令字符串
    const static QString SET_HUMI_MIN;
    const static QString SET_HUMI_MAX;
    //用于客户端请求数据的命令字符串
    const static QString ASK_TEMP_DAT;
    const static QString ASK_HUMI_DAT;
    //用于客户端接收数据的命令字符串
    const static QString TEMP_DAT_TO_CLIENT;
    const static QString HUMI_DAT_TO_CLIENT;
    //用于node节点提交数据的命令字符串
    const static QString TEMP_VALUE_FROM_NODE;
    const static QString HUMI_VALUE_FROM_NODE;
    //用于控制子节点执行的命令字符串
    //开关灯
    const static QString OPEN_THE_LIGHT;
    const static QString CLOSE_THE_LIGHT;
    //用于控制子节点执行的命令字符串
    //开关电扇
    const static QString OPEN_THE_FAN;
    const static QString CLOSE_THE_FAN;
    //对于任务执行状态的描述
    const static int     SUCCESS=0;
    const static int     FAIL=1;
    //服务器UDP监听端口
    const static int     SER_UDP_RCV_PORT=8904;
    //客户端接收使用的端口
    const static int     CLI_UDP_RCV_PORT=8903;
    //数据库名称
    const static QString DATABASE_NAME;
    //传感器节点ID
    const static QString TEMP_ID;
    const static QString HUMI_ID;
    //向数据库添加数据的静态方法
    static int add_data(QString id, QString name, QString type, QString value, QString value_min, QString value_max);
    //向数据库更新数据的静态方法
    //更新数据库 value字段函数
    //输入：节点ID ，QString类型的数据
    //输出：操作状态码
    static int update_value(QString id,QString value);
    //向数据库更新数据的静态方法
    //更新数据库 value_min字段函数
    //输入：节点ID ，QString类型的数据
    //输出：操作状态码
    static int update_value_min(QString id,QString value);
    //向数据库更新数据的静态方法
    //更新数据库 value_max字段函数
    //输入：节点ID ，QString类型的数据
    //输出：操作状态码
    static int update_value_max(QString id,QString value);

    //获取数据库 value字段的值
    //输入：节点ID
    //输出：QString类型的数据
    static QString get_value(QString id);
    //获取数据库 value_min字段的值
    //输入：节点ID
    //输出：QString类型的数据
    static QString get_value_min(QString id);
    //获取数据库 value_max字段的值
    //输入：节点ID
    //输出：QString类型的数据
    static QString get_value_max(QString id);


};

#endif // UTILS_H
