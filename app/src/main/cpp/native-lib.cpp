#include <jni.h>
#include <string>
#include <stdlib.h>
#include  <android/log.h>

#define LOG_TAG "Hello_JNI"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

//创建c++宏替代前缀
#define LINGFUNC(name)Java_com_garena_game_myapplication_MainActivity_##name

extern "C" JNIEXPORT jstring JNICALL
LINGFUNC(stringFromJNI)(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++(Cmake)";

    int a = 10;

    LOGI("toby  我是C代码中的日志    a=%d", a);

    LOGE("hello %s", "world");

    return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT jstring JNICALL
LINGFUNC(getStringFromC)(JNIEnv *env,
                         jobject thiz,
                         jstring a_) {
    const char *a = env->GetStringUTFChars(a_, NULL);
    char *b = "Hello from C++!\n";

    //动态申请一个地址空间
    char *c = (char *) malloc(strlen(a) + strlen(b));
    strcpy(c, b);
    strcat(c, a);

    env->ReleaseStringUTFChars(a_, a);

    return env->NewStringUTF(c);
}

/**
 *  GetIntArrayElements();//得到的是副本，要拷贝数据
    ReleaseIntArrayElements();//对应上面的函数的释放资源的函数

    env->GetPrimitiveArrayCritical();//得到的是指向原数据的指针
    env->ReleasePrimitiveArrayCritical();////对应上面的函数的释放资源的函数
 */
extern "C" void JNICALL LINGFUNC(testArray)(JNIEnv *env, jobject, jintArray array_) {
    int size = env->GetArrayLength(array_);
    int *array = env->GetIntArrayElements(array_, nullptr);
    for (int i = 0; i < size; ++i) {
        printf("array[%d]=%d", i, *(array + i));
        LOGD("array[%d]=%d", i, *(array + i));
    }
    env->ReleaseIntArrayElements(array_, array, 0);

}

/**
 * 字符串拼接
 */
extern "C"
JNIEXPORT jstring JNICALL
LINGFUNC(concatString)(JNIEnv *env, jobject instance, jstring a_, jstring b_) {
    //jstring 转 char*
    const char *a = env->GetStringUTFChars(a_, 0);
    const char *b = env->GetStringUTFChars(b_, 0);

    //动态申请一个地址空间
    char *c = (char *) malloc(strlen(a) + strlen(b));
    strcpy(c, a);
    strcat(c, b);

    //释放拷贝的内存
    /*
     * 第一个参数指定一个jstring变量，即是要释放的本地字符串的来源。
        第二个参数就是要释放的本地字符串
     * */
    env->ReleaseStringUTFChars(a_, a);
    env->ReleaseStringUTFChars(b_, b);

    //将char* 转jstring
    return env->NewStringUTF(c);
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_garena_game_myapplication_MainActivity_compareString(JNIEnv *env, jobject thiz, jstring a_,
                                                              jstring b_) {
    const char *a = env->GetStringUTFChars(a_, 0);
    const char *b = env->GetStringUTFChars(b_, 0);


    env->ReleaseStringUTFChars(a_, a);
    env->ReleaseStringUTFChars(b_, b);

    return strcmp(a, b);
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_garena_game_myapplication_MainActivity_sumArray(JNIEnv *env, jobject thiz,
                                                         jintArray array_) {
    //从java数组获取数组指针
    jint *array = env->GetIntArrayElements(array_, NULL);

    int sum = 0;
    int len = env->GetArrayLength(array_);
    for (int i = 0; i < len; i++) {
        sum += array[i];
    }

    env->ReleaseIntArrayElements(array_, array, 0);

    return sum;
}

/**
 * 二.C调用Java方法
 */
extern "C"
JNIEXPORT void JNICALL
Java_com_garena_game_myapplication_CallJava_callVoidMethod(JNIEnv *env, jobject thiz) {

    //通过反射调用java中的方法
    //找class 使用FindClass方法，参数就是要调用的函数的类的完全限定名，但是需要把点换成/
    jclass clazz = env->FindClass("com/garena/game/myapplication/CallJava");
    //获取对应的函数: 参数1:类class,参数2:方法名,参数3:方法签名
    //ps:方法签名的获取:进入build->intermediates->classes->debug目录下,使用javap -s 类的完全限定名,就能获得函数签名
    jmethodID method = env->GetMethodID(clazz, "hello", "()V");
    //实例化该class对应的实例  使用AllocObject方法，使用clazz创建该class的实例。
    jobject object = env->AllocObject(clazz);
    //调
    env->CallVoidMethod(object, method);
}