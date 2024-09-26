#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <ctime>
#include <fstream>

using namespace std;

int n;  //number of rectangles
int W;  //the given width of the bin


typedef pair<int, int> rectangle;
typedef vector<rectangle>::iterator it_r;
bool cmp(const rectangle &a, const rectangle &b) {
    return a.second > b.second;
}
int NF(vector<rectangle> &rectangles){
    int h_level = 0; //the height of the current level
    int width_left = W; //the width left of the current level
    int sum_h = 0; //the sum of the height

    for (it_r r=rectangles.begin();r!=rectangles.end();r++){
        if(r->first<=width_left){
            width_left -= r->first; //update the width left of the level
            if(r->second>h_level){ 
                h_level = r->second; //update the height of the level
            }
        }
        else{
            sum_h += h_level;   //add the height of the level to the sum
            width_left = W - r->first; //open a new level
            h_level = r->second; //update the height of the level
        }
    }
    sum_h += h_level;
    return sum_h;

}

int FF(vector<rectangle> &rectangles){
    vector<int> h_level;
    vector<int> w_level;
    int cnt=0;    //the number of levels
    int sum_h=0;  //the sum of the height 
    int h_now=0;  //the height of the level now
    int w_left_now=W;   //the width left of the level now
    int fit=0;   //whether the rectangle can be put in the old level
    for (it_r r=rectangles.begin();r!=rectangles.end();r++){
        fit=0;
        int width=r->first;
        int height=r->second;
        int w_left_min=W;
        //search for the old levels and find a level to put the rectangle
        for(int i=0;i<cnt;i++){
            if(width<=w_level[i]&&height<=h_level[i]){
                fit = 1;
                w_level[i]-=width;
                break;
            }
        }
        if(fit != 1){
            //put the rectangle in the now level
            if(width<=w_left_now){
                w_left_now-=width;
                if(height>h_now){
                    h_now=height;
                }
            }
            //open a new level
            else{
                sum_h+=h_now;
                w_level.push_back(w_left_now);
                h_level.push_back(h_now);
                w_left_now=W-width;
                h_now=height;
                cnt++;
            } 
        }
    }
    //add the height of the last level
    sum_h+=h_now;
    return sum_h;
}

int BWF(vector<rectangle> &rectangles){
    vector<int> h_level;
    vector<int> w_level;
    int cnt=0;    //the number of levels
    int sum_h=0;  //the sum of the height 
    int h_now=0;  //the height of the level now
    int w_left_now=W;   //the width left of the level now
    int fit=0;   //whether the rectangle can be put in the old level
    for (it_r r=rectangles.begin();r!=rectangles.end();r++){
        fit=0;
        int width=r->first;
        int height=r->second;
        int w_left_min=W;
        int min_index=-1;
        //search for the old levels and find the best level to put the rectangle
        for(int i=0;i<cnt;i++){
            if(width<=w_level[i]&&height<=h_level[i]){
                fit=1;
                if(w_level[i]<w_left_min){
                    w_left_min=w_level[i];
                    min_index=i;
                }
            }
        }
        //put the rectangle in the best level
        if(fit==1){
            w_level[min_index]-=width;
        }
        else{
            //put the rectangle in the now level
            if(width<=w_left_now){
                w_left_now-=width;
                if(height>h_now){
                    h_now=height;
                }
            }
            //open a new level
            else{
                sum_h+=h_now;
                
                w_level.push_back(w_left_now);
                h_level.push_back(h_now);
                w_left_now=W-width;
                h_now=height;
                cnt++;
            } 
        }
    }
    //add the height of the last level
    sum_h+=h_now;
    return sum_h;
}

void test(char* file_name,int size);

int main(void) {
    
    test("input_10.txt",10);
    test("input_100.txt",100);
    test("input_1000.txt",1000);
    test("input_10000.txt",10000);
    test("input_100000.txt",100000);

    return 0;
}

void test(char* file_name,int size)
{
    clock_t start, finish;
    double FF_Time,BWF_Time,NF_Time;
    int FF_result,BWF_result,NF_result;
    vector<rectangle> rectangles;


    freopen(file_name, "r", stdin);

    // Input
    cin >> W >> n;
    for(int i = 0; i < n; i++) {
        int w, h;
        cin >> w >> h;
        rectangles.push_back(rectangle(w, h));
    }
    sort(rectangles.begin(), rectangles.end(), cmp);

    start=clock();
    FF_result=FF(rectangles);
    finish=clock();
    FF_Time=(double)(finish-start)/CLOCKS_PER_SEC;
    cout << "The minium height of packing "<<size<<" textures using FF algorithm is "<< FF_result<<"." << endl;
    cout <<"This takes "<<finish-start <<" clock,"<<FF_Time<<" ms."<<endl;

    cout<<endl;

    start=clock();
    BWF_result=BWF(rectangles);
    finish=clock();
    BWF_Time=(double)(finish-start)/CLOCKS_PER_SEC;
    cout << "The minium height of packing "<<size<<" textures using BWF algorithm is "<< BWF_result<<"." << endl;
    cout <<"This takes "<<finish-start <<" clock,"<<BWF_Time<<" ms."<<endl;

    cout<<endl;

    start=clock();
    NF_result=NF(rectangles);
    finish=clock();
    NF_Time=(double)(finish-start)/CLOCKS_PER_SEC;
    cout << "The minium height of packing "<<size<<" textures using NF algorithm is "<< NF_result<<"." << endl;
    cout <<"This takes "<<finish-start <<" clock,"<<NF_Time<<" ms."<<endl;
    cout<<"---------------------------------------------------------------------------------------------"<<endl;
    return;
}