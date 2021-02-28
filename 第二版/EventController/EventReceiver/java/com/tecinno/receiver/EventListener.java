 package com.tecinno.receiver;

 import android.os.Handler;
 import android.os.Looper;
 import android.os.Message;
 import android.util.Log;


 public class EventListener {
     final String TAG = "EventListener";
     private EventHandler mhandler;
     public EventListener() {
         if (Looper.myLooper() != null) {
             mhandler = new EventHandler(this, Looper.myLooper());
             Log.e(TAG,"EventHandler Looper.myLooper()");
         } else if (Looper.getMainLooper() != null) {
             mhandler = new EventHandler(this, Looper.getMainLooper());
             Log.e(TAG,"EventHandler Looper.getMainLooper()");
         } else {
             mhandler = null;
             Log.e(TAG,"EventListener thread looper not prepared");
         }
     }

     public EventHandler getEventHandler() {
         if (mhandler != null)
         return mhandler;
         else {
             Log.e(TAG,"mhandler is null");
             return null;
         }
     }

     public class EventHandler extends Handler {
         private EventListener mListener = null;
         public EventHandler(EventListener eventListener, Looper looper) {
             super(looper);
             mListener = eventListener;
         }

         @Override
         public void handleMessage(Message msg) {
             //msg 可以传输其他数据类型，序列化在parcel里
             super.handleMessage(msg);
             switch (msg.what) {
                 case EventInfoData.EN_NOTIFY_A:
                     mListener.notivityEventA(msg.arg1);
                     break;
                 case EventInfoData.EN_NOTIFY_B:
                     mListener.notivityEventB(msg.arg1);
                     break;
                 default:
                     Log.e(TAG, "handleMessage invalid what : "+msg.what);
                     break;
             }
         }

     }

     public void notivityEventA(int data) {
         Log.e(TAG, "notivityEventA data : "+data);
     }

     public void notivityEventB(int data) {
         Log.e(TAG, "notivityEventB data : "+data);
     }

 }
