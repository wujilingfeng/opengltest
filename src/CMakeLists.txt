aux_source_directory(. MYSRC)

aux_source_directory(../thirdpart/glad/src MYSRC)
message("${MYSRC}")
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/temp_libs)
set(myfindlib MESH_VIEWER)
set(mylib mesh_viewer)
FILE(WRITE Find${myfindlib}.cmake "set(CMAKE_PREFIX_PATH \${CMAKE_PREFIX_PATH} \${PROJECT_SOURCE_DIR}/temp_libs)\n set(${myfindlib}_INCLUDE_DIR \${PROJECT_SOURCE_DIR}/include)\n FIND_LIBRARY(${myfindlib}_LIBRARY ${mylib})\n IF(${myfindlib}_INCLUDE_DIR AND ${myfindlib}_LIBRARY)\n SET(${myfindlib}_FOUND TRUE)\n ENDIF(${myfindlib}_INCLUDE_DIR AND ${myfindlib}_LIBRARY)\n")

install(FILES Find${myfindlib}.cmake DESTINATION ${CMAKE_ROOT}/Modules)
include_directories(${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/thirdpart/glad/include)
add_library(${mylib} STATIC ${MYSRC})

