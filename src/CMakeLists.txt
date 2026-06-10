rock_library(motors_yanmar_4lv150
    SOURCES Yanmar4LV150Status.cpp Helpers.cpp
    HEADERS Yanmar4LV150Status.hpp Helpers.hpp
    DEPS_PKGCONFIG j1939 power_base)

rock_executable(motors_yanmar_4lv150_bin Main.cpp
    DEPS motors_yanmar_4lv150)

