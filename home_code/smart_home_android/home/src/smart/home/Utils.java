package smart.home;
/*
 * ����Ϊ���򹤾���
 * �������õı���
 */
public class Utils {
	
	//�ͻ������������ѯ���ݵ�ʱ����
	protected static final long WAIT = 500;
	//handler�������Ϣ����
	public static final int SER_IP = 2;
	public static  int ERROR = 1;
	public static  int SUCCESS = 0;
	public static  int TEMP_ID = 100;
	public static  int HUMI_ID=101;
	//����ʹ�õ�tag
	public static String TAG="smartlife";
	//	�ͻ���udp�����˿�
	public static int LOCAL_REC_UDP_PORT=8903;
	//��������udp�����˿�
	public static int SERVER_REC_UDP_PORT=8904;
	//������tcp�����˿�
	public static int SERVER_REC_TCP_PORT=8888;
	//�����Զ����ҷ�������ָ��
	public static String WHO_IS_SERVER="who_is_server";
	public static String I_AM_SERVER="i_am_server";
	//�ͻ��˿����ӽڵ�ʱ���͵�ָ��
	//���ڿ��ص�
	public static String OPEN_THE_LIGHT="open_the_light";
	public static String CLOSE_THE_LIGHT="close_the_light";
	//�ͻ������������ѯ����ʱʹ�õ�ָ��
	//���������ѯ�¶�
	public static String ASK_TEMP_DAT="give_me_temp";
	//���������ѯʪ��
	public static String ASK_HUMI_DAT="give_me_humi";
	//���������ظ��ͻ��˵�ָ��
	//���������ص��¶�����
	public static String TEMP_DAT_FROM_SER="temp_data_is:";
	//���������ص�ʪ������
	public static String HUMI_DAT_FROM_SER="humi_data_is:";
	

}
