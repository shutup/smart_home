package smart.home;
/*
 * 本类为程序工具类
 * 包括常用的变量
 */
public class Utils {
	
	//客户端向服务器查询数据的时间间隔
	protected static final long WAIT = 500;
	//handler处理的消息类型
	public static final int SER_IP = 2;
	public static  int ERROR = 1;
	public static  int SUCCESS = 0;
	public static  int TEMP_ID = 100;
	public static  int HUMI_ID=101;
	//调试使用的tag
	public static String TAG="smartlife";
	//	客户端udp监听端口
	public static int LOCAL_REC_UDP_PORT=8903;
	//服务器端udp监听端口
	public static int SERVER_REC_UDP_PORT=8904;
	//服务器tcp监听端口
	public static int SERVER_REC_TCP_PORT=8888;
	//用于自动查找服务器的指令
	public static String WHO_IS_SERVER="who_is_server";
	public static String I_AM_SERVER="i_am_server";
	//客户端控制子节点时发送的指令
	//关于开关灯
	public static String OPEN_THE_LIGHT="open_the_light";
	public static String CLOSE_THE_LIGHT="close_the_light";
	//客户端向服务器查询数据时使用的指令
	//向服务器查询温度
	public static String ASK_TEMP_DAT="give_me_temp";
	//向服务器查询湿度
	public static String ASK_HUMI_DAT="give_me_humi";
	//服务器返回给客户端的指令
	//服务器返回的温度数据
	public static String TEMP_DAT_FROM_SER="temp_data_is:";
	//服务器返回的湿度数据
	public static String HUMI_DAT_FROM_SER="humi_data_is:";
	

}
