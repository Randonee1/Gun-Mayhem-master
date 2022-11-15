# Advanced-Language-Programming



### 如何安装

安装git

首先用cocos2d-x新建一个项目

<img src=".\README_image\image-20221115152348815.png" alt="image-20221115152348815"  />

删除掉不需要的文件，留下这两个文件（`.cocos-project.json`不知道要不要用到，先留着）

<img src=".\README_image\image-20221115152859720.png" alt="image-20221115152859720" style="zoom: 80%;" />

在这个路径下打开`git Bash`  输入指令  `git clone https://github.com/Randonee1/Advanced-Language-Programming.git` 将远端仓库中的内容下载到本地，会生成 `Advanced-Language-Programming` 文件夹，里面的文件都被 `git`  管理

<img src=".\README_image\image-20221115162005352.png" alt="image-20221115162005352" style="zoom: 80%;" />

将 `Advanced-Language-Programming` 中的  `cmake.txt`  (cmake 指令如果时vs2019要改一下)和  `CMakeLists.txt` 文件复制到项目文件路径下

![image-20221115194938335](./README_image/image-20221115194938335.png)

在项目文件 `proj.win32`  路径下进入 `cmd` ，输入 `cmake` 指令，指令在仓库中的 `cmake.txt` 文件中，生成解决方案 `sln`

![image-20221114205509986](./README_image/image-20221114205509986.png)

![image-20221114211911009](./README_image/image-20221114211911009.png)

然后程序就可以跑了



### Git 版本管理

pass



### 如何添加文件

在 `Classes` 对应的路径下新建文件，重新在 `proj.win32` 下`cmake`  一遍（直接进入 `cmd` 输入 `cmake`  指令，不需要删除其他文件），在进入  `sln`  文件中就可以看见对应目录下新添加的文件

如果直接在解决方案文件里面直接添加文件，会发现新建的文件会在 `proj.win32` 目录下，这是因为在解决方案对应的文件都以虚文件的方式被管理，同时 `Classes`  文件夹不在 `proj.win32`  文件夹目录下，所以也不能切换到真实目录添加文件。



### 11/14

蔡政特：我把游戏引擎改了，可以实现较为流畅的动作。目前实现了人物的左右移动，跳跃动作，开枪动作，子弹弹壳的关联动画（按o或者1开枪）

<img src=".\README_image\image-20221115164529684.png" alt="image-20221115164529684" style="zoom:50%;" />

<img src=".\README_image\image-20221115164721243.png" alt="image-20221115164721243" style="zoom: 50%;" />

* Cocos2d 引擎修改

  引擎痛点：引擎中自带的action只能实现固定的轨迹，再动作执行过程中无法改变对象的相对位置（比如再游戏过程中需要翻转，对应的动作不会跟着翻转）

  修改方案：在动作更新时，根据对象是否翻转情况，改变对象的坐标。以 ` MoveBy()` 举例，原引擎是在动作开始时先得到对象当前的坐标值，然后在每次更新时，计算相对于开始坐标的移动距离，更新对象的位置，问题在于 `MoveBy()` 

