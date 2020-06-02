#版本信息
cmake_minimum_required(VERSION 3.4.1)

#头文件配置
include_directories(include)

#编译头文件
file(GLOB my_source_path ${CMAKE_SOURCE_DIR}/*.cpp ${CMAKE_SOURCE_DIR}/*.c)

#添加动态库
add_library(OpenCV SHARED ${my_source_path})

add_library(lib_opencv SHARED IMPORTED)

#设置lib_opencv so 动态库的真实地址
set_target_properties(lib_opencv PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/../jniLibs/${ANDROID_ABI}/libopencv_java4.so)

find_library(
        log-lib
        log)

find_library(jnigraphics-lib
        jnigraphics)

target_link_libraries(
        OpenCV
        ${log-lib}
        ${jnigraphics-lib}#图像处理
        lib_opencv)