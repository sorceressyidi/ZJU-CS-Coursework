打开DIPlab5 文件夹，用vscode打开其中的code文件夹，其中包含源文件lab5.c，头文件DIP.h，可执行文件lab5mac,lab5.exe 和24位BMP图像Lena.bmp moon.bmp moon2.bmp	 

(1）打开lab5.c,DIP.h,进入lab5.c，修改希望处理的图像名为input.bmp(如把Lena.bmp修改为input.bmp) , 点击Run Code可开始运行。输出"successfully loaded!"表示文件正常读入，「由于在DIP.h中改变了#pragma pack alignment value,会产生warning，但不影响程序运行」

* 在源码中，注释掉了转为灰度图后处理的情况，如果要观察结果，可uncomment后运行即可。
* 在“请输入滤波窗口的大小:” 后输入滤波窗口的边长
* 程序会输出五张处理后的图片，分别为：
   * mean.bmp 	  :对图像进行均值滤波产生的图像
   * lap1.bmp 	  :以第一种滤波窗口对图像进行滤波得到的图像
   * sharpen1.bmp :以第一种滤波窗口对图像进行拉普拉斯锐化得到的图像
   * lap2.bmp 	  :以第二种滤波窗口对图像进行滤波得到的图像
   * sharpen2.bmp :以第二种滤波窗口对图像进行拉普拉斯锐化得到的图像

(2）如果是Mac用户 在终端中cd进入code目录 输入 chmod +x lab5mac 为其添加执行权限，接着输入 ./lab5mac 可得到如（1）中结果
(3）如果是windows用户，可运行lab5.exe,输出效果与（2）相同

