set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${PROJECT_SOURCE_DIR}/temp_libs)
 set(CSTRUCT_ITERATOR_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
 FIND_LIBRARY(CSTRUCT_ITERATOR_LIBRARY cstruct_iterator)
 IF(CSTRUCT_ITERATOR_INCLUDE_DIR AND CSTRUCT_ITERATOR_LIBRARY)
 SET(CSTRUCT_ITERATOR_FOUND TRUE)
 ENDIF(CSTRUCT_ITERATOR_INCLUDE_DIR AND CSTRUCT_ITERATOR_LIBRARY)
