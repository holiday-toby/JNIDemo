#include <jni.h>
#include <string>
#include <stdlib.h>
#include  <android/log.h>

//创建c++宏替代前缀
#define LOG_TAG "Hello_JNI"
#define LINGFUNC(name)Java_com_garena_game_myapplication_MainActivity_##name

extern "C" JNIEXPORT jstring JNICALL
LINGFUNC(stringFromJNI)(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++(Cmake)";
    return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT jstring JNICALL
LINGFUNC(getStringFromC)(JNIEnv *env,
                         jobject thiz,
                         jstring str_) {
    const char *a = env->GetStringUTFChars(str_, NULL);
    std::string hello = "Hello from C++(getStringFromC)";
    return env->NewStringUTF(hello.c_str());
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
        __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, "array[%d]=%d", i, *(array + i));
    }
    env->ReleaseIntArrayElements(array_, array, 0);

}