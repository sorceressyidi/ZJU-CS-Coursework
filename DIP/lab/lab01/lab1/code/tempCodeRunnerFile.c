 // 打开名为"input.bmp"的BMP文件以读取二进制数据
    FILE *inputFile = fopen("input.bmp", "rb");
    
    // 检查文件是否成功打开
    if (!inputFile) {
        printf("Unable to open input BMP file.\n"); // 输出错误信息
        return 0; // 退出程序
    }
    
    printf("successfully loaded!"); // 成功加载的提示信息

    BMP bmp; // 创建一个BMP结构体变量用于存储BMP文件的信息和数据

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

    // 转换图像为灰度图像
    Gray_Transform(bmp, height, width);
    //修改亮度
    Brightness_Transform(bmp,height,width);
    free(bmp.bitmap);
    return 0;