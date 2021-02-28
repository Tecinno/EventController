概述：
    基于Android binder做的一个native服务，可以管理native信号的派发，将native信号统一管理派发给Java侧，提供注册监听和主动获取的接口给Java服务，来监听native事件，或者主动get。在车机中就需要统一管理汽车硬件事件如设备的插拔。
优点：
    1.维护效率高，使用简单，只需要继承一个listener就可以，不用像AIDL那样写接口，生成stub、proxy;
    2.拓展方便，每次需要增加接口，只需要在EventInfoData.java中加两个变量。在NEventInfoData.h中修改两个枚举结构就可以，方便后面维护。


代码框架：
    1.EventController中的EventControllerService是native的service，负责管理事件，在init进程中启动；
    2.libeventcontroller是EventController生成的共享so库，提供binder接口的；
    3.EventReceiver是Java测试应用和JNI的libeventreceiver，这里由于时间问题还没有做好，之后需要将libeventreceiver做成一个共享库，以及EventReceiver编译到framework.jar中。使用方法就跟MainActivity.java中那样继承EventListener然后register就可以了。(第二版里面把service和jar都做到EventController里面，编译到系统里面就可以)

类图：https://img-blog.csdnimg.cn/20210206002635277.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1RlY2lubm80,size_16,color_FFFFFF,t_70

时序图：
https://img-blog.csdnimg.cn/20210206002739227.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1RlY2lubm80,size_16,color_FFFFFF,t_70


设计图在代码中有。
