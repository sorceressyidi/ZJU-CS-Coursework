#include<stdio.h>
#include "DIP.h"
#include<math.h>
void translate(BMP bmp,int x,int y);
void rot(BMP bmp,double angle);
void rotate(int *x,int *y,double cost,double sint);
void scale(double x,double y,BMP bmp);
void affine(double dx,double dy,BMP bmp);
void mirror(int axis,BMP bmp);
int main(){
    BMP bmp = ReadBMP();  
    BMP gray = Gray_Transform(bmp,bmp.bmpih.height,bmp.bmpih.width);
    //translate
    int x,y;
    printf("What's the translation on the x axis?");
    scanf("%d",&x);
    printf("What's the translation on the y axis?");
    scanf("%d",&y);
    translate(bmp,x,y);
    //translate(gray,x,y);

    //rotate
    double theta;
    printf("What's the rotation angle?");
    scanf("%lf",&theta);
    rot(bmp,theta);
    //rot(gray,theta);
    
    //scale
    double x1,y1;
    printf("What's the scale on the x axis?");
    scanf("%lf",&x1);
    printf("What's the scale on the y axis?");
    scanf("%lf",&y1);
    scale(x1,y1,bmp);
    //scale(x1,y1,gray);

    //Affine
    printf("What's affine dx on the x axis?");
    scanf("%lf",&x1);
    printf("What's the affine dy on the y axis?");
    scanf("%lf",&y1);
    affine(x1,y1,bmp);
    //affine(x1,y1,gray);

    //Mirrow
    int axis;
    printf("What's the mirrow axis?(1 for x and 0 for y)");
    scanf("%d",&axis);
    mirror(axis,bmp);
    //mirror(axis,gray);
    return 0;
}
void translate(BMP bmp,int x,int y){
    BMP translate ;
    memcpy(&translate,&bmp,sizeof(translate));
    int width = translate.bmpih.width;
    int height = translate.bmpih.height;

    int width1 = width + abs(x);
    int height1 = height +abs(y);

    int row_byte1 = (translate.bmpih.bitCount/8*width1+3)/4*4;
    int row_byte = (translate.bmpih.bitCount/8*width+3)/4*4;

    translate.bmpih.height=height1;
    translate.bmpih.width=width1;

    translate.bmpih.imageSize = height1*row_byte1;
    translate.bmph.bfSize=translate.bmph.bfOffset + translate.bmpih.imageSize;
    translate.bitmap=(byte*)calloc(translate.bmpih.imageSize,sizeof(byte));
    for(int i=0;i<translate.bmpih.imageSize;i++){
        translate.bitmap[i]=255;
    }
    if(translate.bmpih.bitCount==8){
        for(int i=0;i<height;i++){
            for(int j=0;j<width;j++){
                int posi = i*row_byte + j;
                int i1,j1;
                if(y<=0){i1=i;}
                else{i1=i+y;}
                if(x>=0){j1=j+x;}
                else{j1=j;}
                int posi1 = i1*row_byte1 + j1;
                translate.bitmap[posi1]=bmp.bitmap[posi];

            }
        }
    }
    else{
        for(int i=0;i<height;i++){
            for(int j=0;j<width;j++){

                int posi = i*row_byte+j*3;

                int i1,j1;
                if(y<=0){i1=i;}
                else{i1=i+y;}
                if(x>=0){j1=j+x;}
                else{j1=j;}
                int posi1 = i1*row_byte1 + j1*3;
                translate.bitmap[posi1]=bmp.bitmap[posi];
                translate.bitmap[posi1+1]=bmp.bitmap[posi+1];
                translate.bitmap[posi1+2]=bmp.bitmap[posi+2];
            }
        }
    }
    FILE *fp = fopen("translate.bmp","wb");
    OUTPUT(&translate,fp);
    free(translate.bitmap);
}
void rotate(int *x,int *y,double cost,double sint){
    double tmp1= *x;
    double tmp2 =*y;
    *x = (tmp1*cost)-(tmp2*sint);
    *y = (tmp1*sint)+(tmp2*cost);
}
void rot(BMP bmp,double angle){
    BMP rot ;
    memcpy(&rot,&bmp,sizeof(rot));
    int width = rot.bmpih.width;
    int height = rot.bmpih.height;
    angle = angle * M_PI/180.0;

    double cos_a = cos(angle);
    double sin_a = sin(angle);

    int width1 = width*fabs(cos_a) + height * fabs(sin_a);
    int height1 = width*fabs(sin_a)+ width*fabs(cos_a);
    int cx=width/2;
    int cy=height/2;
    rotate(&cx,&cy,cos_a,sin_a);

    int row_byte1=(rot.bmpih.bitCount/8*width1+3)/4*4;
    int row_byte = (rot.bmpih.bitCount/8*width+3)/4*4;

    rot.bmpih.height=height1;
    rot.bmpih.width=width1;
    rot.bmpih.imageSize = height1 * row_byte1;
    rot.bmph.bfSize=rot.bmph.bfOffset+rot.bmpih.imageSize;
    rot.bitmap=(byte*)calloc(rot.bmpih.imageSize,sizeof(byte));
    //在逆推原坐标点的过程中，需要考虑平移问题，因为变换了参考系.
    double x = (double)(width1 /2)- cx;
    double y = (double)(height1 /2) -cy;
    if(rot.bmpih.bitCount==8){
        for(int i=0;i<height1;i++){
            for(int j=0;j<width1;j++){
                int posi1 = i*row_byte1 +j;
                double x1 = j - x;
                double y1 = i - y;
                int x2 = round((x1*cos_a)+(y1*sin_a));
                int y2 = round(-(x1*sin_a)+(y1*cos_a));
                int posi = y2*row_byte + x2;
                if(x2<0||y2<0||x2>=width||y2>=height){
                    rot.bitmap[posi1]=255;
                    continue;
                }
                rot.bitmap[posi1]=bmp.bitmap[posi];
            }
        }
    }
    else{
        for(int i=0;i<height1;i++){
            for(int j=0;j<width1;j++){
                int posi1 = i*row_byte1 +j*3;
                double x1 = j - x;
                double y1 = i - y;
                int x2 = round((x1*cos_a)+(y1*sin_a));
                int y2 = round(-(x1*sin_a)+(y1*cos_a));
                int posi = y2*row_byte + x2*3;
                if(x2<0||y2<0||x2>=width||y2>=height){
                    rot.bitmap[posi1]=255;
                    rot.bitmap[posi1+1]=255;
                    rot.bitmap[posi1+2]=255;
                    continue;
                }
                rot.bitmap[posi1]=bmp.bitmap[posi];
                rot.bitmap[posi1+1]=bmp.bitmap[posi+1];
                rot.bitmap[posi1+2]=bmp.bitmap[posi+2];


            }
        }
    }
    FILE* fp = fopen("rotate.bmp","wb");
    OUTPUT(&rot,fp);
    free(rot.bitmap);
}
void scale(double x,double y,BMP bmp){
    BMP scale;
    memcpy(&scale,&bmp,sizeof(scale));

    int width = scale.bmpih.width;
    int height = scale.bmpih.height;
    int width1 =round(width*x);
    int height1 = round(height*y);
    int row_byte = (bmp.bmpih.bitCount/8*width+3)/4*4;
    int row_byte1 = (bmp.bmpih.bitCount/8*width1+3)/4*4;

    scale.bmpih.width=width1;
    scale.bmpih.height=height1;

    scale.bitmap=(byte*)malloc(row_byte1*height1*sizeof(byte));
    scale.bmpih.imageSize=height1*row_byte1;
    scale.bmph.bfSize=scale.bmph.bfOffset+scale.bmpih.imageSize;

    if(scale.bmpih.bitCount==24){
        for(int i=0;i<height1;i++){
            for(int j=0;j<width1;j++){
                int posi = i*row_byte1+j*3;
                int posi1 = round(i/y)*row_byte+round(j/x)*3;

                scale.bitmap[posi]=bmp.bitmap[posi1];
                scale.bitmap[posi+1]=bmp.bitmap[posi1+1];
                scale.bitmap[posi+2]=bmp.bitmap[posi1+2];
            }
        }
    }
    else{
        for(int i=0;i<height1;i++){
            for(int j=0;j<width1;j++){
                int posi = i*row_byte1+j;
                int posi1 = round(i/y)*row_byte+round(j/x);
                scale.bitmap[posi]=bmp.bitmap[posi1];
            }
        }
    }
    FILE* fp = fopen("scale.bmp","wb");
    OUTPUT(&scale,fp);
    free(scale.bitmap);
}
void affine(double dx,double dy,BMP bmp){

    BMP affine;
    memcpy(&affine,&bmp,sizeof(affine));

    int width = affine.bmpih.width;
    int height = affine.bmpih.height;
    //dx = dx/width;
    //dy= dy/height;
    int width1 =round(width+dx*height);
    int height1 = round(height+dy*width);
    int row_byte = (bmp.bmpih.bitCount/8*width+3)/4*4;
    int row_byte1 = (bmp.bmpih.bitCount/8*width1+3)/4*4;

    affine.bmpih.width=width1;
    affine.bmpih.height=height1;

    affine.bitmap=(byte*)malloc(row_byte1*height1*sizeof(byte));
    affine.bmpih.imageSize=height1*row_byte1;
    affine.bmph.bfSize=affine.bmph.bfOffset+affine.bmpih.imageSize;

    if(affine.bmpih.bitCount==24){
        for(int i=0;i<height1;i++){
            for(int j=0;j<width1;j++){
                int posi = i*row_byte1+j*3;
                int x1 = round((j-dx*(i))/(1-dx*dy)); //should not use (height1 - i)because the image itself is upside down!
                int y1 = round((i-dy*j)/(1-dx*dy));
                if(x1<0||y1<0||x1>=width||y1>=height){

                    affine.bitmap[posi]=255;
                    affine.bitmap[posi+1]=255;
                    affine.bitmap[posi+2]=255;
                    continue;
                }

                int posi1 = y1*row_byte+x1*3;
                affine.bitmap[posi]=bmp.bitmap[posi1];
                affine.bitmap[posi+1]=bmp.bitmap[posi1+1];
                affine.bitmap[posi+2]=bmp.bitmap[posi1+2];
            }
        }
    }
    else{
        for(int i=0;i<height1;i++){
            for(int j=0;j<width1;j++){
                int posi = i*row_byte1+j;
                int x1 = round((j-dx*(i))/(1-dx*dy)); //should not use (height1 - i)because the image itself is upside down!
                int y1 = round((i-dy*j)/(1-dx*dy));
                if(x1<0||y1<0||x1>=width||y1>=height){
                    affine.bitmap[posi]=255;
                    continue;
                }
                int posi1 = y1*row_byte+x1;
                affine.bitmap[posi]=bmp.bitmap[posi1];
            }
        }     
    }
    FILE* fp = fopen("affine.bmp","wb");
    OUTPUT(&affine,fp);
    free(affine.bitmap);
}
void mirror(int axis,BMP bmp){
    BMP mirror;
    memcpy(&mirror,&bmp,sizeof(mirror));
    int height= bmp.bmpih.height;
    int width = bmp.bmpih.width;
    int row_byte = (bmp.bmpih.bitCount/8*width+3)/4*4;
    mirror.bitmap = (byte*)calloc(mirror.bmpih.imageSize,sizeof(byte));

    if(mirror.bmpih.bitCount==24){
        for(int i=0;i<height;i++){
            for(int j=0;j<width;j++){
                int posi = i*row_byte+j*3;
                int posi1;
                if(axis){posi1=i*row_byte+(width-j)*3;}
                else{posi1=(height-i)*row_byte+j*3;}
                mirror.bitmap[posi]=bmp.bitmap[posi1];
                mirror.bitmap[posi+1]=bmp.bitmap[posi1+1];
                mirror.bitmap[posi+2]=bmp.bitmap[posi1+2];
            }
        }
    }
    else{
        for(int i=0;i<height;i++){
            for(int j=0;j<width;j++){
                int posi = i*row_byte+j;
                int posi1;
                if(axis){posi1=i*row_byte+(width-j);}
                else{posi1=(height-i)*row_byte+j;}
                mirror.bitmap[posi]=bmp.bitmap[posi1];
            }
        }
    }
    FILE* fp = fopen("mirror.bmp","wb");
    OUTPUT(&mirror,fp);
    free(mirror.bitmap);
}
