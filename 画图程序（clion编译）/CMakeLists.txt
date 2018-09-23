cmake_minimum_required(VERSION 3.10)
project(cgfinal)

set(CMAKE_CXX_STANDARD 11)

add_executable(cgfinal main.cpp MyObject.h MyObject.cpp)

target_link_libraries(cgfinal -I/usr/local/include/opencv -I/usr/local/include -L/usr/local/lib -lopencv_objdetect -lopencv_shape -lopencv_superres -lopencv_ml -lopencv_stitching -lopencv_dnn -lopencv_videostab -lopencv_calib3d -lopencv_features2d -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_video -lopencv_photo -lopencv_imgproc -lopencv_flann -lopencv_core)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
