find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5PrintSupport REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(main_src 
  "main.cpp"
  "mainwindow.cpp"
  "mainwindow.ui" 
  "codeeditor.cpp"
  "resources.qrc"
)

add_executable(Notefad ${main_src})
target_link_libraries(Notefad Qt5::Widgets)
target_link_libraries(Notefad Qt5::PrintSupport)