package io.homenet.alarm.alarm;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.EditText;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.InetAddress;
import java.net.Socket;

public class MainActivity extends AppCompatActivity {

    EditText serverEditText;
    EditText portEditText;

    private InputStream is;
    private OutputStream os;
    private InetAddress ia = null;
    BufferedReader bw;
    private String addressIP;
    private int portNumber;


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
                    Socket socket = null;
                    try {
                        socket = new Socket(addressIP, portNumber);

                    } catch (IOException e) {
                        e.printStackTrace();
                        System.out.println("服务器连接失败！！！！！");
                    } finally {
                        try {
                            socket.close();
                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                    }
                }
            }.start();

            Intent intent = new Intent(MainActivity.this, Main2Activity.class);
            Bundle bundle = new Bundle();
            bundle.putString("addressIP",addressIP);
            bundle.putInt("portNumber",portNumber);
            intent.putExtras(bundle);

            startActivity(intent);
        }
    };
}
