INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/setting) # ${PROJECT_SOURCE_DIR} 相当于 .

# OpenCV 
find_package(OpenCV REQUIRED)
# 将给定的目录添加到编译器用于搜索包含文件的目录。相对路径则相对于当前源目录。 
include_directories(${OpenCV_INCLUDE_DIRS})

# 设置可执行文件的保存路径 
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# 查找当前目录下的所有源文件
# 进入相应文件夹内,但该文件内还有一个 
aux_source_directory(. DIR_SRCS)

# 指定生成目标 
add_executable(run.o ${DIR_SRCS})

# 将给定的库链接到一个目标上 
target_link_libraries(run.o ${OpenCV_LIBS} Setlib)
