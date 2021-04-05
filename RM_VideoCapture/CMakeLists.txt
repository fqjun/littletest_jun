cmake_minimum_required(VERSION 3.10)

# 先编译子目录的内容，再编译根目录的内容
aux_source_directory(. DIR_LIB_SRCS)

# 设置链接库文件的保存路径
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

# OpenCV 部分
# 自动查找OpenCV的头文件
find_package(OpenCV REQUIRED)
# 将给定的目录添加到编译器用于搜索包含文件的目录。相对路径则相对于当前源目录。 1
include_directories(${OpenCV_INCLUDE_DIRS})
# OpenCV 部分

add_library(Camera SHARED ${DIR_LIB_SRCS})

target_include_directories(Camera PUBLIC include)