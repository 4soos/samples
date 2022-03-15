cmake_minimum_required(VERSION 3.0.0)
project(nets VERSION 0.1.0)


set(CMAKE_CXX_STANDARD 11)
add_executable(nets main.cpp)
# target_link_libraries(nets pthread) #for linux host
target_link_libraries(nets -Wl,-Bstatic socket -Wl,-Bstatic) #for qnx
