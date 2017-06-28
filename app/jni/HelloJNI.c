#include<jni.h>
#include <stdio.h>
#include "header/com_wzf_ndkstudy_jni_HelloJNI.h"
#include "header/log.h"
#include <string.h>
#include <stdlib.h>

JNIEXPORT void JNICALL Java_com_wzf_ndkstudy_jni_HelloJNI_sayHello(JNIEnv *env, jobject thisObj) {
   LOG_I("%s  %d\n", "大小为：", 200);
   return;
}

JNIEXPORT jstring JNICALL Java_com_wzf_ndkstudy_jni_HelloJNI_sayHelloString(JNIEnv *env, jobject thisObj) {
   return (*env)->NewStringUTF(env, "Java_com_wzf_jni_HelloJNI_sayHelloString");
}

JNIEXPORT jstring JNICALL Java_com_wzf_ndkstudy_jni_HelloJNI_getStringFromC2(JNIEnv *env, jclass jcls, jstring str){
   return (*env)->NewStringUTF(env, "C STRING 2");
}

//修改非静态属性key
JNIEXPORT jstring JNICALL Java_com_wzf_ndkstudy_jni_HelloJNI_changeKey(JNIEnv *env, jobject thisObj){
   //jfieldID    (*GetFieldID)(JNIEnv*, jclass, const char*, const char*);
   //获取jclass
   jclass cls = (*env)->GetObjectClass(env, thisObj);
   //属性名称和属性签名   签名和属性类型有关,有配置表
   jfieldID fid = (*env)->GetFieldID(env, cls, "key", "Ljava/lang/String;");
   // i am in java ->> i am in java but  modify in c
   //获取key的值
   jstring  jstr = (*env)->GetObjectField(env, thisObj, fid);
   //jstring -->c字符串
   //第三个参数 isCopy
   //jstr 是java里的字符串， 当JNI_TRUE时候，c_str就是拷贝的字符串
                              //当为JNI_FALSE, c_str就是原来的字符串，地址相同
   jboolean boolean = JNI_TRUE;
   char *c_str = (*env)->GetStringUTFChars(env, jstr, &boolean);

   //c的字符串转成jstring
   char text[50];
   strcpy(text, c_str);
   strcat(text," but  modify in c");
   jstring  new_jstr = (*env)->NewStringUTF(env, text);
   //修改key
   (*env)->SetObjectField(env, thisObj, fid, new_jstr);
   return new_jstr;

}

//调用java方法
JNIEXPORT void JNICALL Java_com_wzf_ndkstudy_jni_HelloJNI_runJavaMethod(JNIEnv *env, jobject jObj){
   //获取jclass
   jclass cls = (*env)->GetObjectClass(env, jObj);
   //非静态方法调用
   jmethodID  methodId = (*env)->GetMethodID(env, cls, "callByC", "(I)Ljava/lang/String;");
   if(methodId == NULL){
      LOG_E("%s\n", "method not find");
      return;
   }
   //调用
   jint num = 10;
   jobject  str = (*env)->CallObjectMethod(env, jObj, methodId, num);
   char *retString = (*env)->GetStringUTFChars(env, str, NULL);
   LOG_I("return value is : %s\n", retString);

   //静态方法调用
   jmethodID  smethodId = (*env)->GetStaticMethodID(env, cls, "callStaticByC", "(I)Ljava/lang/String;");
   if(smethodId == NULL){
      LOG_E("%s\n", "smethodId not find");
      return;
   }
   //调用
   str = (*env)->CallStaticObjectMethod(env, cls, smethodId, num);
   retString = (*env)->GetStringUTFChars(env, str, NULL);
   LOG_I("static method return value is : %s\n", retString);

}

//访问构造方法 <init>
//使用java.util.Date产生一个当前的时间戳
JNIEXPORT jobject JNICALL Java_com_wzf_ndkstudy_jni_HelloJNI_callConstructor(JNIEnv *env, jobject jObj){
   jclass cls = (*env)->FindClass(env, "java/util/Date");
   jmethodID  mid = (*env)->GetMethodID(env, cls, "<init>", "()V");
   //实例化一个对象
   jobject  date_obj = (*env)->NewObject(env, cls, mid);
   //获取getTime方法id
   jmethodID  getTimeId = (*env)->GetMethodID(env, cls, "getTime", "()J");
   //调用getTime方法
   jlong  time = (*env)->CallLongMethod(env, date_obj, getTimeId);
   LOG_I("时间戳为：%lld\n", time);

   //可以回收局部资源
   (*env)->DeleteLocalRef(env, date_obj);
   return date_obj;
}

//访问父类方法 java引用调用重写了的父类方法不行， 可以通过c来调用
JNIEXPORT void JNICALL Java_com_wzf_ndkstudy_jni_HelloJNI_callParentMethod(JNIEnv *env, jobject jObj){
   jclass cls = (*env)->GetObjectClass(env, jObj);
   //获取testClass 字段
   jfieldID  fid = (*env)->GetFieldID(env, cls, "testClass", "Lcom/wzf/ndkstudy/model/Parent;");

   //获取字段的对象
   jobject  fid_obj = (*env)->GetObjectField(env, jObj, fid);
   //要想调用父类的被覆盖的方法，就需要FindClass传父类的名称
    jclass  fid_cls = (*env)->FindClass(env, "com/wzf/ndkstudy/model/Parent");
    if(fid_cls == NULL){
        LOG_D("%s\n", "fid_cls IS NULL");
    }
   //获取相应的方法
   jmethodID mid = (*env)->GetMethodID(env,fid_cls, "printFormParent", "(I)Ljava/lang/String;");
    if(mid == NULL){
        LOG_D("%s\n", "MID IS NULL");
    }
   //执行方法
   //正常的执行方法 会执行子类重写的方法
//   jobject result = (*env)->CallObjectMethod(env, fid_obj, mid, 123);
   //可以调用父类的方法 跳过子类的覆盖
   jobject result = (*env)->CallNonvirtualObjectMethod(env, fid_obj, fid_cls, mid, 456);
   char * retString = (*env)->GetStringUTFChars(env, result, NULL);
   LOG_I("method result : %s\n", retString);
}

//中文乱码问题
JNIEXPORT jobject JNICALL Java_com_wzf_ndkstudy_jni_HelloJNI_chineseChars(JNIEnv *env, jobject jObj, jstring str_in){
   //输出打印  UTF->>UTF16 所以会有乱码
   char * c_str = (*env)->GetStringUTFChars(env, str_in, NULL);
   LOG_I("%s\n", c_str);
   char *return_str = "我是来自宋喆";
   //解决方法，  调用java的string类，生成指定格式的字符串
   //执行String(byte bytes[], String charsetName)  构造方法需要的条件
   jclass cls = (*env)->FindClass(env, "java/lang/String");
   jmethodID  mid = (*env)->GetMethodID(env, cls, "<init>", "([BLjava/lang/String;)V");
   //参数1:获取jbytearray   --->>   byte[]
   jbyteArray c_byte_array = (*env)->NewByteArray(env, strlen(return_str));
   //byte数组赋值 从0-strlen(string)
   (*env)->SetByteArrayRegion(env, c_byte_array, 0, strlen(return_str), return_str);
   // 参数2 字符编码jstring
   jstring charName = (*env)->NewStringUTF(env, "UTF-8");
   //实例化一个string对象 调用构造方法，返回编码后的jstring
   jstring  result = (*env)->NewObject(env, cls, mid, c_byte_array, charName);
   return result;
}

// int (*)(const void *, const void *));
int compare(int *a, int *b){
   return *a - *b;
}

//传入数组，排序 ,返回数组
JNIEXPORT jobjectArray JNICALL Java_com_wzf_ndkstudy_jni_HelloJNI_giveSortArray(JNIEnv * env, jobject jobj, jintArray intArray){
   //拿到数组指针 jintarray --> jint * ->c int 数组
   jint  *elems = (*env)->GetIntArrayElements(env, intArray, NULL);
   //数组长度
   int len = (*env)->GetArrayLength(env, intArray);
   qsort(elems, len, sizeof(int), compare);
   int i = 0;
   for(;i < len; i++){
      LOG_I("%d \n", *(elems + i));
   }
   //0:同步到java  释放c/c++数组
   //JNI_ABORT:对java数组不更新，但是释放c/c++数组
   //JNI_COMMIT:对java数组更新，但是不释放c/c++数组（函数执行完成还是会释放的）
   (*env)->ReleaseIntArrayElements(env, intArray, elems, JNI_COMMIT);


   //产生一个String数组返回
   //在jni中通过Get<Type>ArrayElements的方式赋值 需要同步，通过SetObjectArrayElement不需要同步
   char strings[][10] = {"hello", "word", "123"};
   //strings首地址 *strings首行的地址
   len = sizeof(strings)/sizeof(*strings);
   jclass cls = (*env)->FindClass(env, "java/lang/String");
   jobjectArray c_string_array = (*env)->NewObjectArray(env, len, cls, NULL);
   for(;i < len;i++){
      jstring  c_str = (*env)->NewStringUTF(env, strings[i]);
      (*env)->SetObjectArrayElement(env, c_string_array, i, c_str);
   }
   return c_string_array;
}

//局部引用回收
JNIEXPORT void JNICALL Java_com_wzf_ndkstudy_jni_HelloJNI_localRef(JNIEnv * env, jobject jobj){
   jclass cls = (*env)->FindClass(env, "java/util/Date");
   jmethodID  mid = (*env)->GetMethodID(env, cls, "<init>", "()V");
   int i = 0;
   for(;i < 10; i++){
      //实例化一个对象
      jobject  date_obj = (*env)->NewObject(env, cls, mid);
      //可以回收局部资源
      (*env)->DeleteLocalRef(env, date_obj);
   }

}

//全局引用
jstring global_str;

//创建全局引用
JNIEXPORT void JNICALL Java_com_wzf_ndkstudy_jni_HelloJNI_createGlobalRef(JNIEnv * env, jobject jobj){
   jstring  c_str = (*env)->NewStringUTF(env, "i am global rdf");
   //还有弱全局引用 NewWeakGlobalRef,但是在用的时候可能为空,在内存不足时会释放
   global_str = (*env)->NewGlobalRef(env, c_str);

}

//获得全局引用
JNIEXPORT jstring JNICALL Java_com_wzf_ndkstudy_jni_HelloJNI_getGlobalRef(JNIEnv * env, jobject jobj){
   char *c_str = (*env)->GetStringUTFChars(env, global_str, NULL);
   if(c_str != NULL){
      LOG_D("in get : %s\n", c_str);
   }else {
      LOG_E("in get : %s\n", "has delete");
   }
   return global_str;
}

//释放全局引用
JNIEXPORT void JNICALL Java_com_wzf_ndkstudy_jni_HelloJNI_deleteGlobalRef(JNIEnv * env, jobject jobj){
   (*env)->DeleteGlobalRef(env, global_str);
   char *c_str = (*env)->GetStringUTFChars(env, global_str, NULL);
   if(c_str != NULL){
      LOG_D("in delete : %s\n", c_str);
   }else {
      LOG_E("in delete : %s\n", "has delete");
   }
}

//异常处理 JNI自己的异常无法在java捕获, 但是可以主动抛出异常让java层捕获
JNIEXPORT void JNICALL Java_com_wzf_ndkstudy_jni_HelloJNI_exception(JNIEnv * env, jobject jobj){
   jclass cls = (*env)->GetObjectClass(env, jobj);
   //没有key2的字段，会报异常, 需要检测，并且无法在kava层捕获
   jfieldID fid = (*env)->GetFieldID(env, cls, "key2", "Ljava/lang/String;");
   //检测是否发生异常
   jthrowable exception = (*env)->ExceptionOccurred(env);
   if(exception != NULL){
      //让java代码可以继续执行，需要清空异常信息
      (*env)->ExceptionClear(env);
      //可以执行补救措施,保证C继续执行
      fid = (*env)->GetFieldID(env, cls, "key", "Ljava/lang/String;");
      //...
   }

   //抛出异常到java层
   jclass newExcCls = (*env)->FindClass(env, "java/lang/Exception");
   (*env)->ThrowNew(env, newExcCls, "A exception from C");
}

//缓存策略, 用于反复不断的调用场景
JNIEXPORT void JNICALL Java_com_wzf_ndkstudy_jni_HelloJNI_jniCache(JNIEnv *env, jobject jobj){
   jclass cls = (*env)->GetObjectClass(env, jobj);
   //由于在java中反复调用了100次, 所以下面的获取字段id的方法需要缓存
   //jfieldID fid = (*env)->GetFieldID(env, cls, "key", "Ljava/lang/String;");
   //for(int i = 0; i < 100; i++){
   //  jni.jniCache();
   //}
   //方法一：利用局部的静态变量-->>作用域还是方法内（只能在该方法使用），直到整个程序结束才会销毁
   //全局的静态变量作用域太大，不建议使用
   static jfieldID  key_id = NULL;
   if(key_id == NULL){
      key_id = (*env)->GetFieldID(env, cls, "key", "Ljava/lang/String;");
      LOG_D("%s\n", "key_id has init");
   }
}
// 方法二：在加载完静态库的时候，调用初始化方法
jfieldID key_fid;
jmethodID key_mid;
JNIEXPORT void JNICALL Java_com_wzf_ndkstudy_jni_HelloJNI_initIds(JNIEnv *env, jclass cls){
//   jclass cls = (*env)->GetObjectClass(env, jobj);
   //缓存起来
   key_fid = (*env)->GetFieldID(env, cls, "key", "Ljava/lang/String;");
   key_mid = (*env)->GetMethodID(env, cls, "callByC", "(I)Ljava/lang/String;");
   LOG_D("%s\n", "initIds has call");
}
