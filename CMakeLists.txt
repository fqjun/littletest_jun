# CMake 最低版本号要求 
cmake_minimum_required(VERSION 3.10)

# 项目信息 
project(LITTLETEST_JUN)

# set (CMAKE_C_COMPILER "/usr/bin/gcc")
set (CMAKE_CXX_COMPILER "/usr/bin/g++")

# 设置编译参数 cmake3.1以上
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}  -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}  -O3")

# set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_BUILD_TYPE "Debug")

# OpenCV 
find_package(OpenCV REQUIRED)
# 将给定的目录添加到编译器用于搜索包含文件的目录。相对路径则相对于当前源目录。 
include_directories(${OpenCV_INCLUDE_DIRS})

# 设置可执行文件的保存路径 
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# 查找当前目录下的所有源文件
# 进入相应文件夹内,但该文件内还有一个
aux_source_directory(. DIR_SRCS)

# 等同于下面两句
# 添加链接库的文件夹(全部)
add_subdirectory(setting)
add_subdirectory(RM_Link)
add_subdirectory(RM_VideoCapture)

# 等同于上面的一句
# 添加链接库头文件的路径
# 添加链接库的路径
# include_directories("${PROJECT_SOURCE_DIR}/setting/include")
# link_directories("${PROJECT_SOURCE_DIR}/setting/build/lib")
# include_directories("${PROJECT_SOURCE_DIR}/RM_VideoCapture/include")
# link_directories("${PROJECT_SOURCE_DIR}/RM_VideoCapture/build/lib")


# 指定生成目标 
add_executable(run.o ${DIR_SRCS})

# 将给定的库链接到一个目标上 
target_link_libraries(run.o ${OpenCV_LIBS} Link Set MVSDK)
