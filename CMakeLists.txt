cmake_minimum_required(VERSION 3.22)
project(RaspberryPi_project)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        Network
        REQUIRED)

add_executable(RaspberryPi_project main.cpp Buttons.h Buttons.cpp Connection.h Connection.cpp app_v2/main.cpp)
target_link_libraries(RaspberryPi_project
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Network
        )

