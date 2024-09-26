#include<stdio.h>
#include"DIP.h"

// 函数声明
void filtermean(BMP bmp, int size);
void Lap1(BMP bmp);
void Lap2(BMP bmp);

int main() {
    // 读取 BMP 图像
    BMP bmp = ReadBMP();
    // 转换为灰度图像
    BMP gray = Gray_Transform(bmp, bmp.bmpih.height, bmp.bmpih.width);
    int size;
    printf("请输入滤波窗口的大小:");
    scanf("%d", &size);
    // 对原图进行均值滤波
    filtermean(bmp, size);
    // 对灰度图进行均值滤波
    //filtermean(gray, size);


    // 对原图进行 Laplacian 锐化
    Lap1(bmp);
    // 对灰度图进行 Laplacian 锐化
    // Lap1(gray);


    // 对原图进行 Laplacian 锐化
    Lap2(bmp);
    // 对灰度图进行 Laplacian 锐化
    // Lap2(gray);
    return 0;
}

// 均值滤波函数
void filtermean(BMP bmp, int size) {
    BMP mean;
    // 复制 bmp 到 mean
    memcpy(&mean, &bmp, sizeof(mean));
    int width = mean.bmpih.width;
    int height = mean.bmpih.height;
    int rowbyte = (mean.bmpih.bitCount / 8 * width + 3) / 4 * 4;
    mean.bitmap = (byte *)calloc(mean.bmpih.imageSize, sizeof(byte));
    int s = size / 2;
    if (mean.bmpih.bitCount == 24) {
        // 如果每像素位数为24（真彩色图像）
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                double R = 0;
                double G = 0;
                double B = 0;
                int cnt = 0;
                for (int q = i - s; q <= i + s; q++) {
                    for (int p = j - s; p <= j + s; p++) {
                        if (q >= 0 && p >= 0 && q < height && p < width) {
                            int posi1 = q * rowbyte + p * 3;
                            B += bmp.bitmap[posi1];
                            G += bmp.bitmap[posi1 + 1];
                            R += bmp.bitmap[posi1 + 2];
                            cnt++;
                        }
                    }
                }
                B /= cnt;
                G /= cnt;
                R /= cnt;
                int posi = i * rowbyte + j * 3;
                mean.bitmap[posi] = B;
                mean.bitmap[posi + 1] = G;
                mean.bitmap[posi + 2] = R;
            }
        }
    } else {
        // 如果每像素位数为8
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                double P = 0;
                int cnt = 0;
                for (int q = i - s; q <= i + s; q++) {
                    for (int p = j - s; p <= j + s; p++) {
                        if (q >= 0 && p >= 0 && q < height && p < width) {
                            int posi1 = q * rowbyte + p;
                            P += bmp.bitmap[posi1];
                            cnt++;
                        }
                    }
                }
                P /= cnt;
                int posi = i * rowbyte + j;
                mean.bitmap[posi] = P;
            }
        }
    }
    // 保存均值滤波后的图像
    FILE *fp = fopen("mean.bmp", "wb");
    OUTPUT(&mean, fp);
    free(mean.bitmap);
}

// Laplacian 锐化函数1
void Lap1(BMP bmp) {
    BMP lap1;
    BMP g;
    // 复制 bmp 到 lap1 和 g
    memcpy(&g, &bmp, sizeof(lap1));
    memcpy(&lap1, &bmp, sizeof(lap1));
    int width = lap1.bmpih.width;
    int height = lap1.bmpih.height;
    int rowbyte = (lap1.bmpih.bitCount / 8 * width + 3) / 4 * 4;
    lap1.bitmap = (byte *)calloc(lap1.bmpih.imageSize, sizeof(byte));
    g.bitmap = (byte *)calloc(g.bmpih.imageSize, sizeof(byte));
    if (lap1.bmpih.bitCount == 24) {
        // 如果每像素位数为24（真彩色图像）
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                double R = 0;
                double G = 0;
                double B = 0;
                int cnt = 0;
                for (int q = i - 1; q <= i + 1; q++) {
                    for (int p = j - 1; p <= j + 1; p++) {
                        if (q >= 0 && p >= 0 && q < height && p < width) {
                            int posi1 = q * rowbyte + p * 3;
                            B += bmp.bitmap[posi1];
                            G += bmp.bitmap[posi1 + 1];
                            R += bmp.bitmap[posi1 + 2];
                            cnt++;
                        }
                    }
                }
                int posi = i * rowbyte + j * 3;
                double B1 = bmp.bitmap[posi];
                double G1 = bmp.bitmap[posi + 1];
                double R1 = bmp.bitmap[posi + 2];
                B -= B1 * cnt;
                G -= G1 * cnt;
                R -= R1 * cnt;
                lap1.bitmap[posi] = B;
                lap1.bitmap[posi + 1] = G;
                lap1.bitmap[posi + 2] = R;
                g.bitmap[posi] = Adjust2(B1 - B);
                g.bitmap[posi + 1] = Adjust2(G1 - G);
                g.bitmap[posi + 2] = Adjust2(R1 - R);
            }
        }
    } else {
        // 如果每像素位数为8
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                double P = 0;
                int cnt = 0;
                for (int q = i - 1; q <= i + 1; q++) {
                    for (int p = j - 1; q <= j + 1; p++) {
                        if (q >= 0 && p >= 0 && q < height && p < width) {
                            int posi1 = q * rowbyte + p;
                            P += bmp.bitmap[posi1];
                            cnt++;
                        }
                    }
                }
                int posi = i * rowbyte + j;
                double P1 = bmp.bitmap[posi];
                P -= P1 * cnt;
                lap1.bitmap[posi] = P;
                g.bitmap[posi] = Adjust2(P1 - P);
            }
        }
    }
    // 保存 Laplacian 锐化后的图像
    FILE *fp = fopen("lap1.bmp", "wb");
    OUTPUT(&lap1, fp);
    free(lap1.bitmap);
    // 保存 Sharpened 后的图像
    fp = fopen("sharpen1.bmp", "wb");
    OUTPUT(&g, fp);
    free(g.bitmap);
}

// Laplacian 锐化函数2
void Lap2(BMP bmp) {
    BMP lap2;
    BMP g;
    // 复制 bmp 到 lap2 和 g
    memcpy(&g, &bmp, sizeof(lap2));
    memcpy(&lap2, &bmp, sizeof(lap2));
    int width = lap2.bmpih.width;
    int height = lap2.bmpih.height;
    int rowbyte = (lap2.bmpih.bitCount / 8 * width + 3) / 4 * 4;
    lap2.bitmap = (byte *)calloc(lap2.bmpih.imageSize, sizeof(byte));
    g.bitmap = (byte *)calloc(g.bmpih.imageSize, sizeof(byte));
    int dx[5] = {-1, 0, 0, 0, 1};
    int dy[5] = {0, 1, 0, 1, 0};
    if (lap2.bmpih.bitCount == 24) {
        // 如果每像素位数为24（真彩色图像）
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                double R = 0;
                double G = 0;
                double B = 0;
                int cnt = 0;
                for (int q = 0; q < 4; q++) {
                    if (i + dx[q] >= 0 && j + dy[q] >= 0 && i + dx[q] < height && j + dy[q] < width) {
                        int posi1 = (i + dx[q]) * rowbyte + (j + dy[q]) * 3;
                        B += bmp.bitmap[posi1];
                        G += bmp.bitmap[posi1 + 1];
                        R += bmp.bitmap[posi1 + 2];
                        cnt++;
                    }
                }
                int posi = i * rowbyte + j * 3;
                double B1 = bmp.bitmap[posi];
                double G1 = bmp.bitmap[posi + 1];
                double R1 = bmp.bitmap[posi + 2];
                B = B1 * (cnt)-B;
                G = G1 * cnt - G;
                R = R1 * cnt - R;
                lap2.bitmap[posi] = B;
                lap2.bitmap[posi + 1] = G;
                lap2.bitmap[posi + 2] = R;
                g.bitmap[posi] = Adjust2(B1 + B);
                g.bitmap[posi + 1] = Adjust2(G1 + G);
                g.bitmap[posi + 2] = Adjust2(R1 + R);
            }
        }
    } else {
        // 如果每像素位数为8
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                double P = 0;
                int cnt = 0;
                for (int q = 0; q < 4; q++) {
                    if (i + dx[q] >= 0 && j + dy[q] >= 0 && i + dx[q] < height && j + dy[q] < width) {
                        int posi1 = (i + dx[q]) * rowbyte + (j + dy[q]);
                        P += bmp.bitmap[posi1];
                        cnt++;
                    }
                }
                int posi = i * rowbyte + j;
                double P1 = bmp.bitmap[posi];
                P = P1 * cnt - P;
                lap2.bitmap[posi] = P;
                g.bitmap[posi] = Adjust2(P1 + P);
            }
        }
    }
    // 保存 Laplacian 锐化后的图像
    FILE *fp = fopen("lap2.bmp", "wb");
    OUTPUT(&lap2, fp);
    free(lap2.bitmap);
    // 保存 Sharpened 后的图像
    fp = fopen("sharpen2.bmp", "wb");
    OUTPUT(&g, fp);
    free(g.bitmap);
}
