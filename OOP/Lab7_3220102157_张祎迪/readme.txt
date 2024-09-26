进入code文件夹
也可以用vscode等编辑器打开code文件夹

1.文件说明:

1.1 src文件夹
* MemoryPool.h : 内存池的实现
* MyAllocator.h : 分配器的实现

1.2 Test 文件夹
* generate_test.cpp : 生成测试数据
* test1.txt - test8.txt : 测试数据
* char.py : 生成表格

1.3 测试文件
* PTA_Test.cpp ：PTA上给出的测试代码(加上了时间的测试)
* testallocator.cpp ：老师在钉钉群里给出的测试代码(加上了时间的测试)
* TestWithFile.cpp : 从文件中读取数据进行测试(加上了时间的测试):测试数据保存在Test文件夹中

1.4 可执行文件：解压缩exec.zip得到

* PTA_Test.exe : windows下的可执行文件
* testallocator.exe : windows下的可执行文件
* TestWithFile.exe : windows下的可执行文件
* PTA_Test : macos下的可执行文件
* testallocator : macos下的可执行文件
* TestWithFile : macos下的可执行文件

2.使用方法:

* 进入code文件夹，打开终端，首先赋予可执行文件权限，如：chmod +x main
* 运行可执行文件，如：./testallocator（或者./testallocator.exe）
* 如果需要重新编译，可以使用g++进行编译，如：
    g++ -std=c++11 testallocator.cpp -o testallocator
    g++ -std=c++11 TestWithFile.cpp -o TestWithFile
    g++ -std=c++11 PTA_Test.cpp -o PTA_Test

* 注意: 如果是windows系统下编译，需要在/src/MyAllocator.h中加入 `#define _NOEXCEPT noexcept`，然后重新编译

3.测试结果示例：

3.1 PTA_Test
runtime of 10000 vector resize: 0.257214s
runtime of 10000 vector resize: 0.3275s
runtime of 1000 vector resize: 0.090667s
correct assignment in vecints: 5984
correct assignment in vecpts: 9517

3.2 testallocator
runtime of 9996 vector creation: 0.013572s
runtime of 100 vector resize: 0.0038s
incorrect assignment in vector 9999 for object (13,20)

3.3 TestWithFile
The runtime of 30000 allocate operations is 0.811911 s
The runtime of 30000 resize operations is 1.26714 s
delete OK!
The runtime of delete operations is 5.5e-05 s

4.说明：在不同的机器上运行时间可能会有所不同，但是大致在这个范围内。(我在自己的windows虚拟机运行的时间与在mac上就有所不同)