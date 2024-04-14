cmake_minimum_required(VERSION 3.10)
project(HelloGLFW VERSION 0.1.0)

# 使用 C++17 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 设置源代码目录和包含目录
set(SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")
set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/../../include")
set(LIBRARY_DIR "${PROJECT_SOURCE_DIR}/../../lib")

# 添加头文件目录
include_directories(${INCLUDE_DIR})

# 查找源文件
file(GLOB SOURCES "${SOURCE_DIR}/*.cpp" "${PROJECT_SOURCE_DIR}/../../src/glad.c")

# 添加可执行文件
add_executable(${PROJECT_NAME} ${SOURCES})
if(WIN32)
    target_link_libraries(${PROJECT_NAME} "${LIBRARY_DIR}/glfw3.lib")

    #动态链接库方式 不优先考虑
    #  target_link_libraries(${PROJECT_NAME} "${LIBRARY_DIR}/glfw3dll.lib")
endif()

if(APPLE)
    target_link_libraries(${PROJECT_NAME} "${LIBRARY_DIR}/libglfw3.a")

    # 动态链接库方式 不优先考虑
    # target_link_libraries(${PROJECT_NAME} "${LIBRARY_DIR}/libglfw.3.dylib")
endif()

# 如果是在苹果系统上，需要链接额外的框架
if(APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa" "-framework OpenGL" "-framework IOKit" "-framework CoreVideo" "-lobjc")
endif()
