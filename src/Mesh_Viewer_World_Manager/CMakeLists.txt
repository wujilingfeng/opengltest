aux_source_directory(. MYSRC)
set(MYSRC ${MYSRC} ../Interactor_GlobalInfo.c)
message("${MYSRC}")
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/temp_libs)
set(myfindlib MESH_VIEWER_WORLD_MANAGER)
set(mylib mesh_viewer_world_manager)
FILE(WRITE Find${myfindlib}.cmake "set(CMAKE_PREFIX_PATH \${CMAKE_PREFIX_PATH} \${PROJECT_SOURCE_DIR}/temp_libs)\n set(${myfindlib}_INCLUDE_DIR \${PROJECT_SOURCE_DIR}/include)\n FIND_LIBRARY(${myfindlib}_LIBRARY ${mylib})\n IF(${myfindlib}_INCLUDE_DIR AND ${myfindlib}_LIBRARY)\n SET(${myfindlib}_FOUND TRUE)\n ENDIF(${myfindlib}_INCLUDE_DIR AND ${myfindlib}_LIBRARY)\n")

install(FILES Find${myfindlib}.cmake DESTINATION ${CMAKE_ROOT}/Modules)
include_directories(${PROJECT_SOURCE_DIR}/include)
add_library(${mylib} STATIC ${MYSRC})

