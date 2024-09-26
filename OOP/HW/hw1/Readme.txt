文件说明:
* main.cpp: 该文件包含程序的主函数，是程序的入口点
* student1.cpp: 该文件包含了Student类方法的实现
* student1.h: 该头文件声明了Student类及其成员变量和函数原型。它还包括了必要的头文件，并定义了程序中使用的常量值。
* main.exe: 该可执行文件是在Windows环境下编译的程序
* main_macos: 该可执行文件是在苹果操作系统环境下编译的程序
* 运行给出的可执行文件时需要添加执行全县，如： chmod +x main.exe. chmod +x main_macos
编译命令:
* 要编译该程序，请使用以下命令:
* g++ main.cpp student1.cpp -o main
* 该命令将main.cpp文件与student1.cpp文件一起编译，并创建一个名为main的可执行文件。

* 也给出了makefile，可以直接打开文件夹并输入命令 make

使用方法:
* 编译程序后，运行可执行文件main，可看到输出结果

预期结果 ：

no	name	score1	score2	score3	average	
1	K.Weng	5	5	5	5
2	T.Dixon	4	3	2	3
3	V.Chu	3	4	5	4
4	L.Tson	4	3	4	3.66667
5	L.Lee	3	4	3	3.33333
6	I.Young	4	2	5	3.66667
7	K.Hiro	4	2	1	2.33333
8	G.Ping	4	4	4	4
9	H.Gu	2	3	4	3
10	J.Jon	5	4	3	4
	average	3.8	3.4	3.6	
	min	2	2	1	
	max	5	5	5	