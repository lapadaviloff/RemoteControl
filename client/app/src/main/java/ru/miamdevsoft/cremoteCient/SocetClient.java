package ru.miamdevsoft.cremoteCient;
import android.util.Log;

import java.io.IOException;
import java.net.Socket;
public class SocetClient {
    private  Socket  mSocket = null;
    private  String  mHost   = null;
    private  int     mPort   = 0;

    public static final String LOG_TAG = "SOCKET";

    public SocetClient() {}

    public SocetClient (final String host, final int port)
    {
        this.mHost = host;
        this.mPort = port;
    }




    /**
     * Метод открытия сокета
     */
    public void openConnection() throws Exception
    {
        // Если сокет уже открыт, то он закрывается
        closeConnection();
        try {
            // Создание сокета
            mSocket = new Socket(mHost, mPort);
        } catch (IOException e) {
            throw new Exception("Невозможно создать сокет: "+e.getMessage());
        }
    }
    /**
     * Метод закрытия сокета
     */
    public void closeConnection()
    {
        /* Проверяем сокет. Если он не зарыт, то закрываем его и освобдождаем соединение.*/
        if (mSocket != null && !mSocket.isClosed()) {
            try {
                mSocket.close();
            } catch (IOException e) {
                Log.e(LOG_TAG, "Невозможно закрыть сокет: " + e.getMessage());
            } finally {
                mSocket = null;
            }
        }
        mSocket = null;
    }
    /**
     * Метод отправки данных
     */
    public void sendData(byte[] data) throws Exception {
        // Проверка открытия сокета
        if (mSocket == null || mSocket.isClosed()) {
            throw new Exception("Невозможно отправить данные. Сокет не создан или закрыт");
        }
        // Отправка данных
        try {
            mSocket.getOutputStream().write(data);
            mSocket.getOutputStream().flush();
        } catch (IOException e) {
            throw new Exception("Невозможно отправить данные: "+e.getMessage());
        }
    }
    @Override
    protected void finalize() throws Throwable
    {
        try {
            //String text = mEdit.getText().toString();
            //if (text.trim().length() == 0)
            //   text = "Test message";
            /* отправляем на сервер данные */
            String text = "!";
            sendData(text.getBytes());
        } catch (Exception e) {
            Log.e(SocetClient.LOG_TAG, e.getMessage());
        }
        super.finalize();
        closeConnection();
    }



}
