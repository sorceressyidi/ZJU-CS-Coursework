进入code文件夹
也可以用vscode等编辑器打开code文件夹

1.文件说明:
* vector.h: 该文件是vector类的头文件，包含了vector类的声明
* vector.cpp: 该文件是vector类的实现文件，包含了vector类的实现
* main.cpp:测试文件，vector类的测试文件
* main_macos: 该文件是macos下编译的可执行文件
* main_win.zip : 该文件解压后得到windows下编译的可执行文件

* 运行给出的可执行文件时需要添加执行权限，如： chmod +x main.exe. chmod +x main_macos

2.使用方法:

* 进入code文件夹，打开终端，首先赋予可执行文件权限，如：chmod +x main
* 运行可执行文件，如：./main（或者./main.exe）
* 或者直接用vscode等编辑器打开code文件夹，然后运行main.cpp

注明：为了方便检测，我在构造函数、析构函数、拷贝构造函数、inflate函数中添加了输出语句，以便检测程序的运行情况如：
* cout << "Default Constructor called" << endl;
* cout << "Copy Constructor called" << endl;
* cout << "Destructor called" << endl;
* cout << "Inflate called" << endl;
* Constructor called(with size) 

原始运行结果如下：

Default Constructor called
Inflate called
Inflate called
Inflate called
########  Test for push_back(constructor to create an empty vector) #######
v[0] = 1
v[1] = 2
v[2] = 3
#############  Test for operator []  ############
v[0] = 2
v[1] = 3
v[2] = 4
#############  Test for clear() and empty()  ############
Whether the vector is empty after clear operation: 1
Whether the vector is empty after push_back 0
#############  Test for at  ############
Index out of range
#############  Test for ctor(and size and inflate)  ############
Constructor called(with size) 
size: 5
Inflate called
size after push_back(1): 6
v2[0] = 0
v2[1] = 0
v2[2] = 0
v2[3] = 0
v2[4] = 0
v2[5] = 1
v2[6] = 2
v2[7] = 3
v2[8] = 4
v2[9] = 5

Copy Constructor called
v3 is a copy of v2
v3[0] = 0
v3[1] = 0
v3[2] = 0
v3[3] = 0
v3[4] = 0
v3[5] = 1
v3[6] = 2
v3[7] = 3
v3[8] = 4
v3[9] = 5
#############  Test for dtor  ############
Destructor will be called after this line
Destructor called
Destructor called
Destructor called