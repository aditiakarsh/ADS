#include<iostream>
#include<cstdlib>
using namespace std;

void makeset(int arr[],int n){
    for(int i=0;i<n;i++){
        arr[i]=i;
    }
}

int find(int x,int arr[]){
    if(arr[x]==x){
        return x;
    }
    return find(arr[x],arr);
}

void union1(int x1,int x2,int arr[]){
    int temp1=find(x1,arr);
    int temp2=find(x2,arr);
    if(temp1==temp2){
        return;
    }
    else{
        arr[temp1]=temp2;
    }
}

int main(){
    int s;
    cout<<"Enter the size of the maze";
    cin>>s;
    int n=s*s;
    int dis_set[n];
    makeset(dis_set,n);
    while(find(dis_set[0],dis_set)!=find(dis_set[n-1],dis_set)){
        int rand1=rand()%n;
        int rand2=rand()%n;
        int row1=rand1/s;
        int row2=rand2/s;
        int col1=rand1%s;
        int col2=rand2%s;
        if((row1==row2 && (rand1+1==rand2 || rand1-1==rand2)) || (col1==col2 && (rand1+s==rand2 || rand1-s==rand2))){
            union1(rand1,rand2,dis_set);
            cout<<rand1<<"   -   "<<rand2<<"\n";
        }
    }
    cout<<"\n\n---";
    for(int i=0;i<n;i++){
        cout<<dis_set[i]<<"//";
    }
}
