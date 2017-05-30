package io.homenet.alarm.alarm;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.EditText;

import java.io.*;
import java.net.Socket;

public class Main2Activity extends AppCompatActivity {

    EditText messageEditText;

    private InputStreamReader is;
    private OutputStream os;
    private String message;
    private Socket socket;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity2_main);

        messageEditText = (EditText) findViewById(R.id.messageEditText);
        findViewById(R.id.sendButton).setOnClickListener(onSendButtonClick);

        getEcho();

//        Bundle bundle = this.getIntent().getExtras();
//        String addressIP = bundle.getString("addressIP");
//        int portNumber = bundle.getInt("portNumber");
//        System.out.println(addressIP + " " + portNumber);
    }

        public void getEcho () {

            new Thread() {
                public void run() {

                    ApplicationUtil appUtil = (ApplicationUtil) Main2Activity.this.getApplication();
                    socket = appUtil.getSocket();

                    try

                    {
                        is = new InputStreamReader(socket.getInputStream());

                        while (true) {
                            BufferedReader br = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                            String sentence = br.readLine();
                            if(sentence == null) {
                                break;
                            }
                            else System.out.println("return from server: " + sentence);
                        }
                    } catch (IOException e) {
                        System.out.println("服务器连接失败! " + "\n");
                    }
                }
            }.start();

        }

    @Override
    protected void onStart() {
        super.onStart();
    }

    public View.OnClickListener onSendButtonClick = new View.OnClickListener() {
        @Override
        public void onClick(View view) {
            try {
                os = socket.getOutputStream();
                System.out.println("Button click");
                message = "CT"+messageEditText.getText().toString();
                System.out.println(message);
                BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(os));
                bw.write(message);
                bw.newLine();
                bw.flush();

                messageEditText.setText("");

            } catch (IOException e) {
                System.out.println("发送失败");
            }
        }
    };
}
