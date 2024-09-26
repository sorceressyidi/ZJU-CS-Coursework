进入code文件夹
也可以用vscode等编辑器打开code文件夹

1.文件说明:
* entity.h: 该文件包含了entity类的声明
* entity.cpp: 该文件包含了entity类的实现
* diary.h: 该文件包含了diary类的声明
* diary.cpp: 该文件包含了diary类的实现
* pdadd.cpp: 实现向日记本中添加记录的功能
* pdlist.cpp: 实现列出日记本中记录的功能
* pdremove.cpp: 实现删除日记本中记录的功能
* pdshow.cpp: 实现显示日记本中记录的功能

* diary.txt: 该文件是日记本的存储文件，用于存储日记记录

* pdadd: 该可执行文件是在苹果操作系统环境下编译的程序
* pdlist: 该可执行文件是在苹果操作系统环境下编译的程序
* pdremove: 该可执行文件是在苹果操作系统环境下编译的程序
* pdshow: 该可执行文件是在苹果操作系统环境下编译的程序

win_exe.zip 中包含了windows下编译的可执行文件:
* pdadd.exe 
* pdlist.exe
* pdremove.exe
* pdshow.exe

* persnoal_diary.sh: 给出了对diary的操作的shell脚本

* 运行给出的可执行文件时需要添加执行全县，如： chmod +x main.exe. chmod +x main_macos

2.编译命令:
* 给出了makefile，可以直接打开文件夹并输入命令 make

3.使用方法:

* 进入code文件夹，打开终端，首先赋予可执行文件权限，如：chmod +x pdadd
* 运行可执行文件，如：./pdadd（或者./pdadd.exe）
* 根据提示输入内容，具体如下：

3.1 pdadd

*************************************************
Welcome to add content to a diary.
There are a few rules to follow:
1. The date must be in the format: xxxx xx xx
2. The content must end with a line '.'
3. To exit, enter 0 0 0
4. To end the program, press Ctrl-D
(The already input diary will be saved to 'diary.txt')
5. The diary will be saved to 'diary.txt'
*************************************************
如上，程序开始给出了提示，下面是更具体的说明：
* 输入日记内容，以单独一行的'.'结束当前记录内容，之后可以继续添加记录
* 输入日期，以单独一行的'0 0 0'结束输入，之后不再添加记录
* 输入Ctrl-D结束程序，之后不再添加记录

具体来说，如果要输入一条记录，格式为:(当然以Ctrl-D直接结束也可以)
*************************************************
2004 04 10
Today is my BIRTHDAY!
Happy~
.
*************************************************


3.2 pdlist
* 如果使用./pdlist_macos或./pdlist.exe，会列出所有的日记记录
* 如果使用./pdlist_macos 2004 04 10 2034 02 12 或者./pdlist.exe 2004 04 10 2034 02 12，会列出2004年4月10日到2034年2月12日之间的所有日记记录

3.3 pdremove

*************************************************
Welcome to show content of a diary. PLZ input date you want to remove:
There are a few rules to follow:
1. The date must be in the format: xxxx xx xx
2. To exit, enter -1
3. You should confirm the content you want to delete
*************************************************
如上，程序开始给出了提示，下面是更具体的说明：
* 输入日期，以单独一行的'xxxx xx xx'结束输入，之后会列出该日期的所有日记记录
* 输入-1结束程序，之后不再删除记录
* 输入要删除的记录的序号，之后会删除该记录

3.4 pdshow

*************************************************
Welcome to show content of a diary.
There are a few rules to follow:
1. The date must be in the format: xxxx xx xx
2. To exit, enter -1
*************************************************
如上，程序开始给出了提示，下面是更具体的说明：
* 输入日期，以单独一行的'xxxx xx xx'结束输入，之后会列出该日期的日记记录
* 输入-1结束程序，之后不再显示记录

* 同时，程序保证如果有多个日记记录的日期相同，均会显示，下面为一个例子
*************************************************
Welcome to show content of a diary.
There are a few rules to follow:
1. The date must be in the format: xxxx xx xx
2. To exit, enter -1
*************************************************
2004 04 10

Today is my BIRTHDAY!
Happy~

(Repeated Test~)

4.脚本
* 在 code 文件夹中，给出了一个shell脚本，可以直接运行，如下：
./personal_diary.sh pdadd
./personal_diary.sh pdlist
./personal_diary.sh pdremove
./personal_diary.sh pdshow
* 也可以直接运行./personal_diary.sh，然后根据提示输入相应的命令
* 该脚本会自动给出提示，根据提示输入相应的命令即可  

