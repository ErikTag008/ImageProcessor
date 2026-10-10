cmake_minimum_required(VERSION 3.20)

add_executable(ImageProcessor
    main.cpp
    ImageProcessor.cpp
    ImageProcessor.h
)

set_property(TARGET ImageProcessor PROPERTY CXX_STANDARD 20)

find_package(OpenCV REQUIRED)

target_include_directories(ImageProcessor PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(ImageProcessor PRIVATE ${OpenCV_LIBS})