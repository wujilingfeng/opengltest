
find ./  /home/libo/Documents/eigen/Eigen  /usr/include/python3.6m  /home/libo/Documents/glm -name '*.h' -o -name '*.c' -o -name '*.cpp' > ./cscope.files&&cscope -Rbq -P shadertest
