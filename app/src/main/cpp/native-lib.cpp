#include <jni.h>
#include <string>
#include <stdlib.h>

//创建c++宏替代前缀
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

extern "C" void LINGFUNC(OnCameraStart)(JNIEnv * LocalJNIEnv, jobject LocalThiz, jint CameraId, jint PreviewWidth, jint PreviewHeight, jint CameraRotation)
{

}