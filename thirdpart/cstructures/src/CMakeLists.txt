aux_source_directory(. MYSRC)
MESSAGE(${MYSRC})
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/temp_libs)
set(myfindlib CSTRUCTURES)
set(mylib cstructures)
MESSAGE(${CMAKE_ROOT})
FILE(WRITE Find${myfindlib}.cmake "set(CMAKE_PREFIX_PATH \${CMAKE_PREFIX_PATH} \${PROJECT_SOURCE_DIR}/temp_libs)\n set(${myfindlib}_INCLUDE_DIR \${PROJECT_SOURCE_DIR}/include)\n FIND_LIBRARY(${myfindlib}_LIBRARY ${mylib})\n IF(${myfindlib}_INCLUDE_DIR AND ${myfindlib}_LIBRARY)\n SET(${myfindlib}_FOUND TRUE)\n ENDIF(${myfindlib}_INCLUDE_DIR AND ${myfindlib}_LIBRARY)\n")

install(FILES Find${myfindlib}.cmake DESTINATION ${CMAKE_ROOT}/Modules)
#MESSAGE("${CMAKE_PREFIX_PATH} ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_ROOT}")
include_directories(${PROJECT_SOURCE_DIR}/include)
add_library(${mylib} STATIC ${MYSRC})
 		 
