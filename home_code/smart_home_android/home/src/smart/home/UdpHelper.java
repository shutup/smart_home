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
 * UdpHelper帮助类
 */
public class UdpHelper implements Runnable {
	
	public Boolean IsThreadDisable = false;// 指示监听线程是否终止
	private MulticastLock lock;
	private static InetAddress bc_addr;		//广播地址
	private MyHandler myHandler;				//用于向主线程发消息的handler
	private String  ser_addr=null;				//服务器地址
	//构造函数
	public UdpHelper(WifiManager manager, MyHandler myHandler) {
		this.lock = manager.createMulticastLock("UDPwifiLock");
		this.myHandler = myHandler;
	}
	//开始监听函数
	public void StartListen() {
		//获取锁，使能广播数据接收
		this.lock.acquire();
		// 接收的字节大小，客户端发送的数据不能超过这个大小
		byte[] message = new byte[100];
		try {
			// 建立Socket连接
			DatagramSocket datagramSocket = new DatagramSocket(Utils.LOCAL_REC_UDP_PORT);
			DatagramPacket datagramPacket = new DatagramPacket(message,
					message.length);
			try {
				while (!IsThreadDisable) {
					// 准备接收数据
					Log.d("smartLife", "UDP Client准备接受");
					// this.lock.acquire();
					datagramSocket.receive(datagramPacket);
					String strMsg = new String(datagramPacket.getData()).trim();
					//比较是否是服务器的反馈
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
//udp发送数据函数
	public static void send(String message, InetAddress target_host,
			int target_port) {
		message = (message == null ? "亲，你的消息呢？" : message);
		Log.d(Utils.TAG, "UDP发送数据:" + message);
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
//udp广播发送数据函数
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
//线程run函数
	@Override
	public void run() {
		StartListen();
	}

}