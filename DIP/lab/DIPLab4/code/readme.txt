打开lab04 文件夹，用vscode打开其中的code文件夹，其中包含源文件 lab4.c ，头文件 DIP.h ，可执行文件 lab4mac,lab4.exe 和24位BMP图 像 Lena.bmp 

(1)打开lab4.c,DIP.h,进入lab4.c，修改希望处理的图像名为 input.bmp (如把Lena.bmp修改为input.bmp) , 点击Run Code可开始运行。输 出"successfully loaded!"表示文件正常读入，「由于在DIP.h中改变了 #pragma pack alignment value ,会产生warning，但不影响程序运行」

* 代码中注释掉了对灰度图进行几何变化的代码，如果想观察效果可以uncomment后运行
* 在 What's the translation on the x axis? 后输入在x轴的平移量
* 在 What's the translation on the y axis? 后输入在y轴的平移量
* 在 What's the rotation angle?后输入旋转的角度(正值为逆时针)
* 在 What's the scale on the x axis? What's the scale on the y axis? 后分别输入x轴 y轴上的缩放比例(1为大小不变)
* 在 What's affine dx on the x axis? What's the affine dy on the y axis?后分别输入x轴，y轴上由于剪切变换的单位平移量(在0.1-0.3附近 生成图像好观察)
* 在 What's the mirrow axis?(1 for x and 0 for y) 后输入对称轴(1为x轴 0为y轴)

(2) 如果是Mac用户 在终端中cd进入code目录 输入 chmod +x lab4mac 为其添加执行权限，接着输入 ./lab4mac 可得到如(2)中结果 

(3)如果是windows用户，可运行lab4.exe,输出效果与(2)相同
