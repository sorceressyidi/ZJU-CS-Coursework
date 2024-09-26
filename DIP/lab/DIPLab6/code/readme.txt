打开lab06 文件夹，用vscode打开其中的code文件夹，其中包含源文件lab6.c，头文件DIP.h，可执行文件lab6mac,lab6.exe和24位BMP图像 Lena.bmp , cat.bmp。

（1）打开lab6.c,DIP.h,进入lab6.c，修改希望处理的图像名为input.bmp(如把Lena.bmp修改为input.bmp) , 点击Run Code可开始运行。输出"successfully loaded!"表示文件正常读入，「由于在DIP.h中改变了`#pragma pack alignment value`,会产生warning，但不影响程序运行」

 * 在 What's the value of sigma r?  后输入双边滤波的参数sigma_r
 * 在 What's the size of the window? 后输入滤波窗口的边长

（2）程序会输出双边滤波处理后的图片 bilateral.bmp

（3）如果是Mac用户，在终端中cd进入code目录，输入 `chmod +x lab6mac`  为其添加执行权限，接着输入 `./lab6mac` 可得到如(2)中结果 

（4）如果是windows用户，可运行lab6.exe,输出效果与(2)相同
