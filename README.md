#### dependencies 

glfw,glad(最低限度的opengl库)

glfw的安装参照官网，

下载相应版本的glad库，替换thirdpart的glad库即可

#### install

在build文件夹执行 

cmake ..

 make  

make install

#### 网格库

推荐使用libcell库，支持n维流形(当然包含任意多边形)，代码紧凑，功能统一，简洁，高效。

#### 遗留工作

把Mesh_viewer换成Viewer

结构名称统一。

多个shader的支持。