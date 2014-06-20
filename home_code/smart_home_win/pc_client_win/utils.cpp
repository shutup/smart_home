#include "utils.h"
//用于udp查找服务器的命令字符串
const  QString Utils::WHO_IS_SERVER="who_is_server";
const  QString Utils::I_AM_SERVER="i_am_server";
const  QString Utils::I_AM_QUIT="i_am_quit";
//用于更新客户端连接状态的字符串
const  QString Utils::HAVE_SERVER="got server";
const  QString Utils::SERVER_CONNECTED="connected";
//用于设置温度阀值的命令字符串
const  QString Utils::SET_TEMP_MIN="set_temp_min_:";
const  QString Utils::SET_TEMP_MAX="set_temp_max_:";
//用于设置湿度阀值的命令字符串
const  QString Utils::SET_HUMI_MIN="set_humi_min_:";
const  QString Utils::SET_HUMI_MAX="set_humi_max_:";
//用于请求温度的命令字符串
const  QString Utils::ASK_TEMP_DAT="give_me_temp";
//用于请求湿度的命令字符串
const  QString Utils::ASK_HUMI_DAT="give_me_humi";
//用于解析服务器发来的数据的命令字符串
const  QString Utils::TEMP_DAT_FROM_SER="temp_data_is:";
//用于解析服务器发来的数据的命令字符串
const  QString Utils::HUMI_DAT_FROM_SER="humi_data_is:";
//局域网广播地址
const  QString Utils::BROADCAST_ADDR="255.255.255.255";
//用于控制子节点执行的命令字符串
//开关灯
const QString Utils::OPEN_THE_LIGHT="open_the_light";
const QString Utils::CLOSE_THE_LIGHT="close_the_light";
//用于控制子节点执行的命令字符串
//开关电扇
const QString Utils::OPEN_THE_FAN="open_the_fan";
const QString Utils::CLOSE_THE_FAN="close_the_fan";
