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



## 游戏文档/项目进程



### 人物身体组件organ

为实现人物复杂的动画我将人物分解成不同的组件：头、身体、手、脚、脸。不同的身体组件对应不同的响应动画，并且都继承于 `OrganBase`  类，`OrganBase` 基类中包括 `init()` 函数用于初始化组件;`setFlippedX()`  函数用于翻转组件（Cocos中的翻转函数只支持图片像素上的翻转不支持图片坐标的翻转）；`MoveDelay()` 函数用于动画的延迟（用于跳跃动作）

![image-20221118144330603](./README_image/image-20221118144330603.png)

### 人物动画制作



### 11/14

蔡政特：我把游戏引擎改了，可以实现较为流畅的动作。目前实现了人物的左右移动，跳跃动作，开枪动作，子弹弹壳的关联动画（按o或者1开枪）

<img src=".\README_image\image-20221115164529684.png" alt="image-20221115164529684" style="zoom:50%;" />

<img src=".\README_image\image-20221115164721243.png" alt="image-20221115164721243" style="zoom: 50%;" />

* Cocos2d 引擎修改

  引擎痛点：引擎中自带的action只能实现固定的轨迹，再动作执行过程中无法改变对象的相对位置（比如再游戏过程中需要翻转，对应的动作不会跟着翻转）

  修改方案：在动作更新时，根据对象是否翻转情况，改变对象的坐标。以 ` MoveBy()` 举例，原引擎是在动作开始时先得到对象当前的坐标值，然后在每次更新时，计算相对于开始坐标的移动距离，更新对象的位置，问题在于 `MoveBy()` 



### 11/17

实现人物不同floor之间移动：

首先确定每个floor的边界，将所有floor的左右边界放入到  `vector<vector<float>>Floor`  中，每个floor的高度由于不同floor之间的高度是一定的，所以我们只用记录第一层floor的高度和每一层之间的高度差。

人物在不同floor之间移动的基本逻辑是,人物“跳跃‘时 `floor++`  ，人物”下降“时 `floor--`，人物”踩空“时`floor--` , 人物下降在边界外时 `floor--`，这样我们就能确定每一时刻人物对应的floor。

我们可以根据floor计算出该floor对应的高度，利用floor的高度和边界值可以得到人物的”落点区域“，当人物在空中处在下降状态时并且高度下降到floor对应的高度时，若在该floor对应的边界内时人物”落地“，若不在人物继续下降。

<img src="./README_image/image-20221118140854395.png" alt="image-20221118140854395" style="zoom:33%;" />

### 11/19

画布和平台的相对移动：



### 11/20

血迹制作



### 11/22

换枪动作
