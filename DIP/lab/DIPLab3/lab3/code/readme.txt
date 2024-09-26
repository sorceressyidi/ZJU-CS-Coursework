打开lab03 文件夹，用vscode打开其中的code文件夹，其中包含源文件`lab3.c`，头文件`DIP.h`，可执行文件`lab3mac,lab3.exe`和 24位BMP图像`flower.bmp Lena.bmp Drawings.bmp `。

（1）打开lab3.c,DIP.h,进入lab3.c，修改希望处理的图像名为`input.bmp`(如把Lena.bmp修改为input.bmp) , 点击Run Code可开始运行。输出"successfully loaded!"表示文件正常读入，「由于在DIP.h中改变了`#pragma pack alignment value`,会产生warning，但不影响程序运行」

（2）程序会输出五张处理后的图片，分别为：
* enhanced_color.bmp - 对数增强后的彩色图
* enhance_gray.bmp - 对数增强后的灰度图
* direct_equal.bmp - 直接对RGB进行直方图均衡
* gray_equal.bmp - 直接对Y进行直方图均衡
* indirect_equal.bmp - 直接对Y进行直方图均衡后转为RGB彩色图

（3）如果是Mac用户 在终端中cd进入code目录 输入 chmod +x lab3mac 为其添加执行权限，接着输入 ./lab3mac 可得到如（2）中结果

4）如果是windows用户，可运行lab3.exe,输出效果与（2）相同

