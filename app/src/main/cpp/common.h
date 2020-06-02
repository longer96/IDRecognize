
#ifndef NETEASEOCRNATIVE_COMMON_H
#define NETEASEOCRNATIVE_COMMON_H

#include <jni.h>
#include <android/log.h>

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

#endif //NETEASEOCRNATIVE_COMMON_H
