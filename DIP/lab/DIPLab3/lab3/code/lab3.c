#include<stdio.h>
#include "DIP.h"
#include<stdlib.h>
#include<math.h>
// 使用#pragma pack(1)指令设置结构体的字节对齐方式为1字节
#pragma pack(1)
double RED[256]={0};
double GREEN[256]={0};
double BLUE[256]={0};
double GRAY[256]={0};

void enhance(BMP bmp);
void Equal(BMP bmp);
void histogram(BMP bmp);
int main(){
    
    BMP bmp = ReadBMP();
    int width = bmp.bmpih.width; // 获取图像的宽度
    int height = bmp.bmpih.height; // 获取图像的高度
    enhance(bmp);
    Equal(bmp);
    free(bmp.bitmap);
    return 0;
}

void enhance(BMP bmp){
    // 创建一个新的BMP对象 enhanced，用于存储增强后的彩色图像
    BMP enhanced;
    // 复制输入BMP对象的内容到enhanced
    memcpy(&enhanced, &bmp, sizeof(enhanced));
    // 为enhanced分配内存以存储图像数据
    enhanced.bitmap = (byte *)calloc(enhanced.bmpih.imageSize , sizeof(byte));

    // 创建另一个BMP对象 enhanced_gray，用于处理灰度版本的图像
    BMP enhanced_gray;

    // 获取原始图像的高度和宽度
    int height = bmp.bmpih.height;
    int width = bmp.bmpih.width;

    // 计算原始图像每行的字节数和将宽度调整到4的倍数
    int old_byte = (3 * width + 3) / 4 * 4;
    int row = (width + 3) / 4 * 4;

    // 复制输入BMP对象的内容到enhanced_gray
    memcpy(&enhanced_gray, &bmp, sizeof(enhanced_gray));

    // 设置enhanced_gray的相关属性，将其转换为灰度图像
    enhanced_gray.bmph.bfOffset = 256 * 4 + HEADERSIZE;
    enhanced_gray.bmpih.bitCount = 8;
    enhanced_gray.bmpih.imageSize = height * row;
    enhanced_gray.bmph.bfSize = enhanced_gray.bmpih.imageSize + enhanced_gray.bmph.bfOffset;
    // 为enhanced_gray分配内存以存储图像数据
    enhanced_gray.bitmap = (byte*)calloc(enhanced_gray.bmpih.imageSize, sizeof(byte));

    // 初始化一个变量 max，用于存储亮度的最大值
    double max = 0.0;

    // 设置256级灰度颜色表
    for (int i = 0; i < 256; i++) {
        enhanced_gray.colours[i].blue = i;
        enhanced_gray.colours[i].green = i;
        enhanced_gray.colours[i].red = i;
    }

    // 计算原始图像中的最大亮度值
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int posi = i * old_byte + j * 3;
            double B = bmp.bitmap[posi];
            double G = bmp.bitmap[posi + 1];
            double R = bmp.bitmap[posi + 2];
            double Y, U, V;
            RGB_YUV(R, G, B, &Y, &U, &V);
            // 如果Y的值大于max，更新max
            if (Y > max) {
                max = Y;
            }
        }
    }

    // 遍历原始图像的每个像素，执行亮度增强
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int posi = i * old_byte + j * 3;
            int posi2 = i * row + j;
            double B = bmp.bitmap[posi];
            double G = bmp.bitmap[posi + 1];
            double R = bmp.bitmap[posi + 2];
            double Y, U, V;
            RGB_YUV(R, G, B, &Y, &U, &V);
            // 计算新的亮度值Y1，使用对数运算和调整函数
            double Y1 = log(Y + 1) / log(max + 1) * 255;
            Adjust(&Y1);
            // 将Y1作为灰度值存储到enhanced_gray图像中
            enhanced_gray.bitmap[posi2] = Y1;
            // 更新Y值并将YUV颜色转换回RGB颜色
            Y = Y1;
            YUV_RGB(Y, U, V, &R, &G, &B);
            Adjust(&R);
            Adjust(&G);
            Adjust(&B);
            // 存储调整后的RGB值到enhanced图像中
            enhanced.bitmap[posi] = B;
            enhanced.bitmap[posi + 1] = G;
            enhanced.bitmap[posi + 2] = R;
        }
    }

    // 将增强后的彩色图像和灰度图像分别保存为BMP文件
    FILE* fp = fopen("enhanced_color.bmp", "wb");
    OUTPUT(&enhanced, fp);
    fp = fopen("enhance_gray.bmp", "wb");
    OUTPUT(&enhanced_gray, fp);

    // 释放分配的内存
    free(enhanced.bitmap);
    free(enhanced_gray.bitmap);
}

void histogram(BMP bmp) {
    // 获取原始图像的高度和宽度
    int height = bmp.bmpih.height;
    int width = bmp.bmpih.width;

    // 计算图像的总像素数量
    int size = height * width;

    // 计算每行的字节数，将宽度调整到4的倍数
    int row_byte = (width * 3 + 3) / 4 * 4;

    // 遍历原始图像的每个像素，以计算直方图
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // 计算当前像素在图像数据中的位置
            int posi = i * row_byte + j * 3;

            // 获取当前像素的RGB颜色分量
            double B = bmp.bitmap[posi];
            double G = bmp.bitmap[posi + 1];
            double R = bmp.bitmap[posi + 2];

            // 将RGB颜色转换为亮度YUV颜色空间
            double Y, U, V;
            RGB_YUV(R, G, B, &Y, &U, &V);

            // 调整亮度值Y
            Adjust(&Y); 
            // 将像素的RGB分量值分别添加到相应的颜色通道的直方图中
            RED[(int)R] += 1.0;
            GREEN[(int)G] += 1.0;
            BLUE[(int)B] += 1.0;

            // 将像素的亮度值Y添加到灰度通道的直方图中
            GRAY[(int)Y] += 1.0;
        }
    }
}

void Equal(BMP bmp) {
    // 调用 histogram 函数计算原始图像的直方图
    histogram(bmp);

    // 创建数组 s、sR、sG 和 sB 以存储累积概率分布
    double s[256];
    double sR[256];
    double sG[256];
    double sB[256];

    // 获取原始图像的高度和宽度
    int height = bmp.bmpih.height;
    int width = bmp.bmpih.width;

    // 计算图像的总像素数量
    int size = height * width;

    // 计算每行的字节数，将宽度调整到4的倍数
    int row_byte = (width * 3 + 3) / 4 * 4;
    int row = (width + 3) / 4 * 4;

    // 初始化累积概率分布数组的第一个元素
    s[0] = GRAY[0] / size;
    sR[0] = RED[0] / size;
    sG[0] = GREEN[0] / size;
    sB[0] = BLUE[0] / size;

    // 计算累积概率分布数组的其他元素
    for (int i = 1; i < 256; i++) {
        s[i] = s[i - 1] + GRAY[i] / size;
        sR[i] = sR[i - 1] + RED[i] / size;
        sG[i] = sG[i -1] + GREEN[i] / size;
        sB[i] = sB[i -1] + BLUE[i] / size;
    }

    // 创建一个新的BMP对象 direct，用于存储直方图均衡化后的彩色图像
    BMP direct;
    // 复制输入BMP对象的内容到direct
    memcpy(&direct, &bmp, sizeof(direct));
    // 为direct分配内存以存储图像数据
    direct.bitmap = (byte*)calloc(direct.bmpih.imageSize, sizeof(byte));

    // 创建灰度变换后的图像
    BMP gray = Gray_Transform(bmp, height, width);

    // 遍历原始图像的每个像素，进行直方图均衡化
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // 计算当前像素在图像数据中的位置
            int posi = row_byte * i + j * 3;

            // 获取当前像素的RGB颜色分量
            double B = bmp.bitmap[posi];
            double G = bmp.bitmap[posi + 1];
            double R = bmp.bitmap[posi + 2];
            double Y, U, V;
            RGB_YUV(R, G, B, &Y, &U, &V);

            // 调整亮度值Y
            Adjust(&Y);

            // 计算直方图均衡化后的像素值并存储到对应的图像中
            gray.bitmap[row * i + j] = s[(int)Y] * 255;
            direct.bitmap[posi] = sB[(int)B] * 255;
            direct.bitmap[posi + 1] = sG[(int)G] * 255;
            direct.bitmap[posi + 2] = sR[(int)R] * 255;

            // 调整RGB颜色并存储到原始图像中
            Y = s[(int)Y] * 255;
            YUV_RGB(Y, U, V, &R, &G, &B);
            Adjust(&R);
            Adjust(&G);
            Adjust(&B);
            bmp.bitmap[posi] = B;
            bmp.bitmap[posi + 1] = G;
            bmp.bitmap[posi + 2] = R;
        }
    }

    // 将增强后的灰度图像保存为文件
    FILE* fp = fopen("gray_equal.bmp", "wb");
    OUTPUT(&gray, fp);

    // 将增强后的彩色图像保存为文件
    fp = fopen("direct_equal.bmp", "wb");
    OUTPUT(&direct, fp);

    // 将增强后的原始彩色图像保存为文件
    fp = fopen("indirect_equal.bmp", "wb");
    OUTPUT(&bmp, fp);

    // 释放分配的内存
    free(direct.bitmap);
    free(gray.bitmap);
}

