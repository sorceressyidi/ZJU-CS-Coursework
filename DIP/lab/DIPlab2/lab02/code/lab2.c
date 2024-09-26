#include<stdio.h>
#include"DIP.h"
#include<stdlib.h>
// 使用#pragma pack(1)指令设置结构体的字节对齐方式为1字节
#pragma pack(1)
void OTSU(BMP* bmp,int row1,int col1,int row2,int col2);
void OTSU_improve(BMP* bmp,BMP* improve,int row1,int col1,int row2,int col2,int x,int y);
void Solve(BMP bmp);
void Solve_imporve(BMP bmp);
void dilation(BMP bmp,BMP* dila);
void erosion(BMP bmp,BMP* ero);
void open(BMP bmp,BMP *ero);
void close(BMP bmp,BMP *dila);

int main(){
    BMP bmp = ReadBMP();
    int width = bmp.bmpih.width; // 获取图像的宽度
    int height = bmp.bmpih.height; // 获取图像的高度
    
    // 转换图像为灰度图像
    BMP gray = Gray_Transform(bmp, height, width);
    Solve(gray);//全局大津法
    
    //腐蚀 & 开操作
    BMP ero;
    memcpy(&ero,&gray,sizeof(ero));
    open(gray,&ero);

    //膨胀 & 闭操作
    BMP dila;
    memcpy(&dila,&gray,sizeof(dila));
    close(gray,&dila);
    free(gray.bitmap);
    
    // 转换图像为灰度图像
    gray = Gray_Transform(bmp, height, width);
    Solve_imporve(gray);//滑动窗口大津法
    free(gray.bitmap);

    free(bmp.bitmap);
    return 0;
}


//函数执行otsu二值化算法，将图像在指定区域进行二值化处理。

void OTSU(BMP* bmp, int row1, int col1, int row2, int col2) {
    int width = bmp->bmpih.width;
    int height = bmp->bmpih.height;
    int MAX = 0, MIN = 255;

    // 计算每行（带填充）中的字节数。
    int row_byte = (width + 3) / 4 * 4;

    // 寻找指定区域内的最大和最小像素值。
    for (int i = row1; i < height && i < row2; i++) {
        for (int j = col1; j < width && j < col2; j++) {
            int k = row_byte * i + j;
            byte temp = bmp->bitmap[k];
            if (temp > MAX) {
                MAX = temp;
            }
            if (temp < MIN) {
                MIN = temp;
            }
        }
    }

    // 利用Otsu方法进行二值化。
    double n, nfront, nback, front, back;
    int Threshold;
    double variance = 0.0;
    for (int k = MIN + 1; k <= MAX; k++) {
        n = 0.0;
        nback = 0.0;
        nfront = 0.0;
        back=0.0;
        front=0.0;
        for (int i = row1; i < height && i < row2; i++) {
            for (int j = col1; j < width && j < col2; j++) {
                int q = row_byte * i + j;
                n += 1.0;
                byte temp = bmp->bitmap[q];
                if (temp >= k) {
                    nfront += 1.0;
                    front += temp;
                } else {
                    nback += 1.0;
                    back += temp;
                }
            }
        }
        front /= nfront;
        back /= nback;
        double w = (nfront * nback / n / n )* (back - front) * (back - front);

        if (w > variance) {
            variance = w;
            Threshold = k;
        }
    }

    // 应用计算的阈值对指定区域内的图像进行二值化。
    for (int i = row1; i < height && i < row2; i++) {
        for (int j = col1; j < width && j < col2; j++) {
            int k = i * row_byte + j;
            byte temp = bmp->bitmap[k];
            if (temp > Threshold) {
                bmp->bitmap[k] = 255;
            } else {
                bmp->bitmap[k] = 0;
            }
        }
    }
}


// Solve函数将输入的BMP图像划分为较小的块，对每个块应用OTSU_1函数，然后将处理后的图像保存到文件。
void Solve(BMP bmp) {
    int q;
    printf("How many divisions you'd like?\n");
    scanf("%d",&q);
    int block_size_h = bmp.bmpih.height / q;
    int block_size_w = bmp.bmpih.width / q;
    for (int i = 0; i < bmp.bmpih.height; i += block_size_h) {
        for (int j = 0; j < bmp.bmpih.width; j += block_size_w) {
            OTSU(&bmp, i, j, i + block_size_h, j + block_size_w);
        }
    }
    FILE* fp = fopen("OSTU.bmp", "wb");
    OUTPUT(&bmp,fp);
}

void Solve_imporve(BMP bmp){
    int length ;
    printf("What's the window length?\n");
    scanf("%d",&length);
    BMP improve;
    memcpy(&improve, &bmp, sizeof(improve));
    improve.bitmap = (byte *)calloc(improve.bmpih.imageSize ,sizeof(byte));

    int height = bmp.bmpih.height;
    int width = bmp.bmpih.width;
    
    for (int i = 0; i < height; i ++){
       for (int j = 0; j < width; j ++){
        OTSU_improve(&bmp,&improve,i-length/2, j-length/2, i+length/2, j+length/2, i, j);
        printf("%d %d\n",i,j);
        }
    }

    FILE* fp = fopen("OSTU_IMPROVE.bmp", "wb");
    OUTPUT(&improve,fp);
    free(improve.bitmap);
}

void OTSU_improve(BMP* bmp,BMP* improve,int row1,int col1,int row2,int col2,int x,int y){

    if(row1 < 0){row1 = 0;}
    if(row2 < 0){row2 = 0;}

    int width = bmp->bmpih.width;
    int height = bmp->bmpih.height;
    int MAX = 0, MIN = 255;

    // 计算每行（带填充）中的字节数。
    int row_byte = (width + 3) / 4 * 4;

    // 寻找指定区域内的最大和最小像素值。
    for (int i = row1; i < height && i < row2; i++) {
        for (int j = col1; j < width && j < col2; j++) {
            int k = row_byte * i + j;
            byte temp = bmp->bitmap[k];
            if (temp > MAX) {
                MAX = temp;
            }
            if (temp < MIN) {
                MIN = temp;
            }
        }
    }

    // 利用Otsu方法进行二值化。
    double n, nfront, nback, front, back;
    int Threshold;
    double variance = 0.0;
    for (int k = MIN + 1; k <= MAX; k++) {
        n = 0.0;
        nback = 0.0;
        nfront = 0.0;
        back=0.0;
        front=0.0;
        for (int i = row1; i < height && i < row2; i++) {
            for (int j = col1; j < width && j < col2; j++) {
                int q = row_byte * i + j;
                n += 1.0;
                byte temp = bmp->bitmap[q];
                if (temp >= k) {
                    nfront += 1.0;
                    front += temp;
                } else {
                    nback += 1.0;
                    back += temp;
                }
            }
        }
        front /= nfront;
        back /= nback;
        double w = (nfront * nback / n / n )* (back - front) * (back - front);

        if (w > variance) {
            variance = w;
            Threshold = k;
        }
    }
    int k = row_byte*x+y;
    byte temp = bmp->bitmap[k];
    if (temp >= Threshold){improve->bitmap[k]=255;}
    else{improve->bitmap[k]=0;}  
}

void dilation(BMP bmp, BMP*dila){
    dila->bitmap = (byte *)calloc(dila->bmpih.imageSize ,sizeof(byte));
    int width = bmp.bmpih.width;
    int height = bmp.bmpih.height;
    int row_byte = (width + 3) / 4 * 4;
    int xaxis[9] = {-1,0,1,-1,0,1,-1,0,1};
    int yaxis[9] = {-1,-1,-1,0,0,0,1,1,1};
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            int flag = 0;
            for(int p=0;p<9;p++){
                int x =i+xaxis[p];
                int y =j+yaxis[p];
                if(x>=0&&y>=0&&x<height&&y<width&&bmp.bitmap[x*row_byte+y]==255){
                    dila->bitmap[row_byte*i+j]=255;
                    flag = 0;
                    break;
                }
                if(flag){dila->bitmap[row_byte*i+j]=0;}
            }
        }
    }
}

void erosion(BMP bmp,BMP*ero){
    ero->bitmap = (byte *)calloc(ero->bmpih.imageSize ,sizeof(byte));
    int width = bmp.bmpih.width;
    int height = bmp.bmpih.height;
    int row_byte = (width + 3) / 4 * 4;
    int xaxis[9] = {-1,0,1,-1,0,1,-1,0,1};
    int yaxis[9] = {-1,-1,-1,0,0,0,1,1,1};
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            int flag =1;
            for(int p=0;p<9;p++){
                int x =i+xaxis[p];
                int y =j+yaxis[p];
                if(x>=0&&y>=0&&x<height&&y<width&&bmp.bitmap[x*row_byte+y]==0){
                    ero->bitmap[row_byte*i+j]=0;
                    flag = 0;
                    break;
                }
                if(flag){ero->bitmap[row_byte*i+j]=255;}
            }
        }
    }
}
void open(BMP bmp,BMP * ero)
{
    erosion(bmp, ero);
    FILE *fp = fopen("erosion.bmp","wb");
    OUTPUT(ero,fp);
    BMP open;
    memcpy(&open,ero,sizeof(open));
    dilation(*ero, &open);
    fp = fopen("open.bmp","wb");
    OUTPUT(&open,fp);
    free(ero->bitmap);
    free(open.bitmap);
}
void close(BMP bmp,BMP *dila){
    dilation(bmp, dila);
    FILE *fp = fopen("dilation.bmp","wb");
    OUTPUT(dila,fp);
    BMP close;
    memcpy(&close,dila,sizeof(close));
    erosion(*dila, &close);
    fp = fopen("close.bmp","wb");
    OUTPUT(&close,fp);
    free(close.bitmap);
    free(dila->bitmap);
}