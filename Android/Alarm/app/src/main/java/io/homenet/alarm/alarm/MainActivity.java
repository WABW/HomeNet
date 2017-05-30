package io.homenet.alarm.alarm;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.os.Looper;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.EditText;

import java.io.*;
import java.net.Socket;

public class MainActivity extends AppCompatActivity {

    EditText serverEditText;
    EditText portEditText;

    private String addressIP;
    private int portNumber;
    private Socket socket;
    private InputStreamReader is;
    private OutputStream os;
    private String equipment;
    private String response;
    private BufferedReader br;
    private BufferedWriter bw;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        serverEditText = (EditText) findViewById(R.id.serverEditText);
        portEditText = (EditText) findViewById(R.id.portEditText);

        findViewById(R.id.connectButton).setOnClickListener(onConnectButtonClick);
    }

    @Override
    protected void onStart() {
        super.onStart();
    }

    public View.OnClickListener onConnectButtonClick = new View.OnClickListener() {
        @Override
        public void onClick(View view) {
            System.out.println("Button click");
            addressIP = serverEditText.getText().toString();
            portNumber = Integer.parseInt(portEditText.getText().toString());

            new Thread() {
                public void run() {
                    ApplicationUtil appUtil = (ApplicationUtil) MainActivity.this.getApplication();

                    try {
                        appUtil.init(addressIP, portNumber);
                        socket = appUtil.getSocket();
                        br = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                        bw = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
                        equipmentType();
                        if(getResponse()) {
                            Intent intent = new Intent(MainActivity.this, Main2Activity.class);
                            startActivity(intent);
                        }
                        else {
                            Looper.prepare();
                            new AlertDialog.Builder(MainActivity.this)
                                    .setIcon(android.R.drawable.ic_dialog_alert)
                                    .setTitle("提示")
                                    .setMessage("服务器无响应！")
                                    .setPositiveButton("确定", new DialogInterface.OnClickListener()
                                    {
                                        @Override
                                        public void onClick(DialogInterface dialog, int which)
                                        {
                                }
                            })
                                    .create()
                                    .show();
                            Looper.loop();
                        }

                    } catch (IOException e) {
                        e.printStackTrace();
                        System.out.println("服务器连接失败！！！！！");
                    } catch (Exception e) {
                        e.printStackTrace();
                    } finally {

                    }
                }
            }.start();

        }
    };

    public void equipmentType() {
        equipment = "BA000000000000001";
        try {
            bw.write(equipment);
            bw.newLine();
            bw.flush();
            System.out.println("我的设备号： " + equipment);
        } catch (IOException e) {
            System.out.println("设备信息发送失败！");
            e.printStackTrace();
        }
    }

    public boolean getResponse() {
        boolean flag = false;
        try {
            socket.setSoTimeout(5000);
            response = br.readLine();
            socket.setSoTimeout(0);
            System.out.println("收到服务器相应： " + response);
            if (response != "FY") flag = true;
        } catch (IOException e) {
            System.out.println("未收到服务器回应！");
            e.printStackTrace();
        }
        System.out.println(flag);
        return flag;
    }
}
