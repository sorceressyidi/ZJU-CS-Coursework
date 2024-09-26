进入code文件夹[如果使用终端命令行，需要进入code文件夹]
也可以用vscode等编辑器打开code文件夹

1.文件说明:
* create_castle.py: 该文件是一个python脚本，用于生成测试数据test_data.txt
* test_data.txt: 该文件包含了测试数据，用于测试程序
* main.cpp: 该文件包含程序的主函数，是程序的入口点
* castle.h: 该文件包含了castle类的声明
* castle.cpp: 该文件包含了castle类的实现
* main.exe.zip: 解压后得到main.exe 该可执行文件是在Windows环境下编译的程序
* main_macos: 该可执行文件是在苹果操作系统环境下编译的程序
* 运行给出的可执行文件时需要添加执行全县，如： chmod +x main.exe. chmod +x main_macos

1.1 测试文件说明

* test_data.txt: 该文件包含了一个测试文件样例，可以用create_castle.py生成其他
* 该测试文件保证:
(1) 随机生成 5 - 18 个不同房间 （可在.py文件中修改参数）
(2) Monster 和 Princess room 一定存在，且不在Lobby，且不在一个room
(3) Lobby一定可以达到Princess room，Princess room一定可以到达Monster room

2.编译命令:

* 要编译该程序，请使用以下命令:
* g++ main.cpp student.cpp -o main
* 该命令将main.cpp文件与student1.cpp文件一起编译，并创建一个名为main的可执行文件。

* 也给出了makefile，可以直接打开文件夹并输入命令 make

3.使用方法:

* 编译程序后，运行可执行文件main，(./main)可看到输出结果 （注意授予运行权限 chmod +x)
* 如果输入的格式不符合(即不是go east,west,up,down)，会提示重新输入
* 下面是两个示例输出:

3.1
You are in the Lobby. There are 2 exits: down east 
Which way do you want to go?  go down
You are in the Barn. There are 3 exits: up east west 
Which way do you want to go?  go up
You are in the Workshop. There are 2 exits: down east 
Which way do you want to go?  go east
You are in the Vivarium. There are 3 exits: down east west 
Which way do you want to go?  go west
You are in the Gazebo. There are 3 exits: up east west 
Which way do you want to go?  go up
You are in the Vineyard. Oh no!You are eaten by the monster!
Game Over!

3.2
You are in the Lobby. There are 2 exits: down east 
Which way do you want to go?  as sdas
Invalid move,Try again:go north
Invalid move,Try again:go east
You are in the Den. There are 4 exits: up down east west 
Which way do you want to go?  go east
You are in the Habitat. Congratulations!You found the princess
Princess:Oh,my hero!Please take me out of here!Remeber the only way out is the LOBBY!Be aware of the MONSTER!
You:Don't worry!Let's go!

There are 4 exits: up down east west 
Which way do you want to go?  go up
You are in the Gallery. There are 3 exits: up down east 
Which way do you want to go?  go down
You are in the Gazebo. There are 3 exits: up east west 
Which way do you want to go?  go up
You are in the Vineyard. Oh no!You are eaten by the monster!
Game Over!

