package com.example.a14580.siren;

import android.media.MediaPlayer;
import android.media.RingtoneManager;
import android.net.Uri;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

import java.io.*;
import java.net.Socket;

public class MainActivity2 extends AppCompatActivity {

    Button stopButton;
    EditText messageEditText;

    private InputStreamReader is;
    private OutputStream os;
    private String message;
    private Socket socket;
    private MediaPlayer mMediaPlayer;



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main2);


        mMediaPlayer = MediaPlayer.create(this, getSystemDefultRingtoneUri());
        mMediaPlayer.setLooping(true);
        try {
            mMediaPlayer.prepare();
        } catch (IllegalStateException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }

//        messageEditText = (EditText) findViewById(R.id.messageEditText);
//        findViewById(R.id.sendButton).setOnClickListener(onSendButtonClick);

        getEcho();
        stopButton = (Button) findViewById(R.id.stopButton);
        stopButton.setOnClickListener(new View.OnClickListener() {
                    @Override
                    public void onClick(View v) {
                        // TODO Auto-generated method stub
                        mMediaPlayer.stop();
            }
        });

    }

    @Override
    protected void onStart() {
        super.onStart();
    }
//    public View.OnClickListener onSendButtonClick = new View.OnClickListener() {
//        @Override
//        public void onClick(View view) {
//            try {
//                os = socket.getOutputStream();
//                System.out.println("Button click");
//                message = messageEditText.getText().toString();
//                System.out.println(message);
//                BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(os));
//                bw.write(message);
//                bw.newLine();
//                bw.flush();
//
//                messageEditText.setText("");
//
//            } catch (IOException e) {
//                System.out.println("发送失败");
//            }
//        }
//    };

    public void getEcho () {

        new Thread() {
            public void run() {

                ApplicationUtil appUtil = (ApplicationUtil) MainActivity2.this.getApplication();
                socket = appUtil.getSocket();

                try

                {
                    is = new InputStreamReader(socket.getInputStream());

                    while (true) {
                        BufferedReader br = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                        String sentence = br.readLine();
//                        1 == Integer.parseInt(sentence)
                        if(sentence == "bw") {
                            mMediaPlayer.start();
                            break;
                        }
                        else if(sentence == "stop") {
                            mMediaPlayer.stop();
                            break;
                        }
                        else {
                            System.out.println("return from server: " + sentence);
                        }
                    }
                } catch (IOException e) {
                    System.out.println("服务器连接失败! " + "\n");
                }
            }
        }.start();

    }

    private Uri getSystemDefultRingtoneUri() {
        return RingtoneManager.getActualDefaultRingtoneUri(this,
                RingtoneManager.TYPE_RINGTONE);
    }
}
