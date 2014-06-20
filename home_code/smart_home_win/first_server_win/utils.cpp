#include "utils.h"
//用于UDP查找服务器的命令字符串
const  QString Utils::WHO_IS_SERVER="who_is_server";
const  QString Utils::I_AM_SERVER="i_am_server";
const  QString Utils::I_AM_QUIT="i_am_quit";
//用于设置温度最小阀值的命令字符串
const  QString Utils::SET_TEMP_MIN="set_temp_min_:";
const  QString Utils::SET_TEMP_MAX="set_temp_max_:";
// 用于设置温度最大阀值的命令字符串
const  QString Utils::SET_HUMI_MIN="set_humi_min_:";
const  QString Utils::SET_HUMI_MAX="set_humi_max_:";
// 用于客户端请求数据的命令字符串
const  QString Utils::ASK_TEMP_DAT="give_me_temp";
const  QString Utils::ASK_HUMI_DAT="give_me_humi";
// 用于客户端接收数据的命令字符串
const  QString Utils::TEMP_DAT_TO_CLIENT="temp_data_is:";
const  QString Utils::HUMI_DAT_TO_CLIENT="humi_data_is:";
// 用于node节点提交数据的命令字符串
const QString Utils::TEMP_VALUE_FROM_NODE="the_temp_value_is:";
const QString Utils::HUMI_VALUE_FROM_NODE="the_humi_value_is:";
//用于控制子节点执行的命令字符串
//开关灯
const QString Utils::OPEN_THE_LIGHT="open_the_light";
const QString Utils::CLOSE_THE_LIGHT="close_the_light";
//用于控制子节点执行的命令字符串
//开关电扇
const QString Utils::OPEN_THE_FAN="open_the_fan";
const QString Utils::CLOSE_THE_FAN="close_the_fan";
// 数据库名称
const QString Utils::DATABASE_NAME="smart.db";
//温度传感器节点ID
const QString Utils::TEMP_ID="101";
//湿度传感器节点ID
const QString Utils::HUMI_ID="102";

//向数据库添加数据的静态方法
int Utils::add_data(QString id, QString name, QString type, QString value, QString value_min, QString value_max)
{
    //创建数据库命令执行 对象
    QSqlQuery query;
    //保存执行状态
    bool flag;
    //执行数据库插入语句
    flag=query.exec("INSERT INTO  node_data VALUES('"+id+"','"+name+"','"+type+"','"+value+"','"+value_min+"','"+value_max+"')");
    if(flag){
        //返回执行状态
        return Utils::SUCCESS;
    }
    else{
        //返回执行状态
        return Utils::FAIL;
    }
}
//更新数据库 value字段函数
//输入：节点ID ，QString类型的数据
//输出：操作状态码
int Utils::update_value(QString id, QString value)
{
    //创建数据库命令执行 对象
    QSqlQuery query;
    //保存执行状态
    bool flag;
    //执行数据库更新操作
    flag=query.exec("update node_data set node_value = '"+value+"'where node_id='"+id+"'");
    if(flag){
        //返回执行状态
        return Utils::SUCCESS;
    }
    else{
        //返回执行状态
        return Utils::FAIL;
    }
}
//更新数据库 value_min字段函数
//输入：节点ID ，QString类型的数据
//输出：操作状态码
int Utils::update_value_min(QString id, QString value)
{
    //创建数据库命令执行 对象
    QSqlQuery query;
    bool flag;
    //执行数据库更新操作
    flag=query.exec("update node_data set node_value_min = '"+value+"'where node_id='"+id+"'");
    if(flag){
        //返回执行状态
        return Utils::SUCCESS;
    }
    else{
        //返回执行状态
        return Utils::FAIL;
    }
}
//更新数据库 value_max字段函数
//输入：节点ID ，QString类型的数据
//输出：操作状态码
int Utils::update_value_max(QString id, QString value)
{
    //创建数据库命令执行 对象
    QSqlQuery query;
    bool flag;
    //执行数据库更新操作
    flag=query.exec("update node_data set node_value_max = '"+value+"'where node_id='"+id+"'");
    if(flag){
        //返回执行状态
        return Utils::SUCCESS;
    }
    else{
        //返回执行状态
        return Utils::FAIL;
    }
}
//获取数据库 value字段的值
//输入：节点ID
//输出：QString类型的数据
QString Utils::get_value(QString id)
{
    //创建数据库命令执行 对象
    QSqlQuery query;
    // 保存返回结果的临时对象
    QString value=NULL;
    //执行数据库查询操作
    query.exec("select node_value from node_data where node_id= '"+id+"'");
    //使结果集指向第一个记录
    query.next();
    //取出结果集中需要的数据
    value=query.value(0).toString();
    //调试信息
    qDebug()<<"Ser: i got :"<<value;
    //若返回结果不为空，则返回
    if(value !=NULL){
        return value;
    }
    else{
        return NULL;
    }
}
//获取数据库 value_min字段的值
//输入：节点ID
//输出：QString类型的数据
QString Utils::get_value_min(QString id)
{
    //创建数据库命令执行 对象
    QSqlQuery query;
    // 保存返回结果的临时对象
    QString value;
    //执行数据库查询操作
    query.exec("select node_value_min from node_data where node_id= '"+id+"'");
    //使结果集指向第一个记录
    query.next();
    //取出结果集中需要的数据
    value=query.value(0).toString();
    //调试信息
    qDebug()<<"Ser: i got :"<<value;
     //若返回结果不为空，则返回
    if(value !=NULL){
        return value;
    }
    else{
        return NULL;
    }
}
//获取数据库 value_max字段的值
//输入：节点ID
//输出：QString类型的数据
QString Utils::get_value_max(QString id)
{
    //创建数据库命令执行 对象
    QSqlQuery query;
    // 保存返回结果的临时对象
    QString value;
    //执行数据库查询操作
    query.exec("select node_value_max from node_data where node_id= '"+id+"'");
    //使结果集指向第一个记录
    query.next();
    //取出结果集中需要的数据
    value=query.value(0).toString();
    qDebug()<<"Ser: i got :"<<value;
     //若返回结果不为空，则返回
    if(value !=NULL){
        return value;
    }
    else{
        return NULL;
    }
}
