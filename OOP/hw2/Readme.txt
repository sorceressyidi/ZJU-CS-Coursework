进入code文件夹[如果使用终端命令行，需要进入code文件夹]
也可以用vscode等编辑器打开code文件夹

1.文件说明:
* main.cpp: 该文件包含程序的主函数，是程序的入口点
* student.cpp: 该文件包含了Student类方法的实现
* student.h: 该头文件声明了Student类及其成员变量和函数原型。它还包括了必要的头文件，并定义了程序中使用的常量值。
* main.exe.zip: 解压后得到main.exe 该可执行文件是在Windows环境下编译的程序
* main_macos: 该可执行文件是在苹果操作系统环境下编译的程序
* 运行给出的可执行文件时需要添加执行全县，如： chmod +x main.exe. chmod +x main_macos

2.编译命令:

* 要编译该程序，请使用以下命令:
* g++ main.cpp student.cpp -o main
* 该命令将main.cpp文件与student1.cpp文件一起编译，并创建一个名为main的可执行文件。

* 也给出了makefile，可以直接打开文件夹并输入命令 make

3.使用方法:

* 编译程序后，运行可执行文件main，可看到输出结果

4.预期结果 ：     

* 该程序将读取student.txt文件中的数据，并计算每个学生的平均分数。然后，它将输出每个学生的平均分数，以及所有学生的平均分数，最低分数和最高分数。
* 如果某学生未选择某科目，则用None表示
* 如果某学生的某科目成绩为None，则该科目不计入平均分计算

no      name    Chinese Math    English Physics Biology History Chemis  average
1       Amy     1       3       1       5       4       3       None    2.83333
2       Bob     4       1       2       5       2       3       3       2.85714
3       Charles 3       5       5       1       3       5       5       3.85714
4       Daisy   3       5       2       4       5       2       1       3.14286
5       Elize   5       None    5       3       3       4       3       3.83333
6       Peter   2       1       3       2       4       4       5       3
7       Tom     1       3       3       5       2       5       4       3.28571
8       John    4       3       1       None    3       3       2       2.66667
9       Harry   3       2       3       3       5       1       5       3.14286
        average 2.88889 2.55556 2.77778 3.11111 3.44444 3.33333 3.11111
        min     1       1       1       1       2       1       1
        max     5       5       5       5       5       5       5       