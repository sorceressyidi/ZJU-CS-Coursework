#include<stdio.h>
#include<string.h>
#include "DIP.h"
#include<math.h>
void bilateral(BMP bmp,int scale,double r);
double Gauss(double delta,double sigma);
int main(){
    BMP bmp = ReadBMP();
    BMP gray = Gray_Transform(bmp,bmp.bmpih.height,bmp.bmpih.width);
    printf("What's the value of sigma r?");
    double r;
    scanf("%lf",&r);
    printf("What's the size of the window?");
    int size;
    scanf("%d",&size);
    bilateral(bmp,size,r);
    //bilateral(gray,size,r);
    return 0;
}
double Gauss(double delta,double sigma){
    double result = exp(-delta/(2*sigma*sigma));
    return result;
}
void bilateral(BMP bmp, int scale, double r) {
    // 创建一个新的BMP结构体，用于存储双边滤波后的结果
    BMP bilateral;
    memcpy(&bilateral, &bmp, sizeof(bilateral));

    // 计算窗口大小的一半和高斯标准差
    int window = scale / 2;
    double sx = 0.25 * ((bilateral.bmpih.height - 1) * 0.5 - 1) + 0.8;
    double sy = 0.25 * ((bilateral.bmpih.width - 1) * 0.5 - 1) + 0.8;
    double s = (sx + sy) / 2;

    // 获取位图的宽度、高度和每行字节数
    int width = bilateral.bmpih.width;
    int height = bilateral.bmpih.height;
    int row = (bilateral.bmpih.bitCount / 8 * width + 3) / 4 * 4;

    // 分配内存用于存储双边滤波后的位图数据
    bilateral.bitmap = (byte*)malloc(height * row * sizeof(byte));

    // 循环遍历图像的每个像素
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (bilateral.bmpih.bitCount == 24) {
                // 对于24位图像，分别处理每个通道的双边滤波
                double Bsum = 0;
                double Gsum = 0;
                double Rsum = 0;
                int posi = i * row + j * 3;

                // 获取当前像素的B、G、R值
                double B = bmp.bitmap[posi];
                double G = bmp.bitmap[posi + 1];
                double R = bmp.bitmap[posi + 2];

                double WB = 0;
                double WG = 0;
                double WR = 0;

                // 遍历窗口内的像素
                for (int p = i - window; p <= i + window; p++) {
                    for (int q = j - window; q <= j + window; q++) {
                        int x, y;
                        x = p * row;
                        y = q * 3;

                        // 处理边界情况，确保索引不越界
                        if (p < 0) { x = 0; }
                        if (q < 0) { y = 0; }
                        if (p >= height) { x = (height - 1) * row; }
                        if (q >= width) { y = (width - 1) * 3; }

                        // 计算相邻像素的索引
                        int posi1 = x + y;

                        // 获取相邻像素的B、G、R值
                        double B1 = bmp.bitmap[posi1];
                        double G1 = bmp.bitmap[posi1 + 1];
                        double R1 = bmp.bitmap[posi1 + 2];

                        // 计算高斯权重
                        double Gauss_Dist = Gauss((p - i) * (p - i) + (q - j) * (q - j), s);
                        double Gauss_BiB = Gauss((B1 - B) * (B1 - B), r);
                        double Gauss_BiG = Gauss((G1 - G) * (G1 - G), r);
                        double Gauss_BiR = Gauss((R1 - R) * (R1 - R), r);

                        // 累加权重和
                        WB += Gauss_Dist * Gauss_BiB;
                        WG += Gauss_Dist * Gauss_BiG;
                        WR += Gauss_Dist * Gauss_BiR;

                        // 累加加权后的像素值
                        Bsum += Gauss_Dist * Gauss_BiB * B1;
                        Gsum += Gauss_Dist * Gauss_BiG * G1;
                        Rsum += Gauss_Dist * Gauss_BiR * R1;
                    }
                }

                // 更新双边滤波后的像素值
                bilateral.bitmap[posi] = Bsum / WB;
                bilateral.bitmap[posi + 1] = Gsum / WG;
                bilateral.bitmap[posi + 2] = Rsum / WR;
            } else {
                // 处理其他位深度的图像（暂未实现）

                // 初始化变量用于存储像素值和权重
                double sum = 0;
                int posi = i * row + j * 3;
                double Pix = bmp.bitmap[posi];
                double W = 0;

                // 遍历窗口内的像素
                for (int p = i - window; p <= i + window; p++) {
                    for (int q = j - window; q <= j + window; q++) {
                        int x, y;
                        x = p * row;
                        y = q * 3;

                        // 处理边界情况，确保索引不越界
                        if (p < 0) { x = 0; }
                        if (q < 0) { y = 0; }
                        if (p >= height) { x = (height - 1) * row; }
                        if (q >= width) { y = (width - 1) * 3; }

                        // 计算相邻像素的索引
                        int posi1 = x + y;

                        // 获取相邻像素的值
                        double Pix1 = bmp.bitmap[posi1];

                        // 计算高斯权重
                        double Gauss_Dist = Gauss((p - i) * (p - i) + (q - j) * (q - j), s);
                        double Gauss_Pix = Gauss((Pix1 - Pix) * (Pix1 - Pix), r);

                        // 累加权重和
                        W += Gauss_Dist * Gauss_Pix;
                        sum += Gauss_Dist * Gauss_Pix * Pix1;
                    }
                }

                // 更新双边滤波后的像素值
                bilateral.bitmap[posi] = sum / W;
            }
        }
    }

    // 将双边滤波后的结果写入文件
    FILE* fp = fopen("bilateral.bmp", "wb");
    OUTPUT(&bilateral, fp);

    // 释放内存
    free(bilateral.bitmap);
}
