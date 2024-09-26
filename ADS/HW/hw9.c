#include<stdio.h>
#include<stdlib.h>
typedef struct addoil{
    float price;
    float distance;
}addoil;
int cmp(const void *a, const void *b) {
    addoil *ptr_a = (addoil *)a;
    addoil *ptr_b = (addoil *)b;
    if (ptr_a->distance < ptr_b->distance) return -1;
    else if (ptr_a->distance == ptr_b->distance) return 0;
    else return 1;
}

int main(){
    float capacity,distance,consume;
    int num;
    scanf("%f %f %f %d",&capacity,&distance,&consume,&num);
    addoil station[num+1];
    for(int i=0;i<num;i++){
        float price;
        float dist;
        scanf("%f %f",&price,&dist);
        station[i].price = price;
        station[i].distance = dist;
    }
    qsort(station,num,sizeof(addoil),cmp);
    station[num].distance = distance;
    station[num].price = 0;
    float sum = 0;
    if(station[0].distance>0){
        printf("The maximum travel distance = 0.00");
    }
    else{
        int currentNumber = 0;
        float currentPri = station[0].price;
        float currentDist = 0;
        float currentOil = 0;
        float max = consume * capacity;
        while(currentDist<distance){
            if(currentOil*consume >= distance - currentDist){
                break;
            }
            if(capacity*consume < station[currentNumber+1].distance - currentDist){
                printf("The maximum travel distance = %.2f",currentDist + capacity*consume);
                return 0;
            }
            int i = currentNumber+1;
            int flag = 0;
            while(station[i].distance - currentDist <= max){
                if(station[i].price < currentPri){
                    flag = 1;
                    break;
                }
                i++;
            }
            if(flag == 1){
                // add oil to reach the next station.
                int travel = station[i].distance - currentDist;
                if(travel > currentOil*consume){
                    sum += ((travel - currentOil*consume)/consume)*currentPri;
                    currentOil = 0;
                }
                else{
                    currentOil = currentOil - travel/consume;
                }
                currentDist = station[i].distance;
                currentPri = station[i].price;
                currentNumber = i;
            }
            else{
                sum += (capacity - currentOil)*currentPri;
                currentNumber++;
                currentPri = station[currentNumber].price;
                currentDist = station[currentNumber].distance;
                currentOil = (float)capacity - (station[currentNumber].distance-station[currentNumber-1].distance)/(float)consume;
                
            }
        }
    }
    printf("%.2f",sum);
    return 0;
}