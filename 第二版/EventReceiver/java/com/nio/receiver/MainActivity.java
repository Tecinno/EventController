package com.nio.receiver;

import android.app.Activity;

import android.os.Bundle;
import android.os.ParcelUuid;
import android.util.Log;
import android.view.View;

import java.lang.ref.WeakReference;
import java.util.Vector;
// import com.tecinno.receiver;
import com.tecinno.receiver.EventInfoData;
import com.tecinno.receiver.EventListener;
import com.tecinno.receiver.EventReceiver;

public class MainActivity extends Activity {
    public static final int EN_OK = 0;
    public static final int EN_NG = -1;
    public static final String TAG = "MainActivity";
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity);
        Log.e(TAG, "onCreate");
    }

    
    public void button_regist(View view) {
        Log.e(TAG, "button_regist");
        // CEventListener mlistener = new CEventListener();
        int[] ov = {0,1};
        if (EventReceiver.getInstance().regist(new EventListener(){
                @Override
                public void notivityEventA(int data) {
                    Log.e(TAG, "MainActivity notivityEventA data : "+data);
                }

                @Override
                public void notivityEventB(int data) {
                    Log.e(TAG, "MainActivity notivityEventB data : "+data);
                }
            }, 
            ov) == EN_OK) {
            Log.e(TAG, "regist OK");
        } else {
            Log.e(TAG, "regist NG");
        }
    }

    public void button_post(View view) {
        Log.e(TAG, "button_posts");
        // if (EventReceiver.post_test() == EN_OK) {
        //     Log.e(TAG, "test OK");
        // } else {
        //     Log.e(TAG, "test NG");
        // }
    }

    public void button_get(View view) {
       Log.e(TAG, "button_get"); 
        Log.e(TAG,"getEventStausA S: "+EventReceiver.getEventStatus(EventInfoData.EN_NOTIFY_A));
        Log.e(TAG,"getEventStausB : "+EventReceiver.getEventStatus(EventInfoData.EN_NOTIFY_B));
    }

}