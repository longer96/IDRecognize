#include <jni.h>
#include <string>
#include "common.h"
#include "utils.h"
#include <opencv2/opencv.hpp>

#define DEFAULT_CARD_WIDTH 640
#define DEFAULT_CARD_HEIGHT 400
#define FIX_IDCARD_SIZE Size(DEFAULT_CARD_WIDTH,DEFAULT_CARD_HEIGHT)

using namespace std;
using namespace cv;

extern "C"
JNIEXPORT jstring JNICALL
Java_com_longer_idrecognize_MainActivity_stringFromJNI(JNIEnv *env, jobject thiz) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}


extern "C"
JNIEXPORT jobject JNICALL
Java_com_longer_idrecognize_MainActivity_removeColor(JNIEnv *env, jobject instance,
                                                     jobject bitmap, jobject argb8888) {

    // 原图
    Mat src_img;
    // 处理过程中的图
    Mat dst;
    // 原图 裁剪之后的图
    Mat dst_img;

    //c 没有Bitmap 要将Bitmap转成Mat 数组 矩阵
    //1 先将Bitmap转成Mat
    bitmap2Mat(env, bitmap, &src_img);
    //3 归一化
    resize(src_img, src_img, FIX_IDCARD_SIZE);
    //4 灰度化
    cvtColor(src_img, dst, COLOR_RGB2GRAY);

    return createBitmap(env, dst, argb8888);

    //5 二值化
    threshold(dst, dst, 100, 255, THRESH_BINARY);
    //6 膨胀
    Mat erodeElement = getStructuringElement(MORPH_RECT, Size(20, 10));
    erode(dst, dst, erodeElement);
    //7 轮廓检测
    vector<vector<Point>> contours;
    vector<Rect> rects;
    findContours(dst, contours, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
    for (int i = 0; i < contours.size(); i++) {
        //获取到矩形区域
        Rect rect = boundingRect(contours.at(i));
        //绘制
//        rectangle(dst,rect,Scalar(0,0,255));
        //8 逻辑处理，找到号码所在区域
        //身份证号码有固定宽高比>1:8&&<1:16
        if (rect.width > rect.height * 8 && rect.width < rect.height * 16) {

            rects.push_back(rect);
        }
    }
    //9 继续查找坐标最低的矩形区域
    int lowPoint = 0;
    Rect finalRect;
    for (int i = 0; i < rects.size(); i++) {
        Rect rect = rects.at(i);
        Point point = rect.tl();
        if (point.y > lowPoint) {
            lowPoint = point.y;
            finalRect = rect;
        }
    }
    dst_img = src_img(finalRect);
    //2 将Mat转成Bitmap
    return createBitmap(env, dst_img, argb8888);

}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_longer_idrecognize_MainActivity_twoColor(JNIEnv *env, jobject thiz, jobject bitmap1,
                                                  jobject argb8888) {
    // 原图
    Mat src_img;
    // 处理过程中的图
    Mat dst;

    //c 没有Bitmap 要将Bitmap转成Mat 数组 矩阵
    //1 先将Bitmap转成Mat
    bitmap2Mat(env, bitmap1, &src_img);

    // 二值化
    threshold(src_img, dst, 100, 255, THRESH_BINARY);

    return createBitmap(env, dst, argb8888);

}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_longer_idrecognize_MainActivity_swellImg(JNIEnv *env, jobject thiz, jobject bitmap2,
                                                  jobject argb8888) {
    // 原图
    Mat src_img;
    // 处理过程中的图
    Mat dst;

    //c 没有Bitmap 要将Bitmap转成Mat 数组 矩阵
    //1 先将Bitmap转成Mat
    bitmap2Mat(env, bitmap2, &src_img);

    // 膨胀处理
    Mat erodeElement = getStructuringElement(MORPH_RECT, Size(22, 3));
    erode(src_img, dst, erodeElement);

    return createBitmap(env, dst, argb8888);

}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_longer_idrecognize_MainActivity_outSideImage(JNIEnv *env, jobject thiz, jobject bitmap3,
                                                      jobject argb8888) {
    // 原图
    Mat src_img;

    //c 没有Bitmap 要将Bitmap转成Mat 数组 矩阵
    //1 先将Bitmap转成Mat
    bitmap2Mat(env, bitmap3, &src_img);
    //4 灰度化
    cvtColor(src_img, src_img, COLOR_RGB2GRAY);

    //7 轮廓检测
    vector<vector<Point>> contours;
    findContours(src_img, contours, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
    for (int i = 0; i < contours.size(); i++) {
        //获取到矩形区域
        Rect rect = boundingRect(contours.at(i));
        //绘制
        rectangle(src_img, rect, Scalar(0, 0, 255));
    }

    return createBitmap(env, src_img, argb8888);
}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_longer_idrecognize_MainActivity_cropImage(JNIEnv *env, jobject thiz, jobject bitmap4,
                                                   jobject argb8888) {
    // 原图
    Mat src_img;
    // 处理过程中的图
    Mat dst;
    // 原图 裁剪之后的图
    Mat dst_img;

    //c 没有Bitmap 要将Bitmap转成Mat 数组 矩阵
    //1 先将Bitmap转成Mat
    bitmap2Mat(env, bitmap4, &src_img);
    //3 归一化
    resize(src_img, src_img, FIX_IDCARD_SIZE);
    //4 灰度化
    cvtColor(src_img, dst, COLOR_RGB2GRAY);

    //5 二值化
    threshold(dst, dst, 100, 255, THRESH_BINARY);
    //6 膨胀
    Mat erodeElement = getStructuringElement(MORPH_RECT, Size(23, 5));
    erode(dst, dst, erodeElement);
    //7 轮廓检测
    vector<vector<Point>> contours;
    vector<Rect> rects;
    findContours(dst, contours, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
    for (int i = 0; i < contours.size(); i++) {
        //获取到矩形区域
        Rect rect = boundingRect(contours.at(i));
        //绘制
//        rectangle(dst,rect,Scalar(0,0,255));
        //8 逻辑处理，找到号码所在区域
        //身份证号码有固定宽高比>1:8&&<1:16
        if (rect.width > rect.height * 10 && rect.width < rect.height * 16) {

            rects.push_back(rect);
        }
    }
    //9 继续查找坐标最低的矩形区域
    int lowPoint = 0;
    Rect finalRect;
    for (int i = 0; i < rects.size(); i++) {
        Rect rect = rects.at(i);
        Point point = rect.tl();
        if (point.y > lowPoint) {
            lowPoint = point.y;
            finalRect = rect;
        }
    }
    dst_img = src_img(finalRect);
    //2 将Mat转成Bitmap
    return createBitmap(env, dst_img, argb8888);

}













