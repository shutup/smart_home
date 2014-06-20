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
	//�����ֶ����õĶ���
	private Button startButton;
	private EditText IPText;
	private Button sendButtonClient;
	private EditText editMsgTextCilent;
	// auto setup object
	//�����Զ����õĶ���
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
	//������ʾ�¶ȵ��ı���
	private TextView tempText;
	// display humi value
	//������ʾʪ�ȵ��ı���
	private TextView humiText;
	
	// display all message
	//������ʾ������Ϣ���ı���
	private TextView recvText;

	// udp���ֶ���
	UdpHelper udphelper;
	//�����Ķ���
	private Context mContext;
	//��ǰ�Ƿ�������״̬�ı�־
	private boolean isConnecting = false;
	//�ͻ���tcp�����߳�
	private Thread mThreadClientTcpRecv = null;
	//�ͻ���tcp���������ѯ�߳�
	private Thread mThreadClientQuery=null;
	//�ͻ���ͬ������ͨ�ŵ��׽���
	private Socket mSocketClient = null;
	//������װ�����������
	static BufferedReader mBufferedReaderClient = null;
	static PrintWriter mPrintWriterClient = null;
	//���ڱ�������ַ����ı���
	private String recvMessageClient = "";
	//��activity����ʱ���õĻص�����
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		//�Գ����������������
		requestWindowFeature(Window.FEATURE_NO_TITLE);// �����ޱ���
		getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
				WindowManager.LayoutParams.FLAG_FULLSCREEN);// ����ȫ��ģʽ
		getWindow().setFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON,// ���ò�����
				WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
		//���ò���
		setContentView(R.layout.main);
		mContext = this;
		//���ó���������صĲ���
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
		//���߳�ʹ��handler�����̷߳�����Ϣ
		MyHandler handler = new MyHandler(Looper.getMainLooper());
		// get the wifimanager object
		//����wifimanager����
		WifiManager manager = (WifiManager) this
				.getSystemService(Context.WIFI_SERVICE);
		// udp Helper Class
		udphelper = new UdpHelper(manager, handler);
		// IP��ַ�༭��
		IPText = (EditText) findViewById(R.id.IPText);
		// IPText.setText("10.0.2.15:");
		IPText.setText("172.168.1.103:8888");
		// �ͻ��˴������Ӱ�ť
		startButton = (Button) findViewById(R.id.StartConnect);
		startButton.setOnClickListener(StartClickListener);
		// �ͻ��˱༭��
		editMsgTextCilent = (EditText) findViewById(R.id.clientMessageText);
		editMsgTextCilent.setText("give_me_temp");
		// �ͻ��˷�����Ϣ��ť
		sendButtonClient = (Button) findViewById(R.id.SendButtonClient);
		sendButtonClient.setOnClickListener(SendClickListenerClient);
		// search server btn
		//���ҷ�������ť
		searchButton = (Button) findViewById(R.id.searchServer);
		searchButton.setOnClickListener(searchClickListener);
		// open the light btn
		//���ư�ť
		openLightButton = (Button) findViewById(R.id.openLight);
		openLightButton.setOnClickListener(openLightClickListener);
		openLightButton.setEnabled(false);
		// close the light btn
		//�صư�ť
		closeLightButton = (Button) findViewById(R.id.closeLight);
		closeLightButton.setOnClickListener(closeLightClickListener);
		closeLightButton.setEnabled(false);
		//��ʾ���ߵĿؼ�
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
		//��ȡ��ʾ�¶ȵ��ı�
		tempText = (TextView) findViewById(R.id.temp_textView);
		//��ȡ��ʾʪ�ȵ��ı�
		humiText = (TextView) findViewById(R.id.humi_textView);
		// ��ʾ��Ϣ�ı���
		recvText = (TextView) findViewById(R.id.RecvText);
		recvText.setMovementMethod(ScrollingMovementMethod.getInstance());
		
		// udp listen thread
		//����udp�����߳�
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
				startButton.setText("��ʼ����");
				openLightButton.setEnabled(false);
				closeLightButton.setEnabled(false);
				IPText.setEnabled(true);
				recvText.setText("��Ϣ:\n");
			} else {
				isConnecting = true;
				startButton.setText("ֹͣ����");
				IPText.setEnabled(false);

				String msgText = IPText.getText().toString();
				if (msgText.length() <= 0) {
					// Toast.makeText(mContext, "IP����Ϊ�գ�",
					// Toast.LENGTH_SHORT).show();
					recvMessageClient = "IP����Ϊ�գ�\n";// ��Ϣ����
					Message msg = new Message();
					msg.what = Utils.ERROR;
					mHandler.sendMessage(msg);
					return;
				}
				int start = msgText.indexOf(":");
				if ((start == -1) || (start + 1 >= msgText.length())) {
					recvMessageClient = "IP��ַ���Ϸ�\n";// ��Ϣ����
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
					// ���ӷ�����
					mSocketClient = new Socket(sIP, port); // portnum
					// ȡ�����롢�����
					mBufferedReaderClient = new BufferedReader(
							new InputStreamReader(
									mSocketClient.getInputStream()));

					mPrintWriterClient = new PrintWriter(
							mSocketClient.getOutputStream(), true);

					recvMessageClient = "�Ѿ�����server!\n";// ��Ϣ����
					Message msg = new Message();
					msg.what = Utils.SUCCESS;
					mHandler.sendMessage(msg);
					//
					searchButton.setEnabled(false);
					// break;
				} catch (Exception e) {
					recvMessageClient = "����IP�쳣:" + e.toString()
							+ e.getMessage() + "\n";// ��Ϣ����
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
				String msgText = editMsgTextCilent.getText().toString();// ȡ�ñ༭�����������������
				if (msgText.length() <= 0) {
					Toast.makeText(mContext, "�������ݲ���Ϊ�գ�", Toast.LENGTH_SHORT)
							.show();
				} else {
					try {
						mPrintWriterClient.println(msgText);// ���͸�������
//						mPrintWriterClient.flush();
					} catch (Exception e) {

						Toast.makeText(mContext, "�����쳣��" + e.getMessage(),
								Toast.LENGTH_SHORT).show();
					}
				}
			} else {
				Toast.makeText(mContext, "û������", Toast.LENGTH_SHORT).show();
			}
		}
	};

	private OnClickListener searchClickListener = new OnClickListener() {

		@Override
		public void onClick(View v) {

			UdpHelper.broadcast_send(Utils.WHO_IS_SERVER,
					Utils.SERVER_REC_UDP_PORT);
			Toast.makeText(mContext, "��ʼ����...", Toast.LENGTH_SHORT).show();
		}
	};
	//���ư�ť�����ļ������ص�����
	private OnClickListener openLightClickListener = new OnClickListener() {

		@Override
		public void onClick(View v) {

			if (isConnecting && mSocketClient != null) {

				try {
					mPrintWriterClient.println(Utils.OPEN_THE_LIGHT);// ���͸�������
					Toast.makeText(mContext, "����ָ���", Toast.LENGTH_SHORT)
							.show();
//					mPrintWriterClient.flush();
				} catch (Exception e) {

					Toast.makeText(mContext, "�����쳣��" + e.getMessage(),
							Toast.LENGTH_SHORT).show();
				}

			} else {
				Toast.makeText(mContext, "û������", Toast.LENGTH_SHORT).show();
			}

		}
	};
	//�صư�ť�����ļ������ص�����
	private OnClickListener closeLightClickListener = new OnClickListener() {

		@Override
		public void onClick(View v) {

			if (isConnecting && mSocketClient != null) {

				try {
					mPrintWriterClient.println(Utils.CLOSE_THE_LIGHT);
//					mPrintWriterClient.print(Utils.CLOSE_THE_LIGHT);// ���͸�������
//					mPrintWriterClient.flush();
					Toast.makeText(mContext, "�ص�ָ���", Toast.LENGTH_SHORT)
							.show();
				} catch (Exception e) {

					Toast.makeText(mContext, "�����쳣��" + e.getMessage(),
							Toast.LENGTH_SHORT).show();
				}

			} else {
				Toast.makeText(mContext, "û������", Toast.LENGTH_SHORT).show();
			}
		}
	};
	// �߳�:������������������Ϣ
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
					// ��Ϣ����
					parse_cmd(recvMessageClient);
					// }
				} catch (Exception e) {
					recvMessageClient = "�����쳣:" + e.getMessage() + "\n";// ��Ϣ����
					Message msg = new Message();
					msg.what = Utils.ERROR;
					mHandler.sendMessage(msg);
				}
			}
			Log.d(Utils.TAG, "client :tcp listen is over");
		}
//���������
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
	//���������ѯ���߳�
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
						mPrintWriterClient.println(Utils.ASK_TEMP_DAT);// ���͸�������
//						mPrintWriterClient.flush();
						Thread.sleep(Utils.WAIT);
						mPrintWriterClient.println(Utils.ASK_HUMI_DAT);// ���͸�������
//						mPrintWriterClient.flush();
						Thread.sleep(Utils.WAIT);
//						Toast.makeText(mContext, "��ѯָ���", Toast.LENGTH_SHORT)
//								.show();
					} catch (Exception e) {

//						Toast.makeText(mContext, "��ѯָ����쳣��" + e.getMessage(),
//								Toast.LENGTH_SHORT).show();
					}
				}
			}
			Log.d(Utils.TAG, "client :tcp query is over");
			{
//				Toast.makeText(mContext, "û������", Toast.LENGTH_SHORT).show();
			}
		}
	};

	class MyHandler extends Handler {

		public MyHandler(Looper looper) {
			super(looper);

		}
//�������̷߳�������Ϣ��handler
//���ڴ����Զ����ҷ�����
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
	//�������̷߳�������Ϣ��handler
	Handler mHandler = new Handler() {
		public void handleMessage(Message msg) {
			super.handleMessage(msg);
			if (msg.what == Utils.TEMP_ID) {
				recvText.append("temp val update\n"); // ˢ��
				tempText.setText(getString(R.string.textviewTemp) + msg.obj);
				curve_temp.setHeightView(Integer.parseInt((String)msg.obj));
				Log.d("test1", "temp:"+Integer.parseInt((String)msg.obj));
			} else if (msg.what == Utils.HUMI_ID) {
				recvText.append("humi val update\n"); // ˢ��
				humiText.setText(getString(R.string.textviewHumi) + msg.obj);
				curve_humi.setHeightView(Integer.parseInt((String)msg.obj));
				Log.d("test1", "humi:"+Integer.parseInt((String)msg.obj));
			} else if (msg.what == Utils.ERROR) {
				recvText.append("ERROR: " + recvMessageClient); // ˢ��
			} else if (msg.what == Utils.SUCCESS) {
				recvText.append("SUCCESS: " + recvMessageClient); // ˢ��
			}
		}
	};

	
//����������ʱ���õ�activity�ص�����
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