find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5PrintSupport REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# When adding files here, please add them into the install files below as well
set(main_src 
  "codeeditor.cpp"
  "files.cpp"
  "filedirectory.cpp"
  "main.cpp"
  "mainwindow.cpp"
  "mainwindow.ui" 
  "findwordwindow.cpp"
  "findwordwindow.ui"
  "syntaxhighlighter.cpp"
  "resources.qrc"
  "plugins/testplugin.cpp"
)

add_executable(Axolotl ${main_src})

target_link_libraries(Axolotl Qt5::Widgets
                              Qt5::PrintSupport
)

# Copying Qt binaries for Windows
if(WIN32)
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
  # Debug
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_PREFIX_PATH}/bin/Qt5Cored.dll         ${Axolotl_BINARY_DIR}/src/Debug
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_PREFIX_PATH}/bin/Qt5Guid.dll          ${Axolotl_BINARY_DIR}/src/Debug
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_PREFIX_PATH}/bin/Qt5Widgetsd.dll      ${Axolotl_BINARY_DIR}/src/Debug
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_PREFIX_PATH}/bin/Qt5PrintSupportd.dll ${Axolotl_BINARY_DIR}/src/Debug

  # Release
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_PREFIX_PATH}/bin/Qt5Core.dll         ${Axolotl_BINARY_DIR}/src/Release
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_PREFIX_PATH}/bin/Qt5Gui.dll          ${Axolotl_BINARY_DIR}/src/Release
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_PREFIX_PATH}/bin/Qt5Widgets.dll      ${Axolotl_BINARY_DIR}/src/Release
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_PREFIX_PATH}/bin/Qt5PrintSupport.dll ${Axolotl_BINARY_DIR}/src/Release
)
endif(WIN32)

# Installation packaging 
install (TARGETS "${CMAKE_PROJECT_NAME}" DESTINATION bin)

install (FILES
  "${CMAKE_PREFIX_PATH}/bin/Qt5Cored.dll"
  "${CMAKE_PREFIX_PATH}/bin/Qt5Guid.dll"
  "${CMAKE_PREFIX_PATH}/bin/Qt5Widgetsd.dll"
  "${CMAKE_PREFIX_PATH}/bin/Qt5PrintSupportd.dll"
  DESTINATION bin
)

install (FILES 
  "Main.cpp" 
  "codeeditor.cpp"
  "files.cpp"
  "filedirectory.cpp"
  "main.cpp"
  "mainwindow.cpp"
  "mainwindow.ui" 
  "findwordwindow.cpp"
  "findwordwindow.ui"
  "syntaxhighlighter.cpp"
  "resources.qrc"
  "plugins/testplugin.cpp"
  DESTINATION src
)

INCLUDE(CPack)

#Finding all the folders in a directory
MACRO(SUBDIRLIST result curdir)
  FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
  SET(dirlist "") #setting this as a empty string
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${curdir}/${child})
        LIST(APPEND dirlist ${child})
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist})
ENDMACRO()

SUBDIRLIST( SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR})

FOREACH(subdir ${SUBDIRS})
  ADD_SUBDIRECTORY(${subdir})
ENDFOREACH()

# Turn on the ability to create folders to organize projects (.vcproj)
# It creates "CMakePredefinedTargets" folder by default and adds CMake
# defined projects like INSTALL.vcproj and ZERO_CHECK.vcproj
set_property(GLOBAL PROPERTY USE_FOLDERS ON)