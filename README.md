#### Viewer

要改进的地方，

* 渲染字体的实现
* 对点，线，面的拾取已经实现，但对面上的点，线拾取还没实现
* opengl原生UI工具的开发，可以将UI工具放到Something框架，极大降低学习成本。

#### dependencies

* linux

```bash
sudo apt install cmake xorg-dev libglu1-mesa-dev build-essential libgl1-mesa-dev
```



cstructures freetype glad glfw

上面的lib库放在lib文件夹或者安装到的系统目录

cstructures freetype glad文件放在thirdpart中

glfw安装到系统目录，或者自行放到include和lib文件夹

#### install

在build目录下

```bash
cmake ..
make 
sudo make install

```

