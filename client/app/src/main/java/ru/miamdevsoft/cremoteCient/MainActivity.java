package ru.miamdevsoft.cremoteCient;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.util.Log;

public class MainActivity extends AppCompatActivity {

    private Button       mBtnVolUp  = null;
    private Button       mBtnVolDown  = null;
    private Button       mBtnFullScreen = null;
    private Button       mBtnRL  = null;
    private Button       mBtnPlay  = null;
    private Button       mBtnRR = null;
    private Button       mBtnNext = null;
    private Button       mBtnMute = null;
   // private EditText     mEdit     = null;
    private SocetClient  mSocetClient  = null;

    private  String     HOST      = "192.168.1.21";
    private  int        PORT      = 1500;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mBtnVolUp  = (Button) findViewById(R.id.volUP);
        mBtnVolDown  = (Button) findViewById(R.id.volDOWN);
        mBtnFullScreen  = (Button) findViewById(R.id.FullScreen);
        mBtnRL  = (Button) findViewById(R.id.RL);
        mBtnRR  = (Button) findViewById(R.id.RR);
        mBtnPlay  = (Button) findViewById(R.id.Play);
        mBtnNext  = (Button) findViewById(R.id.Next);
        mBtnMute  = (Button) findViewById(R.id.Mute);




      //  mEdit     = (EditText) findViewById(R.id.EditText);
        mSocetClient = new SocetClient(HOST, PORT);
       // mBtnSend .setEnabled(false);
       // mBtnClose.setEnabled(false);

        mBtnVolUp.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                connect("keyboardEmulator:VolUp");
            }
        });

        mBtnVolDown.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                connect("keyboardEmulator:VolDown");
            }
        });

        mBtnFullScreen.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                connect("keyboardEmulator:FullScreen");
            }

        });
        mBtnRL.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                connect("keyboardEmulator:RL");
            }

        });
        mBtnRR.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                connect("keyboardEmulator:RR");
            }

        });
        mBtnPlay.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                connect("keyboardEmulator:Play");
            }

        });
        mBtnNext.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                connect("keyboardEmulator:Next");
            }

        });
         mBtnMute.setOnClickListener(new View.OnClickListener() {
        @Override
        public void onClick(View v) {
            connect("keyboardEmulator:Mute");
        }

    });

    }


    private void connect(String s) {

        if (mSocetClient == null) {
            Log.d(SocetClient.LOG_TAG, "Соединение не установлено");
        } else {
            Log.d(SocetClient.LOG_TAG, "Отправка сообщения");
            new Thread(new Runnable() {
                @Override
                public void run() {
                    try {
                        mSocetClient.openConnection();

                        Log.d(SocetClient.LOG_TAG, "Соединение установлено");
                        Log.d(SocetClient.LOG_TAG, "(mConnect != null) = " + (mSocetClient != null));
                    } catch (Exception e) {
                        Log.e(SocetClient.LOG_TAG, e.getMessage());
                        mSocetClient = null;
                    }

                    try {
                        //String text = mEdit.getText().toString();
                        //if (text.trim().length() == 0)
                        //   text = "Test message";
                        /* отправляем на сервер данные */
                        String text = s + "\0";
                        Log.i("myTag", s);
                        mSocetClient.sendData(text.getBytes());
                    } catch (Exception e) {
                        Log.e(SocetClient.LOG_TAG, e.getMessage());
                    }


                    mSocetClient.closeConnection();

                }
            }).start();
        }
    }
}