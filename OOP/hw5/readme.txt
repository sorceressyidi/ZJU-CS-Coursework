进入code文件夹
也可以用vscode等编辑器打开code文件夹



* frac.h : 该文件是分数类的头文件，包含了分数类的声明
* frac.cpp: 该文件是分数类的实现文件，包含了分数类的实现
* main.cpp:测试文件，包含了对分数类的测试
* frac.txt : 测试文件，测试分数类从文件中读取数据
* output.txt: 测试文件，测试分数类将数据输出到文件

* main_macos: 该文件是macos下编译的可执行文件
* main_win.zip : 该文件解压后得到windows下编译的可执行文件

* 运行给出的可执行文件时需要添加执行权限，如： chmod +x main.exe. chmod +x main_macos

2.使用方法:

* 进入code文件夹，打开终端，首先赋予可执行文件权限，如：chmod +x main
* 运行可执行文件，如：./main（或者./main.exe）
* 或者直接用vscode等编辑器打开code文件夹，然后运行main.cpp

* 可以在frac.txt中更改分数，然后重新运行可执行文件，查看输出结果
* 在output.txt中查看输出结果
* 注明，因为c++本身并没有把小数转换为分数的直接操作，所以采用的是构造函数进行type Conversion

原始运行结果如下：

##############################   Test    ############################
###################### Test of constructor and to_string #####################

The first fraction is: 1/2
The second fraction is: 2/3
######################## Test of copy constructor ########################

The copy of fraction1 is: 1/2
###################### Test of Arithmetic operators #######################

The sum of the two fractions is: 7/6 or 1.16667
The difference of the two fractions is: 1/-6 or -0.166667
The product of the two fractions is: 1/3 or 0.333333
The division of the two fractions is: 3/4 or 0.75
The sum of 1.414 and the first fraction  1/2  is: 957/500 or 1.914
The difference of 1.414 and the first fraction  1/2  is: 457/500 or 0.914
The product of 1.414 and the first fraction  1/2  is: 707/1000 or 0.707
The division of 1.414 and the first fraction  1/2  is: 707/250 or 2.828
######################### Test of Comparison operators #######################

The first fraction is equal to the second fraction: 0
The first fraction is not equal to the second fraction: 1
The first fraction is less than the second fraction: 1
The first fraction is greater than the second fraction: 0
The first fraction is less than or equal to the second fraction: 1
The first fraction is greater than or equal to the second fraction: 0
1.414 is equal to the first fraction: 0
1.414 is not equal to the first fraction: 1
1.414 is less than the first fraction: 0
1.414 is greater than the first fraction: 1
1.414 is less than or equal to the first fraction: 0
1.414 is greater than or equal to the first fraction: 1
##################### Test of Inserter and extractor for streams ##################

The fractions are written to the file output.txt
##################### Test of Conversion from a finite decimal string ##################