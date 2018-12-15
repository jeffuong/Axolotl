#find_package(Qt5Widgets REQUIRED)

#set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTOUIC ON)
#set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(main_src "main.cpp")

add_executable(Notefad ${main_src})
#target_link_libraries(Notefad Qt5::Widgets)