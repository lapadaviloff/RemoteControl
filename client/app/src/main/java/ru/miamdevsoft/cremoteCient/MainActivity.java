package ru.miamdevsoft.cremoteCient;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.util.Log;

import java.net.InetAddress;

public class MainActivity extends AppCompatActivity {

    private Button       mBtnOpen  = null;
    private Button       mBtnSend  = null;
    private Button       mBtnClose = null;
    private EditText     mEdit     = null;
    private SocetClient  mSocetClient  = null;

    private  String     HOST      = "192.168.1.21";
    private  int        PORT      = 1500;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mBtnOpen  = (Button) findViewById(R.id.buttonOpen );
        mBtnSend  = (Button) findViewById(R.id.buttonSend );
        mBtnClose = (Button) findViewById(R.id.buttonClose);
        mEdit     = (EditText) findViewById(R.id.EditText);
        mSocetClient = new SocetClient(HOST, PORT);
       // mBtnSend .setEnabled(false);
       // mBtnClose.setEnabled(false);

        mBtnOpen.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                onOpenClick();
            }
        });

        mBtnSend.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                onSendClick();
            }
        });

        mBtnClose.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                onCloseClick();
            }
        });

    }
    private void onOpenClick()
    {
        Log.i("my","AAAAAAAAAAAAAAAAAAAAAAA");
        // Создание подключения
       // mSocetClient = new SocetClient(HOST, PORT);
        // Открытие сокета в отдельном потоке
        new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    mSocetClient.openConnection();
                    // Разблокирование кнопок в UI потоке
                    runOnUiThread(new Runnable() {
                        @Override
                        public void run() {
                            mBtnSend.setEnabled(true);
                            mBtnClose.setEnabled(true);
                        }
                    });
                    Log.d(SocetClient.LOG_TAG, "Соединение установлено");
                    Log.d(SocetClient.LOG_TAG, "(mConnect != null) = " + (mSocetClient != null));
                } catch (Exception e) {
                    Log.e(SocetClient.LOG_TAG, e.getMessage());
                    mSocetClient = null;
                }
            }
        }).start();
    }
    private void onSendClick()
    {
        if (mSocetClient == null) {
            Log.d(SocetClient.LOG_TAG, "Соединение не установлено");
        }  else {
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
                        String text = "keyboardEmulator:XF86AudioMute";
                        mSocetClient.sendData(text.getBytes());
                    } catch (Exception e) {
                        Log.e(SocetClient.LOG_TAG, e.getMessage());
                    }


                    mSocetClient.closeConnection();

                }
            }).start();
        }
    }
    private void onCloseClick() {

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
                        String text = "!";
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