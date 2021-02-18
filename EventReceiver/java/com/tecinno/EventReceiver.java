 package com.tecinno;

 import android.os.Handler;
 import android.os.Message;
 import android.os.Parcel;
 import android.util.Log;

 import java.lang.ref.WeakReference;
 import java.util.Iterator;
 import java.util.Vector;

 public class EventReceiver {
     public static final int EN_OK = 0;
     public static final int EN_NG = -1;
     private static EventReceiver instance = null;
     private static Object mLock = null;
     private final static String TAG = "EventReceiver";
     private Vector<ListenerEntry> mListenerVector;
     private EventReceiver() {
         Log.e(TAG,"EventReceiver");
         mListenerVector = new Vector();
         mLock = new Object();
     }

     static {
         System.loadLibrary("eventreceiver");
     }

     public static EventReceiver getInstance() {
         if (instance == null) {
             instance = new EventReceiver();
            
         }
         return instance;
     }

     public static Integer getEventA() {
         return getEventStatus(EventInfoData.EN_GET_A);
     }

     public static Integer getEventB() {
         return getEventStatus(EventInfoData.EN_GET_B);
     }

     public Vector<ListenerEntry> getListenerEntry() {
         return mListenerVector;
     }

     public int regist(EventListener listener, int[] OverrideInfo) {
         Log.e(TAG,"regist");
         synchronized (mLock) {
             if (listener != null) {
                 if (nativeInit() == EN_OK) {
                     Log.e(TAG,"nativeInit OK");
                 } else {
                     Log.e(TAG,"nativeInit NG");
                 }
                 ListenerEntry entry = new ListenerEntry(listener, OverrideInfo);
                 if (!(mListenerVector.contains(entry))) {
                     mListenerVector.addElement(entry);
                     registToService(new WeakReference<EventReceiver>(instance), OverrideInfo);
                     return EN_OK;
                 } else {
                     Log.e(TAG,"mListenerVector contains listener already");
                     return EN_NG;
                 }
             } else {
                 Log.e(TAG,"listener is null");
                 return EN_NG;
             }
         }
     }

     public static void postEvent(Object ref,  int what, int arg1, int arg2, Object parcel) {
         Log.e(TAG,"postEvent");
         synchronized (mLock) {
             EventReceiver er = (EventReceiver)((WeakReference)ref).get();
             Vector<ListenerEntry> mEntrys = er.getListenerEntry();
             if (er == null) {
                 Log.e(TAG,"postEvent, EventReceiver Reference is null");
                 return;
             }
             if (mEntrys != null && !mEntrys.isEmpty()) {
                 Iterator<ListenerEntry> it = mEntrys.iterator();
                 while (it.hasNext()) {
                     Handler handler = it.next().mlistener.getEventHandler();
                     if (handler == null) {
                         Log.e(TAG,"postEvent handler is null ");
                         continue;
                     }
                     Message msg = handler.obtainMessage();
                     msg.what = what;
                     msg.arg1 = arg1;
                     msg.arg2 = arg2;
                     //需要添加其他数据类型
                     msg.obj = parcel;
                     handler.sendMessage(msg);
                 }
             }
         }

     }
     public static void post() {
         Log.e(TAG,"post");
     }
     public static int post_test() {
         Log.e(TAG,"post_test");
         return test();
     }
     private class ListenerEntry {
         public EventListener mlistener;
         public int[] mOverrideInfo;
         public ListenerEntry(EventListener listener, int[] overrideInfo) {
             mlistener = listener;
         }
         public EventListener getListener() {
             return mlistener;
         }
         public int[] getOverrideInfo() {
             return mOverrideInfo;
         }
         @Override
         public boolean equals(Object o) {
             //自反性
             if (this == o) return true;
             //任何对象不等于null，比较是否为同一类型
             if (!(o instanceof ListenerEntry)) return false;
             //强制类型转换
             ListenerEntry entry = (ListenerEntry) o;
             //比较属性值
             return entry.mlistener == this.mlistener;
         }
     }
     //================native method======================
     private static native final int nativeInit();
     public static native int getEventStatus(int code);
     private static native int registToService(Object ref_this, int[] override_info);
     public static native int test();
 }
