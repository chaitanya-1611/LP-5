#include<iostream>
#include<omp.h>
#include<stdlib.h>

using namespace std;

void bubble(int *arr,int n){
    for(int i=0;i<n;i++){
        int first = i%2;

        #pragma omp parallel for shared(arr,first)
        for(int j=first;j<n-1;j+=2){
            if(arr[j]>arr[j+1]){
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int main(){
    int n;
    cout<<"Enter the number of elements: ";
    cin>>n;
    int *arr = new int[n];
    cout<<"Enter the elements: ";
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    bubble(arr,n);
    cout<<"Sorted array: ";
    for(int i=0;i<n;i++){
        cout<<arr[i]<<" ";
    }
    return 0;
}