set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${PROJECT_SOURCE_DIR}/temp_libs)
 set(VIEWER_OPENGLALG_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
 FIND_LIBRARY(VIEWER_OPENGLALG_LIBRARY viewer_openglalg)
 IF(VIEWER_OPENGLALG_INCLUDE_DIR AND VIEWER_OPENGLALG_LIBRARY)
 SET(VIEWER_OPENGLALG_FOUND TRUE)
 ENDIF(VIEWER_OPENGLALG_INCLUDE_DIR AND VIEWER_OPENGLALG_LIBRARY)
