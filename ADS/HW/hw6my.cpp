#include<iostream>
#include<vector>
#include<math.h>
using namespace std;
vector<int>input;
vector<int>wolves;

int check(int N,int L){
    vector<int>liers;
    vector<int>identities(N+1,1);
    for(int i=0;i<wolves.size();i++){
        identities[wolves[i]]=-1;
    }
    //set the identities
    for(int i=1;i<=N;i++){
        int identity=identities[i]*i;
        identities[i]=identity;
    }
    //search the liers
    int wolve_liers=0;
    for(int i=0;i<N;i++){
        int claim = input[i];
        int identity = identities[abs(claim)];
        if(claim!=identity){
            liers.push_back(i+1);
            if(identities[i+1]<0){
                wolve_liers++;
            }
        }
        if(wolve_liers>wolves.size()){return 0;}
        if(liers.size()>L){return 0;}

    }
    if(liers.size()==L){
        /*int wolve_liers=0;
        for(int i=0;i<liers.size();i++){
            if(identities[liers[i]]<0){
                wolve_liers++;
            }
        }*/
        if(wolve_liers>0 && wolve_liers<wolves.size()){
            return 1;
        }
    }

    return 0;

    
}

int BT(int N,int M,int L,int last){
    if(wolves.size()==M){
        if(check(N,L)){return 1;}
        else{return 0;}
    }
    else{
        while(last){
            wolves.push_back(last);
            last--;
            if(BT(N,M,L,last)){return 1;}
            else{wolves.pop_back();}
        }
    }
    return 0;
}

int main(){
    int M,N,L;
    cin>>N>>M>>L;
    for(int i=0;i<N;i++){
        int temp;
        cin>>temp;
        input.push_back(temp);
    }
    if(BT(N,M,L,N)){
      vector<int>::iterator it;
      for(it=wolves.begin();it!=wolves.end();it++){
            cout<<*it<<" ";
       }
       cout<<endl;
    }
    else{cout<<"No Solution"<<endl;}
}
