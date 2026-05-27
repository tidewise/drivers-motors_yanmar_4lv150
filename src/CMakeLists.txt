rock_library(motors_yanmar_4lv150
    SOURCES Dummy.cpp
    HEADERS Dummy.hpp)

rock_executable(motors_yanmar_4lv150_bin Main.cpp
    DEPS motors_yanmar_4lv150)

