package smart.home;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

import android.app.Activity;
import android.content.Context;
import android.net.wifi.WifiManager;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.os.StrictMode;
import android.text.method.ScrollingMovementMethod;
import android.util.Log;
import android.view.View;
import android.view.ViewTreeObserver;
import android.view.Window;
import android.view.WindowManager;
import android.view.View.OnClickListener;
import android.view.ViewTreeObserver.OnPreDrawListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

public class SmartHomeActivity extends Activity {
	/** Called when the activity is first created. */
	// manual setup object
	//用于手动配置的对象
	private Button startButton;
	private EditText IPText;
	private Button sendButtonClient;
	private EditText editMsgTextCilent;
	// auto setup object
	//用于自动配置的对象
	private Button searchButton;
	private Button openLightButton;
	private Button closeLightButton;
	//the view to show curve
	private MyCurveView curve_temp;
	//the view to show curve
	private MyCurveView curve_humi;
	private boolean   hasMeasured_t= false;
	private boolean   hasMeasured_h = false;
	// display temp value
	//用于显示温度的文本框
	private TextView tempText;
	// display humi value
	//用于显示湿度的文本框
	private TextView humiText;
	
	// display all message
	//用于显示调试信息的文本框
	private TextView recvText;

	// udp助手对象
	UdpHelper udphelper;
	//上下文对象
	private Context mContext;
	//当前是否处于连接状态的标志
	private boolean isConnecting = false;
	//客户端tcp接收线程
	private Thread mThreadClientTcpRecv = null;
	//客户端tcp向服务器查询线程
	private Thread mThreadClientQuery=null;
	//客户端同服务器通信的套接字
	private Socket mSocketClient = null;
	//经过封装的输入输出流
	static BufferedReader mBufferedReaderClient = null;
	static PrintWriter mPrintWriterClient = null;
	//用于保存接收字符串的变量
	private String recvMessageClient = "";
	//当activity建立时调用的回调函数
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		//对程序主题风格进行设置
		requestWindowFeature(Window.FEATURE_NO_TITLE);// 设置无标题
		getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
				WindowManager.LayoutParams.FLAG_FULLSCREEN);// 设置全屏模式
		getWindow().setFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON,// 设置不锁屏
				WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
		//设置布局
		setContentView(R.layout.main);
		mContext = this;
		//设置程序网络相关的策略
		StrictMode.setThreadPolicy(new StrictMode.ThreadPolicy.Builder()
				.detectDiskReads().detectDiskWrites().detectNetwork() // or
																		// .detectAll()
																		// for
																		// all
																		// detectable
																		// problems
				.penaltyLog().build());
		StrictMode.setVmPolicy(new StrictMode.VmPolicy.Builder()
				.detectLeakedSqlLiteObjects().penaltyLog().penaltyDeath()
				.build());
		// thread use this handler to send msg to main thread
		//子线程使用handler向主线程发送消息
		MyHandler handler = new MyHandler(Looper.getMainLooper());
		// get the wifimanager object
		//声明wifimanager对象
		WifiManager manager = (WifiManager) this
				.getSystemService(Context.WIFI_SERVICE);
		// udp Helper Class
		udphelper = new UdpHelper(manager, handler);
		// IP地址编辑框
		IPText = (EditText) findViewById(R.id.IPText);
		// IPText.setText("10.0.2.15:");
		IPText.setText("172.168.1.103:8888");
		// 客户端创建连接按钮
		startButton = (Button) findViewById(R.id.StartConnect);
		startButton.setOnClickListener(StartClickListener);
		// 客户端编辑框
		editMsgTextCilent = (EditText) findViewById(R.id.clientMessageText);
		editMsgTextCilent.setText("give_me_temp");
		// 客户端发送消息按钮
		sendButtonClient = (Button) findViewById(R.id.SendButtonClient);
		sendButtonClient.setOnClickListener(SendClickListenerClient);
		// search server btn
		//查找服务器按钮
		searchButton = (Button) findViewById(R.id.searchServer);
		searchButton.setOnClickListener(searchClickListener);
		// open the light btn
		//开灯按钮
		openLightButton = (Button) findViewById(R.id.openLight);
		openLightButton.setOnClickListener(openLightClickListener);
		openLightButton.setEnabled(false);
		// close the light btn
		//关灯按钮
		closeLightButton = (Button) findViewById(R.id.closeLight);
		closeLightButton.setOnClickListener(closeLightClickListener);
		closeLightButton.setEnabled(false);
		//显示曲线的控件
		curve_temp=(smart.home.MyCurveView) findViewById(R.id.curve_temp);
		curve_humi=(smart.home.MyCurveView) findViewById(R.id.curve_humi);
	//	curve_temp.setWidthHeight(curve_temp.getWidth(), curve_temp.getHeight());
	//	curve_humi.setWidthHeight(curve_humi.getWidth(), curve_humi.getHeight());
		ViewTreeObserver vto2_t = curve_temp.getViewTreeObserver();
        vto2_t.addOnPreDrawListener(new OnPreDrawListener()
        {

            @Override
            public boolean onPreDraw()
            {
                if (hasMeasured_t == false)
                {
                	curve_temp.setWidthHeight(curve_temp.getWidth(), curve_temp.getHeight());
                    Log.d("test", "k:"+curve_temp.getWidth()+" h: "+curve_temp.getHeight());
                  
                    hasMeasured_t = true;
                }
                return true;
            }
        });
        ViewTreeObserver vto2_h = curve_humi.getViewTreeObserver();
        vto2_h.addOnPreDrawListener(new OnPreDrawListener()
        {

            @Override
            public boolean onPreDraw()
            {
                if (hasMeasured_h == false)
                {
                	curve_humi.setWidthHeight(curve_humi.getWidth(), curve_humi.getHeight());
                    Log.d("test", "k:"+curve_humi.getWidth()+" h: "+curve_humi.getHeight());
                  
                    hasMeasured_h= true;
                }
                return true;
            }
        });
		//获取显示温度的文本
		tempText = (TextView) findViewById(R.id.temp_textView);
		//获取显示湿度的文本
		humiText = (TextView) findViewById(R.id.humi_textView);
		// 显示消息文本框
		recvText = (TextView) findViewById(R.id.RecvText);
		recvText.setMovementMethod(ScrollingMovementMethod.getInstance());
		
		// udp listen thread
		//开启udp监听线程
		Thread udpReceived = new Thread(udphelper);
		udpReceived.start();
	}

	// the click callback function of startBtn
	private OnClickListener StartClickListener = new OnClickListener() {
		@Override
		public void onClick(View arg0) {

			if (isConnecting) {
				isConnecting = false;
				try {
					if (mSocketClient != null) {
						mSocketClient.close();
						mSocketClient = null;

						mPrintWriterClient.close();
						mPrintWriterClient = null;
					}
				} catch (IOException e) {

					e.printStackTrace();
				}
				// mThreadClient.interrupt();
				searchButton.setEnabled(true);
				startButton.setText("开始连接");
				openLightButton.setEnabled(false);
				closeLightButton.setEnabled(false);
				IPText.setEnabled(true);
				recvText.setText("信息:\n");
			} else {
				isConnecting = true;
				startButton.setText("停止连接");
				IPText.setEnabled(false);

				String msgText = IPText.getText().toString();
				if (msgText.length() <= 0) {
					// Toast.makeText(mContext, "IP不能为空！",
					// Toast.LENGTH_SHORT).show();
					recvMessageClient = "IP不能为空！\n";// 消息换行
					Message msg = new Message();
					msg.what = Utils.ERROR;
					mHandler.sendMessage(msg);
					return;
				}
				int start = msgText.indexOf(":");
				if ((start == -1) || (start + 1 >= msgText.length())) {
					recvMessageClient = "IP地址不合法\n";// 消息换行
					Message msg = new Message();
					msg.what = Utils.ERROR;
					mHandler.sendMessage(msg);
					return;
				}
				String sIP = msgText.substring(0, start);
				String sPort = msgText.substring(start + 1);
				int port = Integer.parseInt(sPort);

				Log.d(Utils.TAG, "try connect  to IP:" + sIP + ":" + port);

				try {
					// 连接服务器
					mSocketClient = new Socket(sIP, port); // portnum
					// 取得输入、输出流
					mBufferedReaderClient = new BufferedReader(
							new InputStreamReader(
									mSocketClient.getInputStream()));

					mPrintWriterClient = new PrintWriter(
							mSocketClient.getOutputStream(), true);

					recvMessageClient = "已经连接server!\n";// 消息换行
					Message msg = new Message();
					msg.what = Utils.SUCCESS;
					mHandler.sendMessage(msg);
					//
					searchButton.setEnabled(false);
					// break;
				} catch (Exception e) {
					recvMessageClient = "连接IP异常:" + e.toString()
							+ e.getMessage() + "\n";// 消息换行
					Message msg = new Message();
					msg.what = Utils.ERROR;
					mHandler.sendMessage(msg);
					return;
				}

				mThreadClientTcpRecv = new Thread(mRunnable);
				mThreadClientTcpRecv.start();
				mThreadClientQuery =new Thread(queryRunnable);
				mThreadClientQuery.start();
				openLightButton.setEnabled(true);
				closeLightButton.setEnabled(true);
			}
		}
	};
	// the click callback function of sendBtn
	private OnClickListener SendClickListenerClient = new OnClickListener() {
		@Override
		public void onClick(View arg0) {

			if (isConnecting && mSocketClient != null) {
				String msgText = editMsgTextCilent.getText().toString();// 取得编辑框中我们输入的内容
				if (msgText.length() <= 0) {
					Toast.makeText(mContext, "发送内容不能为空！", Toast.LENGTH_SHORT)
							.show();
				} else {
					try {
						mPrintWriterClient.println(msgText);// 发送给服务器
//						mPrintWriterClient.flush();
					} catch (Exception e) {

						Toast.makeText(mContext, "发送异常：" + e.getMessage(),
								Toast.LENGTH_SHORT).show();
					}
				}
			} else {
				Toast.makeText(mContext, "没有连接", Toast.LENGTH_SHORT).show();
			}
		}
	};

	private OnClickListener searchClickListener = new OnClickListener() {

		@Override
		public void onClick(View v) {

			UdpHelper.broadcast_send(Utils.WHO_IS_SERVER,
					Utils.SERVER_REC_UDP_PORT);
			Toast.makeText(mContext, "开始查找...", Toast.LENGTH_SHORT).show();
		}
	};
	//开灯按钮点击后的监听器回调函数
	private OnClickListener openLightClickListener = new OnClickListener() {

		@Override
		public void onClick(View v) {

			if (isConnecting && mSocketClient != null) {

				try {
					mPrintWriterClient.println(Utils.OPEN_THE_LIGHT);// 发送给服务器
					Toast.makeText(mContext, "开灯指令发送", Toast.LENGTH_SHORT)
							.show();
//					mPrintWriterClient.flush();
				} catch (Exception e) {

					Toast.makeText(mContext, "发送异常：" + e.getMessage(),
							Toast.LENGTH_SHORT).show();
				}

			} else {
				Toast.makeText(mContext, "没有连接", Toast.LENGTH_SHORT).show();
			}

		}
	};
	//关灯按钮点击后的监听器回调函数
	private OnClickListener closeLightClickListener = new OnClickListener() {

		@Override
		public void onClick(View v) {

			if (isConnecting && mSocketClient != null) {

				try {
					mPrintWriterClient.println(Utils.CLOSE_THE_LIGHT);
//					mPrintWriterClient.print(Utils.CLOSE_THE_LIGHT);// 发送给服务器
//					mPrintWriterClient.flush();
					Toast.makeText(mContext, "关灯指令发送", Toast.LENGTH_SHORT)
							.show();
				} catch (Exception e) {

					Toast.makeText(mContext, "发送异常：" + e.getMessage(),
							Toast.LENGTH_SHORT).show();
				}

			} else {
				Toast.makeText(mContext, "没有连接", Toast.LENGTH_SHORT).show();
			}
		}
	};
	// 线程:监听服务器发来的消息
	private Runnable mRunnable = new Runnable() {
		public void run() {
			while (isConnecting) {
//				if(mSocketClient.isInputShutdown() || mSocketClient.isClosed())
//				{
//					isConnecting=false;
//					startButton.setEnabled(true);
//					openLightButton.setEnabled(false);
//					closeLightButton.setEnabled(false);
//					recvText.setText("");
//				}
				try {
					recvMessageClient = mBufferedReaderClient.readLine();
					// if ((count = mBufferedReaderClient.read(buffer)) > 0) {
					// recvMessageClient = getInfoBuff(buffer, count) + "\n";//
					// 消息换行
					parse_cmd(recvMessageClient);
					// }
				} catch (Exception e) {
					recvMessageClient = "接收异常:" + e.getMessage() + "\n";// 消息换行
					Message msg = new Message();
					msg.what = Utils.ERROR;
					mHandler.sendMessage(msg);
				}
			}
			Log.d(Utils.TAG, "client :tcp listen is over");
		}
//命令解析器
		private void parse_cmd(String msg) {
			// TODO Auto-generated method stub
			if (msg.startsWith(Utils.TEMP_DAT_FROM_SER)) {
				Log.d(Utils.TAG, "from server:" + msg);
				int start = msg.indexOf(':');
				Message mesg = new Message();
				mesg.what = Utils.TEMP_ID;
				mesg.obj = msg.substring(start + 1);
				mHandler.sendMessage(mesg);
			} else if (msg.startsWith(Utils.HUMI_DAT_FROM_SER)) {
				Log.d(Utils.TAG, "from server:" + msg);
				int start = msg.indexOf(':');
				Message mesg = new Message();
				mesg.what = Utils.HUMI_ID;
				mesg.obj = msg.substring(start + 1);
				mHandler.sendMessage(mesg);
			}
		}
	};
	//向服务器查询子线程
	private Runnable queryRunnable = new Runnable() {

		@Override
		public void run() {
			// TODO Auto-generated method stub
			while (isConnecting) {
//				Log.d(Utils.TAG, mSocketClient.isClosed()+" isClosed");
//				Log.d(Utils.TAG, mSocketClient.isInputShutdown()+" isInputShutDown");
//				if(mSocketClient.isInputShutdown() || mSocketClient.isClosed())
//				{
//					
//					//isConnecting=false;
//					startButton.setEnabled(true);
//					openLightButton.setEnabled(false);
//					closeLightButton.setEnabled(false);
//					recvText.setText("");
//				}
				if (mSocketClient != null) {
					try {
						mPrintWriterClient.println(Utils.ASK_TEMP_DAT);// 发送给服务器
//						mPrintWriterClient.flush();
						Thread.sleep(Utils.WAIT);
						mPrintWriterClient.println(Utils.ASK_HUMI_DAT);// 发送给服务器
//						mPrintWriterClient.flush();
						Thread.sleep(Utils.WAIT);
//						Toast.makeText(mContext, "查询指令发送", Toast.LENGTH_SHORT)
//								.show();
					} catch (Exception e) {

//						Toast.makeText(mContext, "查询指令发送异常：" + e.getMessage(),
//								Toast.LENGTH_SHORT).show();
					}
				}
			}
			Log.d(Utils.TAG, "client :tcp query is over");
			{
//				Toast.makeText(mContext, "没有连接", Toast.LENGTH_SHORT).show();
			}
		}
	};

	class MyHandler extends Handler {

		public MyHandler(Looper looper) {
			super(looper);

		}
//处理子线程发送来消息的handler
//用于处理自动查找服务器
		@Override
		public void handleMessage(Message msg) {

			if (msg.what== Utils.SER_IP) {
				recvText.setText("");
				recvText.setText("Info: find server @"+ (String)msg.obj+"\n");
				IPText.setText((String)(msg.obj)+":"+Utils.SERVER_REC_TCP_PORT);
			}
			

			super.handleMessage(msg);

		}

	}
	//处理子线程发送来消息的handler
	Handler mHandler = new Handler() {
		public void handleMessage(Message msg) {
			super.handleMessage(msg);
			if (msg.what == Utils.TEMP_ID) {
				recvText.append("temp val update\n"); // 刷新
				tempText.setText(getString(R.string.textviewTemp) + msg.obj);
				curve_temp.setHeightView(Integer.parseInt((String)msg.obj));
				Log.d("test1", "temp:"+Integer.parseInt((String)msg.obj));
			} else if (msg.what == Utils.HUMI_ID) {
				recvText.append("humi val update\n"); // 刷新
				humiText.setText(getString(R.string.textviewHumi) + msg.obj);
				curve_humi.setHeightView(Integer.parseInt((String)msg.obj));
				Log.d("test1", "humi:"+Integer.parseInt((String)msg.obj));
			} else if (msg.what == Utils.ERROR) {
				recvText.append("ERROR: " + recvMessageClient); // 刷新
			} else if (msg.what == Utils.SUCCESS) {
				recvText.append("SUCCESS: " + recvMessageClient); // 刷新
			}
		}
	};

	
//当程序销毁时调用的activity回调函数
	public void onDestroy() {
		super.onDestroy();
		if (isConnecting) {
			isConnecting = false;
			try {
				if (mSocketClient != null) {
					mSocketClient.close();
					mSocketClient = null;

					mPrintWriterClient.close();
					mPrintWriterClient = null;
				}
				if(udphelper.IsThreadDisable)
				{
					udphelper.IsThreadDisable=true;
				}
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			mThreadClientTcpRecv.interrupt();
		}

	}
}