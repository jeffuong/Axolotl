#Grabbing every single 
file(GLOB SRCS *.h *.hpp *.c *.cpp)


#Get the append to the listVar_Base which was declared one dir back
#set(listVar ${listVar} ${SRCS} PARENT_SCOPE)

#Gets the sub directory list
SUBDIRLIST( SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR})
if(SUBDIRS STREQUAL "")
  message("There is nothing here")
else(NOT SUBDIRS STREQUAL "")
  foreach(subdir ${SUBDIRS})
    add_subdirectory(${subdir})
  endforeach()
  set(listVar ${listVar} ${SRCS} PARENT_SCOPE)
endif()