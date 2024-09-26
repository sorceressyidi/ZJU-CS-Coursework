#include<stdio.h>
int main(){
    int num,length;
    printf("HLLLL");
    scanf("%d %d",&num,&length);
    int bas[num];
    for (int i=0;i<num;i++){
        scanf("%d",&bas[i]);
    }
    int position = bas[0] - length;
    int maxnum = 1;
    int lef = 0, rig = 0, cnt = 1;
    while (rig < num - 1) {
        while (bas[rig] - bas[lef] <= length) {
            rig++;
            if (rig == num) {
                break;
            }
            cnt++;
        }
        rig--;
        cnt--;
        if (cnt > maxnum) {
            maxnum = cnt;
            position = bas[rig] - length;
        } 
        else if (cnt == maxnum) {
            if ((bas[rig]-length) <position){
                position = bas[rig]-length;
            }
        }
        lef++;
        cnt--;
    }
    printf("%d %d\n", position, maxnum);
    return 0;
}
