cmake_minimum_required(VERSION 3.10)

# 先编译子目录的内容，再编译根目录的内容
aux_source_directory(. DIR_LIB_SRCS)

# 命名链接库
add_library(Serial SHARED ${DIR_LIB_SRCS})

# 包含头文件
target_include_directories(Serial PUBLIC include)