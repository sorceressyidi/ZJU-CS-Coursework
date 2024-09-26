
#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include"BAS.h"
clock_t start_time, end_time;
double duration;

int main() {
 
    node root = NULL;
    FILE *file = fopen("test2_10000.txt", "r");
    if (file == NULL){
        printf("无法打开文件\n");
        return 1;
    }
    int N,temp;
    fscanf(file, "%d", &N);

   /*----------------------BST-------------------------------------------*/
    start_time = clock();
    for(int i = 0; i < N; i++){
        fscanf(file, "%d", &temp);
        root = insert_unBST(root, temp);
    }
    
    for(int i = 0; i < N; i++){
        fscanf(file, "%d", &temp);
        root = delete_unBST(root, temp);
    }
    end_time = clock(); 
    fclose(file);
    duration = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("BST 程序运行了 %.6f 秒 \n", duration);

    /*----------------------BST-------------------------------------------*/

    root = NULL;
    file = fopen("test2_10000.txt", "r");
    if (file == NULL){
        printf("无法打开文件\n");
        return 1;
    }
    fscanf(file, "%d", &N);

    /*----------------------splay-------------------------------------------*/
    start_time = clock();
    for(int i = 0; i < N; i++){
        fscanf(file, "%d", &temp);
        root = insert_splay(root, temp);
    }
    
    for(int i = 0; i < N; i++){
        fscanf(file, "%d", &temp);
        root = delete_splay(root, temp);
    }
    end_time = clock(); 
    fclose(file);
    duration = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("splay trees 程序运行了 %.6f 秒 \n", duration);
    /*----------------------splay-------------------------------------------*/


    root = NULL;
    file = fopen("test2_10000.txt", "r");
    if (file == NULL){
        printf("无法打开文件\n");
        return 1;
    }
    fscanf(file, "%d", &N);
    /*----------------------AVL-------------------------------------------*/
    start_time = clock();
    for(int i = 0; i < N; i++){
        fscanf(file, "%d", &temp);
        root = insert_AVL(root, temp);
    }
    
    for(int i = 0; i < N; i++){
        fscanf(file, "%d", &temp);
        root = delete_AVL(root, temp);
    }
    end_time = clock(); 
    fclose(file);

    duration = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("AVL 程序运行了 %.6f 秒 \n", duration);
    /*----------------------AVL-------------------------------------------*/
}
