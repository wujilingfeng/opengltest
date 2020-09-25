set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${PROJECT_SOURCE_DIR}/temp_libs)
 set(VIEWER_WORLD_MANAGER_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
 FIND_LIBRARY(VIEWER_WORLD_MANAGER_LIBRARY viewer_world_manager)
 IF(VIEWER_WORLD_MANAGER_INCLUDE_DIR AND VIEWER_WORLD_MANAGER_LIBRARY)
 SET(VIEWER_WORLD_MANAGER_FOUND TRUE)
 ENDIF(VIEWER_WORLD_MANAGER_INCLUDE_DIR AND VIEWER_WORLD_MANAGER_LIBRARY)
