set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${PROJECT_SOURCE_DIR}/temp_libs)
 set(CSTRUCTURES_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
 FIND_LIBRARY(CSTRUCTURES_LIBRARY cstructures)
 IF(CSTRUCTURES_INCLUDE_DIR AND CSTRUCTURES_LIBRARY)
 SET(CSTRUCTURES_FOUND TRUE)
 ENDIF(CSTRUCTURES_INCLUDE_DIR AND CSTRUCTURES_LIBRARY)
