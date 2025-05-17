cmake_minimum_required(VERSION 3.28)
project(scene-manager LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


add_executable(main
    main.cpp
)



target_compile_features(main PRIVATE cxx_std_17)
