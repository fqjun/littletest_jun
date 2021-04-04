# CMake 最低版本号要求 1
CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

# 项目信息 1
PROJECT(LITTLETEST_JUN)

# 设置参数 1
set(CMAKE_CXX_FLAGS "-std=c++14")
include_directories(${PROJECT_NAME}/setting)

# OpenCV 1
set(OpenCV_DIR /home/jun/workplace/OpenCV/opencv-4.4.0/build)
find_package(OpenCV REQUIRED)
# 将给定的目录添加到编译器用于搜索包含文件的目录。相对路径则相对于当前源目录。 1
include_directories(${OpenCV_INCLUDE_DIRS})


# set(SRC ${PROJECT_SOURCE_DIR}/setting.cpp)

# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

# 设置可执行文件的保存路径 1
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# 查找当前目录下的所有源文件
# 进入相应文件夹内,但该文件内还有一个 1
aux_source_directory(. DIR_SRCS)

# 向构建中添加子目录
# add_subdirectory(${PROJECT_SOURCE_DIR}/setting)

# 指定生成目标 1
add_executable(run ${DIR_SRCS})


# 将给定的库链接到一个目标上 1
target_link_libraries(run ${OpenCV_LIBS} Setlib)

# target_link_libraries(${PROJECT_NAME} Set ${OpenCV_LIBS})
# target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
# message(${OpenCV_LIBS})
# target_link_libraries(${PROJECT_NAME} Setting)
