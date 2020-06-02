
#ifndef NETEASEOCRNATIVE_UTILS_H
#define NETEASEOCRNATIVE_UTILS_H

#include <android/bitmap.h>
#include <opencv2/opencv.hpp>

using namespace cv;


extern "C" {

void bitmap2Mat(JNIEnv *env, jobject bitmap, Mat* mat, bool needPremultiplyAlpha = 0);

void mat2Bitmap(JNIEnv *env, Mat mat, jobject bitmap, bool needPremultiplyAlpha = 0);

jobject createBitmap(JNIEnv *env,Mat srcData,jobject config);
}
#endif //NETEASEOCRNATIVE_UTILS_H
