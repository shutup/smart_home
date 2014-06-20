package smart.home;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.UnknownHostException;

import smart.home.SmartHomeActivity.MyHandler;
import android.net.wifi.WifiManager;
import android.net.wifi.WifiManager.MulticastLock;
import android.os.Message;
import android.util.Log;

/**
 * UdpHelper������
 */
public class UdpHelper implements Runnable {
	
	public Boolean IsThreadDisable = false;// ָʾ�����߳��Ƿ���ֹ
	private MulticastLock lock;
	private static InetAddress bc_addr;		//�㲥��ַ
	private MyHandler myHandler;				//���������̷߳���Ϣ��handler
	private String  ser_addr=null;				//��������ַ
	//���캯��
	public UdpHelper(WifiManager manager, MyHandler myHandler) {
		this.lock = manager.createMulticastLock("UDPwifiLock");
		this.myHandler = myHandler;
	}
	//��ʼ��������
	public void StartListen() {
		//��ȡ����ʹ�ܹ㲥���ݽ���
		this.lock.acquire();
		// ���յ��ֽڴ�С���ͻ��˷��͵����ݲ��ܳ��������С
		byte[] message = new byte[100];
		try {
			// ����Socket����
			DatagramSocket datagramSocket = new DatagramSocket(Utils.LOCAL_REC_UDP_PORT);
			DatagramPacket datagramPacket = new DatagramPacket(message,
					message.length);
			try {
				while (!IsThreadDisable) {
					// ׼����������
					Log.d("smartLife", "UDP Client׼������");
					// this.lock.acquire();
					datagramSocket.receive(datagramPacket);
					String strMsg = new String(datagramPacket.getData()).trim();
					//�Ƚ��Ƿ��Ƿ������ķ���
					if(strMsg.equalsIgnoreCase(Utils.I_AM_SERVER))
					{
						Log.d(Utils.TAG, "found server");
						ser_addr=datagramPacket.getAddress().getHostAddress();
						if(ser_addr==null)
						{
							Log.d(Utils.TAG, "are you kidding me ?");
						}
						Log.d(Utils.TAG, ser_addr);
					}
					Message msg = myHandler.obtainMessage();
					msg.what = Utils.SER_IP;
					msg.obj=ser_addr;
					myHandler.sendMessage(msg);
					Log.d(Utils.TAG, datagramPacket.getAddress().getHostAddress()
							.toString()
							+ ":" + strMsg);
					// this.lock.release();
				}
				Log.d(Utils.TAG,"client :udp listen is over");
			} catch (IOException e) {// IOException
				e.printStackTrace();
			}
		} catch (SocketException e) {
			e.printStackTrace();
		}

	}
//udp�������ݺ���
	public static void send(String message, InetAddress target_host,
			int target_port) {
		message = (message == null ? "�ף������Ϣ�أ�" : message);
		Log.d(Utils.TAG, "UDP��������:" + message);
		DatagramSocket s = null;
		try {
			s = new DatagramSocket();
			s.setBroadcast(true);
			} catch (SocketException e) {
			e.printStackTrace();
		}
		int msg_length = message.length();
		byte[] messageByte = message.getBytes();
		DatagramPacket p = new DatagramPacket(messageByte, msg_length,
				target_host, target_port);
		try {
			s.send(p);
			s.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
//udp�㲥�������ݺ���
	public static void broadcast_send(String message, int target_port)
	{
		try {
			bc_addr = InetAddress.getByName("255.255.255.255");
		} catch (UnknownHostException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		send(message, bc_addr, target_port);
	}
//�߳�run����
	@Override
	public void run() {
		StartListen();
	}

}