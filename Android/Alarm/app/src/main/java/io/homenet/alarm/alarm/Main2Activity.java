package io.homenet.alarm.alarm;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

public class Main2Activity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity2_main);

        Bundle bundle = this.getIntent().getExtras();
        String addressIP = bundle.getString("addressIP");
        int portNumber = bundle.getInt("portNumber");

        System.out.println(addressIP + " " + portNumber);
    }
}
