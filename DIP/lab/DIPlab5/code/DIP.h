#include <stdio.h>
#include <stdlib.h>
#include<string.h>


#pragma pack(1)
// 定义BMP文件头的大小为54个字节，通常情况下固定不变
#define HEADERSIZE 54

// 定义几种不同数据类型的别名，以便在代码中使用更具可读性的名称
typedef unsigned char byte;
typedef unsigned short word;
typedef unsigned int dword;


// 定义BMP文件头的结构体
typedef struct {
    word bfType;          // BMP文件的类型标识，通常为"BM"
    dword bfSize;         // BMP文件的大小，以字节为单位
    word reserved1;       // 保留字段，设置为0
    word reserved2;       // 保留字段，设置为0
    dword bfOffset;       // 位图数据的偏移量，即文件头的大小
} BMPHeader;

// 定义BMP信息头的结构体
typedef struct {
    dword size;           // 信息头的大小，通常为40字节
    int width;            // 图像的宽度，以像素为单位
    int height;           // 图像的高度，以像素为单位
    word planes;          // 颜色平面数，通常为1
    word bitCount;        // 每个像素的位数
    dword compression;    // 压缩类型
    dword imageSize;      // 位图数据的大小，以字节为单位
    int xPixelsPerMeter;  // 水平分辨率，每米的像素数
    int yPixelsPerMeter;  // 垂直分辨率，每米的像素数
    dword colorsUsed;     // 使用的颜色数
    dword colorsImportant; // 重要颜色数
} BMPInfoHeader;

// 定义调色板中的一个颜色的结构体
typedef struct {
    byte blue;     // 蓝色分量
    byte green;    // 绿色分量
    byte red;      // 红色分量
    byte reserved; // 保留字段，通常设置为0
} pallete;

// 定义包含BMP文件头、BMP信息头、调色板和位图数据的完整BMP图像的结构体
typedef struct {
    BMPHeader bmph;         // BMP文件头
    BMPInfoHeader bmpih;    // BMP信息头
    pallete colours[256];   // 调色板，通常用于8位颜色索引图像
    byte *bitmap;           // 位图数据
} BMP;

void RGB_YUV(double R,double G,double B,double* Y,double* U,double* V);
void YUV_RGB(double Y,double U,double V,double* R,double* G,double* B);
BMP Gray_Transform(BMP bmp,int height,int width);
void Brightness_Transform(BMP bmp,int height,int width);
void Adjust(double* x);
void OUTPUT (BMP *bmp, FILE *fp);
BMP ReadBMP(){
    BMP bmp;
    // 打开名为"input.bmp"的BMP文件以读取二进制数据
    FILE *inputFile = fopen("input.bmp", "rb");
    
    // 检查文件是否成功打开
    if (!inputFile) {
        printf("Unable to open input BMP file.\n"); // 输出错误信息
        return bmp; // 退出程序
    }
    
    printf("successfully loaded!\n"); // 成功加载的提示信息

    // 从文件中读取BMP文件头和信息头
    fread(&(bmp), HEADERSIZE, 1, inputFile);
    int width = bmp.bmpih.width; // 获取图像的宽度
    int height = bmp.bmpih.height; // 获取图像的高度
    // 如果图像大小为0，则计算图像数据大小
    if (bmp.bmpih.imageSize == 0) {
        bmp.bmpih.imageSize = bmp.bmph.bfSize - bmp.bmph.bfOffset;
    }

    // 为位图数据分配内存
    bmp.bitmap = (byte*)malloc(sizeof(byte) * (bmp.bmph.bfSize - HEADERSIZE));

    // 从文件中读取位图数据
    fread(bmp.bitmap, bmp.bmph.bfSize - HEADERSIZE, 1, inputFile);
    fclose(inputFile); // 关闭文件
    return bmp;
}

void RGB_YUV(double R,double G,double B,double* Y,double* U,double* V){
    *Y=0.299*R + 0.587*G+0.114*B;
    *U = -0.147*R-0.289*G+0.435*B;
    *V = 0.615*R-0.515*G-0.100*B;
}


BMP Gray_Transform(BMP bmp, int height, int width) {
    BMP Gbmp; // 创建一个新的BMP结构体用于存储灰度图像
    int row = (width + 3) / 4 * 4; // 计算每行像素数据的字节数，确保按4字节对齐
    // 复制原始BMP的文件头和信息头到Gbmp
    memcpy(&Gbmp, &bmp, HEADERSIZE);
    Gbmp.bmpih.bitCount = 8; // 设置位图的位深度为8位
    Gbmp.bmph.bfOffset = 256 * 4 + HEADERSIZE; // 计算新的数据偏移量
    Gbmp.bmpih.imageSize = height * row; // 计算新的图像数据大小
    Gbmp.bmph.bfSize = Gbmp.bmpih.imageSize + Gbmp.bmph.bfOffset; // 计算新的文件大小
    // 为新的位图数据分配内存并初始化
    Gbmp.bitmap = (byte*)malloc(Gbmp.bmpih.imageSize * sizeof(byte));
    // 初始化灰度调色板，将RGB值与索引关联
    for (int i = 0; i < 256; i++) {
        Gbmp.colours[i].blue = i;
        Gbmp.colours[i].green = i;
        Gbmp.colours[i].red = i;
    }
    int old_byte = (3 * width + 3) / 4 * 4; // 计算每行原始像素数据的字节数
    // 遍历原始图像像素，计算YUV值并填充到新的位图数据中
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int cnt = i * old_byte + j * 3;
            double B = bmp.bitmap[cnt];
            double G = bmp.bitmap[cnt + 1];
            double R = bmp.bitmap[cnt + 2];
            double Y, U, V;
            RGB_YUV(R, G, B, &Y, &U, &V);
            Adjust(&Y);//防止Y越界
            Gbmp.bitmap[row * i + j] = Y;
        }
    }
    return Gbmp;
}

void YUV_RGB(double Y,double U,double V,double* R,double* G,double* B){
   *R = Y+1.3707*V;
   *G = Y-0.3376*V-0.6980*U;
   *B = Y+1.7324*U;  
}

void Brightness_Transform(BMP bmp, int height, int width) {
    int row = (3 * width + 3) / 4 * 4; // 计算每行像素数据的字节数，确保按4字节对齐
    // 遍历图像的每个像素
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int cnt = i * row + j * 3; // 计算当前像素在位图数据中的偏移量
            // 获取当前像素的RGB值并将其转换为YUV颜色空间
            double B = bmp.bitmap[cnt];
            double G = bmp.bitmap[cnt + 1];
            double R = bmp.bitmap[cnt + 2];
            double Y, U, V;
            RGB_YUV(R, G, B, &Y, &U, &V);
            // 调整亮度
            Y = Y * 0.5;
            Adjust(&Y);//防止Y越界
            // 将调整后的YUV值转换回RGB颜色空间
            YUV_RGB(Y, U, V, &R, &G, &B);
            //防止RGB越界
            Adjust(&R);
            Adjust(&G);
            Adjust(&B);
            // 更新图像像素的RGB值
            bmp.bitmap[cnt] = (byte)B;
            bmp.bitmap[cnt + 1] = (byte)G;
            bmp.bitmap[cnt + 2] = (byte)R;
    }
 }
    // 打开文件并将调整后的BMP数据写入文件
    FILE* fp = fopen("brightness.bmp", "wb");
    fwrite(&(bmp), HEADERSIZE, 1, fp); // 写入文件头
    fwrite(bmp.bitmap, bmp.bmpih.imageSize, 1, fp); // 写入位图数据
    fclose(fp); // 关闭文件
}

void Adjust(double* x){
    if(*x>=0){
        if(*x>255.0){*x=255.0;}
    }
    else{*x = 0.0;}
}
double Adjust2(double x){
    if(x>=0){
        if(x>255.0){x=255.0;}
    }
    else{x = 0.0;}
    return x;
}

void OUTPUT (BMP *bmp, FILE *fp)
{
    if(!fp) {
        printf("NO OUTPUT FIILE ! ");
        exit(0); 
    }
    fwrite(&(bmp->bmph), HEADERSIZE, 1, fp); // 写入文件头
    if(bmp->bmpih.bitCount == 8) // 如果是灰度图，那需要输出调色板
    fwrite(bmp->colours, 4 * 256, 1, fp); // 写入颜色调色板数据
    fwrite(bmp->bitmap, bmp->bmpih.imageSize, 1, fp); // 写入图像数据
    fclose(fp); // 关闭文件。
}